#include <cmath>
#include <string>
#include <sstream>
#include <cstdio>
#include <iostream>
#include <utility>
#include "src/main.hxx"

using namespace std;




void runPagerankBatch(const string& data, bool show, int skip, int batch) {
  int repeat = 5;
  vector<float>  ranksAdj;
  vector<float> *initStatic  = nullptr;
  vector<float> *initDynamic = &ranksAdj;

  DiGraph<> x;
  stringstream s(data);
  while (true) {
    // Skip some edges (to speed up execution)
    if (!readSnapTemporal(x, s, skip)) break;
    auto xt = transposeWithDegree(x);
    auto a1 = pagerankLevelwise(x, xt);
    auto ksOld    = vertices(x);
    auto ranksOld = move(a1.ranks);

    // Read edges for this batch.
    auto y = copy(x);
    if (!readSnapTemporal(y, s, batch)) break;
    auto yt = transposeWithDegree(y);
    auto ks = vertices(y);
    ranksAdj.resize(y.span());

    // Find static pagerank of updated graph.
    auto a2 = pagerankLevelwise(y, yt, initStatic, {repeat});
    auto e2 = l1Norm(a2.ranks, a2.ranks);
    print(yt); printf(" [%09.3f ms; %03d iters.] [%.4e err.] pagerankStatic\n", a2.time, a2.iterations, e2);

    // Find dynamic pagerank, with scaled-fill.
    adjustRanks(ranksAdj, ranksOld, ksOld, ks, 0.0f, float(ksOld.size())/ks.size(), 1.0f/ks.size());
    auto a3 = pagerankLevelwise(y, yt, initDynamic, {repeat});
    auto e3 = l1Norm(a3.ranks, a2.ranks);
    print(yt); printf(" [%09.3f ms; %03d iters.] [%.4e err.] pagerankDynamic\n", a3.time, a3.iterations, e3);

    // Find dynamic pagerank, with skip-comp and scaled-fill.
    auto a4 = pagerankLevelwise(x, xt, y, yt, initDynamic, {repeat});
    auto e4 = l1Norm(a4.ranks, a2.ranks);
    print(yt); printf(" [%09.3f ms; %03d iters.] [%.4e err.] pagerankDynamic [skip-comp]\n", a4.time, a4.iterations, e4);
    x = move(y);
  }
}


void runPagerank(const string& data, bool show) {
  int M = countLines(data), steps = 100;
  printf("Temporal edges: %d\n\n", M);
  for (int batch=1, i=0; batch<M; batch*=i&1? 2:5, i++) {
    int skip = max(M/steps - batch, 0);
    printf("# Batch size %.0e\n", (double) batch);
    runPagerankBatch(data, show, skip, batch);
    printf("\n");
  }
}


int main(int argc, char **argv) {
  char *file = argv[1];
  bool  show = argc > 2;
  printf("Using graph %s ...\n", file);
  string d = readFile(file);
  runPagerank(d, show);
  return 0;
}
