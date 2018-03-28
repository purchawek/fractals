#ifndef ARG_TYPE_HPP
#define ARG_TYPE_HPP

#include <string>

struct arg_type {
    enum type {t_int, t_double, t_bool, t_string};

    template<typename T>
    static arg_type create() {
        arg_type res;
        if(std::is_same<T, std::string>()) {
            res.type_ = t_string;
        } else if (std::is_same<T, int>()) {
            res.type_ = t_int;
        } else if (std::is_same<T, double>()) {
            res.type_ = t_double;
        } else if (std::is_same<T, bool>()) {
            res.type_ = t_bool;
        };
        return res;
    }

    template<typename T>
    bool is() const {
        return
            (std::is_same<T, std::string>() && type_ == t_string)
            || (std::is_same<T, int>() && type_ == t_int)
            || (std::is_same<T, double>() && type_ == t_double)
            || (std::is_same<T, bool>() && type_ == t_bool);
    }
private:
    type type_;
};

#endif
