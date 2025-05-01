//
// Created by arseniy on 30.4.25.
//

#ifndef RK4_ASTRODYNAMICSIMULATOR_H
#define RK4_ASTRODYNAMICSIMULATOR_H
#include "components/dynamicsSimulators/RK4_DynamicsSimulator.h"
#include "dto/poses/astrodynamic/spaceshipState/SpaceshipState.h"


class RK4_AstrodynamicSimulator : public RK4_DynamicsSimulator<SpaceshipState>
{
public:
    static std::unique_ptr<IComponent> createComponent(const ComponentConfig &config, const ReaderContext &context)
    {
        return std::make_unique<RK4_AstrodynamicSimulator>();
    }

    CapabilitySet getCapabilities() const override { return CapabilitySet{Capability::AstrodynamicEnv}; };
};



#endif //RK4_ASTRODYNAMICSIMULATOR_H
