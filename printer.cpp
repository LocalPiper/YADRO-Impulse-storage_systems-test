#include "printer.hpp"
#include "queries.hpp"
#include "util.hpp"
#include <iostream>
#include <ostream>
#include <string>

void print(const InQuery &inQ, std::optional<OutQuery> outQ = std::nullopt) {
  std::string out = int_to_time(inQ.time) + " " +
                    std::to_string(inQ.event_type) + " " + inQ.client;
  if (inQ.table != 0)
    out += " " + std::to_string(inQ.table);
  std::cout << out << std::endl;
  if (outQ.has_value()) {
    OutQuery q = outQ.value();
    out = int_to_time(q.time) + " " + std::to_string(q.event_type);
    if (q.event_type == OUT_LEFT) {
      out += " " + inQ.client;
    } else if (q.event_type == OUT_PLACED) {
      out += " " + inQ.client + " " + std::to_string(inQ.table);
    } else if (q.event_type == OUT_ERROR) {
      out += " " + q.body;
    }
    std::cout << out << std::endl;
  }
}
