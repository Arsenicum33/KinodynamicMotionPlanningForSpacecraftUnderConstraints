//
// Created by arseniy on 28.10.24.
//

#ifndef IMPNNSEARCH_H
#define IMPNNSEARCH_H
#include <memory>

#include "components/IComponent.h"
#include "../INearestNeighborSearch.h"

template <typename PositionType>
class IMPNNsearch : public INearestNeighborSearch
{
public:
    virtual int findNearestNeighbourIndex(const PositionType& pose) = 0;
    virtual std::vector<int> findKnearestNeighboursIndexes(const PositionType& pose) = 0;
    virtual void addPoint(const PositionType& pose) = 0;


};

#endif //IMPNNSEARCH_H
