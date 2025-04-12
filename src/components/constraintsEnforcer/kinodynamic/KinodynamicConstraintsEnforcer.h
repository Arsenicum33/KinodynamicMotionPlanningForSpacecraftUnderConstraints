//
// Created by arseniy on 26.3.25.
//

#ifndef CONSTRAINTSENFORCER_H
#define CONSTRAINTSENFORCER_H
#include <dto/poses/dynamic/kinodynamic/state/State.h>

#include "components/constraintsEnforcer/IConstraintsEnforcer.h"


class KinodynamicConstraintsEnforcer : public IConstraintsEnforcer<State>
{
public:
    KinodynamicConstraintsEnforcer(double maxAngularVelocity, double maxTime)
        : maxAngularVelocity(maxAngularVelocity),
          maxTime(maxTime) {}

    static std::unique_ptr<IComponent> createComponent(const ComponentConfig &config, const ReaderContext &context);


    CapabilitySet getCapabilities() const override { return CapabilitySet{ Capability::KinodynamicEnv}; }

    bool satisfiesConstraints(const State &position) const override;

private:
    double maxAngularVelocity;
    double maxTime;
};



#endif //CONSTRAINTSENFORCER_H
