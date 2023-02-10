Performance of **static** vs **dynamic** [levelwise] PageRank ([pull], [CSR],
[skip-teleport], [compute-10], [skip-comp], [scaled-fill]).

This experiment was for comparing performance between:
1. Find **static** [monolithic] pagerank of updated graph.
2. Find **dynamic** [monolithic] pagerank of updated graph.
3. Find **static** [levelwise] pagerank of updated graph.
4. Find **dynamic** [levelwise] pagerank of updated graph.

Each approach was attempted on a number of graphs, running each with multiple
batch sizes (`1`, `5`, `10`, `50`, ...). Each batch size was run with 5
different updates to graph, and each specific update was run 5 times for each
approach to get a good time measure. **Levelwise** pagerank is the
[STIC-D algorithm], without **ICD** optimizations (using single-thread).
Indeed, **dynamic levelwise** pagerank is **faster** than the *static* approach
for many batch sizes.

All outputs are saved in [gist] and a small part of the output is listed
here. Some [charts] are also included below, generated from [sheets]. The input
data used for this experiment is available at ["graphs"] (for small ones), and
the [SuiteSparse Matrix Collection]. For previous experiments, see [branches].
This experiment was done with guidance from [Prof. Dip Sankar Banerjee] and
[Prof. Kishore Kothapalli].

<br>

```bash
$ g++ -O3 main.cxx
$ ./a.out ~/data/min-1DeadEnd.mtx
$ ./a.out ~/data/min-2SCC.mtx
$ ...

# (SHORTENED)
# ...
#
# Loading graph soc-LiveJournal1.mtx ...
# order: 4847571 size: 69532893 {}
# [12668.787 ms; 058 iters.] [0.0000e+0 err.] pagerankMonolithic [static]
#
# # Batch size 1e+0
# order: 4847571 size: 69532893 {} [14646.302 ms; 058 iters.] [0.0000e+0 err.] pagerankMonolithic [static]
# order: 4847571 size: 69532893 {} [00260.511 ms; 001 iters.] [8.2087e-7 err.] pagerankMonolithic [dynamic]
# order: 4847571 size: 69532893 {} [11125.110 ms; 048 iters.] [4.3743e-6 err.] pagerankLevelwise [static]
# order: 4847571 size: 69532893 {} [00307.653 ms; 001 iters.] [1.9579e-6 err.] pagerankLevelwise [dynamic]
#
# # Batch size 5e+0
# order: 4847571.8 size: 69532897.2 {} [13682.162 ms; 058 iters.] [0.0000e+0 err.] pagerankMonolithic [static]
# order: 4847571.8 size: 69532897.2 {} [00387.617 ms; 002 iters.] [1.4035e-6 err.] pagerankMonolithic [dynamic]
# order: 4847571.8 size: 69532897.2 {} [11802.027 ms; 048 iters.] [4.5082e-6 err.] pagerankLevelwise [static]
# order: 4847571.8 size: 69532897.2 {} [00425.332 ms; 001 iters.] [2.4458e-6 err.] pagerankLevelwise [dynamic]
#
# # Batch size 1e+1
# order: 4847572.4 size: 69532902.6 {} [13843.962 ms; 058 iters.] [0.0000e+0 err.] pagerankMonolithic [static]
# order: 4847572.4 size: 69532902.6 {} [00817.951 ms; 003 iters.] [2.5009e-6 err.] pagerankMonolithic [dynamic]
# order: 4847572.4 size: 69532902.6 {} [11042.868 ms; 048 iters.] [4.3755e-6 err.] pagerankLevelwise [static]
# order: 4847572.4 size: 69532902.6 {} [00643.971 ms; 002 iters.] [3.0971e-6 err.] pagerankLevelwise [dynamic]
#
# # Batch size 5e+1
# order: 4847579.2 size: 69532945.4 {} [14503.045 ms; 058 iters.] [0.0000e+0 err.] pagerankMonolithic [static]
# order: 4847579.2 size: 69532945.4 {} [01527.028 ms; 006 iters.] [3.7688e-6 err.] pagerankMonolithic [dynamic]
# order: 4847579.2 size: 69532945.4 {} [11322.564 ms; 048 iters.] [4.3753e-6 err.] pagerankLevelwise [static]
# order: 4847579.2 size: 69532945.4 {} [01384.388 ms; 005 iters.] [3.9506e-6 err.] pagerankLevelwise [dynamic]
#
# # Batch size 1e+2
# order: 4847593.6 size: 69533002.4 {} [14422.219 ms; 058 iters.] [0.0000e+0 err.] pagerankMonolithic [static]
# order: 4847593.6 size: 69533002.4 {} [01719.306 ms; 007 iters.] [4.4769e-6 err.] pagerankMonolithic [dynamic]
# order: 4847593.6 size: 69533002.4 {} [11850.397 ms; 048 iters.] [4.6429e-6 err.] pagerankLevelwise [static]
# order: 4847593.6 size: 69533002.4 {} [01493.358 ms; 005 iters.] [4.4062e-6 err.] pagerankLevelwise [dynamic]
#
# # Batch size 5e+2
# order: 4847664.2 size: 69533438.4 {} [14351.504 ms; 058 iters.] [0.0000e+0 err.] pagerankMonolithic [static]
# order: 4847664.2 size: 69533438.4 {} [03126.178 ms; 013 iters.] [5.4575e-6 err.] pagerankMonolithic [dynamic]
# order: 4847664.2 size: 69533438.4 {} [11168.244 ms; 048 iters.] [4.5073e-6 err.] pagerankLevelwise [static]
# order: 4847664.2 size: 69533438.4 {} [02511.217 ms; 009 iters.] [4.6976e-6 err.] pagerankLevelwise [dynamic]
#
# # Batch size 1e+3
# order: 4847754.6 size: 69533982.8 {} [14298.010 ms; 058 iters.] [0.0000e+0 err.] pagerankMonolithic [static]
# order: 4847754.6 size: 69533982.8 {} [03735.319 ms; 015 iters.] [5.9059e-6 err.] pagerankMonolithic [dynamic]
# order: 4847754.6 size: 69533982.8 {} [11098.437 ms; 048 iters.] [4.1063e-6 err.] pagerankLevelwise [static]
# order: 4847754.6 size: 69533982.8 {} [02806.995 ms; 010 iters.] [5.0374e-6 err.] pagerankLevelwise [dynamic]
#
# # Batch size 5e+3
# order: 4848473.8 size: 69538341.6 {} [13779.579 ms; 058 iters.] [0.0000e+0 err.] pagerankMonolithic [static]
# order: 4848473.8 size: 69538341.6 {} [05644.183 ms; 023 iters.] [6.3678e-6 err.] pagerankMonolithic [dynamic]
# order: 4848473.8 size: 69538341.6 {} [11370.945 ms; 048 iters.] [4.5057e-6 err.] pagerankLevelwise [static]
# order: 4848473.8 size: 69538341.6 {} [03748.607 ms; 014 iters.] [5.1052e-6 err.] pagerankLevelwise [dynamic]
#
# # Batch size 1e+4
# order: 4849387 size: 69543816.6 {} [13892.167 ms; 058 iters.] [0.0000e+0 err.] pagerankMonolithic [static]
# order: 4849387 size: 69543816.6 {} [06480.091 ms; 027 iters.] [6.6531e-6 err.] pagerankMonolithic [dynamic]
# order: 4849387 size: 69543816.6 {} [11111.501 ms; 048 iters.] [4.3712e-6 err.] pagerankLevelwise [static]
# order: 4849387 size: 69543816.6 {} [04311.836 ms; 017 iters.] [4.9571e-6 err.] pagerankLevelwise [dynamic]
#
# # Batch size 5e+4
# order: 4856570.4 size: 69587387.4 {} [14690.137 ms; 058 iters.] [0.0000e+0 err.] pagerankMonolithic [static]
# order: 4856570.4 size: 69587387.4 {} [09296.277 ms; 036 iters.] [6.9243e-6 err.] pagerankMonolithic [dynamic]
# order: 4856570.4 size: 69587387.4 {} [11539.316 ms; 048 iters.] [4.7576e-6 err.] pagerankLevelwise [static]
# order: 4856570.4 size: 69587387.4 {} [06218.165 ms; 025 iters.] [5.2890e-6 err.] pagerankLevelwise [dynamic]
#
# # Batch size 1e+5
# order: 4865395.4 size: 69641767.2 {} [15206.625 ms; 058 iters.] [0.0000e+0 err.] pagerankMonolithic [static]
# order: 4865395.4 size: 69641767.2 {} [10402.461 ms; 040 iters.] [6.9157e-6 err.] pagerankMonolithic [dynamic]
# order: 4865395.4 size: 69641767.2 {} [11337.619 ms; 048 iters.] [4.4500e-6 err.] pagerankLevelwise [static]
# order: 4865395.4 size: 69641767.2 {} [07077.232 ms; 028 iters.] [4.7922e-6 err.] pagerankLevelwise [dynamic]
#
# # Batch size 5e+5
# order: 4930425.6 size: 70072376.2 {} [14456.011 ms; 058 iters.] [0.0000e+0 err.] pagerankMonolithic [static]
# order: 4930425.6 size: 70072376.2 {} [12216.102 ms; 049 iters.] [6.5462e-6 err.] pagerankMonolithic [dynamic]
# order: 4930425.6 size: 70072376.2 {} [12107.682 ms; 048 iters.] [4.3418e-6 err.] pagerankLevelwise [static]
# order: 4930425.6 size: 70072376.2 {} [08950.657 ms; 036 iters.] [4.6610e-6 err.] pagerankLevelwise [dynamic]
#
# # Batch size 1e+6
# order: 4999322.4 size: 70601643.8 {} [15158.798 ms; 058 iters.] [0.0000e+0 err.] pagerankMonolithic [static]
# order: 4999322.4 size: 70601643.8 {} [13570.468 ms; 052 iters.] [6.3167e-6 err.] pagerankMonolithic [dynamic]
# order: 4999322.4 size: 70601643.8 {} [11772.159 ms; 047 iters.] [4.8520e-6 err.] pagerankLevelwise [static]
# order: 4999322.4 size: 70601643.8 {} [09941.125 ms; 039 iters.] [5.1141e-6 err.] pagerankLevelwise [dynamic]
#
# # Batch size 5e+6
# order: 5258409.4 size: 74648491.8 {} [16121.553 ms; 058 iters.] [0.0000e+0 err.] pagerankMonolithic [static]
# order: 5258409.4 size: 74648491.8 {} [15813.341 ms; 056 iters.] [4.0638e-6 err.] pagerankMonolithic [dynamic]
# order: 5258409.4 size: 74648491.8 {} [14045.177 ms; 048 iters.] [4.4396e-6 err.] pagerankLevelwise [static]
# order: 5258409.4 size: 74648491.8 {} [12739.185 ms; 045 iters.] [5.3607e-6 err.] pagerankLevelwise [dynamic]
#
# # Batch size 1e+7
# order: 5321133.4 size: 79595609.8 {} [17086.229 ms; 056 iters.] [0.0000e+0 err.] pagerankMonolithic [static]
# order: 5321133.4 size: 79595609.8 {} [17617.048 ms; 055 iters.] [2.5437e-6 err.] pagerankMonolithic [dynamic]
# order: 5321133.4 size: 79595609.8 {} [15693.925 ms; 047 iters.] [5.0412e-6 err.] pagerankLevelwise [static]
# order: 5321133.4 size: 79595609.8 {} [15508.460 ms; 047 iters.] [4.8508e-6 err.] pagerankLevelwise [dynamic]
#
# # Batch size 5e+7
# order: 5332329 size: 119532804.6 {} [18241.328 ms; 032 iters.] [0.0000e+0 err.] pagerankMonolithic [static]
# order: 5332329 size: 119532804.6 {} [17787.548 ms; 031 iters.] [8.0504e-7 err.] pagerankMonolithic [dynamic]
# order: 5332329 size: 119532804.6 {} [19525.692 ms; 032 iters.] [7.5338e-7 err.] pagerankLevelwise [static]
# order: 5332329 size: 119532804.6 {} [19546.696 ms; 031 iters.] [1.2832e-6 err.] pagerankLevelwise [dynamic]
#
# ...
```

[![](https://i.imgur.com/51l9Fvu.gif)][sheets]
[![](https://i.imgur.com/qrLpXzh.gif)][sheets]

<br>
<br>


## References

- [STIC-D: algorithmic techniques for efficient parallel pagerank computation on real-world graphs][STIC-D algorithm]
- [PageRank Algorithm, Mining massive Datasets (CS246), Stanford University](https://www.youtube.com/watch?v=ke9g8hB0MEo)
- [SuiteSparse Matrix Collection]

<br>
<br>

[![](https://i.imgur.com/bOHuBVU.jpg)](https://www.youtube.com/watch?v=RUar5sFdkh8)

[Prof. Dip Sankar Banerjee]: https://sites.google.com/site/dipsankarban/
[Prof. Kishore Kothapalli]: https://cstar.iiit.ac.in/~kkishore/
[STIC-D algorithm]: https://www.slideshare.net/SubhajitSahu/sticd-algorithmic-techniques-for-efficient-parallel-pagerank-computation-on-realworld-graphs
[SuiteSparse Matrix Collection]: https://suitesparse-collection-website.herokuapp.com
["graphs"]: https://github.com/puzzlef/graphs
[monolithic]: https://github.com/puzzlef/pagerank-levelwise
[levelwise]: https://github.com/puzzlef/pagerank-levelwise
[pull]: https://github.com/puzzlef/pagerank
[CSR]: https://github.com/puzzlef/pagerank
[skip-teleport]: https://github.com/puzzlef/pagerank-levelwise
[compute-10]: https://github.com/puzzlef/pagerank-levelwise
[skip-comp]: https://github.com/puzzlef/pagerank-levelwise-dynamic
[scaled-fill]: https://github.com/puzzlef/pagerank-dynamic
[branches]: https://github.com/puzzlef/pagerank-levelwise-dynamic/branches
[gist]: https://gist.github.com/wolfram77/b78e00855f48b5c7e210254742128954
[charts]: https://photos.app.goo.gl/29GpUSZEjPBtZkfq6
[sheets]: https://docs.google.com/spreadsheets/d/13-ijfokEXlpX3r5bRNOWg_8mPvomNilF8Yyy4KYOj-s/edit?usp=sharing
