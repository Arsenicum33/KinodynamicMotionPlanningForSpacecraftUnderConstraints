//
// Created by arseniy on 13.1.25.
//

#ifndef HIGHLEVELEXPORTER_H
#define HIGHLEVELEXPORTER_H
#include "IHighLevelExporter.h"


class HighLevelExporter : public IHighLevelExporter
{
public:
    void exportOutput(IComponentManager* componentManager,ExecutorOutput executorOutput) override;
};



#endif //HIGHLEVELEXPORTER_H
