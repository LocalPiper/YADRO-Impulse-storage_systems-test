#include "interpreter.hpp"
#include "club.hpp"
#include "printer.hpp"
#include "queries.hpp"
#include <optional>
#include <stdexcept>
void interpret(const DataBox &box) {
  Club club(box.num_of_tables, box.cost, box.start_time, box.end_time);

  for (auto query : box.queries) {
    std::string client = query.client;
    int time = query.time;
    InEventType event_type = query.event_type;
    int table = query.table;

    switch (event_type) {
    case IN_ENTER: {
      int result = club.try_enter(time, client);
      if (result == 0) {
        print(query, std::nullopt);
        break;
      }
      OutQuery outQ = {time, OUT_ERROR,
                       (result == 1) ? "NotOpenYet" : "YouShallNotPass"};
      print(query, outQ);
      break;
    }
    case IN_PLACED: {
      break;
    }
    case IN_WAIT: {
      break;
    }
    case IN_LEAVE: {
      break;
    }
    default:
      throw std::runtime_error("this should not happen");
    }
  }
}
