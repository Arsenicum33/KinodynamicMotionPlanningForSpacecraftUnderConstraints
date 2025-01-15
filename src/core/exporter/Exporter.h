//
// Created by arseniy on 13.1.25.
//

#ifndef EXPORTER_H
#define EXPORTER_H
#include "IExporter.h"


class Exporter : public IExporter
{
public:
    void exportOutput(IComponentManager* componentManager,ExecutorOutput executorOutput) override;
};



#endif //EXPORTER_H
