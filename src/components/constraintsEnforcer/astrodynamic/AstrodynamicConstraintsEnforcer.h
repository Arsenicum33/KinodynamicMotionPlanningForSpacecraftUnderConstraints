//
// Created by arseniy on 12.4.25.
//

#ifndef ASTRODYNAMICCONSTRAINTSENFORCER_H
#define ASTRODYNAMICCONSTRAINTSENFORCER_H
#include "components/constraintsEnforcer/IConstraintsEnforcer.h"
#include "components/constraintsEnforcer/kinodynamic/KinodynamicConstraintsEnforcer.h"
#include "dto/poses/astrodynamic/spaceshipState/SpaceshipState.h"


class AstrodynamicConstraintsEnforcer : public IConstraintsEnforcer<SpaceshipState>
{
public:
    AstrodynamicConstraintsEnforcer(std::unique_ptr<KinodynamicConstraintsEnforcer> kinodynamicConstraintsEnforcer) :
        kinodynamicConstraintsEnforcer(std::move(kinodynamicConstraintsEnforcer)) {}
    static std::unique_ptr<IComponent> createComponent(const ComponentConfig &config, const ReaderContext &context);

    CapabilitySet getCapabilities() const override { return CapabilitySet { Capability::AstrodynamicEnv }; };

    bool satisfiesConstraints(const SpaceshipState &position) const override;

    void resolveDependencies(const ComponentConfig &config, ComponentManager *manager) override;

private:
    std::unique_ptr<KinodynamicConstraintsEnforcer> kinodynamicConstraintsEnforcer;
};


#endif //ASTRODYNAMICCONSTRAINTSENFORCER_H
