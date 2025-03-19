//
// Created by arseniy on 13.1.25.
//

#include "HighLevelExporter.h"

#include <components/collisionHandlers/ICollisionHandler.h>
#include <components/exporters/ATypedExporter.h>

void HighLevelExporter::exportOutput(IComponentManager* componentManager,ExecutorOutput executorOutput)
{
     std::shared_ptr<IComponent> exporterComponent = componentManager->getComponent(ComponentType::Exporter);
     std::shared_ptr<IPositionExporter> exporter = std::dynamic_pointer_cast<IPositionExporter>(exporterComponent);
     exporter->exportPositions(executorOutput.path);
}
