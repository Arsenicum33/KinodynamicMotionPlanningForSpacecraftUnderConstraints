// MIT License
// Copyright (c) 2025 Arseniy Panyukov
//
// See the LICENSE file in the root directory for full license information.


#ifndef IREADERFACTORY_H
#define IREADERFACTORY_H
#include "core/reader/IReader.h"


class IReaderFactory
{
public:
    virtual ~IReaderFactory() = default;
    virtual std::unique_ptr<IReader> createReader(int argc, char* argv[]) = 0;
};

#endif //IREADERFACTORY_H
