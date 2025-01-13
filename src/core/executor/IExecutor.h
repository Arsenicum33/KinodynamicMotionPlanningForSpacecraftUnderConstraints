//
// Created by arseniy on 13.1.25.
//

#ifndef IEXECUTOR_H
#define IEXECUTOR_H

struct ExecutorOutput
{

};

class IExecutor
{
public:
    virtual ~IExecutor() = default;
    virtual ExecutorOutput run() = 0;
};

#endif //IEXECUTOR_H
