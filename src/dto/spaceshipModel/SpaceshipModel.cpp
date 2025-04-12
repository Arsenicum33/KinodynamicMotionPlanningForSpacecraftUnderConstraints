//
// Created by arseniy on 9.4.25.
//

#include "SpaceshipModel.h"

#define SPACESHIP_DENSITY 100
#define PI 3.1415926
Eigen::Matrix3d SpaceshipModel::getInertiaTensor(const SpaceshipState &state) const
{
    double mass = getTotalMass(state);
    double constant = (3.0 / (4.0 * PI * SPACESHIP_DENSITY));
    double moment = (2.0/5.0) * std::pow(constant, 2.0 / 3.0) * std::pow(mass, 5.0 / 3.0);
    Eigen::Matrix3d inertiaTensor = Eigen::Matrix3d::Zero();
    inertiaTensor(0, 0) = moment;
    inertiaTensor(1, 1) = moment;
    inertiaTensor(2, 2) = moment;
    return inertiaTensor;
}
