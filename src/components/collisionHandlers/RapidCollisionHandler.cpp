//
// Created by arseniy on 30.10.24.
//

#include "RapidCollisionHandler.h"

bool RapidCollisionHandler::isPoseCollisionFree(Pose &pose) const
{
    std::array<double, 3> zero_transaltion = {0, 0, 0};
    double zero_rotation[3][3] = {{1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}, {0.0, 0.0, 1.0}};

    for (auto& obstacle : obstacles)
    {
        RAPID_Collide(pose.rotation, pose.translation.data(), agent.get(), zero_rotation, zero_transaltion.data(), obstacle.get());
        if (RAPID_num_contacts > 0)
            return false;
    }

    return true;
}


bool RapidCollisionHandler::arePosesCollisionFree(std::vector<Pose> &poses) const
{
    for (Pose& pose : poses)
    {
        if (!isPoseCollisionFree(pose))
            return false;
    }
    return true;
}

void RapidCollisionHandler::resolveDependencies(ComponentConfig &config, ComponentManager *manager)
{
    return;
}
