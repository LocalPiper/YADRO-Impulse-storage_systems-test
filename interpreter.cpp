#include "interpreter.hpp"
#include "club.hpp"
#include "printer.hpp"
#include "queries.hpp"
#include <optional>
#include <stdexcept>
#include <string>
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
      int result = club.try_place(time, client, table);
      if (result == 0) {
        print(query, std::nullopt);
        auto p = club.try_place_from_queue(time, table);
        if (p.first != "")
          print({time, OUT_PLACED, p.first + " " + std::to_string(p.second)});
        break;
      }
      OutQuery outQ = {time, OUT_ERROR,
                       (result == 1)   ? "PlaceIsBusy"
                       : (result == 2) ? "ClientUnknown"
                                       : "BackInTheLine!"};
      print(query, outQ);
      break;
    }
    case IN_WAIT: {
      int result = club.try_queue(time, client);
      if (result == 0) {
        print(query, std::nullopt);
        break;
      }
      OutQuery outQ = {time, OUT_ERROR,
                       (result == 1)   ? "ICanWaitNoLonger!"
                       : (result == 2) ? "IShallNotWait!"
                                       : "ClientUnknown"};
      print(query, outQ);
      break;
    }
    case IN_LEAVE: {
      int result = club.try_leave(time, client);
      if (result == 0) {
        print(query, std::nullopt);
        auto p = club.try_place_from_queue(time, 0);
        if (p.first != "")
          print({time, OUT_PLACED, p.first + " " + std::to_string(p.second)});
        break;
      }
      OutQuery outQ = {time, OUT_ERROR, "ClientUnknown"};
      print(query, outQ);
      break;
    }
    default:
      throw std::runtime_error("this should not happen");
    }
  }
}
