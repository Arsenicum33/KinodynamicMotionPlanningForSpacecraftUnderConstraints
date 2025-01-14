//
// Created by arseniy on 13.1.25.
//

#ifndef EXECUTOR_H
#define EXECUTOR_H
#include "IExecutor.h"
#include "core/creator/IComponentManager.h"


class Executor : public IExecutor
{
public:
    ExecutorOutput run(IComponentManager* component_manager, EnvSettings envSettings) override;
};



#endif //EXECUTOR_H
