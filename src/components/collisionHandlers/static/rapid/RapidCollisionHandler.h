//
// Created by arseniy on 30.10.24.
//

#ifndef RAPIDCOLLISIONHANDLER_H
#define RAPIDCOLLISIONHANDLER_H
#include <memory>

#include "RapidCollisionHandlerFactory.h"


class RapidCollisionHandler : public ICollisionHandler
{
public:
    RapidCollisionHandler(std::shared_ptr<RAPID_model> agent, const std::vector<std::shared_ptr<RAPID_model>>& obstacles) : //TODO maybe modify ownership of obstacles
        agent(agent), obstacles(obstacles) {}
    bool isPoseCollisionFree(Pose &pose) const override;

    bool arePosesCollisionFree(std::vector<Pose> &poses, Pose *collidingPose) const override;

    CapabilitySet getCapabilities() const override { return CapabilitySet { Capability::StaticEnv}; }

private:
    std::shared_ptr<RAPID_model> agent;
    std::vector<std::shared_ptr<RAPID_model>> obstacles;
};

#endif //RAPIDCOLLISIONHANDLER_H
