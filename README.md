CoCoS: Fast and Accurate Distributed Triangle Counting in Graph Streams
========================

**CoCoS** is a distributed streaming algorithm for estimating global and local triangle counts in graph streams.
**CoCoS** processes and samples edges across multiple machines to reduce redundancy in computation and storage.
**CoCoS** has the following advantages:
 * *Accurate*: **CoCoS** produces up to 30X smaller estimation error than its competitors with similar speeds
 * *Fast*: **CoCoS** runs in linear time up to 10.4X faster while giving more accurate estimates
 * *Theoretically Sound*: **CoCoS** gives unbiased estimates.

Datasets
========================
The download links for the datasets used in the paper are [here](http://dmlab.kaist.ac.kr/cocos/)

Building and Running WRS
========================
Please see [User Guide](user_guide.pdf)

Running Demo
========================
For demo, please type 'make'

Reference
========================
If you use this code as part of any published research, please acknowledge the following paper.
```
@article{shin2021cocos,
  title     = {CoCoS: Fast and Accurate Distributed Triangle Counting in Graph Streams},
  author    = {Kijung Shin and Euiwoong Lee and Jinoh Oh and Mohammad Hammoud and Christos Faloutsos},
  journal   = {ACM Transactions on Knowledge Discovery from Data (TKDD)},
  year      = {2021},
}
```
