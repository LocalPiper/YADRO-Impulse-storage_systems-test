#ifndef QUERIES_HPP
#define QUERIES_HPP

#include <string>
enum InEventType {
  IN_ENTER = 1,
  IN_PLACED = 2,
  IN_WAIT = 3,
  IN_LEAVE = 4,
};

enum OutEventType { OUT_LEFT = 11, OUT_PLACED = 12, OUT_ERROR = 13 };

struct InQuery {
  std::string time;
  InEventType eventType;
  std::string client;
  int table = 0; // optional
};

struct OutQuery {
  std::string time;
  OutEventType eventType;
  std::string body;
};

#endif // QUERIES_HPP
