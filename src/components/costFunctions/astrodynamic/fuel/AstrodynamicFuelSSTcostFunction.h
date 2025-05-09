//
// Created by arseniy on 9.5.25.
//

#ifndef ASTRODYNAMICFUELSSTCOSTFUNCTION_H
#define ASTRODYNAMICFUELSSTCOSTFUNCTION_H
#include "components/costFunctions/ISSTcostFunction.h"
#include "dto/poses/astrodynamic/spaceshipState/SpaceshipState.h"


class AstrodynamicFuelSSTcostFunction : public ISSTcostFunction<SpaceshipState>
{
public:
    static std::unique_ptr<IComponent> createComponent(const ComponentConfig &config, const ReaderContext &context)
    {
        return std::make_unique<AstrodynamicFuelSSTcostFunction>();
    }
    CapabilitySet getCapabilities() const override { return CapabilitySet{ Capability::AstrodynamicEnv }; };

    double getCost(std::shared_ptr<SSTnode<SpaceshipState>> parent, const SpaceshipState &currentState) override;
};



#endif //ASTRODYNAMICFUELSSTCOSTFUNCTION_H
