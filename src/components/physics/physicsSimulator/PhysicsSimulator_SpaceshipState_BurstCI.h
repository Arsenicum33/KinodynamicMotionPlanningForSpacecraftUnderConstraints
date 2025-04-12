//
// Created by arseniy on 12.4.25.
//

#ifndef PHYSICSSIMULATOR_SPACESHIPSTATE_BURSTCI_H
#define PHYSICSSIMULATOR_SPACESHIPSTATE_BURSTCI_H
#include "PhysicsSimulator.h"
#include "dto/poses/dynamic/kinodynamic/burstControlInput/BurstControlInput.h"

class PhysicsSimulator_SpaceshipState_BurstCI : public PhysicsSimulator<SpaceshipState, BurstControlInput>
{
public:
    PhysicsSimulator_SpaceshipState_BurstCI(double timeResolution) :
        PhysicsSimulator<SpaceshipState, BurstControlInput>(timeResolution) {}
    static std::unique_ptr<IComponent> createComponent(const ComponentConfig &config, const ReaderContext &context);
};

inline std::unique_ptr<IComponent> PhysicsSimulator_SpaceshipState_BurstCI::createComponent(
    const ComponentConfig &config, const ReaderContext &context)
{
    const auto& configMap = config.config;

    double timeResolution = std::any_cast<double>(configMap.at("timeResolution"));

    return std::make_unique<PhysicsSimulator_SpaceshipState_BurstCI>(timeResolution);
}

#endif //PHYSICSSIMULATOR_SPACESHIPSTATE_BURSTCI_H
