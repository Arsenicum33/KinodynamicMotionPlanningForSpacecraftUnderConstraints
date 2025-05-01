//
// Created by arseniy on 30.4.25.
//

#ifndef EULERASTRODYNAMICSIMULATOR_H
#define EULERASTRODYNAMICSIMULATOR_H
#include "components/dynamicsSimulators/Euler_DynamicsSimulator.h"
#include "dto/poses/astrodynamic/spaceshipState/SpaceshipState.h"


class EulerAstrodynamicSimulator : public Euler_DynamicsSimulator<SpaceshipState>
{
public:
    static std::unique_ptr<IComponent> createComponent(const ComponentConfig &config, const ReaderContext &context)
    {
        return std::make_unique<EulerAstrodynamicSimulator>();
    }

    CapabilitySet getCapabilities() const override { return CapabilitySet{Capability::AstrodynamicEnv}; };
};



#endif //EULERASTRODYNAMICSIMULATOR_H
