#ifndef _VORONOI_HPP_
#define _VORONOI_HPP_

#include <random>
#include <unordered_set>

#include "Yume/GameState.hpp"


struct pair_hash {
  template <class T1, class T2>
  std::size_t operator () (std::pair<T1, T2> const& pair) const {
    std::size_t h1 = std::hash<T1>()(pair.first);
    std::size_t h2 = std::hash<T2>()(pair.second);
    // this is pretty bad, it needs to be replaced
    return h1 ^ h2;
  }
};


class Voronoi : public GameState{
public:
  Voronoi();

  void init(Engine* e, DisplayManager* dm);
  void cleanUp();

  void update(const int dt) override;
  void display(DisplayManager* const dm, const int dt) override;

private:
  int ToroidalDistance(int x1, int y1, int x2, int y2);


  bool generate;
  bool refresh;

  std::unordered_set<std::pair<int, int>, pair_hash> points;
};

#endif // _VORONOI_HPP_
