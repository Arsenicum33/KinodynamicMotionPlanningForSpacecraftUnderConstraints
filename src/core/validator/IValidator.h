// MIT License
// Copyright (c) 2025 Arseniy Panyukov
//
// See the LICENSE file in the root directory for full license information.


#ifndef IVALIDATOR_H
#define IVALIDATOR_H
#include "core/executor/IExecutor.h"

class IValidator
{
public:
    virtual ~IValidator() = default;
    virtual void validate(IComponentManager* componentManager, const EnvSettings& envSettings,const ExecutorOutput& executorOutput) = 0;
    virtual void validateComponents(IComponentManager* componentManager, const ReaderContext& readerContext) = 0;


};

#endif //IVALIDATOR_H
