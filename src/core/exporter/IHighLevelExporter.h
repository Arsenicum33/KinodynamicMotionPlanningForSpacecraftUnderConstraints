// MIT License
// Copyright (c) 2025 Arseniy Panyukov
//
// See the LICENSE file in the root directory for full license information.


#ifndef IEXPORTER_H
#define IEXPORTER_H
#include "core/executor/IExecutor.h"

class IHighLevelExporter
{
public:
    virtual ~IHighLevelExporter() = default;
    virtual void exportOutput(IComponentManager* componentManager, ExecutorOutput executorOutput) = 0;
};

#endif //IEXPORTER_H
