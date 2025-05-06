#include "club.hpp"
#include "util.hpp"
#include <string>

Club::Club(int num, int cost, int start, int end)
    : number_of_tables(num), cost_per_hour(cost), start_time(start),
      end_time(end),
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

bool is_table_occupied(const Tables &tables, const int table) {
  return tables.table_to_client.find(table) != tables.table_to_client.end();
}

int Club::try_place(const int place_time, const std::string &client,
                    const int table) {
  // precedence: first we check if client is even in the club, then we
  // check if he can sit
  if (client_set.s.find(client) != client_set.s.end()) {
    // client is in the club and not waiting
    if (is_table_occupied(tables, table)) {
      return 1; // PlaceIsBusy
    }
    tables.client_to_table[client] = table;
    tables.table_to_client[table] = {client, place_time};
    client_set.s.erase(client);
    return 0;
  }
  if (tables.client_to_table.find(client) != tables.client_to_table.end()) {
    // client is already sitting at the table and wants to switch
    if (is_table_occupied(tables, table)) {
      return 1; // PlaceIsBusy
    }
    // record the last sitting
    int lastTable = tables.client_to_table[client];
    auto [_, start] = tables.table_to_client[lastTable];
    tables.table_to_client.erase(lastTable);
    auto &rec = table_records[lastTable];
    rec.time_operating += place_time - start;
    rec.accumulated_cost += ceil_time(place_time - start);

    // replace with new one
    tables.client_to_table[client] = table;
    tables.table_to_client[table] = {client, place_time};
    return 0;
  }
  // otherwise client is not in the club
  return 2; // ClientUnknown
}

int Club::try_queue(const int queue_time, const std::string &client) {
  // precedence: first we check if client is even in the club,
  // then we check if he can wait
  if (client_set.s.find(client) != client_set.s.end()) {
    // he is in the club and not waiting
    if (tables.table_to_client.size() < number_of_tables) {
      return 1; // ICanWaitNoLonger!
    }
    waiting_queue.push(client);
    return 0;
  }
  // yeah, but what if he is already in the queue or already sitting?
  // that was not specified in the task, so i will enforce my rules
  // client cannot go to the queue if he is already there
  if (tables.client_to_table.find(client) != tables.client_to_table.end() ||
      waiting_queue.contains(client)) {
    return 2; // IShallNotWait!
  }
  // i'll also make sure that he cannot wait if he is not in the club
  return 3; // ClientUnknown
}

int Club::try_leave(const int leave_time, const std::string &client) {
  // precedence: first we check if client is even in the club
  if (client_set.s.find(client) != client_set.s.end()) {
    // if he is in the club and not waiting or sitting, we can delete him
    client_set.s.erase(client);
    return 0;
  }
  if (tables.client_to_table.find(client) != tables.client_to_table.end()) {
    // record his sitting and delete him
    int lastTable = tables.client_to_table[client];
    auto [_, start] = tables.table_to_client[lastTable];
    tables.table_to_client.erase(lastTable);
    tables.client_to_table.erase(client);
    auto &rec = table_records[lastTable];
    rec.time_operating += leave_time - start;
    rec.accumulated_cost += ceil_time(leave_time - start);
    return 0;
  }
  return 1; // ClientUnknown
}
