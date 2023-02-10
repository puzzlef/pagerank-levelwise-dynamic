Design of *Levelwise* **Dynamic** *PageRank algorithm* for link analysis.

[Levelwise PageRank] is the [STIC-D algorithm], without **ICD** optimizations
(using a single-thread here). We use a rank [pull] based approach, and perform
the computation upon the [CSR] representation of a graph. If the size of a
component is fewer than 50 vertices, we combine multiple components together
([comp-50]). To take into account removed/added vertices upon the dynamic graph,
we scale the previous ranks using the [scaled-fill] approach.

We attempt each experiment (mentioned below) on different types of graphs,
running each with multiple batch sizes (`1`, `5`, `10`, `50`, ...). Each
pagerank computation was run 5 times for both approaches to get a good time
measure. The input data used for each experiment is available at ["graphs"] (for
small ones), the [SuiteSparse Matrix Collection], and the [Stanford Large
Network Dataset Collection]. Experiments were done with guidance from [Prof. Dip
Sankar Banerjee] and [Prof. Kishore Kothapalli].

<br>


### Skipping unchanged components

We first check the correctness of Levelwise PageRank when unchanged (unaffected)
components are skipped ([validate-skip-unchanged-components]). We then perform
the same experiment as above, but skip the unchanged components with Levelwise
PageRank. On average, we observe that skipping unchanged components is *barely*
*faster* than not skipping; on both temporal graphs ([skip-unchanged-components]),
and fixed graphs with randomly generated batches of edge insertions
([skip-unchanged-components-with-mtx-insertions]).

[validate-skip-unchanged-components]: https://github.com/puzzlef/pagerank-levelwise-dynamic/tree/validate-skip-unchanged-components
[skip-unchanged-components]: https://github.com/puzzlef/pagerank-levelwise-dynamic/tree/skip-unchanged-components
[skip-unchanged-components-with-mtx-insertions]: https://github.com/puzzlef/pagerank-levelwise-dynamic/tree/skip-unchanged-components-with-mtx-insertions

<br>


### Comparison with Monolithic approach

In this experiment ([compare-monolithic], [main]), we compare the performance of
*static* and *dynamic Monolithic/Levelwise PageRank* on temporal graphs. Our
results indicated that *dynamic Levelwise PageRank* faster is than the *static*
approach for most batch sizes. We repeat this experiment on fixed graphs with
randomly generated batches of edge insertions ([with-mtx-insertions]), and
observe a similar result.

[compare-monolithic]: https://github.com/puzzlef/pagerank-levelwise-dynamic/tree/compare-monolithic
[with-mtx-insertions]: https://github.com/puzzlef/pagerank-levelwise-dynamic/tree/with-mtx-insertions
[main]: https://github.com/puzzlef/pagerank-levelwise-dynamic

<br>


## References

- [STIC-D: algorithmic techniques for efficient parallel pagerank computation on real-world graphs][STIC-D algorithm]
- [PageRank Algorithm, Mining massive Datasets (CS246), Stanford University](https://www.youtube.com/watch?v=ke9g8hB0MEo)
- [Stanford Large Network Dataset Collection]
- [SuiteSparse Matrix Collection]
- [Merge git repo into branch of another repo](https://stackoverflow.com/a/21353836/1413259)

<br>
<br>


[![](https://img.youtube.com/vi/xEfsE8H6sok/maxresdefault.jpg)](https://www.youtube.com/watch?v=xEfsE8H6sok)


[Prof. Dip Sankar Banerjee]: https://sites.google.com/site/dipsankarban/
[Prof. Kishore Kothapalli]: https://faculty.iiit.ac.in/~kkishore/
[Levelwise PageRank]: https://ieeexplore.ieee.org/abstract/document/9835216/
[STIC-D algorithm]: https://dl.acm.org/doi/abs/10.1145/2833312.2833322
[Stanford Large Network Dataset Collection]: http://snap.stanford.edu/data/index.html
[SuiteSparse Matrix Collection]: https://sparse.tamu.edu/
["graphs"]: https://github.com/puzzlef/graphs
[levelwise]: https://github.com/puzzlef/pagerank-levelwise
[levelwise algorithm]: https://github.com/puzzlef/pagerank-levelwise
[standard algorithm]: https://github.com/puzzlef/pagerank-levelwise
[pull]: https://github.com/puzzlef/pagerank
[CSR]: https://github.com/puzzlef/pagerank
[comp-50]: https://github.com/puzzlef/pagerank-levelwise
[scaled-fill]: https://github.com/puzzlef/pagerank-dynamic
[charts]: https://photos.app.goo.gl/1XqKzvtL73xN8Tro6
[sheets]: https://docs.google.com/spreadsheets/d/1azuAqSPU2RP8Z8wVxNSbW5AJuq1jQmZVo9fA90rf-_s/edit?usp=sharing
