//
// Created by arseniy on 11.1.25.
//

#ifndef ICOMPONENTFACTORY_H
#define ICOMPONENTFACTORY_H
#include <any>
#include <memory>
#include <unordered_map>

#include "core/creator/ComponentManager.h"
#include "core/reader/IReader.h"
#include "input/ComponentsParser.h"

template <typename T>
class IComponentFactory
{
public:
    virtual ~IComponentFactory() = default;

    virtual std::shared_ptr<T> createComponent(const ComponentConfig &config, const ReaderContext &context) = 0;
};

#endif //ICOMPONENTFACTORY_H
