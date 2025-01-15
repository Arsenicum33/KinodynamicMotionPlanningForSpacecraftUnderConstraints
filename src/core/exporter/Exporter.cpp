//
// Created by arseniy on 13.1.25.
//

#include "Exporter.h"

#include <components/exporters/AbstractExporter.h>

void Exporter::exportOutput(IComponentManager* componentManager,ExecutorOutput executorOutput)
{
    std::shared_ptr<AbstractExporter> exporter = std::dynamic_pointer_cast<AbstractExporter>(componentManager->getComponent("Exporter"));
   // exporter->exportPoses(executorOutput.poses);
}
