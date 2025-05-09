//
// Created by arseniy on 8.5.25.
//

#include "KinodynamicAgentModel.h"

std::unique_ptr<IComponent> KinodynamicAgentModel::createComponent(const ComponentConfig &config,
    const ReaderContext &context)
{
    const auto& configMap = config.config;

    double dryMass = std::any_cast<double>(configMap.at("dryMass"));

    return std::make_unique<KinodynamicAgentModel>(dryMass);
}

double KinodynamicAgentModel::getTotalMass(const State &state) const
{
    return dryMass;
}

Eigen::Matrix3d KinodynamicAgentModel::getInertiaTensor(const State &state) const
{
    if (!inertiaCached) {
        double constant = (3.0 / (4.0 * PI * SPACESHIP_DENSITY));
        double moment = (2.0 / 5.0) * std::pow(constant, 2.0 / 3.0) * std::pow(getTotalMass(state), 5.0 / 3.0);

        cachedInertia = Eigen::Matrix3d::Zero();
        cachedInertia.diagonal().setConstant(moment);
        inertiaCached = true;
    }
    return cachedInertia;
}
