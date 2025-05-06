#ifndef UTIL_HPP
#define UTIL_HPP

#include <string>

int time_to_int(std::string time);

std::string int_to_time(int time);

int ceil_time(int time);

bool is_valid_time(const std::string &time);

bool is_valid_client(const std::string &client);

#endif // UTIL_HPP
