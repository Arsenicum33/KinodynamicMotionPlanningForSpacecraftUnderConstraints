//
// Created by arseniy on 13.1.25.
//

#include "Program.h"

#include "components/capabilities/manager/CapabilityManager.h"


void Program::run()
{
    spdlog::info("Program started");
    ReaderContext context = reader->run();
    CapabilityManager::build(context);
    componentManager->initialize(context);
    validator->validateComponents(componentManager.get(), context);
    ExecutorOutput result = executor->run(componentManager.get(), *(context.envSettings.get()));
    validator->validate(componentManager.get(), *(context.envSettings.get()), result);
    exporter->exportOutput(componentManager.get(), result);
}

