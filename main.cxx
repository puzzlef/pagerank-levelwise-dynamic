#include <cmath>
#include <string>
#include <sstream>
#include <cstdio>
#include <iostream>
#include <utility>
#include "src/main.hxx"

using namespace std;




template <class F, class T=float>
auto runCall(bool show, const char *name, F fn, const vector<T> *ranks=nullptr) {
  auto a = fn(); auto e = absError(a.ranks, ranks? *ranks : a.ranks);
  if (name) { printf("[%09.3f ms; %03d iters.] [%.4e err.] %s\n", a.time, a.iterations, e, name); }
  if (show) { println(a.ranks); printf("\n"); }
  return a;
}


void runPagerank(const string& data, int original, int update, bool show) {
  vector<float>  ranksAdj;
  vector<float> *initStatic  = nullptr;
  vector<float> *initDynamic = &ranksAdj;

  DiGraph<> w;
  stringstream s(data);

  // Find static pagerank of original graph.
  readSnapTemporal(w, s, original);
  printf("original-graph: "); println(w, true); printf("\n");
  auto wt = transposeWithDegree(w);
  auto a1 = runCall(show, "pagerankStatic", [&] { return pagerankLevelwise(w, wt, initStatic); });
  auto ksOld    = vertices(w);
  auto ranksOld = move(a1.ranks);

  // Load new edges for updated graph.
  auto x = copy(w);
  readSnapTemporal(x, s, update);
  printf("updated-graph: "); println(x, true); printf("\n");
  auto xt  = transposeWithDegree(x);
  auto ks  = vertices(x);
  ranksAdj.resize(x.span());

  // Find static pagerank of post-graph.
  auto a2 = runCall(show, "pagerankStatic", [&] { return pagerankLevelwise(x, xt, initStatic); });

  // Find dynamic pagerank of post-graph.
  adjustRanks(ranksAdj, ranksOld, ksOld, ks, 0.0f, float(ksOld.size())/ks.size(), 1.0f/ks.size());
  auto a3 = runCall(show, "pagerankDynamic", [&] { return pagerankLevelwise(x, xt, initDynamic); }, &a2.ranks);

  // Find dynamic pagerank of post-graph, skipping unchanged components.
  auto a4 = runCall(show, "pagerankDynamic [skip-comp]", [&] { return pagerankLevelwise(w, wt, x, xt, initDynamic); }, &a2.ranks);
}


int main(int argc, char **argv) {
  char *file = argv[1];
  int   original = stoi(argv[2]);
  int   update   = stoi(argv[3]);
  bool  show     = argc > 4;
  printf("Using graph %s ...\n", file);
  string d = readFile(file);
  runPagerank(d, original, update, show);
  return 0;
}
