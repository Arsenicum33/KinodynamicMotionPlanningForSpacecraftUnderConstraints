//
// Created by arseniy on 13.1.25.
//

#ifndef EXECUTOR_H
#define EXECUTOR_H
#include "IExecutor.h"


class Executor : public IExecutor
{
public:
    ExecutorOutput run() override;
};



#endif //EXECUTOR_H
