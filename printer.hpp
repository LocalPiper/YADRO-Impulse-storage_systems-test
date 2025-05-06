#ifndef PRINTER_HPP
#define PRINTER_HPP

#include "queries.hpp"
#include <optional>

// this should be used for input and 13 output queries only
void print(const InQuery &inQ, std::optional<OutQuery> outQ);

// this should be used for 11 and 12 output queries only
void print(const OutQuery &outQ);

#endif // PRINTER_HPP
