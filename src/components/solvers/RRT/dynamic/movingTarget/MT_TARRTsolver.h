// MIT License
// Copyright (c) 2025 Arseniy Panyukov
//
// See the LICENSE file in the root directory for full license information.


#ifndef MT_TARRT_H
#define MT_TARRT_H

#include "components/solvers/RRT/AGeometricRRTsolver.h"

class MT_TARRTsolver : public AGeometricRRTsolver<Keyframe, Animation, Keyframe>
{
public:
    static std::unique_ptr<IComponent> createComponent(const ComponentConfig &config, const ReaderContext &context);
    MT_TARRTsolver(int maxIterations, double maxStepSize, double velocity, int outputPeriod) :
        AGeometricRRTsolver(maxIterations, maxStepSize, outputPeriod), velocity(velocity){}
    CapabilitySet getCapabilities() const override { return CapabilitySet { Capability::DynamicEnv, Capability::MovingTarget }; }

protected:
    Keyframe getExtendedPosition(std::shared_ptr<const TreeNode<Keyframe>> neighbor, const Keyframe &sample) override;
    double velocity;
};



#endif //MT_TARRT_H
