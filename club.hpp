#ifndef CLUB_HPP
#define CLUB_HPP

#include <iterator>
#include <list>
#include <set>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>

class WaitingQueue {
private:
  std::list<std::string> queue;
  std::unordered_map<std::string, std::list<std::string>::iterator> lookup;

public:
  void push(const std::string &client) {
    queue.push_back(client);
    auto it = std::prev(queue.end());
    lookup[client] = it;
  }

  void remove(const std::string &client) {
    auto it = lookup.find(client);
    if (it != lookup.end()) {
      queue.erase(it->second);
      lookup.erase(it);
    }
  }

  bool contains(const std::string &client) const {
    return lookup.count(client) > 0;
  }

  std::string front() const { return queue.front(); }

  void pop() {
    if (!queue.empty()) {
      lookup.erase(queue.front());
      queue.pop_front();
    }
  }

  bool empty() const { return queue.empty(); }

  int size() const { return queue.size(); }
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
  int recently_freed_table = 0;
  Club(int num, int cost, int start, int end);
  int try_enter(const int enter_time, const std::string &client);
  int try_place(const int place_time, const std::string &client,
                const int table);
  int try_queue(const int queue_time, const std::string &client);
  int try_leave(const int leave_time, const std::string &client);
  std::pair<std::string, int> try_place_from_queue(const int place_time,
                                                   int table);
  std::set<std::string> kick_clients();
  std::unordered_map<int, Record> get_records();
};

#endif // CLUB_HPP
