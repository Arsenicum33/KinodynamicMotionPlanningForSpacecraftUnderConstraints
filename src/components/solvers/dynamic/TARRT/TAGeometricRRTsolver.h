//
// Created by arseniy on 17.3.25.
//

#ifndef TARRT_H
#define TARRT_H
#include "components/solvers/AGeometricRRTsolver.h"

class TAGeometricRRTsolver : public AGeometricRRTsolver<Keyframe, Pose, Keyframe>
{
public:
    static std::unique_ptr<IComponent> createComponent(const ComponentConfig &config, const ReaderContext &context);
    TAGeometricRRTsolver(int maxIterations, double maxStepSize, double velocity, int outputPeriod) :
        AGeometricRRTsolver(maxIterations, maxStepSize, outputPeriod), velocity(velocity){}
    CapabilitySet getCapabilities() const override { return CapabilitySet { Capability::DynamicEnv }; }

protected:
    Keyframe getExtendedPosition(std::shared_ptr<const TreeNode<Keyframe>> neighbor, const Keyframe &sample) override;
    double velocity;
};



#endif //TARRT_H
