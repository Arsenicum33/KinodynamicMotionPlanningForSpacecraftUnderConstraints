//
// Created by arseniy on 11.4.25.
//

#ifndef IFORCETOACCELERATIONCONVERTER_H
#define IFORCETOACCELERATIONCONVERTER_H
#include <components/IComponent.h>

#include "components/physics/totalForce/TotalForce.h"
#include "dto/totalAcceleration/TotalAcceleration.h"

template <typename StateType>
class IForceToAccelerationConverter : public IComponent
{
public:
    virtual TotalAcceleration convert(const TotalForce& force, const StateType& state) = 0;

    ComponentType getType() const override { return ComponentType::ForceToAccelerationConverter; };
};
#endif //IFORCETOACCELERATIONCONVERTER_H
