//
// Created by arseniy on 28.10.24.
//

#ifndef ABSTRACTNEARESTNEIGHBOURSEARCH_H
#define ABSTRACTNEARESTNEIGHBOURSEARCH_H
#include <memory>

#include "components/IComponent.h"

template <typename PositionType>
class AbstractNearestNeighbourSearch : public IComponent
{
public:
    virtual int findNearestNeighbourIndex(const PositionType& pose) = 0;
    virtual std::vector<int> findKnearestNeighboursIndexes(const PositionType& pose) = 0;
    virtual void addPoint(const PositionType& pose) = 0;

    ComponentType getType() const override { return ComponentType::NearestNeighbourSearch; };
};

#endif //ABSTRACTNEARESTNEIGHBOURSEARCH_H
