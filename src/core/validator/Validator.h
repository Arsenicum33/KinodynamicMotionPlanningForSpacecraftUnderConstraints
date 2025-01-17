//
// Created by arseniy on 13.1.25.
//

#ifndef VALIDATOR_H
#define VALIDATOR_H
#include "IValidator.h"


class Validator : public IValidator
{
public:
    void validate(IComponentManager* component_manager, EnvSettings envSettings, ExecutorOutput executorOutput) override;
    void test_dynamic_collisions(IComponentManager* component_manager, EnvSettings envSettings) override;
};



#endif //VALIDATOR_H
