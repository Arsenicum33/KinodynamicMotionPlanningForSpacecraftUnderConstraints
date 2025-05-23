// MIT License
// Copyright (c) 2025 Arseniy Panyukov
//
// See the LICENSE file in the root directory for full license information.


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

