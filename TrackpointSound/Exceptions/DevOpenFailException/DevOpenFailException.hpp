#pragma once

#include <exception>
#include <string>

class DevOpenFailException : public std::exception
{
public:
    explicit DevOpenFailException(const std::string& message)
        : message_(message) {}

    virtual const char* what() const noexcept override
    {
        return message_.c_str();
    }

private:
    std::string message_;
};
