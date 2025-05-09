//
// Created by arseniy on 12.4.25.
//

#ifndef PHYSICSSIMULATOR_SPACESHIPSTATE_BURSTCI_H
#define PHYSICSSIMULATOR_SPACESHIPSTATE_BURSTCI_H
#include "PhysicsSimulator.h"
#include "dto/poses/dynamic/kinodynamic/burstControlInput/BurstControlInput.h"

class AstrodynamicPhysicsSimulator : public PhysicsSimulator<SpaceshipState>
{
public:
    static std::unique_ptr<IComponent> createComponent(const ComponentConfig &config, const ReaderContext &context);
};

inline std::unique_ptr<IComponent> AstrodynamicPhysicsSimulator::createComponent(
    const ComponentConfig &config, const ReaderContext &context)
{
    return std::make_unique<AstrodynamicPhysicsSimulator>();
}



#endif //PHYSICSSIMULATOR_SPACESHIPSTATE_BURSTCI_H
