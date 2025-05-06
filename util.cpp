#include "util.hpp"
#include <regex>

bool is_valid_time(const std::string &time) {
  std::regex time_regex(R"(^([01]?\d|2[0-3]):[0-5]\d$)");
  return std::regex_match(time, time_regex);
}

bool is_valid_client(const std::string &client) {
  std::regex client_regex(R"(^[a-z0-9_]+$)");
  return std::regex_match(client, client_regex);
}

int time_to_int(std::string time) {
  int h = std::stoi(time.substr(0, 2));
  int m = std::stoi(time.substr(3, 2));
  return h * 60 + m;
}

int ceil_time(int time) { return (time + 59) / 60; }

std::string int_to_time(int time) {
  int h = time / 60;
  int m = time % 60;
  return ((h < 10) ? "0" + std::to_string(h) : std::to_string(h)) + ":" +
         ((m < 10) ? "0" + std::to_string(m) : std::to_string(m));
}
