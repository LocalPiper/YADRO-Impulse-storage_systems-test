#include "util.hpp"
#include <queue>
#include <string>
#include <unordered_map>
#include <utility>

struct WaitingQueue {
  std::queue<std::string> q;
};

struct Tables {
  std::unordered_map<int, std::pair<std::string, int>> tableToClient;
  std::unordered_map<std::string, int> clientToTable;
};

struct Record {
  long long accumulatedCost;
  int timeOperating;
};

class Club {
  int numberOfTables;
  int costPerHour;
  int startTime;
  int endTime;
  WaitingQueue waitingQueue;
  Tables tables;
  std::unordered_map<int, Record> tableRecords;

public:
  Club(int num, int cost, std::string start, std::string end)
      : numberOfTables(num), costPerHour(cost), startTime(timeToInt(start)),
        endTime(timeToInt(end)), waitingQueue({std::queue<std::string>()}),
        tables({std::unordered_map<int, std::pair<std::string, int>>(),
                std::unordered_map<std::string, int>()}) {
    for (int x = 1; x <= num; ++x) {
      tableRecords[x] = {0, 0};
    }
  }
};
