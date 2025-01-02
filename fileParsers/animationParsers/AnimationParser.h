//
// Created by arseniy on 2.1.25.
//

#ifndef ANIMATIONPARSER_H
#define ANIMATIONPARSER_H
#include <memory>

#include "../../poses/dynamic/DynamicObject.h"

template <typename MeshType>
class  AnimationParser
{
public:
    virtual ~AnimationParser() = default;

    virtual std::unique_ptr<DynamicObject<MeshType>> parse(const std::string& filepath) = 0;
};

#endif //ANIMATIONPARSER_H
