//
// Created by arseniy on 18.3.25.
//

#ifndef DYNAMICTERMINATIONCONDITION_H
#define DYNAMICTERMINATIONCONDITION_H
#include <components/distanceMeasurement/IDistanceMetric.h>

#include "components/terminationConditions/ITerminationCondition.h"


class DynamicTerminationCondition : public ITerminationCondition<Keyframe, Pose>
{
public:
    static std::unique_ptr<IComponent> createComponent(const ComponentConfig &config, const ReaderContext &context);
    DynamicTerminationCondition(double threshold) : ITerminationCondition<Keyframe, Pose>(threshold) {}

    CapabilitySet getCapabilities() const override { return CapabilitySet{Capability::DynamicEnv};}


    void resolveDependencies(const ComponentConfig &config, ComponentManager *manager) override;

protected:
    double computeDistance(const Keyframe &currentPosition, const Pose &target) override;

    std::shared_ptr<IDistanceMetric> distanceMetric;
};



#endif //DYNAMICTERMINATIONCONDITION_H
