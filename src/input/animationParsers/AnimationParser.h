// MIT License
// Copyright (c) 2025 Arseniy Panyukov
//
// See the LICENSE file in the root directory for full license information.


#ifndef ANIMATIONPARSER_H
#define ANIMATIONPARSER_H
#include <memory>


template <typename MeshType>
class  AnimationParser
{
public:
    virtual ~AnimationParser() = default;

    virtual std::shared_ptr<DynamicObject<MeshType>> parse(const std::string &filepath) = 0;
};

#endif //ANIMATIONPARSER_H
