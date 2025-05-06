#include "parser.hpp"
#include "queries.hpp"
#include "util.hpp"
#include <sstream>
#include <vector>

DataBox parse(std::vector<std::string> &lines) {
  if (lines.size() < 3) {
    throw ValidationError("There are less than 3 lines in the file!");
  }
  // line 1: number of tables
  int num_of_tables;
  try {
    num_of_tables = std::stoi(lines[0]);
    if (num_of_tables <= 0) {
      throw ValidationError("Format error on line 1");
    }
  } catch (...) {
    throw ValidationError("Format error on line 1");
  }
  // line 2: start-end times
  std::istringstream ss2(lines[1]);
  std::string t1, t2;
  if (!(ss2 >> t1 >> t2) || !is_valid_time(t1) || !is_valid_time(t2)) {
    throw ValidationError("Format error on line 2");
  }
  int start_time, end_time;
  start_time = time_to_int(t1);
  end_time = time_to_int(t2);
  if (t1 > t2)
    throw ValidationError("Format error on line 2");
  // line 3: cost
  int cost;
  try {
    cost = std::stoi(lines[2]);
    if (cost <= 0) {
      throw ValidationError("Format error on line 3");
    }
  } catch (...) {
    throw ValidationError("Format error on line 3");
  }

  // all other lines
  int prev_time = 0;
  std::vector<InQuery> queries;
  for (int i = 3; i < (int)lines.size(); ++i) {
    std::istringstream ss(lines[i]);
    std::string time_str, event_type_str, client, table_str, extra;
    int event_type, table_num;

    if (!(ss >> time_str >> event_type_str) || !is_valid_time(time_str)) {
      throw ValidationError("Format error on line " + std::to_string(i + 1));
    }

    int curr_time = time_to_int(time_str);
    if (curr_time < prev_time) {
      throw ValidationError("Format error on line " + std::to_string(i + 1));
    }
    prev_time = curr_time;

    try {
      event_type = std::stoi(event_type_str);
      if (event_type < 1 || event_type > 4) {
        throw ValidationError("Format error on line " + std::to_string(i + 1));
      }
    } catch (...) {
      throw ValidationError("Format error on line " + std::to_string(i + 1));
    }

    if (!(ss >> client) || !is_valid_client(client)) {
      throw ValidationError("Format error on line " + std::to_string(i + 1));
    }

    if (event_type == 2) {
      if (!(ss >> table_str)) {
        throw ValidationError("Format error on line " + std::to_string(i + 1));
      }

      try {
        table_num = std::stoi(table_str);
        if (table_num < 1 || table_num > num_of_tables) {
          throw ValidationError("Format error on line " +
                                std::to_string(i + 1));
        }
      } catch (...) {
        throw ValidationError("Format error on line " + std::to_string(i + 1));
      }
    }

    if (ss >> extra) {
      throw ValidationError("Format error on line " + std::to_string(i + 1));
    }

    queries.push_back({curr_time, static_cast<InEventType>(event_type), client,
                       (event_type == 2) ? table_num : 0});
  }

  return {num_of_tables, start_time, end_time, cost, queries};
}
