//
// Created by arseniy on 1.4.25.
//

#ifndef CELESTIALBODY_H
#define CELESTIALBODY_H
#include <dto/poses/dynamic/dynamicObject/DynamicObject.h>


class CelestialBody : public DynamicObject<RAPID_model>
{
public:
    CelestialBody(std::shared_ptr<Animation> animation, std::shared_ptr<RAPID_model> mesh,
        long double mass, double radius, std::string name)
        : DynamicObject<RAPID_model>(animation, mesh),
          mass(mass), radius(radius), name(name) {}

    unsigned long long getMass() const { return mass; };
    const std::string& getName() const { return name; };
    double getRadius() const { return radius; };
private:
    long double mass;
    std::string name;
    double radius;
};



#endif //CELESTIALBODY_H
