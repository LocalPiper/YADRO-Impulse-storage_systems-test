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

int Club::try_enter(const int enter_time, const std::string &client) {
  if (enter_time < start_time || enter_time > end_time) {
    return 1; // NotOpenYet
  }
  if (client_set.s.find(client) != client_set.s.end()) {
    return 2; // YouShallNotPass
  }
  client_set.s.insert(client);
  return 0;
}
