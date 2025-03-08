//
// Created by arseniy on 8.3.25.
//

#ifndef DEFAULTSTATICTERMINATIONCONDITION_H
#define DEFAULTSTATICTERMINATIONCONDITION_H
#include <components/distanceMeasurement/IDistanceMetric.h>
#include <poses/static/Pose.h>

#include "ITerminationCondition.h"

//TODO: incorporate this class into appropriate solvers
class DefaultTerminationCondition : public ITerminationCondition<Pose, Pose>
{
public:
    DefaultTerminationCondition(double threshold) : threshold(threshold) {}

    CapabilitySet getCapabilities() const override { return CapabilitySet {Capability::StaticEnv, Capability::DynamicEnv}; }

    bool isTargetReached(const Pose &currentPosition, const Pose& target) const override;

    void resolveDependencies(const ComponentConfig &config, ComponentManager *manager) override;

private:
    double threshold;
    std::shared_ptr<IDistanceMetric> distanceMetric;
};



#endif //DEFAULTSTATICTERMINATIONCONDITION_H
