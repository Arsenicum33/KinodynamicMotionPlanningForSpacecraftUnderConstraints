//
// Created by arseniy on 13.1.25.
//

#ifndef IEXECUTOR_H
#define IEXECUTOR_H
#include <variant>
#include <vector>
#include <dto/EnvSettings.h>

#include "poses/static/Pose.h"
#include "core/creator/IComponentManager.h"

struct ExecutorOutput
{
    std::vector<std::any> path;
};

class IExecutor
{
public:
    virtual ~IExecutor() = default;
    virtual ExecutorOutput run(IComponentManager* component_manager, EnvSettings envSettings) = 0;
};

#endif //IEXECUTOR_H
