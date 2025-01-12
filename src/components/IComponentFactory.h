//
// Created by arseniy on 11.1.25.
//

#ifndef ICOMPONENTFACTORY_H
#define ICOMPONENTFACTORY_H
#include <any>
#include <memory>
#include <unordered_map>

template <typename T>
class IComponentFactory
{
public:
    virtual ~IComponentFactory() = default;

    virtual T* createComponent(std::unordered_map<std::string, std::any> data) = 0;
};

#endif //ICOMPONENTFACTORY_H
