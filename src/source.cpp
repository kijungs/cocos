#include "source.hpp"

Source::Source(int workerNum, Method_t method, double tolerance):
        method(method), workerNum(workerNum), tolerancePlusOne(tolerance+1.0), workerToLoad(nullptr), minLoad(0), threshold(0.0), minLoadWorker(0),
        nodeToWorker(nullptr),  maxVId(128), missingMId(-1)
{

    if(method == Method_t::OPT)
    {
        capacity = maxVId;
        workerToLoad = new long[workerNum];
        for (MID i = 0; i < workerNum; i++)
        {
            workerToLoad[i] = 0;
        }

        nodeToWorker = new MID[maxVId];
        for (VID i = 0; i < maxVId; i++)
        {
            nodeToWorker[i] = missingMId;
        }

        //for (MID i = 0; i < workerNum; i++)
        //{
        //    workerToLoad.push_back(0l);
        //    minHeap.insert(std::pair<long, MID>(0l, i));
        //}
    }

}

Source::~Source()
{
    if(workerToLoad != nullptr) {
        delete[] workerToLoad;
    }

    if(nodeToWorker != nullptr) {
        delete[] nodeToWorker;
    }

}

VID Source::getMaxVId()
{
    return maxVId;
}


/**
 *
 * @param iEdge input edge
 * @param oDstMID1 destination machine 1
 * @param oDstMID2 destination machine 2
 * @return whether to broadcast
 */
bool Source::processEdge(Edge &iEdge, MID &oDstMID1, MID &oDstMID2)
{

    VID src = iEdge.src;
    VID dst = iEdge.dst;
    if (src > maxVId) {
        maxVId = src;
    }
    if (dst > maxVId) {
        maxVId = dst;
    }
	if(method == Method_t::NAIVE)
    {
        return true;
	}
	else if(method == Method_t::HASH)
    {
        oDstMID1 = src % workerNum;
        oDstMID2 = dst % workerNum;

        return oDstMID1 != oDstMID2;
	}
	else // (method == Method_t::OPT) // Default
	{

        if(maxVId >= capacity) {

            VID newCapacity = 2 * maxVId;
            MID * newNodeToWorker = new MID[newCapacity];
            memcpy(newNodeToWorker, nodeToWorker, capacity * sizeof(MID));
            memset(newNodeToWorker + capacity, missingMId, (newCapacity - capacity) * sizeof(MID));
            capacity = newCapacity;
            delete[] nodeToWorker;
            nodeToWorker = newNodeToWorker;
        }

        if(nodeToWorker[src] == missingMId)
        {
            if(nodeToWorker[dst] == missingMId) // two new nodes
            {
                oDstMID1 = minLoadWorker;
                oDstMID2 = minLoadWorker;
                nodeToWorker[src] = oDstMID1;
                nodeToWorker[dst] = oDstMID2;
            }
            else // one new node
            {
                oDstMID2 = nodeToWorker[dst];
                if(workerToLoad[oDstMID2] <= threshold)
                {
                    oDstMID1 = oDstMID2;
                }
                else
                {
                    oDstMID1 = minLoadWorker;
                }
                nodeToWorker[src] = oDstMID1;
            }
        }
        else
        {
            if(nodeToWorker[dst] == missingMId) // one new node
            {
                oDstMID1 = nodeToWorker[src];
                if(workerToLoad[oDstMID1] <= threshold)
                {
                    oDstMID2 = oDstMID1;
                }
                else
                {
                    oDstMID2 = minLoadWorker;
                }
                nodeToWorker[dst] = oDstMID2;
            }
            else // zero new node
            {
                oDstMID1 = nodeToWorker[src];
                oDstMID2 = nodeToWorker[dst];
            }
        }

        if(oDstMID1 == oDstMID2) {
            workerToLoad[oDstMID1] += 1;
        }
        else {
            workerToLoad[oDstMID1] += 1;
            workerToLoad[oDstMID2] += 1;
        }

        //find new minimum load worker
        if(oDstMID1 == minLoadWorker || oDstMID2 == minLoadWorker)
        {
            minLoad = workerToLoad[minLoadWorker];
            for(MID i = 0; i < workerNum; i++) {
                if (workerToLoad[i] < minLoad) {
                    minLoad = workerToLoad[i];
                    minLoadWorker = i;
                }
            }
            threshold = minLoad * tolerancePlusOne;
        }

        return oDstMID1 != oDstMID2;
	}
}

#ifdef _TEST_

TEST_CASE("Source.getEdge()", "[Source]")
{

    std::unordered_map<int,char> example;
    example[1]='c';
    example[1]='d';
    int count = example.count(1);
    REQUIRE(count == 1);
    REQUIRE(example.find(1)!=example.end());
    REQUIRE(example.find(2)==example.end());

	//Source	src(2, Method_t::NAIVE);
	//Edge	edge;

	//src.getEdge(edge);
	//REQUIRE(edge.src == 9203210);
	//REQUIRE(edge.dst == 9801208);
	//src.getEdge(edge);
	//REQUIRE(edge.src == 9203210);
	//REQUIRE(edge.dst == 9801209);
	//
	//int cnt(2);
	//while(src.getEdge(edge))
	//{
	//	cnt++;
	//}
	//REQUIRE(cnt == 346849);
}

#endif // _TEST_
