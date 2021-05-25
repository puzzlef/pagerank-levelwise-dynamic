#include <cmath>
#include <random>
#include <cstdio>
#include <iostream>
#include "src/main.hxx"

using namespace std;




template <class G>
void runPagerankBatch(const G& x, const vector<float>& ranksOld, int batch) {
  int repeat = 5, minComponentSize = 50;
  int span = int(1.1 * x.span());
  vector<float> ranksAdj;
  vector<float> *initStatic  = nullptr;
  vector<float> *initDynamic = &ranksAdj;
  random_device dev;
  default_random_engine rnd(dev());

  // Add random edges
  auto y = copy(x);
  for (int i=0; i<batch; i++)
    addRandomEdgeByDegree(y, rnd, span);
  loopDeadEnds(y);
  auto yt = transposeWithDegree(y);

  // Adjust ranks for dynamic pagerank
  auto ksOld = vertices(x);
  auto ks    = vertices(y);
  ranksAdj.resize(y.span());
  adjustRanks(ranksAdj, ranksOld, ksOld, ks, 0.0f, float(ksOld.size())/ks.size(), 1.0f/ks.size());

  // Find static pagerank using standard algorithm.
  auto a1 = pagerankMonolithic(yt, initStatic, {repeat});
  auto e1 = absError(a1.ranks, a1.ranks);
  print(y); printf(" [%09.3f ms; %03d iters.] [%.4e err.] pagerankMonolithic\n", a1.time, a1.iterations, e1);

  // Find static pagerank component-wise in topologically-ordered fashion (levelwise).
  auto a2 = pagerankLevelwise(y, yt, initStatic, {repeat, minComponentSize});
  auto e2 = absError(a2.ranks, a1.ranks);
  print(y); printf(" [%09.3f ms; %03d iters.] [%.4e err.] pagerankLevelwise\n", a2.time, a2.iterations, e2);

  // Find dynamic pagerank component-wise in topologically-ordered fashion (levelwise).
  auto a3 = pagerankLevelwise(y, yt, initDynamic, {repeat, minComponentSize});
  auto e3 = absError(a3.ranks, a1.ranks);
  print(y); printf(" [%09.3f ms; %03d iters.] [%.4e err.] pagerankLevelwise [dynamic]\n", a3.time, a3.iterations, e3);
}


template <class G, class H>
void runPagerank(const G& x, const H& xt, bool show) {
  int repeat = 5;
  vector<float> *init = nullptr;

  // Find pagerank using standard algorithm.
  auto a1 = pagerankMonolithic(xt, init, {repeat});
  auto e1 = absError(a1.ranks, a1.ranks);
  printf("[%09.3f ms; %03d iters.] [%.4e err.] pagerankMonolithic\n", a1.time, a1.iterations, e1);
  if (show) println(a1.ranks);

  // Find pagerank for different batch sizes.
  for (int batch=1, i=0; batch<x.size(); batch*=i&1? 2:5, i++) {
    printf("# Batch size %.0e\n", (double) batch);
    for (int repeat=0; repeat<5; repeat++)
      runPagerankBatch(x, a1.ranks, batch);
    printf("\n");
  }
}


int main(int argc, char **argv) {
  char *file = argv[1];
  bool  show = argc > 2;
  printf("Loading graph %s ...\n", file);
  auto x  = readMtx(file); println(x);
  loopDeadEnds(x); print(x); printf(" (loopDeadEnds)\n");
  auto xt = transposeWithDegree(x); print(xt); printf(" (transposeWithDegree)\n");
  runPagerank(x, xt, show);
  printf("\n");
  return 0;
}
