//
// Created by arseniy on 2.1.25.
//

#ifndef DYNAMICOBJECT_H
#define DYNAMICOBJECT_H
#include <memory>
#include <RAPID.H>
#include "dto/poses/dynamic/animation/Animation.h"

template <typename MeshType>
class DynamicObject
{
public:
    DynamicObject(std::unique_ptr<Animation> animation, std::shared_ptr<MeshType> mesh)
    : animation(std::move(animation)), mesh(std::move(mesh)) {}

    const Animation* getAnimation() const { return animation.get(); }
    MeshType* getMesh() const { return mesh.get(); }
private:
    std::unique_ptr<Animation> animation;
    std::shared_ptr<MeshType> mesh;
};



#endif //DYNAMICOBJECT_H
