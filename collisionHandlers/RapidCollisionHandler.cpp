//
// Created by arseniy on 30.10.24.
//

#include "RapidCollisionHandler.h"

RapidCollisionHandler::RapidCollisionHandler(const std::string& agentFilepath, const std::string& obstacleFilepath,
     MeshParser<RAPID_model>& parser)
{
    agent = std::move(parser.parse(agentFilepath)[0]);
    obstacles = std::move(parser.parse(obstacleFilepath));
}

bool RapidCollisionHandler::isPoseCollisionFree(Pose &pose)
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


bool RapidCollisionHandler::arePosesCollisionFree(std::vector<Pose> &poses)
{
    for (Pose& pose : poses)
    {
        if (!isPoseCollisionFree(pose))
            return false;
    }
    return true;
}
