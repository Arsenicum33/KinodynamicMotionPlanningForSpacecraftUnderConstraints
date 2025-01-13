//
// Created by arseniy on 13.1.25.
//

#ifndef IEXPORTER_H
#define IEXPORTER_H
#include "core/executor/IExecutor.h"

class IExporter
{
public:
    virtual ~IExporter() = default;
    virtual void exportOutput(ExecutorOutput executorOutput) = 0;
};

#endif //IEXPORTER_H
