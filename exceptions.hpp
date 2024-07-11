/**
 * @file  exceptions.hpp
 */

#ifndef EXCEPTIONS_HPP
#define EXCEPTIONS_HPP

#include <exception>
#include <string>

/**
 * @brief Exception class for indicating micellaneous exceptions.
 *
 * This class inherits from std::exception and provides a custom message
 * for describing the exception.
 */
class general_exception_t : public std::exception {
private:
    std::string message;

public:
    general_exception_t(const std::string& msg);

    virtual const char* what() const noexcept override;
};

/**
 * @brief Exception class for indicating multiple missing definitions.
 */
class multiple_missing_def_exception_t : public general_exception_t {
public:
    multiple_missing_def_exception_t(const std::string& msg);
};
#endif
