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
    RapidCollisionHandler(std::shared_ptr<RAPID_model> agent, std::vector<std::shared_ptr<RAPID_model>>&& obstacles) : //TODO maybe modify ownership of obstacles
        agent(std::move(agent)), obstacles(std::move(obstacles)) {}
    bool isPoseCollisionFree(Pose &pose) const override;

    bool arePosesCollisionFree(std::vector<Pose> &poses) const override;

    CapabilitySet getCapabilities() const override { return CapabilitySet { Capability::StaticEnv}; }

    void resolveDependencies(ComponentConfig &config, ComponentManager *manager) override;

private:
    std::shared_ptr<RAPID_model> agent;
    std::vector<std::shared_ptr<RAPID_model>> obstacles;
};

#endif //RAPIDCOLLISIONHANDLER_H
