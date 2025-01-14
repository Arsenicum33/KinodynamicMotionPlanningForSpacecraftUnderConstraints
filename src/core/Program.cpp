//
// Created by arseniy on 13.1.25.
//

#include "Program.h"

void Program::run()
{
    ReaderContext context = reader->run();
    componentManager->initialize(context);
    auto result = executor->run(componentManager.get(), context.envSettings);
    printf("result");
}
