Performance of levelwise based static vs dynamic PageRank ([pull], [CSR],
[comp-50], [scaled-fill]).

This experiment was for comparing performance between:
1. Find static pagerank of updated graph with [standard algorithm] (**monolithic**).
2. Find **static** pagerank with [levelwise algorithm] and *minimum component size* `50`.
3. Find **dynamic** pagerank with levelwise algorithm, **scaling** old vertices, and using **1/N** for new vertices.

Each approach was attempted on a number of graphs, running each with multiple
batch sizes (`1`, `5`, `10`, `50`, ...). Each batch size was run with 5
different updates to graph, and each specific update was run 5 times for each
approach to get a good time measure. **Levelwise** pagerank is the
[STIC-D algorithm], without **ICD** optimizations (using single-thread).
On average, **dynamic** *levelwise* pagerank faster than the **static** approach.

All outputs are saved in [out/](out/) and a small part of the output is listed
here. Some [charts] are also included below, generated from [sheets]. The input
data used for this experiment is available at the
[Stanford Large Network Dataset Collection].

<br>

```bash
$ g++ -O3 main.cxx
$ ./a.out ~/data/web-Stanford.mtx

# (SHORTENED)
# Loading graph web-Stanford.mtx ...
# order: 281905 size: 2312671 {}
# [00470.739 ms; 063 iters.] [0.0000e+0 err.] pagerankMonolithic
#
# # Batch size 1e+0
# order: 281903.6 size: 2312670.4 {} [00474.657 ms; 063 iters.] [0.0000e+0 err.] pagerankMonolithic
# order: 281903.6 size: 2312670.4 {} [00272.149 ms; 059 iters.] [4.6930e-6 err.] pagerankLevelwise
# order: 281903.6 size: 2312670.4 {} [00053.976 ms; 020 iters.] [3.2146e-6 err.] pagerankLevelwise [dynamic]
#
# # Batch size 5e+0
# order: 281904 size: 2312674.6 {} [00468.401 ms; 063 iters.] [0.0000e+0 err.] pagerankMonolithic
# order: 281904 size: 2312674.6 {} [00282.219 ms; 061 iters.] [5.3450e-6 err.] pagerankLevelwise
# order: 281904 size: 2312674.6 {} [00076.729 ms; 023 iters.] [4.9250e-6 err.] pagerankLevelwise [dynamic]
#
# # Batch size 1e+1
# order: 281904.8 size: 2312679.8 {} [00471.123 ms; 063 iters.] [0.0000e+0 err.] pagerankMonolithic
# order: 281904.8 size: 2312679.8 {} [00261.659 ms; 058 iters.] [4.3289e-6 err.] pagerankLevelwise
# order: 281904.8 size: 2312679.8 {} [00120.335 ms; 030 iters.] [4.9927e-6 err.] pagerankLevelwise [dynamic]
#
# # Batch size 5e+1
# order: 281911.4 size: 2312723.8 {} [00468.246 ms; 063 iters.] [0.0000e+0 err.] pagerankMonolithic
# order: 281911.4 size: 2312723.8 {} [00265.751 ms; 059 iters.] [4.4554e-6 err.] pagerankLevelwise
# order: 281911.4 size: 2312723.8 {} [00175.687 ms; 039 iters.] [5.0645e-6 err.] pagerankLevelwise [dynamic]
#
# # Batch size 1e+2
# order: 281921.6 size: 2312775.6 {} [00467.646 ms; 063 iters.] [0.0000e+0 err.] pagerankMonolithic
# order: 281921.6 size: 2312775.6 {} [00273.600 ms; 060 iters.] [4.5840e-6 err.] pagerankLevelwise
# order: 281921.6 size: 2312775.6 {} [00187.408 ms; 041 iters.] [5.1768e-6 err.] pagerankLevelwise [dynamic]
#
# # Batch size 5e+2
# order: 281988.8 size: 2313211 {} [00475.009 ms; 063 iters.] [0.0000e+0 err.] pagerankMonolithic
# order: 281988.8 size: 2313211 {} [00282.947 ms; 061 iters.] [4.2973e-6 err.] pagerankLevelwise
# order: 281988.8 size: 2313211 {} [00274.067 ms; 056 iters.] [5.5608e-6 err.] pagerankLevelwise [dynamic]
#
# # Batch size 1e+3
# order: 282083 size: 2313756 {} [00474.187 ms; 063 iters.] [0.0000e+0 err.] pagerankMonolithic
# order: 282083 size: 2313756 {} [00279.321 ms; 060 iters.] [3.7562e-6 err.] pagerankLevelwise
# order: 282083 size: 2313756 {} [00195.390 ms; 042 iters.] [5.4178e-6 err.] pagerankLevelwise [dynamic]
#
# # Batch size 5e+3
# order: 282797 size: 2318116 {} [00469.349 ms; 063 iters.] [0.0000e+0 err.] pagerankMonolithic
# order: 282797 size: 2318116 {} [00318.607 ms; 064 iters.] [4.9286e-6 err.] pagerankLevelwise
# order: 282797 size: 2318116 {} [00282.029 ms; 057 iters.] [5.7355e-6 err.] pagerankLevelwise [dynamic]
#
# # Batch size 1e+4
# order: 283667 size: 2323529.6 {} [00462.717 ms; 062 iters.] [0.0000e+0 err.] pagerankMonolithic
# order: 283667 size: 2323529.6 {} [00327.875 ms; 064 iters.] [4.9259e-6 err.] pagerankLevelwise
# order: 283667 size: 2323529.6 {} [00300.609 ms; 059 iters.] [5.9095e-6 err.] pagerankLevelwise [dynamic]
#
# # Batch size 5e+4
# order: 289675.2 size: 2366237 {} [00453.141 ms; 059 iters.] [0.0000e+0 err.] pagerankMonolithic
# order: 289675.2 size: 2366237 {} [00344.715 ms; 061 iters.] [5.8546e-6 err.] pagerankLevelwise
# order: 289675.2 size: 2366237 {} [00369.381 ms; 066 iters.] [6.2114e-6 err.] pagerankLevelwise [dynamic]
#
# # Batch size 1e+5
# order: 295291 size: 2418266.2 {} [00441.054 ms; 057 iters.] [0.0000e+0 err.] pagerankMonolithic
# order: 295291 size: 2418266.2 {} [00409.150 ms; 067 iters.] [7.5346e-6 err.] pagerankLevelwise
# order: 295291 size: 2418266.2 {} [00401.787 ms; 066 iters.] [7.3301e-6 err.] pagerankLevelwise [dynamic]
#
# # Batch size 5e+5
# order: 308976.4 size: 2817155.4 {} [00455.233 ms; 053 iters.] [0.0000e+0 err.] pagerankMonolithic
# order: 308976.4 size: 2817155.4 {} [00379.538 ms; 053 iters.] [9.4779e-6 err.] pagerankLevelwise
# order: 308976.4 size: 2817155.4 {} [00370.324 ms; 049 iters.] [5.9380e-6 err.] pagerankLevelwise [dynamic]
#
# # Batch size 1e+6
# order: 310051.2 size: 3313741.6 {} [00387.216 ms; 049 iters.] [0.0000e+0 err.] pagerankMonolithic
# order: 310051.2 size: 3313741.6 {} [00510.640 ms; 066 iters.] [9.4354e-6 err.] pagerankLevelwise
# order: 310051.2 size: 3313741.6 {} [00424.974 ms; 054 iters.] [7.6112e-6 err.] pagerankLevelwise [dynamic]
```

[![](https://i.imgur.com/qcnQm9d.png)][sheets]
[![](https://i.imgur.com/GcfV2MT.png)][sheets]

<br>
<br>


## References

- [STIC-D: algorithmic techniques for efficient parallel pagerank computation on real-world graphs][STIC-D algorithm]
- [PageRank Algorithm, Mining massive Datasets (CS246), Stanford University](http://snap.stanford.edu/class/cs246-videos-2019/lec9_190205-cs246-720.mp4)
- [Stanford Large Network Dataset Collection]

<br>
<br>

[![](https://i.imgur.com/pH5CTr2.jpg)](https://www.youtube.com/watch?v=rskLxOHNF3k)

[pull]: https://github.com/puzzlef/pagerank-push-vs-pull
[CSR]: https://github.com/puzzlef/pagerank-class-vs-csr
[comp-50]: https://github.com/puzzlef/pagerank-levelwise-openmp-adjust-component-size
[scaled-fill]: https://github.com/puzzlef/pagerank-dynamic-adjust-ranks
[standard algorithm]: https://github.com/puzzlef/pagerank-monolithic-vs-levelwise
[levelwise algorithm]: https://github.com/puzzlef/pagerank-monolithic-vs-levelwise
[STIC-D algorithm]: https://www.slideshare.net/SubhajitSahu/sticd-algorithmic-techniques-for-efficient-parallel-pagerank-computation-on-realworld-graphs
[charts]: https://photos.app.goo.gl/Mb8BgHi9npT3ePAn6
[sheets]: https://docs.google.com/spreadsheets/d/1USB2k3b7gE8GP15CrlGB-fYXbpxzFfH-cGDgjrg8SdE/edit?usp=sharing
[Stanford Large Network Dataset Collection]: http://snap.stanford.edu/data/index.html
