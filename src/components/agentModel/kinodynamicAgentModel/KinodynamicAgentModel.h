//
// Created by arseniy on 8.5.25.
//

#ifndef KINODYNAMICAGENTMODEL_H
#define KINODYNAMICAGENTMODEL_H
#include <dto/poses/dynamic/kinodynamic/state/State.h>

#include "components/agentModel/IAgentModel.h"


class KinodynamicAgentModel : public IAgentModel<State>
{
public:
    static std::unique_ptr<IComponent> createComponent(const ComponentConfig &config, const ReaderContext &context);

    KinodynamicAgentModel(double dryMass)
        : dryMass(dryMass)
    {}

    CapabilitySet getCapabilities() const override { return CapabilitySet { Capability::KinodynamicEnv};}

    double getTotalMass(const State &state) const override;

    Eigen::Matrix3d getInertiaTensor(const State &state) const override;
private:
    double dryMass;
    mutable bool inertiaCached = false;
    mutable Eigen::Matrix3d cachedInertia;
};


#endif //KINODYNAMICAGENTMODEL_H
