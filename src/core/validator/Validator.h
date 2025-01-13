//
// Created by arseniy on 13.1.25.
//

#ifndef VALIDATOR_H
#define VALIDATOR_H
#include "IValidator.h"


class Validator : public IValidator
{
public:
    void validate(ExecutorOutput executorOutput) override;
};



#endif //VALIDATOR_H
