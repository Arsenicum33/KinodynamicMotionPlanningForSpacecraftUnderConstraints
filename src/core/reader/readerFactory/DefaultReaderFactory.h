//
// Created by arseniy on 14.1.25.
//

#ifndef DEFAULTREADERFACTORY_H
#define DEFAULTREADERFACTORY_H
#include "IReaderFactory.h"


class DefaultReaderFactory : public IReaderFactory
{
public:
    std::unique_ptr<IReader> createReader(int argc, char* argv[]) override;
};



#endif //DEFAULTREADERFACTORY_H
