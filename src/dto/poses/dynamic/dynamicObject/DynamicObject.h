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
    DynamicObject(std::shared_ptr<Animation> animation, std::shared_ptr<MeshType> mesh)
    : animation(animation), mesh(mesh) {}

    const Animation* getAnimation() const { return animation.get(); }
    RAPID_model *getMesh() const { return mesh.get(); }

    std::shared_ptr<Animation> animation;
    std::shared_ptr<MeshType> mesh;
};



#endif //DYNAMICOBJECT_H
