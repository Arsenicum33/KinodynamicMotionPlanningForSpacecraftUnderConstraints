//
// Created by arseniy on 17.3.25.
//

#ifndef TARRT_H
#define TARRT_H
#include "components/solvers/newHierarchy/ARRTsolver.h"


class TARRTsolver : public ARRTsolver<Keyframe, Pose>
{
public:
    static std::unique_ptr<IComponent> createComponent(const ComponentConfig &config, const ReaderContext &context);
    TARRTsolver(int maxIterations, double maxStepSize, double velocity, int outputPeriod) :
        ARRTsolver(maxIterations, maxStepSize, outputPeriod), velocity(velocity){}
    CapabilitySet getCapabilities() const override { return CapabilitySet { Capability::DynamicEnv }; }

protected:
    Keyframe getExtendedPosition(std::shared_ptr<const TreeNode<Keyframe>> neighbor, const Keyframe &sample) override;
    double velocity;
};



#endif //TARRT_H
