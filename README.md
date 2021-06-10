Checking the performance benefit of [levelwise] PageRank when unchanged
components are [skipped][skip-comp] ([pull], [CSR], [comp-50], [scaled-fill]).

This experiment was for comparing performance between:
1. Find static levelwise pagerank.
2. Find dynamic levelwise pagerank (process all components).
3. Find dynamic levelwise pagerank, [skipping unchanged components][skip-comp].

Each approach was attempted on a number of temporal graphs, running each with
multiple batch sizes (`1`, `5`, `10`, `50`, ...). Each batch size was run 5
times for each approach to get a good time measure. **Levelwise** pagerank is
the [STIC-D algorithm], without **ICD** optimizations (using single-thread).
On average, skipping unchanged components is **barely faster** than not
skipping.

All outputs are saved in [out](out/) and a small part of the output is listed
here. Some [charts] are also included below, generated from [sheets]. The input
data used for this experiment is available at the
[Stanford Large Network Dataset Collection].

<br>

```bash
$ g++ -O3 main.cxx
$ ./a.out ~/data/email-Eu-core-temporal.txt
$ ./a.out ~/data/CollegeMsg.txt
$ ...

# (SHORTENED)
# ...
#
# Using graph sx-stackoverflow ...
# Temporal edges: 63497051
# order: 2601975 size: 36951021 {}
#
# # Batch size 1e+0
# [02439.089 ms; 049 iters.] [0.0000e+0 err.] pagerankStatic
# [00094.460 ms; 001 iters.] [6.6644e-7 err.] pagerankDynamic
# [00058.680 ms; 000 iters.] [4.8293e-7 err.] pagerankDynamic [skip-comp]
#
# # Batch size 5e+0
# [02411.729 ms; 049 iters.] [0.0000e+0 err.] pagerankStatic
# [00122.591 ms; 001 iters.] [9.8462e-7 err.] pagerankDynamic
# [00113.988 ms; 001 iters.] [9.2387e-7 err.] pagerankDynamic [skip-comp]
#
# # Batch size 1e+1
# [02392.791 ms; 049 iters.] [0.0000e+0 err.] pagerankStatic
# [00154.871 ms; 001 iters.] [1.1933e-6 err.] pagerankDynamic
# [00150.654 ms; 001 iters.] [1.1575e-6 err.] pagerankDynamic [skip-comp]
#
# # Batch size 5e+1
# [02435.785 ms; 049 iters.] [0.0000e+0 err.] pagerankStatic
# [00254.584 ms; 002 iters.] [2.0129e-6 err.] pagerankDynamic
# [00253.247 ms; 002 iters.] [1.9810e-6 err.] pagerankDynamic [skip-comp]
#
# # Batch size 1e+2
# [02442.940 ms; 049 iters.] [0.0000e+0 err.] pagerankStatic
# [00301.574 ms; 003 iters.] [2.4152e-6 err.] pagerankDynamic
# [00299.359 ms; 003 iters.] [2.3857e-6 err.] pagerankDynamic [skip-comp]
#
# # Batch size 5e+2
# [02432.011 ms; 049 iters.] [0.0000e+0 err.] pagerankStatic
# [00435.612 ms; 005 iters.] [3.6108e-6 err.] pagerankDynamic
# [00439.719 ms; 005 iters.] [3.5922e-6 err.] pagerankDynamic [skip-comp]
#
# # Batch size 1e+3
# [02546.070 ms; 049 iters.] [0.0000e+0 err.] pagerankStatic
# [00534.300 ms; 007 iters.] [4.0567e-6 err.] pagerankDynamic
# [00530.003 ms; 006 iters.] [4.0360e-6 err.] pagerankDynamic [skip-comp]
#
# # Batch size 5e+3
# [02454.957 ms; 049 iters.] [0.0000e+0 err.] pagerankStatic
# [00795.388 ms; 012 iters.] [4.5533e-6 err.] pagerankDynamic
# [00798.701 ms; 011 iters.] [4.5399e-6 err.] pagerankDynamic [skip-comp]
#
# # Batch size 1e+4
# [02678.003 ms; 049 iters.] [0.0000e+0 err.] pagerankStatic
# [01042.808 ms; 014 iters.] [4.5984e-6 err.] pagerankDynamic
# [01045.956 ms; 014 iters.] [4.5913e-6 err.] pagerankDynamic [skip-comp]
#
# # Batch size 5e+4
# [02853.757 ms; 049 iters.] [0.0000e+0 err.] pagerankStatic
# [01632.881 ms; 021 iters.] [4.6485e-6 err.] pagerankDynamic
# [01627.506 ms; 021 iters.] [4.6454e-6 err.] pagerankDynamic [skip-comp]
#
# # Batch size 1e+5
# [02810.581 ms; 049 iters.] [0.0000e+0 err.] pagerankStatic
# [01844.752 ms; 024 iters.] [4.6653e-6 err.] pagerankDynamic
# [01849.970 ms; 024 iters.] [4.6565e-6 err.] pagerankDynamic [skip-comp]
#
# # Batch size 5e+5
# [02960.564 ms; 049 iters.] [0.0000e+0 err.] pagerankStatic
# [02450.280 ms; 031 iters.] [4.4982e-6 err.] pagerankDynamic
# [02456.433 ms; 031 iters.] [4.4951e-6 err.] pagerankDynamic [skip-comp]
```

[![](https://i.imgur.com/8jYDOA5.gif)][sheets]

<br>
<br>


## References

- [STIC-D: algorithmic techniques for efficient parallel pagerank computation on real-world graphs][STIC-D algorithm]
- [PageRank Algorithm, Mining massive Datasets (CS246), Stanford University](http://snap.stanford.edu/class/cs246-videos-2019/lec9_190205-cs246-720.mp4)
- [Stanford Large Network Dataset Collection]

<br>
<br>

[![](https://i.imgur.com/YWmqWAg.jpg)](https://www.youtube.com/watch?v=SoiKp2oSUl0)

[levelwise]: https://github.com/puzzlef/pagerank-monolithic-vs-levelwise
[pull]: https://github.com/puzzlef/pagerank-push-vs-pull
[CSR]: https://github.com/puzzlef/pagerank-class-vs-csr
[comp-50]: https://github.com/puzzlef/pagerank-levelwise-adjust-component-size
[scaled-fill]: https://github.com/puzzlef/pagerank-dynamic-adjust-ranks
[skip-comp]: https://github.com/puzzlef/pagerank-levelwise-dynamic-validate-skip-unchanged-components
[STIC-D algorithm]: https://www.slideshare.net/SubhajitSahu/sticd-algorithmic-techniques-for-efficient-parallel-pagerank-computation-on-realworld-graphs
[Stanford Large Network Dataset Collection]: http://snap.stanford.edu/data/index.html
[charts]: https://photos.app.goo.gl/TF4SQpZWH4LtkWM88
[sheets]: https://docs.google.com/spreadsheets/d/1TBWQkhiI2NZwO5eBAK7qdJ1jafDMiU332fqOVS4V8NM/edit?usp=sharing
