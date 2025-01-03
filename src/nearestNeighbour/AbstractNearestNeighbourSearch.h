//
// Created by arseniy on 28.10.24.
//

#ifndef ABSTRACTNEARESTNEIGHBOURSEARCH_H
#define ABSTRACTNEARESTNEIGHBOURSEARCH_H
#include <memory>
#include "../solvers/treeSolvers/TreeNode.h"
#include "../poses/static/Pose.h"

class AbstractNearestNeighbourSearch
{
public:

    virtual ~AbstractNearestNeighbourSearch() = default;
    virtual int findNearestNeighbourIndex(const Pose& pose) = 0;
    virtual std::vector<int> findKnearestNeighboursIndexes(const Pose& pose) = 0;
    virtual void addPoint(const Pose& pose) = 0;
};

#endif //ABSTRACTNEARESTNEIGHBOURSEARCH_H
