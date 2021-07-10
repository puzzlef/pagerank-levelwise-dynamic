Checking for correctness of [levelwise] PageRank when **unchanged components**
are **skipped** ([pull], [CSR], [scaled-fill]).

3 simple temporal graphs were taken to check for validity of the idea that an
**unchanged component** can simply be **skipped** from pagerank computation,
after all old ranks have been *scaled*, and new ranks are initialized to
*1/N*. Here, an *unchanged component* means that not a single edge within the
component has been altered. From the 3 examples taken, it appears that
**unchanged components can indeed be skipped**. I intially considered this to
be incorrect because my original component equality check simply compared the
vertices, and not the edges.

All outputs are saved in [out](out/) and a small part of the output is listed
here. Input graphs are in [data](data/), with [drawings](drawings/). This
experiment was done with guidance from [Prof. Dip Sankar Banerjee] and
[Prof. Kishore Kothapalli].

<br>

```bash
$ g++ -O3 main.cxx
$ ./a.out data/min2c1l.txt 5 2 true

# Using graph data/min2c1l.txt ...
# original-graph: order: 4 size: 5 {
#   1 -> 2
#   2 -> 1 3
#   3 -> 4
#   4 -> 3
# }
#
# [00000.005 ms; 049 iters.] [0.0000e+00 err.] pagerankStatic
# { 0 0.0836598 0.108611 0.41634 0.391389 }
#
# updated-graph: order: 5 size: 7 {
#   1 -> 2
#   2 -> 1 3
#   3 -> 4
#   4 -> 3 5
#   5 -> 5
# }
#
# [00000.005 ms; 036 iters.] [0.0000e+00 err.] pagerankStatic
# { 0 0.0669278 0.0868886 0.124741 0.13603 0.585416 }
#
# [00000.004 ms; 027 iters.] [1.1846e-06 err.] pagerankDynamic
# { 0 0.0669277 0.0868886 0.12474 0.136029 0.585415 }
#
# [00000.004 ms; 026 iters.] [1.0282e-06 err.] pagerankDynamic [skip-comp]
# { 0 0.0669278 0.0868886 0.12474 0.136029 0.585415 }
```

<br>
<br>


## References

- [STIC-D: algorithmic techniques for efficient parallel pagerank computation on real-world graphs][STIC-D algorithm]
- [PageRank Algorithm, Mining massive Datasets (CS246), Stanford University](https://www.youtube.com/watch?v=ke9g8hB0MEo)

<br>
<br>

[![](https://i.imgur.com/mJoiKnM.jpg)](https://www.youtube.com/watch?v=J3sfsP9W048)

[Prof. Dip Sankar Banerjee]: https://sites.google.com/site/dipsankarban/
[Prof. Kishore Kothapalli]: https://cstar.iiit.ac.in/~kkishore/
[STIC-D algorithm]: https://www.slideshare.net/SubhajitSahu/sticd-algorithmic-techniques-for-efficient-parallel-pagerank-computation-on-realworld-graphs
[levelwise]: https://github.com/puzzlef/pagerank-monolithic-vs-levelwise
[pull]: https://github.com/puzzlef/pagerank-push-vs-pull
[CSR]: https://github.com/puzzlef/pagerank-class-vs-csr
[scaled-fill]: https://github.com/puzzlef/pagerank-dynamic-adjust-ranks
