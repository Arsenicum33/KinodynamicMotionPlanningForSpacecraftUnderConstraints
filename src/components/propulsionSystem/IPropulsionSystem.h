//
// Created by arseniy on 7.4.25.
//

#ifndef IPROPULSIONSYSTEM_H
#define IPROPULSIONSYSTEM_H
#include <components/IComponent.h>

#include "dto/accelerationProfiles/AccelerationProfile.h"

template <typename ControlInput>
class IPropulsionSystem : public IComponent
{
public:
    virtual AccelerationProfile<ControlInput> generateAccelerationProfile(const ControlInput& controlInput) = 0;
};
#endif //IPROPULSIONSYSTEM_H
