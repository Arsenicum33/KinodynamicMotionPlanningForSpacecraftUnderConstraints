//
// Created by arseniy on 30.10.24.
//

#ifndef RAPIDCOLLISIONHANDLER_H
#define RAPIDCOLLISIONHANDLER_H
#include <memory>

#include "ICollisionHandler.h"
#include "RapidCollisionHandlerFactory.h"
#include "../Capability.h"
#include "../../fileParsers/meshParsers/MeshParser.h"
#include "components/ComponentRegistry.h"


class RapidCollisionHandler : public ICollisionHandler
{
public:
    RapidCollisionHandler(const std::string& agentFilepath, const std::string& obstacleFilepath, MeshParser<RAPID_model>& parser);
    bool isPoseCollisionFree(Pose &pose) const override;

    bool arePosesCollisionFree(std::vector<Pose> &poses) const override;

    CapabilitySet getCapabilities() const override { return CapabilitySet { Capability::StaticEnv}; };

private:
    std::unique_ptr<RAPID_model> agent;
    std::vector<std::unique_ptr<RAPID_model>> obstacles;
};

#endif //RAPIDCOLLISIONHANDLER_H
