//
// Created by arseniy on 13.1.25.
//

#ifndef VALIDATOR_H
#define VALIDATOR_H
#include "IValidator.h"


class Validator : public IValidator
{
public:
    void validate(IComponentManager* componentManager, const EnvSettings& envSettings, const ExecutorOutput& executorOutput) override;

    void validateComponents(IComponentManager *componentManager, const ReaderContext& readerContext) override;

private:
    void validateStatic(IComponentManager* componentManager, const EnvSettings& envSettings, const ExecutorOutput& executorOutput);
    void validateDynamic(IComponentManager* componentManager, const EnvSettings& envSettings, const ExecutorOutput& executorOutput);
    CapabilitySet deduceCapabilitySet(const ReaderContext& readerContext);
};



#endif //VALIDATOR_H
