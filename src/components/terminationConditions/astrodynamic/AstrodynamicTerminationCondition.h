// MIT License
// Copyright (c) 2025 Arseniy Panyukov
//
// See the LICENSE file in the root directory for full license information.


#ifndef ASTRODYNAMICTERMINATIONCONDITION_H
#define ASTRODYNAMICTERMINATIONCONDITION_H
#include <components/distanceMeasurement/IDistanceMetric.h>
#include <components/terminationConditions/ITerminationCondition.h>
#include <components/terminationConditions/kinodynamic/KinodynamicTerminationCondition.h>

#include "dto/poses/astrodynamic/celestialBody/CelestialBody.h"
#include "dto/poses/astrodynamic/spaceshipState/SpaceshipState.h"


class AstrodynamicTerminationCondition : public ITerminationCondition<SpaceshipState, CelestialBody>
{
public:
    static std::unique_ptr<IComponent> createComponent(const ComponentConfig &config, const ReaderContext &context);
    AstrodynamicTerminationCondition(double threshold) :
        ITerminationCondition<SpaceshipState, CelestialBody>(threshold) {}
    CapabilitySet getCapabilities() const override { return CapabilitySet{ Capability::AstrodynamicEnv}; }


    void resolveDependencies(const ComponentConfig &config, ComponentManager *manager) override;

protected:
    double computeDistance(const SpaceshipState &currentPosition, const CelestialBody &target) override;

    void outputDebugInfo(const SpaceshipState &currentPosition) override;

private:
    std::shared_ptr<IDistanceMetric> distanceMetric;
};



#endif //ASTRODYNAMICTERMINATIONCONDITION_H
