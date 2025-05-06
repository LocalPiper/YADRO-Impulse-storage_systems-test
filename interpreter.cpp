
#include "box.hpp"
#include "club.hpp"
#include "queries.hpp"
#include <stdexcept>
void interpret(const DataBox &box) {
  Club club(box.num_of_tables, box.cost, box.start_time, box.end_time);

  for (auto query : box.queries) {
    switch (query.event_type) {
    case IN_ENTER: {
    }
    case IN_PLACED: {
    }
    case IN_WAIT: {
    }
    case IN_LEAVE: {
    }
    default:
      throw std::runtime_error("this should not happen");
    }
  }
}
