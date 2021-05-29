Checking for correctness of [levelwise] PageRank when unchanged components are
skipped ([pull], [CSR], [scaled-fill]).

A simple temporal graph [min1c1l](data/min1c1l.txt) was taken to check for
validity of the idea that an **unchanged component** can simply be **skipped**
from pagerank computation, after all old ranks have been *scaled*, and new
ranks are initialized to *1/N*. The *temporal graph* initially has 2 vertices
pointing to each other, and so initial ranks are `0.5` each. The updated graph
has a new vertex `3` which is pointed by `2` and itself (levelwise pagerank
algorithm does not work is a graph has dead-ends, causing teleports). If we
skip the unchanged components, i.e., `[1, 2]` with scaled ranks `0.33` each,
and run pagerank on `3` only, its final ranks comes to be `1.2777`, which is
**incorrect**. This shows that simply skipping unchanged components is not
correct (one counter example is sufficient).

Output is saved in [out/](out/) and is listed here. The drawing for `minc1l1`
is below.

[![](https://i.imgur.com/tjoPesM.jpg)](drawings/min1c1l.jpeg)

<br>

```bash
$ g++ -O3 main.cxx
$ ./a.out data/min1c1l.txt 2 2 true

# Using graph data/min1c1l.txt ...
# original-graph: order: 2 size: 2 {
#   1 -> 2
#   2 -> 1
# }
#
# [00000.000 ms; 001 iters.] [0.0000e+00 err.] pagerankStatic
# { 0 0.5 0.5 }
#
# updated-graph: order: 3 size: 4 {
#   1 -> 2
#   2 -> 1 3
#   3 -> 3
# }
#
# [00000.004 ms; 042 iters.] [0.0000e+00 err.] pagerankStatic
# { 0 0.111546 0.144814 0.743641 }
#
# [00000.004 ms; 042 iters.] [0.0000e+00 err.] pagerankDynamic
# { 0 0.111546 0.144814 0.743641 }
#
# [00000.003 ms; 027 iters.] [9.4444e-01 err.] pagerankDynamic [skip-comp]
# { 0 0.333333 0.333333 1.27778 }
```

<br>
<br>


## References

- [STIC-D: algorithmic techniques for efficient parallel pagerank computation on real-world graphs][STIC-D algorithm]
- [PageRank Algorithm, Mining massive Datasets (CS246), Stanford University](http://snap.stanford.edu/class/cs246-videos-2019/lec9_190205-cs246-720.mp4)

<br>
<br>

[![](https://i.imgur.com/tCdIBkh.png)](https://www.youtube.com/watch?v=CefQiC3ZE0E)

[levelwise]: https://github.com/puzzlef/pagerank-monolithic-vs-levelwise
[pull]: https://github.com/puzzlef/pagerank-push-vs-pull
[CSR]: https://github.com/puzzlef/pagerank-class-vs-csr
[scaled-fill]: https://github.com/puzzlef/pagerank-dynamic-adjust-ranks
[STIC-D algorithm]: https://www.slideshare.net/SubhajitSahu/sticd-algorithmic-techniques-for-efficient-parallel-pagerank-computation-on-realworld-graphs
