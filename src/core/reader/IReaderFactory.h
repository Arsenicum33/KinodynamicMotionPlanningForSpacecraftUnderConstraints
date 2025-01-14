//
// Created by arseniy on 14.1.25.
//

#ifndef IREADERFACTORY_H
#define IREADERFACTORY_H
#include "IReader.h"

class IReaderFactory
{
public:
    virtual ~IReaderFactory() = default;
    virtual std::unique_ptr<IReader> createReader(int argc, char* argv[]) = 0;
};

#endif //IREADERFACTORY_H
