/**
 * @file  exceptions.cpp
 */

#include "exceptions.hpp"

/**
 * @brief Constructor for initializing the exception with a message.
 * @param msg The error message to be associated with the exception.
 */
multiple_missing_def_exception_t::multiple_missing_def_exception_t(const std::string& msg) : message(msg) {}

/**
 * @brief Returns the error message associated with the exception.
 * @return A C-string pointer to the error message.
 */
const char* multiple_missing_def_exception_t::what() const noexcept {
    return message.c_str();
}
