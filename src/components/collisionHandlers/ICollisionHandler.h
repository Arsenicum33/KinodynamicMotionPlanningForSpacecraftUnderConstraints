//
// Created by arseniy on 30.10.24.
//

#ifndef ICOLLISIONHANDLER_H
#define ICOLLISIONHANDLER_H
#include "../../poses/static/Pose.h"
#include "components/IComponent.h"

template <typename PositionType>
class ICollisionHandler : public IComponent
{
public:
    virtual bool isCollisionFree(PositionType& position) const = 0;
    bool areCollisionFree(std::vector<PositionType>& positions, PositionType* collidingPosition = nullptr) const;
    virtual std::shared_ptr<RAPID_model> getAgent() const = 0;
    ComponentType getType() const override { return ComponentType::CollisionHandler; }
};

template<typename PositionType>
bool ICollisionHandler<PositionType>::areCollisionFree(std::vector<PositionType> &positions,
    PositionType *collidingPosition) const
{
    for (PositionType& position :  positions)
    {
        if (isCollisionFree(position))
            continue;
        if (collidingPosition != nullptr)
            *collidingPosition = position;
        return false;
    }
    return true;
}

#endif //ICOLLISIONHANDLER_H
