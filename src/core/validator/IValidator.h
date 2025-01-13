//
// Created by arseniy on 13.1.25.
//

#ifndef IVALIDATOR_H
#define IVALIDATOR_H
#include "core/executor/IExecutor.h"

class IValidator
{
public:
    virtual ~IValidator() = default;
    virtual void validate(ExecutorOutput executorOutput) = 0;
};

#endif //IVALIDATOR_H
