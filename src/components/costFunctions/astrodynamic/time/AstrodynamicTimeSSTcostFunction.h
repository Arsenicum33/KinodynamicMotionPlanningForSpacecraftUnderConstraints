// MIT License
// Copyright (c) 2025 Arseniy Panyukov
//
// See the LICENSE file in the root directory for full license information.


#ifndef ASTRODYNAMICSSTCOSTFUNCTION_H
#define ASTRODYNAMICSSTCOSTFUNCTION_H
#include "components/costFunctions/ISSTcostFunction.h"
#include "dto/poses/astrodynamic/spaceshipState/SpaceshipState.h"


class AstrodynamicTimeSSTcostFunction : public ISSTcostFunction<SpaceshipState>
{
public:
    static std::unique_ptr<IComponent> createComponent(const ComponentConfig &config, const ReaderContext &context)
    {
        return std::make_unique<AstrodynamicTimeSSTcostFunction>();
    }
    CapabilitySet getCapabilities() const override { return CapabilitySet{ Capability::AstrodynamicEnv }; };

    double getCost(std::shared_ptr<SSTnode<SpaceshipState>> parent, const SpaceshipState &currentState) override;
};



#endif //ASTRODYNAMICSSTCOSTFUNCTION_H
