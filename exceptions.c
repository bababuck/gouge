/**
 * @brief Constructor for initializing the exception with a message.
 * @param msg The error message to be associated with the exception.
 */
multiple_missing_definition_t::multiple_missing_definition_t(const std::string& msg) : message(msg) {}

/**
 * @brief Returns the error message associated with the exception.
 * @return A C-string pointer to the error message.
 */
virtual const char* multiple_missing_definition_t::what() const noexcept override {
    return message.c_str();
}