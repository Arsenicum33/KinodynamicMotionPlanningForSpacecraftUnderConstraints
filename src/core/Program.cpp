//
// Created by arseniy on 13.1.25.
//

#include "Program.h"

void Program::run()
{
    spdlog::info("Program started");
    ReaderContext context = reader->run();
    componentManager->initialize(context);
    validator->validateComponents(componentManager.get(), context);
    ExecutorOutput result = executor->run(componentManager.get(), context.envSettings);
    validator->validate(componentManager.get(), context.envSettings, result);
    exporter->exportOutput(componentManager.get(), result);
}

