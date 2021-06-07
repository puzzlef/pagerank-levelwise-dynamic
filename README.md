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
# Using graph sx-stackoverflow.txt ...
# Temporal edges: 63497051
# order: 2601975 size: 36233429 {}
#
# # Batch size 1e+0
# [02978.498 ms; 038 iters.] [0.0000e+0 err.] pagerankStatic
# [00135.908 ms; 001 iters.] [6.2857e-7 err.] pagerankDynamic
# [00085.419 ms; 000 iters.] [4.4804e-7 err.] pagerankDynamic [skip-comp]
#
# # Batch size 5e+0
# [02936.456 ms; 038 iters.] [0.0000e+0 err.] pagerankStatic
# [00172.335 ms; 001 iters.] [9.1362e-7 err.] pagerankDynamic
# [00162.908 ms; 001 iters.] [8.7759e-7 err.] pagerankDynamic [skip-comp]
#
# # Batch size 1e+1
# [02885.442 ms; 038 iters.] [0.0000e+0 err.] pagerankStatic
# [00198.521 ms; 001 iters.] [1.0716e-6 err.] pagerankDynamic
# [00193.457 ms; 001 iters.] [1.0754e-6 err.] pagerankDynamic [skip-comp]
#
# # Batch size 5e+1
# [02886.161 ms; 038 iters.] [0.0000e+0 err.] pagerankStatic
# [00309.427 ms; 002 iters.] [1.7384e-6 err.] pagerankDynamic
# [00305.640 ms; 002 iters.] [1.7189e-6 err.] pagerankDynamic [skip-comp]
#
# # Batch size 1e+2
# [02892.402 ms; 038 iters.] [0.0000e+0 err.] pagerankStatic
# [00365.238 ms; 002 iters.] [2.0316e-6 err.] pagerankDynamic
# [00361.614 ms; 002 iters.] [2.0111e-6 err.] pagerankDynamic [skip-comp]
#
# # Batch size 5e+2
# [02763.193 ms; 038 iters.] [0.0000e+0 err.] pagerankStatic
# [00475.344 ms; 004 iters.] [3.0299e-6 err.] pagerankDynamic
# [00476.270 ms; 003 iters.] [3.0195e-6 err.] pagerankDynamic [skip-comp]
#
# # Batch size 1e+3
# [02617.351 ms; 038 iters.] [0.0000e+0 err.] pagerankStatic
# [00508.506 ms; 004 iters.] [3.5513e-6 err.] pagerankDynamic
# [00509.847 ms; 004 iters.] [3.5458e-6 err.] pagerankDynamic [skip-comp]
#
# # Batch size 5e+3
# [02716.211 ms; 038 iters.] [0.0000e+0 err.] pagerankStatic
# [00784.180 ms; 007 iters.] [4.7989e-6 err.] pagerankDynamic
# [00783.999 ms; 007 iters.] [4.7847e-6 err.] pagerankDynamic [skip-comp]
#
# # Batch size 1e+4
# [02677.057 ms; 038 iters.] [0.0000e+0 err.] pagerankStatic
# [00946.650 ms; 009 iters.] [5.1626e-6 err.] pagerankDynamic
# [00947.246 ms; 009 iters.] [5.1700e-6 err.] pagerankDynamic [skip-comp]
#
# # Batch size 5e+4
# [02804.050 ms; 038 iters.] [0.0000e+0 err.] pagerankStatic
# [01522.539 ms; 015 iters.] [5.4852e-6 err.] pagerankDynamic
# [01520.592 ms; 015 iters.] [5.4861e-6 err.] pagerankDynamic [skip-comp]
#
# # Batch size 1e+5
# [02255.807 ms; 038 iters.] [0.0000e+0 err.] pagerankStatic
# [01406.559 ms; 018 iters.] [5.4895e-6 err.] pagerankDynamic
# [01405.330 ms; 018 iters.] [5.4860e-6 err.] pagerankDynamic [skip-comp]
#
# # Batch size 5e+5
# [02371.252 ms; 038 iters.] [0.0000e+0 err.] pagerankStatic
# [01961.793 ms; 025 iters.] [5.3335e-6 err.] pagerankDynamic
# [01975.427 ms; 025 iters.] [5.3339e-6 err.] pagerankDynamic [skip-comp]
```

[![](https://i.imgur.com/8jYDOA5.gif)][sheets]
[![](https://i.imgur.com/abDT6I1.gif)][sheets]
[![](https://i.imgur.com/1wdNKhV.gif)][sheets]
[![](https://i.imgur.com/taLRaKb.gif)][sheets]
[![](https://i.imgur.com/Hlap6PW.gif)][sheets]
[![](https://i.imgur.com/J2hdgin.gif)][sheets]
[![](https://i.imgur.com/CEaPgbe.gif)][sheets]
[![](https://i.imgur.com/TxP5g79.gif)][sheets]
[![](https://i.imgur.com/tUrFy5U.gif)][sheets]
[![](https://i.imgur.com/M24MKEV.gif)][sheets]
[![](https://i.imgur.com/u4vEPzS.gif)][sheets]
[![](https://i.imgur.com/VwxUVEK.gif)][sheets]
[![](https://i.imgur.com/8j3o3EG.gif)][sheets]
[![](https://i.imgur.com/NcoM9kN.gif)][sheets]

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
