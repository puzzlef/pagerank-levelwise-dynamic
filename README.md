Performance of [levelwise] based static vs dynamic PageRank ([pull], [CSR],
[comp-50], [scaled-fill]).

This experiment was for comparing performance between:
1. Find **static** pagerank with *minimum component size* `50`.
2. Find **dynamic** pagerank, **scaling** old vertices, and using **1/N** for new vertices.

Each approach was attempted on a number of graphs, running each with multiple
batch sizes (`1`, `5`, `10`, `50`, ...). Each pagerank computation was run 5
times for both approaches to get a good time measure. **Levelwise** pagerank
is the [STIC-D algorithm], without **ICD** optimizations (using single-thread).
For some reason, dynamic pagerank becomes faster as batch size increases
initially, and then starts slowing down (as expected). This is only observed on
large graphs. I don't have an explanation for this yet. However, on average,
**dynamic** pagerank faster than the **static** approach.

All outputs are saved in [out/](out/) and a small part of the output is listed
here. Some [charts] are also included below, generated from [sheets]. The input
data used for this experiment is available at the
[Stanford Large Network Dataset Collection].

<br>

```bash
$ g++ -O3 main.cxx
$ ./a.out ~/data/email-Eu-core-temporal.txt

# (SHORTENED)
# Using graph email-Eu-core-temporal.txt ...
# Temporal edges: 332335
# order: 986 size: 24928 {}
#
# # Batch size 1e+0
# [00001.091 ms; 045 iters.] [0.0000e+0 err.] pagerankStatic
# [00000.038 ms; 002 iters.] [5.0336e-7 err.] pagerankDynamic
#
# # Batch size 5e+0
# [00001.091 ms; 045 iters.] [0.0000e+0 err.] pagerankStatic
# [00000.085 ms; 004 iters.] [1.4829e-6 err.] pagerankDynamic
#
# # Batch size 1e+1
# [00001.091 ms; 045 iters.] [0.0000e+0 err.] pagerankStatic
# [00000.109 ms; 005 iters.] [1.9689e-6 err.] pagerankDynamic
#
# # Batch size 5e+1
# [00001.091 ms; 045 iters.] [0.0000e+0 err.] pagerankStatic
# [00000.238 ms; 011 iters.] [4.4606e-6 err.] pagerankDynamic
#
# # Batch size 1e+2
# [00001.093 ms; 045 iters.] [0.0000e+0 err.] pagerankStatic
# [00000.313 ms; 014 iters.] [5.1184e-6 err.] pagerankDynamic
#
# # Batch size 5e+2
# [00001.091 ms; 045 iters.] [0.0000e+0 err.] pagerankStatic
# [00000.467 ms; 020 iters.] [4.7077e-6 err.] pagerankDynamic
#
# # Batch size 1e+3
# [00001.091 ms; 045 iters.] [0.0000e+0 err.] pagerankStatic
# [00000.520 ms; 022 iters.] [5.4688e-6 err.] pagerankDynamic
```

[![](https://i.imgur.com/mwCrwI8.gif)][sheets]
[![](https://i.imgur.com/nsITafb.gif)][sheets]

<br>
<br>

```bash
$ g++ -O3 main.cxx
$ ./a.out ~/data/sx-stackoverflow.txt

# (SHORTENED)
# Using graph sx-stackoverflow.txt ...
# Temporal edges: 63497051
# order: 2601975 size: 36233429 {}
#
# # Batch size 1e+0
# [02627.784 ms; 046 iters.] [0.0000e+0 err.] pagerankStatic
# [02128.730 ms; 035 iters.] [1.6053e-6 err.] pagerankDynamic
#
# # Batch size 5e+0
# [02619.256 ms; 046 iters.] [0.0000e+0 err.] pagerankStatic
# [02126.841 ms; 035 iters.] [1.7517e-6 err.] pagerankDynamic
#
# # Batch size 1e+1
# [02617.894 ms; 046 iters.] [0.0000e+0 err.] pagerankStatic
# [02101.227 ms; 034 iters.] [1.8761e-6 err.] pagerankDynamic
#
# # Batch size 5e+1
# [02599.442 ms; 046 iters.] [0.0000e+0 err.] pagerankStatic
# [02099.375 ms; 032 iters.] [2.2399e-6 err.] pagerankDynamic
#
# # Batch size 1e+2
# [02596.791 ms; 046 iters.] [0.0000e+0 err.] pagerankStatic
# [02126.262 ms; 031 iters.] [2.3886e-6 err.] pagerankDynamic
#
# # Batch size 5e+2
# [02596.925 ms; 046 iters.] [0.0000e+0 err.] pagerankStatic
# [02124.541 ms; 030 iters.] [2.9008e-6 err.] pagerankDynamic
#
# # Batch size 1e+3
# [02597.036 ms; 046 iters.] [0.0000e+0 err.] pagerankStatic
# [01952.306 ms; 029 iters.] [3.1536e-6 err.] pagerankDynamic
#
# # Batch size 5e+3
# [02599.763 ms; 046 iters.] [0.0000e+0 err.] pagerankStatic
# [02109.000 ms; 032 iters.] [3.5813e-6 err.] pagerankDynamic
#
# # Batch size 1e+4
# [02597.678 ms; 046 iters.] [0.0000e+0 err.] pagerankStatic
# [02319.547 ms; 035 iters.] [3.6413e-6 err.] pagerankDynamic
#
# # Batch size 5e+4
# [02605.443 ms; 046 iters.] [0.0000e+0 err.] pagerankStatic
# [02385.647 ms; 037 iters.] [3.7451e-6 err.] pagerankDynamic
#
# # Batch size 1e+5
# [02594.903 ms; 046 iters.] [0.0000e+0 err.] pagerankStatic
# [02318.656 ms; 038 iters.] [3.7420e-6 err.] pagerankDynamic
#
# # Batch size 5e+5
# [02608.896 ms; 046 iters.] [0.0000e+0 err.] pagerankStatic
# [02552.501 ms; 041 iters.] [3.6014e-6 err.] pagerankDynamic
```

[![](https://i.imgur.com/mfaPm7t.gif)][sheets]
[![](https://i.imgur.com/8CW5pyw.gif)][sheets]

<br>
<br>


## References

- [STIC-D: algorithmic techniques for efficient parallel pagerank computation on real-world graphs][STIC-D algorithm]
- [PageRank Algorithm, Mining massive Datasets (CS246), Stanford University](http://snap.stanford.edu/class/cs246-videos-2019/lec9_190205-cs246-720.mp4)
- [Stanford Large Network Dataset Collection]

<br>
<br>

[![](https://i.imgur.com/cL6ZNtU.jpg)](https://www.youtube.com/watch?v=xEfsE8H6sok)

[levelwise]: https://github.com/puzzlef/pagerank-monolithic-vs-levelwise
[pull]: https://github.com/puzzlef/pagerank-push-vs-pull
[CSR]: https://github.com/puzzlef/pagerank-class-vs-csr
[comp-50]: https://github.com/puzzlef/pagerank-levelwise-openmp-adjust-component-size
[scaled-fill]: https://github.com/puzzlef/pagerank-dynamic-adjust-ranks
[STIC-D algorithm]: https://www.slideshare.net/SubhajitSahu/sticd-algorithmic-techniques-for-efficient-parallel-pagerank-computation-on-realworld-graphs
[charts]: https://photos.app.goo.gl/rLTCfxrGoLosf1YHA
[sheets]: https://docs.google.com/spreadsheets/d/1T4LuZGJ07MjQ5zb6nPy27n255BqO2tJrZ50bLUzH0pI/edit?usp=sharing
[Stanford Large Network Dataset Collection]: http://snap.stanford.edu/data/index.html
