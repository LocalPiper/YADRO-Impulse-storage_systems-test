#ifndef PARSER_HPP
#define PARSER_HPP

#include <string>
#include <vector>

class ValidationError : public std::exception {
private:
  std::string message;

public:
  explicit ValidationError(const std::string &msg) : message(msg) {}

  const char *what() const noexcept override { return message.c_str(); }
};

std::string parse(std::vector<std::string> &lines);

#endif // PARSER_HPP
