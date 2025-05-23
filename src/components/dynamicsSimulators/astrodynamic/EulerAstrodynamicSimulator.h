// MIT License
// Copyright (c) 2025 Arseniy Panyukov
//
// See the LICENSE file in the root directory for full license information.


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
