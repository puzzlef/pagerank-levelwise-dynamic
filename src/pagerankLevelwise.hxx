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

using std::vector;
using std::swap;




template <class G, class H, class T>
auto pagerankComponents(const G& x, const H& xt, const PagerankOptions<T>& o) {
  auto a = joinUntilSize(components(x, xt), o.minComponentSize);
  auto b = blockgraph(x, a);
  auto bks = topologicalSort(b);
  reorder(a, bks);
  return a;
}


template <class G, class C>
auto pagerankComponentSizes(const G& w, const C& wcs, const G& x, const C& xcs) {
  vector<int> a; bool fail = false;
  for (int i=0, W=wcs.size(), X=xcs.size(); i<X; i++) {
    if (!fail && i<W && componentsEqual(w, wcs[i], x, xcs[i])) a.push_back(-xcs[i].size());
    else { a.push_back(xcs[i].size()); fail = true; }
  }
  return a;
}


template <class T, class J>
int pagerankLevelwiseLoop(vector<T>& a, vector<T>& r, vector<T>& c, const vector<T>& f, const vector<int>& vfrom, const vector<int>& efrom, const vector<int>& vdata, J&& ns, int N, T p, T E, int L) {
  int v = 0; float l = 0;
  for (int n : ns) {
    if (n<0) { v += -n; continue; }
    l += pagerankMonolithicLoop(a, r, c, f, vfrom, efrom, vdata, v, v+n, N, p, E * (float(n)/N), L) * (float(n)/N);
    swap(a, r);
    v += n;
  }
  swap(a, r);
  return int(l);
}


// Find pagerank of components in topological order (pull, CSR, skip-comp).
// @param w  previous graph
// @param wt previous transpose graph, with vertex-data=out-degree
// @param x  current graph
// @param xt current transpose graph, with vertex-data=out-degree
// @param q initial ranks (optional)
// @param o options {damping=0.85, tolerance=1e-6, maxIterations=500}
// @returns {ranks, iterations, time}
template <class G, class H, class T=float>
PagerankResult<T> pagerankLevelwise(const G& w, const H& wt, const G& x, const H& xt, const vector<T> *q=nullptr, PagerankOptions<T> o={}) {
  T    p = o.damping;
  T    E = o.tolerance;
  int  L = o.maxIterations, l;
  int  N = xt.order();
  auto wcs = pagerankComponents(w, wt, o);
  auto xcs = pagerankComponents(x, xt, o);
  auto ns = pagerankComponentSizes(w, wcs, x, xcs);
  auto ks = join(xcs);
  auto vfrom = sourceOffsets(xt, ks);
  auto efrom = destinationIndices(xt, ks);
  auto vdata = vertexData(xt, ks);
  vector<T> a(N), r(N), c(N), f(N), qc;
  if (q) qc = compressContainer(xt, *q, ks);
  float t = measureDurationMarked([&](auto mark) {
    fill(a, T());
    if (q) copy(r, qc);
    else fill(r, T(1)/N);
    mark([&] { pagerankFactor(f, vfrom, efrom, vdata, 0, N, N, p); multiply(c, r, f); copy(a, r); });
    mark([&] { l = pagerankLevelwiseLoop(a, r, c, f, vfrom, efrom, vdata, ns, N, p, E, L); });
  }, o.repeat);
  return {decompressContainer(xt, a, ks), l, t};
}


// Find pagerank of components in topological order (pull, CSR).
// @param x  current graph
// @param xt current transpose graph, with vertex-data=out-degree
// @param q initial ranks (optional)
// @param o options {damping=0.85, tolerance=1e-6, maxIterations=500}
// @returns {ranks, iterations, time}
template <class G, class H, class T=float>
PagerankResult<T> pagerankLevelwise(const G& x, const H& xt, const vector<T> *q=nullptr, PagerankOptions<T> o={}) {
  DiGraph<> w; DiGraph<int> wt;
  return pagerankLevelwise(w, wt, x, xt, q, o);
}
