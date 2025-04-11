//
// Created by arseniy on 11.4.25.
//

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
    AstrodynamicTerminationCondition(std::unique_ptr<KinodynamicTerminationCondition> terminationCondition) :
        terminationCondition(std::move(terminationCondition)) {}
    CapabilitySet getCapabilities() const override { return CapabilitySet{ Capability::AstrodynamicEnv}; }

    bool isTargetReached(const SpaceshipState &currentPosition, const CelestialBody &target) override;

    void resolveDependencies(const ComponentConfig &config, ComponentManager *manager) override;

private:
    double minDistToGoal = std::numeric_limits<double>::max();
    std::shared_ptr<IDistanceMetric> distanceMetric;
    std::unique_ptr<KinodynamicTerminationCondition> terminationCondition;
};



#endif //ASTRODYNAMICTERMINATIONCONDITION_H
