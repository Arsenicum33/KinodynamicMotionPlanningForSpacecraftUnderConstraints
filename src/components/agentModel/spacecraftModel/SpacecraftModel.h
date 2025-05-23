// MIT License
// Copyright (c) 2025 Arseniy Panyukov
//
// See the LICENSE file in the root directory for full license information.


#ifndef SPACECRAFTMODEL_H
#define SPACECRAFTMODEL_H
#include "components/agentModel/IAgentModel.h"
#include "dto/poses/astrodynamic/spaceshipState/SpaceshipState.h"


class SpacecraftModel : public IAgentModel<SpaceshipState>
{
public:
    static std::unique_ptr<IComponent> createComponent(const ComponentConfig &config, const ReaderContext &context);

    SpacecraftModel(double dryMass, const FuelState &initialFuel, double mainThrusterFuelToMassRatio,
        double rotationThrustersFuelToMassRatio)
        : dryMass(dryMass),
          initialFuel(initialFuel),
          mainThrusterFuelToMassRatio(mainThrusterFuelToMassRatio),
          rotationThrustersFuelToMassRatio(rotationThrustersFuelToMassRatio)
    {}

    CapabilitySet getCapabilities() const override { return CapabilitySet { Capability::AstrodynamicEnv};}

    double getTotalMass(const SpaceshipState &state) const override;

    Eigen::Matrix3d getInertiaTensor(const SpaceshipState &state) const override;

    FuelState getInitialFuel() const { return initialFuel;}
private:
    double dryMass;
    FuelState initialFuel;
    double mainThrusterFuelToMassRatio;
    double rotationThrustersFuelToMassRatio;
};



#endif //SPACECRAFTMODEL_H
