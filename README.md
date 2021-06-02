Checking for correctness of [levelwise] PageRank when unchanged components are
skipped ([pull], [CSR], [scaled-fill]).

3 simple temporal graphs were taken to check for validity of the idea that an
**unchanged component** can simply be **skipped** from pagerank computation,
after all old ranks have been *scaled*, and new ranks are initialized to
*1/N*. Here, an *unchanged component* means that not a single edge within the
component has been altered. From the 3 examples taken, it appears that
*unchanged components* can indeed be skipped. I intially considered this to be
incorrect because my original component equality check simply compared the
vertices, and not the edges.

Output is saved in [out](out/) and a part of it is listed here. Input graphs
are in [data](data/), with [drawings](drawings/).

<br>

```bash
$ g++ -O3 main.cxx
$ ./a.out data/min2c1l.txt 5 2 true

# ...
```

<br>
<br>


## References

- [STIC-D: algorithmic techniques for efficient parallel pagerank computation on real-world graphs][STIC-D algorithm]
- [PageRank Algorithm, Mining massive Datasets (CS246), Stanford University](http://snap.stanford.edu/class/cs246-videos-2019/lec9_190205-cs246-720.mp4)

<br>
<br>

[![](https://i.imgur.com/mJoiKnM.jpg)](https://www.youtube.com/watch?v=J3sfsP9W048)

[levelwise]: https://github.com/puzzlef/pagerank-monolithic-vs-levelwise
[pull]: https://github.com/puzzlef/pagerank-push-vs-pull
[CSR]: https://github.com/puzzlef/pagerank-class-vs-csr
[scaled-fill]: https://github.com/puzzlef/pagerank-dynamic-adjust-ranks
[STIC-D algorithm]: https://www.slideshare.net/SubhajitSahu/sticd-algorithmic-techniques-for-efficient-parallel-pagerank-computation-on-realworld-graphs
