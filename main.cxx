#include <vector>
#include <cstdio>
#include <iostream>
#include "src/main.hxx"

using namespace std;




template <class G, class H>
void runPagerank(const G& x, const H& xt, bool show) {
  int repeat = 5;
  bool skipInidenticals = true;
  vector<float> *init   = nullptr;

  // Find in-identicals.
  auto is = inIdenticals(x, xt);
  printf("inidenticals: %d inidentical-groups: %d {}\n", size2d(is), size(is));

  // Find pagerank without optimization.
  auto a1 = pagerankSeq(x, xt, init, {repeat});
  auto e1 = l1Norm(a1.ranks, a1.ranks);
  printf("[%09.3f ms; %03d iters.] [%.4e err.] pagerankSeq\n", a1.time, a1.iterations, e1);

  // Find pagerank skipping rank calculation of in-identical vertices.
  auto a2 = pagerankSeq(x, xt, init, {repeat, skipInidenticals});
  auto e2 = l1Norm(a2.ranks, a1.ranks);
  printf("[%09.3f ms; %03d iters.] [%.4e err.] pagerankSeq [skip]\n", a2.time, a2.iterations, e2);
}


int main(int argc, char **argv) {
  char *file = argv[1];
  bool  show = argc > 2;
  printf("Loading graph %s ...\n", file);
  auto x  = readMtx(file); println(x);
  auto xt = transposeWithDegree(x); print(xt); printf(" (transposeWithDegree)\n");
  runPagerank(x, xt, show);
  printf("\n");
  return 0;
}
