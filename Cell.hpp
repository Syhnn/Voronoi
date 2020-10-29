#ifndef _CELL_HPP_
#define _CELL_HPP_

#include <vector>

#include "Edge.hpp"


class Cell {
public:
  std::pair<int, int> point;
  std::vector<Edge> edges;

  bool operator<(const Cell& c);
};

#endif // _CELL_HPP_
