#include <stdexcept>
#include <string>
int timeToInt(std::string time) {
  if (time.size() != 5 || time[2] != ':')
    throw std::runtime_error(
        "Error: time of incorrect format: should be XX:XX");
  int h = std::stoi(time.substr(0, 2));
  int m = std::stoi(time.substr(3, 2));
  return h * 60 + m;
}

std::string intToTime(int time) {
  int h = time / 60;
  int m = time % 60;
  if (h > 23 || m > 59)
    throw std::runtime_error("Error: time out of bounds");
  return ((h < 10) ? "0" + std::to_string(h) : std::to_string(h)) + ":" +
         ((m < 10) ? "0" + std::to_string(m) : std::to_string(m));
}
