// MIT License
// Copyright (c) 2025 Arseniy Panyukov
//
// See the LICENSE file in the root directory for full license information.


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
