Performance of static vs dynamic [levelwise] PageRank ([pull], [CSR],
[comp-50], [skip-comp], [scaled-fill]).

This experiment was for comparing performance between:
1. Find static [monolithic][levelwise] pagerank of updated graph.
2. Find **static** [levelwise] pagerank of updated graph.
3. Find **dynamic** [levelwise] pagerank of updated graph.

Each approach was attempted on a number of graphs, running each with multiple
batch sizes (`1`, `5`, `10`, `50`, ...). Each batch size was run with 5
different updates to graph, and each specific update was run 5 times for each
approach to get a good time measure. **Levelwise** pagerank is the
[STIC-D algorithm], without **ICD** optimizations (using single-thread).
Indeed, **dynamic levelwise** pagerank is **faster** than the *static* approach
for many batch sizes.

All outputs are saved in [out](out/) and a small part of the output is listed
here. Some [charts] are also included below, generated from [sheets]. The input
data used for this experiment is available at ["graphs"] (for small ones), and
the [SuiteSparse Matrix Collection].

<br>

```bash
$ g++ -O3 main.cxx
$ ./a.out ~/data/min-1DeadEnd.mtx
$ ./a.out ~/data/min-2SCC.mtx
$ ...

# (SHORTENED)
# ...
#
# Loading graph web-Stanford.mtx ...
# order: 281903 size: 2312670 {}
# [00444.150 ms; 063 iters.] [0.0000e+0 err.] pagerankMonolithic [static]
#
# # Batch size 1e+0
# order: 281903.2 size: 2312670 {} [00435.871 ms; 063 iters.] [0.0000e+0 err.] pagerankMonolithic [static]
# order: 281903.2 size: 2312670 {} [00275.550 ms; 055 iters.] [4.4412e-6 err.] pagerankLevelwise [static]
# order: 281903.2 size: 2312670 {} [00011.404 ms; 002 iters.] [1.7593e-6 err.] pagerankLevelwise [dynamic]
#
# # Batch size 5e+0
# order: 281904 size: 2312674.4 {} [00433.913 ms; 063 iters.] [0.0000e+0 err.] pagerankMonolithic [static]
# order: 281904 size: 2312674.4 {} [00275.051 ms; 055 iters.] [4.1328e-6 err.] pagerankLevelwise [static]
# order: 281904 size: 2312674.4 {} [00034.792 ms; 006 iters.] [3.2651e-6 err.] pagerankLevelwise [dynamic]
#
# # Batch size 1e+1
# order: 281905.8 size: 2312681.2 {} [00436.958 ms; 063 iters.] [0.0000e+0 err.] pagerankMonolithic [static]
# order: 281905.8 size: 2312681.2 {} [00274.929 ms; 055 iters.] [4.0723e-6 err.] pagerankLevelwise [static]
# order: 281905.8 size: 2312681.2 {} [00052.611 ms; 009 iters.] [3.3602e-6 err.] pagerankLevelwise [dynamic]
#
# # Batch size 5e+1
# order: 281913.2 size: 2312723.8 {} [00437.902 ms; 063 iters.] [0.0000e+0 err.] pagerankMonolithic [static]
# order: 281913.2 size: 2312723.8 {} [00279.574 ms; 056 iters.] [3.9809e-6 err.] pagerankLevelwise [static]
# order: 281913.2 size: 2312723.8 {} [00076.524 ms; 013 iters.] [4.2255e-6 err.] pagerankLevelwise [dynamic]
#
# # Batch size 1e+2
# order: 281919.8 size: 2312779 {} [00440.232 ms; 063 iters.] [0.0000e+0 err.] pagerankMonolithic [static]
# order: 281919.8 size: 2312779 {} [00281.765 ms; 056 iters.] [4.0137e-6 err.] pagerankLevelwise [static]
# order: 281919.8 size: 2312779 {} [00105.659 ms; 018 iters.] [4.3918e-6 err.] pagerankLevelwise [dynamic]
#
# # Batch size 5e+2
# order: 281994.2 size: 2313212.8 {} [00438.127 ms; 063 iters.] [0.0000e+0 err.] pagerankMonolithic [static]
# order: 281994.2 size: 2313212.8 {} [00292.174 ms; 057 iters.] [3.5737e-6 err.] pagerankLevelwise [static]
# order: 281994.2 size: 2313212.8 {} [00143.936 ms; 026 iters.] [4.7993e-6 err.] pagerankLevelwise [dynamic]
#
# # Batch size 1e+3
# order: 282083.4 size: 2313762.6 {} [00438.341 ms; 063 iters.] [0.0000e+0 err.] pagerankMonolithic [static]
# order: 282083.4 size: 2313762.6 {} [00297.578 ms; 058 iters.] [3.5121e-6 err.] pagerankLevelwise [static]
# order: 282083.4 size: 2313762.6 {} [00169.553 ms; 031 iters.] [4.8817e-6 err.] pagerankLevelwise [dynamic]
#
# # Batch size 5e+3
# order: 282787.6 size: 2318096.8 {} [00439.086 ms; 063 iters.] [0.0000e+0 err.] pagerankMonolithic [static]
# order: 282787.6 size: 2318096.8 {} [00310.246 ms; 058 iters.] [3.4964e-6 err.] pagerankLevelwise [static]
# order: 282787.6 size: 2318096.8 {} [00222.063 ms; 041 iters.] [5.0511e-6 err.] pagerankLevelwise [dynamic]
#
# # Batch size 1e+4
# order: 283696.4 size: 2323533.6 {} [00433.409 ms; 062 iters.] [0.0000e+0 err.] pagerankMonolithic [static]
# order: 283696.4 size: 2323533.6 {} [00320.906 ms; 058 iters.] [3.4256e-6 err.] pagerankLevelwise [static]
# order: 283696.4 size: 2323533.6 {} [00242.370 ms; 044 iters.] [4.8888e-6 err.] pagerankLevelwise [dynamic]
#
# # Batch size 5e+4
# order: 289693 size: 2366222.8 {} [00419.136 ms; 059 iters.] [0.0000e+0 err.] pagerankMonolithic [static]
# order: 289693 size: 2366222.8 {} [00337.880 ms; 055 iters.] [5.2480e-6 err.] pagerankLevelwise [static]
# order: 289693 size: 2366222.8 {} [00291.496 ms; 049 iters.] [5.0268e-6 err.] pagerankLevelwise [dynamic]
#
# # Batch size 1e+5
# order: 295284 size: 2418286.6 {} [00410.074 ms; 057 iters.] [0.0000e+0 err.] pagerankMonolithic [static]
# order: 295284 size: 2418286.6 {} [00345.830 ms; 054 iters.] [6.9942e-6 err.] pagerankLevelwise [static]
# order: 295284 size: 2418286.6 {} [00309.389 ms; 048 iters.] [5.1309e-6 err.] pagerankLevelwise [dynamic]
#
# # Batch size 5e+5
# order: 308993.8 size: 2817128.6 {} [00425.298 ms; 054 iters.] [0.0000e+0 err.] pagerankMonolithic [static]
# order: 308993.8 size: 2817128.6 {} [00317.386 ms; 042 iters.] [1.0004e-5 err.] pagerankLevelwise [static]
# order: 308993.8 size: 2817128.6 {} [00330.857 ms; 044 iters.] [5.2392e-6 err.] pagerankLevelwise [dynamic]
#
# # Batch size 1e+6
# order: 310055 size: 3313707.6 {} [00418.040 ms; 048 iters.] [0.0000e+0 err.] pagerankMonolithic [static]
# order: 310055 size: 3313707.6 {} [00305.578 ms; 036 iters.] [4.4362e-6 err.] pagerankLevelwise [static]
# order: 310055 size: 3313707.6 {} [00338.449 ms; 040 iters.] [5.5595e-6 err.] pagerankLevelwise [dynamic]
#
# ...
```

[![](https://i.imgur.com/GXjAjZW.gif)][sheets]
[![](https://i.imgur.com/3HKmnJw.gif)][sheets]

<br>
<br>


## References

- [STIC-D: algorithmic techniques for efficient parallel pagerank computation on real-world graphs][STIC-D algorithm]
- [PageRank Algorithm, Mining massive Datasets (CS246), Stanford University](http://snap.stanford.edu/class/cs246-videos-2019/lec9_190205-cs246-720.mp4)
- [SuiteSparse Matrix Collection]

<br>
<br>

[![](https://i.imgur.com/pH5CTr2.jpg)](https://www.youtube.com/watch?v=rskLxOHNF3k)

[levelwise]: https://github.com/puzzlef/pagerank-monolithic-vs-levelwise
[pull]: https://github.com/puzzlef/pagerank-push-vs-pull
[CSR]: https://github.com/puzzlef/pagerank-class-vs-csr
[comp-50]: https://github.com/puzzlef/pagerank-levelwise-adjust-component-size
[skip-comp]: https://github.com/puzzlef/pagerank-levelwise-dynamic-validate-skip-unchanged-components
[scaled-fill]: https://github.com/puzzlef/pagerank-dynamic-adjust-ranks
[STIC-D algorithm]: https://www.slideshare.net/SubhajitSahu/sticd-algorithmic-techniques-for-efficient-parallel-pagerank-computation-on-realworld-graphs
[charts]: https://photos.app.goo.gl/cvr79cUjgicXM5KDA
[sheets]: https://docs.google.com/spreadsheets/d/1sQ1FXmv9rc2liBxnB-2Qf_rfJVZQWKiO_5AO7hu1Rl0/edit?usp=sharing
["graphs"]: https://github.com/puzzlef/graphs
[SuiteSparse Matrix Collection]: https://suitesparse-collection-website.herokuapp.com
