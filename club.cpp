#include "club.hpp"

Club::Club(int num, int cost, int start, int end)
    : number_of_tables(num), cost_per_hour(cost), start_time(start),
      end_time(end), waiting_queue({std::queue<std::string>()}),
      tables({std::unordered_map<int, std::pair<std::string, int>>(),
              std::unordered_map<std::string, int>()}) {
  for (int x = 1; x <= num; ++x) {
    table_records[x] = {0, 0};
  }
};
