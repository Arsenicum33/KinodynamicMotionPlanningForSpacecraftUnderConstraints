//
// Created by arseniy on 13.1.25.
//

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
