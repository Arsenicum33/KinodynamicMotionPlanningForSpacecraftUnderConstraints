//
// Created by arseniy on 15.1.25.
//

#ifndef DISTANCECOSTFUNCTION_H
#define DISTANCECOSTFUNCTION_H
#include <components/distanceMeasurement/IDistanceMetric.h>

#include "ICostFunction.h"


class DistanceTimeFunction : public ICostFunction<Keyframe>
{
public:
    DistanceTimeFunction(double velocity)
        : velocity(velocity) {}

    void apply(const TreeNode<Keyframe> &nearestNode, TreeNode<Keyframe> &newNode) override;

    void resolveDependencies(const ComponentConfig &config, ComponentManager *manager) override;

private:
    double velocity;
    std::shared_ptr<IDistanceMetric> distanceMetric;
};



#endif //DISTANCECOSTFUNCTION_H
