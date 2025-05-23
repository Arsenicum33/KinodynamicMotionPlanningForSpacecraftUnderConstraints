// MIT License
// Copyright (c) 2025 Arseniy Panyukov
//
// See the LICENSE file in the root directory for full license information.


#ifndef CELESTIALBODY_H
#define CELESTIALBODY_H
#include <dto/poses/dynamic/dynamicObject/DynamicObject.h>


class CelestialBody
{
public:
    CelestialBody(std::shared_ptr<Animation> animation, long double mass, double radius, std::string name)
        : animation(animation), mass(mass), radius(radius), name(name) {}

    long double  getMass() const { return mass; };
    const std::string& getName() const { return name; };
    double getRadius() const { return radius; };
    const Animation* getAnimation() const { return animation.get(); }
private:
    long double mass;
    std::string name;
    double radius;
    std::shared_ptr<Animation> animation;
};



#endif //CELESTIALBODY_H
