//
// Created by arseniy on 10.4.25.
//

#ifndef TOTALFORCE_H
#define TOTALFORCE_H
#include <array>
#include <utils/PhysicsUtils.h>

class TotalForce
{
public:
    TotalForce() : force{0, 0, 0}, torque{0, 0, 0} {}
    TotalForce(std::array<double, 3>  force, std::array<double, 3>  torque) : force(force), torque(torque) {}

    const std::array<double, 3>& getForce() const { return force; }
    const std::array<double, 3>& getTorque() const { return torque; }


    TotalForce operator+(const TotalForce& other) const {
        using namespace PhysicsUtils;
        return TotalForce(force + other.force, torque + other.torque);
    }
    TotalForce &operator+=(const TotalForce & other)
    {
        using namespace PhysicsUtils;
        force+=other.force;
        torque+=other.torque;
        return *this;
    }


private:
    std::array<double, 3> force;  // Linear force (N)
    std::array<double, 3> torque; // Torque (N·m)
};

#endif //TOTALFORCE_H
