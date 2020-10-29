#ifndef _EDGE_HPP_
#define _EDGE_HPP_

#include <utility>


class Edge {
public:
  Edge(std::pair<int, int> p1, std::pair<int, int> p2);

  std::pair<int, int> point1;
  std::pair<int, int> point2;
};

#endif // _EDGE_HPP_