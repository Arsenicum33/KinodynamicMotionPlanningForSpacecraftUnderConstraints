//
// Created by arseniy on 13.1.25.
//

#ifndef IVALIDATOR_H
#define IVALIDATOR_H
#include "components/Capability.h"
#include "core/executor/IExecutor.h"

class IValidator
{
public:
    virtual ~IValidator() = default;
    virtual void validate(IComponentManager* componentManager, const EnvSettings& envSettings,const ExecutorOutput& executorOutput) = 0;
    virtual void validateComponents(IComponentManager* componentManager, const ReaderContext& readerContext) = 0;


};

#endif //IVALIDATOR_H
