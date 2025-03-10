//
// Created by arseniy on 28.10.24.
//

#ifndef ABSTRACTNEARESTNEIGHBOURSEARCH_H
#define ABSTRACTNEARESTNEIGHBOURSEARCH_H
#include <memory>

#include "../../poses/static/Pose.h"
#include "components/IComponent.h"

template <typename PositionType>
class AbstractNearestNeighbourSearch : public IComponent
{
public:
    virtual int findNearestNeighbourIndex(const PositionType& pose) = 0;
    virtual std::vector<int> findKnearestNeighboursIndexes(const PositionType& pose) = 0;
    virtual void addPoint(const PositionType& pose) = 0;

    std::string getName() const override { return "NearestNeighbourSearch"; };
};

#endif //ABSTRACTNEARESTNEIGHBOURSEARCH_H
