#include "Edge.hpp"


using namespace std;


// Constructors and destructor

Edge::Edge(std::pair<int, int> p1, std::pair<int, int> p2) :
  point1(p1),
  point2(p2)
{}


// Public methods

bool Edge::operator<(const Edge& e) const {
  return point1.second < e.point1.second || point1.second == e.point1.second && point1.first < e.point1.first;
}
