#ifndef CLUB_HPP
#define CLUB_HPP

#include <queue>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>

struct WaitingQueue {
  std::queue<std::string> q;
};

struct ClientSet {
  std::unordered_set<std::string> s;
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
  ClientSet client_set;
  Tables tables;
  std::unordered_map<int, Record> table_records;

public:
  Club(int num, int cost, int start, int end);
  int try_enter(const int enter_time, const std::string &client);
  int try_place(const int place_time, const std::string &client,
                const int table);
};

#endif // CLUB_HPP
