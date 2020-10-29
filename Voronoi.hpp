#ifndef _VORONOI_HPP_
#define _VORONOI_HPP_

#include <random>
#include <set>

#include "Yume/GameState.hpp"

#include "Cell.hpp"


class Voronoi : public GameState{
public:
  Voronoi();

  void init(Engine* e, DisplayManager* dm);
  void cleanUp();

  void update(const int dt) override;
  void display(DisplayManager* const dm, const int dt) override;

private:
  int toroidalDistance(int x1, int y1, int x2, int y2);

  void blueNoise();
  void initVoronoi();


  int step;

  // you should be able to use this to sizz the window
  const int window_width;
  const int window_height;

  bool generate;
  bool refresh;

  std::set<std::pair<int, int>> points;
  std::set<Edge> edges;
  std::set<Cell> cells;
};

#endif // _VORONOI_HPP_
