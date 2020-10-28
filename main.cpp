#include <iostream>

#include "Yume/Engine.hpp"

#include "Voronoi.hpp"


using namespace std;


int main(int argc, char* argv[]) {
  Engine e;

  if (!e.init()) {
    cout << "shit happened" << endl;
    return -1;
  }

  e.pushState(new Voronoi());

  e.mainloop();

  return 0;
}