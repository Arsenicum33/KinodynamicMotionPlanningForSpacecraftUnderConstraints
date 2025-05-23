// MIT License
// Copyright (c) 2025 Arseniy Panyukov
//
// See the LICENSE file in the root directory for full license information.

#ifndef DEFAULTREADERFACTORY_H
#define DEFAULTREADERFACTORY_H
#include "IReaderFactory.h"


class DefaultReaderFactory : public IReaderFactory
{
public:
    std::unique_ptr<IReader> createReader(int argc, char* argv[]) override;
};



#endif //DEFAULTREADERFACTORY_H
