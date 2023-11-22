#ifndef CUSTOM_EXCEPTION_H
#define CUSTOM_EXCEPTION_H

#include <stdexcept>

class InvalidInputException : public std::invalid_argument {
public:
	explicit InvalidInputException(const std::string& message) : std::invalid_argument(message) {}
};

class GameOverException : public std::runtime_error {
public:
	explicit GameOverException(const std::string& message) : std::runtime_error(message) {}
};

#endif // CUSTOM_EXCEPTION_H
