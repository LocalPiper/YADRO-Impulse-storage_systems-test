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

class Club {
  int numberOfTables;
  int costPerHour;
  int startTime;
  int endTime;
  WaitingQueue q;
  Tables t;
};
