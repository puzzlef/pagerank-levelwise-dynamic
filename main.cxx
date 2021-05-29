#include <cmath>
#include <string>
#include <sstream>
#include <cstdio>
#include <iostream>
#include <utility>
#include "src/main.hxx"

using namespace std;




void runPagerank(const string& data, int pre, int post, bool show) {
  vector<float>  ranksAdj;
  vector<float> *initStatic  = nullptr;
  vector<float> *initDynamic = &ranksAdj;

  DiGraph<> x;
  stringstream s(data);
  readSnapTemporal(x, s, pre);
  auto xt  = transposeWithDegree(x);
  auto a1  = pagerankLevelwise(x, xt, initStatic);
  auto e1  = absError(a1.ranks, a1.ranks);
  print(xt); printf(" [%09.3f ms; %03d iters.] [%.4e err.] pagerankStatic [pre]\n", a1.time, a1.iterations, e1);
  auto xks    = vertices(x);
  auto xranks = move(a1.ranks);

  auto y = copy(x);
  readSnapTemporal(y, s, post);
  auto yt  = transposeWithDegree(y);
  auto yks = vertices(y);
  ranksAdj.resize(y.span());

  // Find static pagerank of updated graph.
  auto a2  = pagerankLevelwise(y, yt, initStatic);
  auto e2  = absError(a2.ranks, a2.ranks);
  print(yt); printf(" [%09.3f ms; %03d iters.] [%.4e err.] pagerankStatic [post]\n", a2.time, a2.iterations, e2);

  // Find dynamic pagerank of updated graph.
  auto a3  = pagerankLevelwise(y, yt, initDynamic);
  auto e3  = absError(a3.ranks, a2.ranks);
  print(yt); printf(" [%09.3f ms; %03d iters.] [%.4e err.] pagerankDynamic [post]\n", a3.time, a3.iterations, e3);

  // Find dynamic pagerank of updated graph, skipping unchanged components.
  auto a4  = pagerankLevelwiseSkip(x, xt, y, yt, initDynamic);
  auto e4  = absError(a4.ranks, a2.ranks);
  print(yt); printf(" [%09.3f ms; %03d iters.] [%.4e err.] pagerankDynamicSkip [post]\n", a4.time, a4.iterations, e4);
}


int main(int argc, char **argv) {
  char *file = argv[1];
  int   pre  = stoi(argv[2]);
  int   post = stoi(argv[3]);
  bool  show = argc > 4;
  printf("Using graph %s ...\n", file);
  string d = readFile(file);
  runPagerank(d, pre, post, show);
  return 0;
}
