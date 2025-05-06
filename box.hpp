#ifndef BOX_HPP
#define BOX_HPP

#include "queries.hpp"
#include <vector>

struct DataBox {
  int num_of_tables;
  int start_time;
  int end_time;
  int cost;
  std::vector<InQuery> queries;
};

#endif // BOX_HPP
