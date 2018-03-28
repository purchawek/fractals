#ifndef ARG_SETUP_HPP
#define ARG_SETUP_HPP

#include <iostream>
#include <algorithm>
#include <memory>
#include <vector>
#include <set>

#include "arg_type.hpp"
#include "arg_exc.hpp"

namespace pur {

using namespace std::string_literals;

struct arg_base {
    virtual ~arg_base() {}

    virtual const std::string& get_name() const = 0;
    virtual const arg_type& get_type() const = 0;
    virtual bool needs_value() const = 0;
    virtual bool has_value() const = 0;
    virtual const std::string& get_help() const = 0;
};

template<typename T>
struct arg : arg_base {
    arg(const std::string& name)
        : name_{name},
          type_{arg_type::create<T>()},
          has_value_{false}{}

    arg(const std::string& name, T val)
        : name_{name},
          type_{arg_type::create<T>()},
          val_{val},
          has_value_{true}{}

    arg<T>& set_help(const std::string& help_msg) {
        help_ = help_msg;
        return *this;
    }

    const std::string& get_help() const override {
        return help_;
    }

    const std::string& get_name() const override {
        return name_;
    }

    const arg_type& get_type() const override {
        return type_;
    }

    void set_val(T val) {
        val_ = std::move(val);
        has_value_ = true;
    }

    const T& get_val() const {
        return val_;
    }

    bool needs_value() const override;

    bool has_value() const override {
        return has_value_;
    }

private:
    std::string help_;
    std::string name_;
    arg_type type_;
    T val_;
    bool has_value_;
};

template<typename T>
bool arg<T>::needs_value() const {
    return !std::is_same<T, bool>();
}

/* 
 * Structure holding argument names with their corresponding types
 *
 */
struct arg_parser {
    template<typename T>
    void register_arg(const std::string& name);

    template<typename T>
    void register_arg(const std::string& name, T val) {
        register_arg<T>(name);
        set_val(name, val);
    }

    template<typename T>
    void register_arg(arg<T> arg_);

    template<typename T>
    void set_val(const std::string& name, T val);

    void set_val_by_name(const std::string& name,
                         const std::string& val);

    bool needs_value(const std::string& name) const {
        return get_unique(name)->needs_value();
    }

    bool has_value(const std::string& name) const {
        return get_unique(name)->has_value();
    }

    template<typename T>
    const T& get_val(std::string name) const {
        return extract_ptr<T>(name)->get_val();
    }

    bool parse_program_params(int argc, char** argv);

    void print_help() const;

private:
    std::vector<std::unique_ptr<arg_base>> args_;

    const std::unique_ptr<arg_base>& get_unique(
    const std::string& name) const {
        auto ptr  = std::find_if(args_.begin(), args_.end(),
            [&name](const auto& ptr) {
                return ptr->get_name() == name; });
        if(ptr == args_.end())
            throw argparser_invalid_name_exc{
                "Name "s + name + " was not registered"};
        return *ptr;
    }


    template<typename T>
    arg<T>* const extract_ptr(const std::string& name) const {
        auto& ptr = get_unique(name);

        if(!ptr->get_type().template is<T>())
            throw argparser_invalid_name_exc{
                "Name "s + name + " is accessed with a wrong type"
            };
        auto p = dynamic_cast<arg<T>*>(ptr.get());
        if(p == nullptr) throw;
        return p;
    }
};


template<typename T>
void arg_parser::register_arg(const std::string& name) {
    args_.push_back(std::make_unique<arg<T>>(name));
}

template<typename T>
void arg_parser::register_arg(arg<T> arg_) {
    args_.push_back(std::make_unique<arg<T>>(std::move(arg_)));
}

template<typename T>
void arg_parser::set_val(const std::string& name, T val) {
    extract_ptr<T>(name)->set_val(val);
}

template<>
void arg_parser::register_arg<std::string>(
const std::string& name) {
    args_.push_back(
        std::make_unique<arg<std::string>>(name));
}


void arg_parser::set_val_by_name(
const std::string& name, const std::string& val) {
    auto& ptr = get_unique(name);
    if(ptr->get_type().template is<int>())
        set_val<int>(name, std::stoi(val));
    else if(ptr->get_type(). template is<double>())
        set_val<double>(name, std::stod(val));
    else if(ptr->get_type(). template is<std::string>())
        set_val<std::string>(name, val);
    else if(ptr->get_type(). template is<bool>())
        set_val<bool>(name, true);
    else
        throw;
}

//TODO this shouldn't handle the error here
bool arg_parser::parse_program_params(int argc, char **argv) {
    try {
        for(int i = 1; i < argc; ++i) {
            if(needs_value(argv[i])) {
                set_val_by_name(argv[i], argv[i+1]);
                ++i;
            } else {
                set_val(argv[i], true);
            }
        }
    } catch (const std::exception& e) {
        print_help();
        return false;
    }
    return true;
}


void arg_parser::print_help() const {
    std::cout << "Help: ";
    for(const auto& arg : args_)
        std::cout << "\n\t" << arg->get_name() << "\t" <<  arg->get_help();

    std::cout << std::endl;
}
}


#endif
