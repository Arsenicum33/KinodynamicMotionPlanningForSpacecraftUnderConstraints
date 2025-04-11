//
// Created by arseniy on 7.4.25.
//

#ifndef IPROPULSIONSYSTEM_H
#define IPROPULSIONSYSTEM_H
#include <components/IComponent.h>

#include <dto/controlInputPlan/ControlInputPlan.h>

template <typename ControlInput>
class IPropulsionSystem : public IComponent
{
public:
    virtual ControlInputPlan<ControlInput> generateControlInputPlan(const ControlInput& controlInput) = 0;
};
#endif //IPROPULSIONSYSTEM_H
