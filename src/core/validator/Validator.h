// MIT License
// Copyright (c) 2025 Arseniy Panyukov
//
// See the LICENSE file in the root directory for full license information.

#ifndef VALIDATOR_H
#define VALIDATOR_H
#include "IValidator.h"
#include "components/capabilities/Capability.h"


class Validator : public IValidator
{
public:
    void validate(IComponentManager* componentManager, const EnvSettings& envSettings, const ExecutorOutput& executorOutput) override;

    void validateComponents(IComponentManager *componentManager, const ReaderContext& readerContext) override;

};



#endif //VALIDATOR_H
