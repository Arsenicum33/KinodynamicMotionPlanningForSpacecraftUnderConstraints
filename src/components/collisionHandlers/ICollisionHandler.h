//
// Created by arseniy on 30.10.24.
//

#ifndef ICOLLISIONHANDLER_H
#define ICOLLISIONHANDLER_H
#include "../../poses/static/Pose.h"
#include "components/IComponent.h"

class ICollisionHandler : public IComponent
{
public:
    virtual bool isPoseCollisionFree(Pose& pose) const = 0;
    virtual bool arePosesCollisionFree(std::vector<Pose>& poses, Pose *collidingPose) const = 0;

    ComponentType getType() const override { return ComponentType::CollisionHandler; }
};

#endif //ICOLLISIONHANDLER_H
