#ifndef _SOURCE_HPP_
#define _SOURCE_HPP_

#include "base_struct.hpp"
#include "io.hpp"

#include <mpi.h>
#include <set>
#include <unordered_map>
#include <vector>
#include <iostream>

class Source {
_PRIVATE:

    // one among {MODE_NAIVE, METHOD_HASH, MODE_OPT}
    const Method_t method;

    // worker number
    const int workerNum;

    // used in MODE_OPT
    double tolerancePlusOne;

    // load in each worker
    long* workerToLoad;

    // minimum load
    long minLoad;

    // threshold
    double threshold;

    // minimum load worker id
    long minLoadWorker;

//    // list of (load, worker id)
//    std::set<pair<long,MID>> minHeap;

    // node to the assigned machine
    MID* nodeToWorker;

    // max node id
    VID maxVId;

    // capacity
    VID capacity;

    const MID missingMId;

    Source(): method(Method_t::OPT), workerNum(0), missingMId(-1) {;}

public:

    Source(int workerNum, Method_t mode, double tolerance);

    ~Source();

	// Only for MPI
    bool processEdge(Edge &iEdge, MID &oDstMID1, MID &oDstMID2);

    VID getMaxVId();
};

#endif // _SOURCE_HPP_
