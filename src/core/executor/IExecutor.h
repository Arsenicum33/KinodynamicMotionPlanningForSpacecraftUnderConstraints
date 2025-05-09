//
// Created by arseniy on 13.1.25.
//

#ifndef IEXECUTOR_H
#define IEXECUTOR_H
#include <variant>
#include <vector>
#include "core/creator/IComponentManager.h"

struct ExecutorOutput
{
    std::vector<std::any> path;
    int totalIterations;
    int totalTime;
    bool success;
};

class IExecutor
{
public:
    virtual ~IExecutor() = default;
    virtual ExecutorOutput run(IComponentManager* component_manager,const EnvSettings& envSettings) = 0;
};

#endif //IEXECUTOR_H
