Checking the performance benefit of [levelwise] PageRank when **unchanged**
**components** are [skipped][skip-comp] ([pull], [CSR], [comp-50], [scaled-fill]).

This experiment was for comparing performance between:
1. Find **static** levelwise pagerank.
2. Find **dynamic** levelwise pagerank (process all components).
3. Find **dynamic** levelwise pagerank, [skipping unchanged components][skip-comp].

Each approach was attempted on a number of graphs, running each with multiple
batch sizes (`1`, `5`, `10`, `50`, ...). Each batch size was run with 5
different updates to graph, and each specific update was run 5 times for each
approach to get a good time measure. **Levelwise** pagerank is the
[STIC-D algorithm], without **ICD** optimizations (using single-thread).
On average, **skipping unchanged components** is **barely faster** than not
skipping.

All outputs are saved in [out](out/) and a small part of the output is listed
here. Some [charts] are also included below, generated from [sheets]. The input
data used for this experiment is available at ["graphs"] (for small ones), and
the [SuiteSparse Matrix Collection]. This experiment was done with guidance
from [Prof. Dip Sankar Banerjee] and [Prof. Kishore Kothapalli].

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
# [00289.478 ms; 055 iters.] [0.0000e+0 err.] pagerankStatic
#
# # Batch size 1e+0
# order: 281903.6 size: 2312670 {} [00288.784 ms; 055 iters.] [0.0000e+0 err.] pagerankStatic
# order: 281903.6 size: 2312670 {} [00011.943 ms; 003 iters.] [4.7413e-6 err.] pagerankDynamic
# order: 281903.6 size: 2312670 {} [00011.207 ms; 002 iters.] [4.8122e-6 err.] pagerankDynamic [skip-comp]
#
# # Batch size 5e+0
# order: 281903.6 size: 2312674.6 {} [00283.569 ms; 055 iters.] [0.0000e+0 err.] pagerankStatic
# order: 281903.6 size: 2312674.6 {} [00041.063 ms; 007 iters.] [5.7416e-6 err.] pagerankDynamic
# order: 281903.6 size: 2312674.6 {} [00040.629 ms; 007 iters.] [5.8932e-6 err.] pagerankDynamic [skip-comp]
#
# # Batch size 1e+1
# order: 281905 size: 2312680 {} [00287.039 ms; 055 iters.] [0.0000e+0 err.] pagerankStatic
# order: 281905 size: 2312680 {} [00052.546 ms; 009 iters.] [5.1295e-6 err.] pagerankDynamic
# order: 281905 size: 2312680 {} [00051.863 ms; 008 iters.] [5.1860e-6 err.] pagerankDynamic [skip-comp]
#
# # Batch size 5e+1
# order: 281911.8 size: 2312723.6 {} [00287.199 ms; 055 iters.] [0.0000e+0 err.] pagerankStatic
# order: 281911.8 size: 2312723.6 {} [00075.264 ms; 012 iters.] [5.6967e-6 err.] pagerankDynamic
# order: 281911.8 size: 2312723.6 {} [00074.761 ms; 012 iters.] [5.7511e-6 err.] pagerankDynamic [skip-comp]
#
# # Batch size 1e+2
# order: 281919.6 size: 2312777.8 {} [00291.606 ms; 056 iters.] [0.0000e+0 err.] pagerankStatic
# order: 281919.6 size: 2312777.8 {} [00097.839 ms; 016 iters.] [5.7187e-6 err.] pagerankDynamic
# order: 281919.6 size: 2312777.8 {} [00097.574 ms; 016 iters.] [5.7523e-6 err.] pagerankDynamic [skip-comp]
#
# # Batch size 5e+2
# order: 281999.4 size: 2313216.8 {} [00300.087 ms; 057 iters.] [0.0000e+0 err.] pagerankStatic
# order: 281999.4 size: 2313216.8 {} [00144.393 ms; 025 iters.] [5.6139e-6 err.] pagerankDynamic
# order: 281999.4 size: 2313216.8 {} [00144.469 ms; 025 iters.] [5.6221e-6 err.] pagerankDynamic [skip-comp]
#
# # Batch size 1e+3
# order: 282100.4 size: 2313765.4 {} [00305.483 ms; 057 iters.] [0.0000e+0 err.] pagerankStatic
# order: 282100.4 size: 2313765.4 {} [00172.303 ms; 030 iters.] [6.1304e-6 err.] pagerankDynamic
# order: 282100.4 size: 2313765.4 {} [00171.817 ms; 030 iters.] [6.1303e-6 err.] pagerankDynamic [skip-comp]
#
# # Batch size 5e+3
# order: 282786.4 size: 2318109.8 {} [00319.801 ms; 058 iters.] [0.0000e+0 err.] pagerankStatic
# order: 282786.4 size: 2318109.8 {} [00222.559 ms; 040 iters.] [6.5054e-6 err.] pagerankDynamic
# order: 282786.4 size: 2318109.8 {} [00222.381 ms; 040 iters.] [6.5050e-6 err.] pagerankDynamic [skip-comp]
#
# # Batch size 1e+4
# order: 283684.6 size: 2323537.2 {} [00328.964 ms; 058 iters.] [0.0000e+0 err.] pagerankStatic
# order: 283684.6 size: 2323537.2 {} [00250.695 ms; 044 iters.] [6.0296e-6 err.] pagerankDynamic
# order: 283684.6 size: 2323537.2 {} [00249.633 ms; 044 iters.] [6.0296e-6 err.] pagerankDynamic [skip-comp]
#
# # Batch size 5e+4
# order: 289659.8 size: 2366234.4 {} [00355.759 ms; 055 iters.] [0.0000e+0 err.] pagerankStatic
# order: 289659.8 size: 2366234.4 {} [00304.739 ms; 049 iters.] [5.4007e-6 err.] pagerankDynamic
# order: 289659.8 size: 2366234.4 {} [00304.992 ms; 049 iters.] [5.4007e-6 err.] pagerankDynamic [skip-comp]
#
# # Batch size 1e+5
# order: 295331.4 size: 2418311.4 {} [00367.519 ms; 054 iters.] [0.0000e+0 err.] pagerankStatic
# order: 295331.4 size: 2418311.4 {} [00331.725 ms; 049 iters.] [5.8706e-6 err.] pagerankDynamic
# order: 295331.4 size: 2418311.4 {} [00330.377 ms; 049 iters.] [5.8706e-6 err.] pagerankDynamic [skip-comp]
#
# # Batch size 5e+5
# order: 308987.4 size: 2817184 {} [00337.737 ms; 042 iters.] [0.0000e+0 err.] pagerankStatic
# order: 308987.4 size: 2817184 {} [00351.875 ms; 044 iters.] [8.6573e-6 err.] pagerankDynamic
# order: 308987.4 size: 2817184 {} [00351.934 ms; 044 iters.] [8.6573e-6 err.] pagerankDynamic [skip-comp]
#
# # Batch size 1e+6
# order: 310048.8 size: 3313740.2 {} [00319.345 ms; 035 iters.] [0.0000e+0 err.] pagerankStatic
# order: 310048.8 size: 3313740.2 {} [00353.927 ms; 039 iters.] [1.2086e-6 err.] pagerankDynamic
# order: 310048.8 size: 3313740.2 {} [00353.871 ms; 039 iters.] [1.2086e-6 err.] pagerankDynamic [skip-comp]
#
# ...
```

[![](https://i.imgur.com/vjuPtlS.gif)][sheets]
[![](https://i.imgur.com/0v0yeon.gif)][sheets]

<br>
<br>


## References

- [STIC-D: algorithmic techniques for efficient parallel pagerank computation on real-world graphs][STIC-D algorithm]
- [PageRank Algorithm, Mining massive Datasets (CS246), Stanford University](https://www.youtube.com/watch?v=ke9g8hB0MEo)
- [SuiteSparse Matrix Collection]

<br>
<br>

[![](https://i.imgur.com/YWmqWAg.jpg)](https://www.youtube.com/watch?v=SoiKp2oSUl0&t=1554s)

[Prof. Dip Sankar Banerjee]: https://sites.google.com/site/dipsankarban/
[Prof. Kishore Kothapalli]: https://cstar.iiit.ac.in/~kkishore/
[STIC-D algorithm]: https://www.slideshare.net/SubhajitSahu/sticd-algorithmic-techniques-for-efficient-parallel-pagerank-computation-on-realworld-graphs
[SuiteSparse Matrix Collection]: https://suitesparse-collection-website.herokuapp.com
["graphs"]: https://github.com/puzzlef/graphs
[levelwise]: https://github.com/puzzlef/pagerank-monolithic-vs-levelwise
[pull]: https://github.com/puzzlef/pagerank-push-vs-pull
[CSR]: https://github.com/puzzlef/pagerank-class-vs-csr
[comp-50]: https://github.com/puzzlef/pagerank-levelwise-adjust-component-size
[skip-comp]: https://github.com/puzzlef/pagerank-levelwise-dynamic-validate-skip-unchanged-components
[scaled-fill]: https://github.com/puzzlef/pagerank-dynamic-adjust-ranks
[charts]: https://photos.app.goo.gl/BVK4d6NiwgFdpG718
[sheets]: https://docs.google.com/spreadsheets/d/1u2V3eIblQk9DkNK3NXlCpSaGI5vEkFUaFI_hOOyybxg/edit?usp=sharing
