#include "Cell.hpp"


using namespace std;


// Public methods

bool Cell::operator<(const Cell& c) const {
  return point.second < c.point.second || point.second == c.point.second && point.first < c.point.first;
}
