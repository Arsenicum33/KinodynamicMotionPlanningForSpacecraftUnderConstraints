// MIT License
// Copyright (c) 2025 Arseniy Panyukov
//
// See the LICENSE file in the root directory for full license information.


#ifndef IAGENTMODEL_H
#define IAGENTMODEL_H
#include <components/IComponent.h>

#define SPACESHIP_DENSITY 100
#define PI 3.1415926

template <typename StateType>
class IAgentModel : public IComponent
{
public:
    virtual double getTotalMass(const StateType& state) const = 0;
    virtual Eigen::Matrix3d getInertiaTensor(const StateType& state) const = 0;

    ComponentType getType() const override { return ComponentType::AgentModel; }
};

#endif //IAGENTMODEL_H
