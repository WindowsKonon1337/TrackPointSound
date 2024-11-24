#pragma once

#include <exception>
#include <string>

class EmptyAudioFolderException : public std::exception
{
public:
    explicit EmptyAudioFolderException(const std::string& message)
        : message_(message) {}

    virtual const char* what() const noexcept override
    {
        return message_.c_str();
    }

private:
    std::string message_;
};
