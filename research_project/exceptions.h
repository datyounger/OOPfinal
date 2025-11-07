#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <exception>
#include <string>

class DuplicateIDException : public std::exception {
private:
    std::string message;
public:
    DuplicateIDException(const std::string& id) {
        message = "Duplicate ID found: " + id;
    }
    const char* what() const noexcept override {
        return message.c_str();
    }
};

class InvalidYearException : public std::exception {
private:
    int year;
public:
    InvalidYearException(int y) : year(y) {}
    const char* what() const noexcept override {
        return "Invalid year (must be between 2000 and 2025)";
    }
};

class InvalidValueException : public std::exception {
private:
    std::string message;
public:
    InvalidValueException(const std::string& field) {
        message = "Invalid value for field: " + field + " (must be positive)";
    }
    const char* what() const noexcept override {
        return message.c_str();
    }
};

#endif