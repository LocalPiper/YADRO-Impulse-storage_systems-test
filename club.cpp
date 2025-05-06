#include "util.hpp"
#include <queue>
#include <string>
#include <unordered_map>
#include <utility>

struct WaitingQueue {
  std::queue<std::string> q;
};

struct Tables {
  std::unordered_map<int, std::pair<std::string, int>> table_to_client;
  std::unordered_map<std::string, int> client_to_table;
};

struct Record {
  long long accumulated_cost;
  int time_operating;
};

class Club {
  int number_of_tables;
  int cost_per_hour;
  int start_time;
  int end_time;
  WaitingQueue waiting_queue;
  Tables tables;
  std::unordered_map<int, Record> table_records;

public:
  Club(int num, int cost, std::string start, std::string end)
      : number_of_tables(num), cost_per_hour(cost),
        start_time(time_to_int(start)), end_time(time_to_int(end)),
        waiting_queue({std::queue<std::string>()}),
        tables({std::unordered_map<int, std::pair<std::string, int>>(),
                std::unordered_map<std::string, int>()}) {
    for (int x = 1; x <= num; ++x) {
      table_records[x] = {0, 0};
    }
  }
};
