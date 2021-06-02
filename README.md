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

# ...
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
