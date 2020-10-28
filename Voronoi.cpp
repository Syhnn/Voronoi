#include "Voronoi.hpp"

#include <iostream>

#include "Yume/DisplayManager.hpp"
#include "Yume/Engine.hpp"


using namespace std;


// Constructors and destructor

Voronoi::Voronoi() :
  GameState(),

  generate(true),
  refresh(false)
{}


// Public methodse

void Voronoi::init(Engine* e, DisplayManager* dm) {
  

  dm->setClearColor(0x00, 0x00, 0x00);
}

void Voronoi::cleanUp() {

}

int Voronoi::ToroidalDistance(int x1, int y1, int x2, int y2)
{
  int dx = std::abs(x2 - x1);
  int dy = std::abs(y2 - y1);

  if (dx > 512)
    dx = 1024 - dx;

  if (dy > 384)
    dy = 768 - dy;

  return dx * dx + dy * dy; // no need to sqrt
}

void Voronoi::update(const int dt) {
  if (generate) {
    random_device rd;
    mt19937 e2(rd());
    uniform_real_distribution<> dist1(uniform_real_distribution<>(0, 1024));
    uniform_real_distribution<> dist2(uniform_real_distribution<>(0, 768));

    points.insert(make_pair(rand() % 1024, rand() % 768));
    int m(1);

    for (int i(1); i < 300; ++i) {
      int m = 1; // sample fact
      int x = 0;
      int y = 0;
      int d = 0;
      for (int j(0); j < points.size() * m; ++j) {
        int xc = dist1(e2);
        int yc = dist2(e2);
        int dc = 100000000;
        for (auto p : points) {
          int tdc = ToroidalDistance(xc, yc, p.first, p.second);
          if (tdc < dc) {
            dc = tdc;
          }
        }
        if (dc > d) {
          x = xc;
          y = yc;
          d = dc;
        }
      }

      points.insert(make_pair(x, y));
    }

    generate = false;
    refresh = true;
  }
}

void Voronoi::display(DisplayManager* const dm, const int dt) {
  if (refresh) {
    dm->clear();
    dm->setColor(0xff, 0xff, 0xff);
    for (auto p : points) {
      dm->drawPoint(static_cast<float>(p.first), static_cast<float>(p.second));
      dm->drawPoint(static_cast<float>(p.first) + 1, static_cast<float>(p.second));
      dm->drawPoint(static_cast<float>(p.first), static_cast<float>(p.second) + 1);
      dm->drawPoint(static_cast<float>(p.first) - 1, static_cast<float>(p.second));
      dm->drawPoint(static_cast<float>(p.first), static_cast<float>(p.second) - 1);
    }
    dm->render();
    refresh = false;
  }
}
