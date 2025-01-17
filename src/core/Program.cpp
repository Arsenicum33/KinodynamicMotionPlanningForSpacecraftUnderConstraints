//
// Created by arseniy on 13.1.25.
//

#include "Program.h"

void Program::run()
{
    ReaderContext context = reader->run();
   // context.obstacles.clear();
    componentManager->initialize(context);
    validator->test_dynamic_collisions(componentManager.get(), context.envSettings);
    ExecutorOutput result = executor->run(componentManager.get(), context.envSettings);
    validator->validate(componentManager.get(), context.envSettings, result);
    exporter->exportOutput(componentManager.get(), result);
}

