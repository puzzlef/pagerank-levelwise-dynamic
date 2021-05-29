#pragma once
#include <vector>
#include <algorithm>
#include "vertices.hxx"
#include "edges.hxx"
#include "csr.hxx"
#include "components.hxx"
#include "blockgraph.hxx"
#include "topologicalSort.hxx"
#include "pagerank.hxx"
#include "pagerankMonolithic.hxx"
#include "pagerankLevelwise.hxx"

using std::vector;
using std::swap;




template <class C>
auto pagerankComponentSizes(const C& xcs, const C& ycs) {
  vector<int> a; bool fail = false;
  for (int i=0, X=xcs.size(), Y=ycs.size(); i<Y; i++) {
    if (!fail && i<X && xcs[i]==ycs[i]) a.push_back(-ycs[i].size());
    else { a.push_back(ycs[i].size()); fail = true; }
  }
  return a;
}


template <class T, class J>
int pagerankLevelwiseSkipLoop(vector<T>& a, vector<T>& r, vector<T>& c, const vector<T>& f, const vector<int>& vfrom, const vector<int>& efrom, const vector<int>& vdata, J&& ns, int N, T p, T E, int L) {
  int v = 0; float l = 0;
  for (int n : ns) {
    if (n >= 0) {
      int k = pagerankMonolithicLoop(a, r, c, f, vfrom, efrom, vdata, v, v+n, N, p, E * (float(n)/N), L);
      swap(a, r);
      l += k * (float(n)/N);
    }
    v += n;
  }
  return int(l);
}


// Find pagerank of components in topological order (pull, CSR).
// @param xt transpose graph, with vertex-data=out-degree
// @param q initial ranks (optional)
// @param o options {damping=0.85, tolerance=1e-6, maxIterations=500}
// @returns {ranks, iterations, time}
template <class G, class H, class T=float>
PagerankResult<T> pagerankLevelwiseSkip(const G& x, const H& xt, const G& y, const H& yt, const vector<T> *q=nullptr, PagerankOptions<T> o={}) {
  T    p = o.damping;
  T    E = o.tolerance;
  int  L = o.maxIterations, l;
  int  N = yt.order();
  auto xcs = pagerankComponents(x, xt, o);
  auto ycs = pagerankComponents(y, yt, o);
  auto ns = pagerankComponentSizes(xcs, ycs);
  auto ks = join(ycs);
  auto vfrom = sourceOffsets(yt, ks);
  auto efrom = destinationIndices(yt, ks);
  auto vdata = vertexData(yt, ks);
  vector<T> a(N), r(N), c(N), f(N), qc;
  if (q) qc = compressContainer(yt, *q, ks);
  float t = measureDurationMarked([&](auto mark) {
    fill(a, T());
    if (q) copy(r, qc);
    else fill(r, T(1)/N);
    mark([&] { pagerankFactor(f, vfrom, efrom, vdata, 0, N, N, p); });
    mark([&] { l = pagerankLevelwiseSkipLoop(a, r, c, f, vfrom, efrom, vdata, ns, N, p, E, L); });
  }, o.repeat);
  return {decompressContainer(xt, a, ks), l, t};
}
