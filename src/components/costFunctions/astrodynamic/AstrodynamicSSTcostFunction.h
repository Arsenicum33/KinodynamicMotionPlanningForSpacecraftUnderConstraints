//
// Created by arseniy on 5.5.25.
//

#ifndef ASTRODYNAMICSSTCOSTFUNCTION_H
#define ASTRODYNAMICSSTCOSTFUNCTION_H
#include "components/costFunctions/ISSTcostFunction.h"
#include "dto/poses/astrodynamic/spaceshipState/SpaceshipState.h"


class AstrodynamicSSTcostFunction : public ISSTcostFunction<SpaceshipState>
{
public:
    static std::unique_ptr<IComponent> createComponent(const ComponentConfig &config, const ReaderContext &context)
    {
        return std::make_unique<AstrodynamicSSTcostFunction>();
    }
    CapabilitySet getCapabilities() const override { return CapabilitySet{ Capability::AstrodynamicEnv }; };

    double getCost(std::shared_ptr<SSTnode<SpaceshipState>> parent, const SpaceshipState &currentState) override;
};



#endif //ASTRODYNAMICSSTCOSTFUNCTION_H
