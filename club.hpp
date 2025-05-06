#ifndef CLUB_HPP
#define CLUB_HPP

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
  Club(int num, int cost, int start, int end);
};

#endif // CLUB_HPP
