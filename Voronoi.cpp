#include "Voronoi.hpp"

#include <iostream>

#include "Yume/DisplayManager.hpp"
#include "Yume/Engine.hpp"


using namespace std;


// Constructors and destructor

Voronoi::Voronoi() :
  GameState(),

  generate(true),
  refresh(false),

  step(1),

  window_width(1024),
  window_height(768)
{}


// Public methodse

void Voronoi::init(Engine* e, DisplayManager* dm) {
  

  dm->setClearColor(0x00, 0x00, 0x00);
}

void Voronoi::cleanUp() {

}

void Voronoi::update(const int dt) {
  switch (step) {
  case 1:
    blueNoise();
    break;
  case 2:
    initVoronoi();
    break;
  case 3:
    //
    break;
  case 4:
    cout << "done" << endl;
    break;
  default: break;
  }
}

void Voronoi::display(DisplayManager* const dm, const int dt) {
  switch (step) {
  case 1:
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
    ++step;
    break;
  case 2:
    dm->clear();
    dm->setColor(0xff, 0xff, 0xff);
    for (auto c : cells) {
      dm->drawPoint(static_cast<float>(c.point.first), static_cast<float>(c.point.second));
      dm->drawPoint(static_cast<float>(c.point.first) + 1, static_cast<float>(c.point.second));
      dm->drawPoint(static_cast<float>(c.point.first), static_cast<float>(c.point.second) + 1);
      dm->drawPoint(static_cast<float>(c.point.first) - 1, static_cast<float>(c.point.second));
      dm->drawPoint(static_cast<float>(c.point.first), static_cast<float>(c.point.second) - 1);
      for (auto e : c.edges) {
        dm->drawLine(static_cast<float>(e.point1.first),
          static_cast<float>(e.point1.second),
          static_cast<float>(e.point2.first),
          static_cast<float>(e.point2.second));
      }
    }
    dm->render();
    ++step;
    break;
  case 3:
    //
    ++step;
    break;
  case 4:
    ++step;
    break;
  default: break;
  }
}


// Private methods

int Voronoi::toroidalDistance(int x1, int y1, int x2, int y2)
{
  int dx = std::abs(x2 - x1);
  int dy = std::abs(y2 - y1);

  static int half_width = window_width / 2;
  static int half_height = window_height / 2;

  if (dx > half_width)
    dx = window_width - dx;

  if (dy > half_height)
    dy = window_height - dy;

  return dx * dx + dy * dy; // no need to sqrt
}

void Voronoi::blueNoise() {
  random_device rd;
  mt19937 e2(rd());
  uniform_real_distribution<> dist1(uniform_real_distribution<>(0, window_width));
  uniform_real_distribution<> dist2(uniform_real_distribution<>(0, window_height));

  points.insert(make_pair(dist1(e2), dist2(e2)));
  int m(1);

  for (int i(1); i < 300; ++i) {
    int m = 1; // sample fact
    int x = 0;
    int y = 0;
    int d = 0;
    for (int j(0); j < points.size() * m; ++j) {
      int xc = static_cast<int>(dist1(e2));
      int yc = static_cast<int>(dist2(e2));
      int dc = 100000000;
      for (auto p : points) {
        int tdc = toroidalDistance(xc, yc, p.first, p.second);
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

void Voronoi::initVoronoi() {
  Cell c1;
  c1.point = make_pair(-window_width, -window_height);
  c1.edges.push_back(Edge(make_pair(-10 * window_width, window_height / 2), make_pair(window_width / 2, window_height / 2)));
  c1.edges.push_back(Edge(make_pair(window_width / 2, -10 * window_height), make_pair(window_width / 2, window_height / 2)));
  cells.insert(c1);
  Cell c2;
  c2.point = make_pair(-window_width, 2 * window_height);
  c2.edges.push_back(Edge(make_pair(-10 * window_width, window_height / 2), make_pair(window_width / 2, window_height / 2)));
  c2.edges.push_back(Edge(make_pair(window_width / 2,  10 * window_height), make_pair(window_width / 2, window_height / 2)));
  cells.insert(c2);
  Cell c3;
  c3.point = make_pair(2 * window_width, -window_height);
  c3.edges.push_back(Edge(make_pair( 10 * window_width, window_height / 2), make_pair(window_width / 2, window_height / 2)));
  c3.edges.push_back(Edge(make_pair(window_width / 2, -10 * window_height), make_pair(window_width / 2, window_height / 2)));
  cells.insert(c3);
  Cell c4;
  c4.point = make_pair(2 * window_width, 2 * window_height);
  c4.edges.push_back(Edge(make_pair( 10 * window_width, window_height / 2), make_pair(window_width / 2, window_height / 2)));
  c4.edges.push_back(Edge(make_pair(window_width / 2,  10 * window_height), make_pair(window_width / 2, window_height / 2)));
  cells.insert(c4);
}

void Voronoi::runVoronoi() {
  for (auto p : points) {
    Cell cell;
    cell.point = make_pair(p.first, p.second);

    for (auto c : cells) {
      int midpoint_x = (cell.point.first + c.point.first) / 2;
      int midpoint_y = (cell.point.second + c.point.second) / 2;

      if (cell.point.second == c.point.second) {

      } else {
        int a = -(cell.point.first - c.point.first) / (cell.point.second - c.point.second);
        int b = midpoint_y - a * midpoint_x;

        for (auto e : c.edges) {
          // check both points of e

          // if both are closer than the ab line, store it and delete it after the loop
          // if one is closer and one is farther, cut the line at the intersection
          // otherwise do nothing the segment remains
        }
      }
    }
    break; // to be removed - only testing the first point for now
  }
}
