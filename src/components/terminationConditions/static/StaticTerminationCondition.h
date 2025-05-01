//
// Created by arseniy on 8.3.25.
//

#ifndef DEFAULTSTATICTERMINATIONCONDITION_H
#define DEFAULTSTATICTERMINATIONCONDITION_H
#include <components/distanceMeasurement/IDistanceMetric.h>
#include "components/terminationConditions/ITerminationCondition.h"

//TODO: incorporate this class into appropriate solvers
class StaticTerminationCondition : public ITerminationCondition<Pose, Pose>
{
public:
    static std::unique_ptr<IComponent> createComponent(const ComponentConfig &config, const ReaderContext &context);

    StaticTerminationCondition(double threshold) : ITerminationCondition<Pose, Pose>(threshold) {}

    CapabilitySet getCapabilities() const override { return CapabilitySet {Capability::StaticEnv, Capability::DynamicEnv}; }

    void resolveDependencies(const ComponentConfig &config, ComponentManager *manager) override;

protected:
    double computeDistance(const Pose &currentPosition, const Pose &target) override;

private:
    std::shared_ptr<IDistanceMetric> distanceMetric;
};



#endif //DEFAULTSTATICTERMINATIONCONDITION_H
