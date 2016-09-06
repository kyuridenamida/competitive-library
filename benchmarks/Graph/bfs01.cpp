#include "../util.hpp"

double test_bfs01() {
  auto g = random_cgraph(0, 2);
  Timer timer;
  bfs01(g, 0);
  return timer.stop() / edge_num;
}
