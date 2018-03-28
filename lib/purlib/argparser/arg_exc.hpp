#ifndef ARG_EXC_HPP
#define ARG_EXC_HPP

#include <exception>
#include <string>

namespace pur {
class argparser_invalid_name_exc : public std::exception {
    std::string what_;

public:
    argparser_invalid_name_exc(const std::string&& msg)
        : what_ {std::move(msg)} {}

    virtual const char* what() const throw() override {
        return what_.c_str();
    }
};

class argparser_invalid_type_exc : public std::exception {
    std::string what_;

public:
    argparser_invalid_type_exc(const std::string&& msg)
        : what_ {std::move(msg)} {}

    virtual const char* what() const throw() override {
        return what_.c_str();
    }
};

}


#endif

