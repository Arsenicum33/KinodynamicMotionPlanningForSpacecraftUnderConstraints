//
// Created by arseniy on 13.1.25.
//

#ifndef IVALIDATOR_H
#define IVALIDATOR_H
#include "core/executor/IExecutor.h"

class IValidator
{
public:
    virtual ~IValidator() = default;
    virtual void validate(IComponentManager* component_manager, EnvSettings envSettings,ExecutorOutput executorOutput) = 0;
    virtual void test_dynamic_collisions(IComponentManager* component_manager, EnvSettings envSettings) = 0;
};

#endif //IVALIDATOR_H
