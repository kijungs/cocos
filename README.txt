=================================================================================

 CoCoS: Fast and Accurate Distributed Triangle Counting in Graph Streams
 Authors: Kijung Shin (kijungs@kaist.ac.kr) and Jinoh Oh (joh@adobe.com)

 Version: 1.0
 Date: Oct 10, 2019
 Main Contact: Kijung Shin

 This software is free of charge under research purposes.
 For commercial purposes, please contact the author.

 =================================================================================

CoCoS is a distributed streaming algorithm for global and local triangle counting in graph streams. 
CoCoS processes and samples edges across multiple machines to reduce redundancy in computation and storage. 
CoCoS has the following advantages: 
 - Accurate: CoCoS produces up to 30X smaller estimation error than its competitors with similar speeds
 - Fast: CoCoS runs in linear time up to 10.4X faster while giving more accurate estimates
 - Theoretically Sound: CoCoS gives unbiased estimates.

For detailed information, see 'user_guide.pdf'

For demo, type 'make demo'