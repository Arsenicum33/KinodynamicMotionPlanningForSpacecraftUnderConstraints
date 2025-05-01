//
// Created by arseniy on 23.3.25.
//

#ifndef KINODYNAMICTERMINATIONCONDITION_H
#define KINODYNAMICTERMINATIONCONDITION_H
#include <components/distanceMeasurement/IDistanceMetric.h>

#include "components/terminationConditions/ITerminationCondition.h"
#include "dto/poses/dynamic/kinodynamic/state/State.h"


class KinodynamicTerminationCondition : public ITerminationCondition<State, Animation>
{
public:
    static std::unique_ptr<IComponent> createComponent(const ComponentConfig &config, const ReaderContext &context);
    KinodynamicTerminationCondition(double threshold) : ITerminationCondition<State, Animation>(threshold) {}
    CapabilitySet getCapabilities() const override { return CapabilitySet{ Capability::KinodynamicEnv}; }

    void resolveDependencies(const ComponentConfig &config, ComponentManager *manager) override;

protected:
    double computeDistance(const State &currentPosition, const Animation &target) override;

    std::shared_ptr<IDistanceMetric> distanceMetric;
};



#endif //KINODYNAMICTERMINATIONCONDITION_H
