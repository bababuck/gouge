/**
 * @file  exceptions.hpp
 */

#ifndef EXCEPTIONS_HPP
#define EXCEPTIONS_HPP

#include <exception>
#include <string>

/**
 * @brief Exception class for indicating multiple missing definitions.
 *
 * This class inherits from std::exception and provides a custom message
 * for describing the exception.
 */
class multiple_missing_def_exception_t : public std::exception {
private:
    std::string message;

public:
    multiple_missing_def_exception_t(const std::string& msg);

    virtual const char* what() const noexcept override;
};

#endif
