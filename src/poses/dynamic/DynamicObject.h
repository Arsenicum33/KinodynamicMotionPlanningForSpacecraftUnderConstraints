//
// Created by arseniy on 2.1.25.
//

#ifndef DYNAMICOBJECT_H
#define DYNAMICOBJECT_H
#include <memory>
#include <RAPID.H>

#include "Animation.h"

template <typename MeshType>
class DynamicObject
{
public:
    DynamicObject(std::unique_ptr<Animation> animation, std::unique_ptr<MeshType> mesh)
    : animation(std::move(animation)), mesh(std::move(mesh)) {}

    const Animation* getAnimation() const { return animation.get(); }
    const MeshType* getMesh() const { return mesh.get(); }
private:
    std::unique_ptr<Animation> animation;
    std::unique_ptr<MeshType> mesh;
};



#endif //DYNAMICOBJECT_H
