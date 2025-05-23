// MIT License
// Copyright (c) 2025 Arseniy Panyukov
//
// See the LICENSE file in the root directory for full license information.


#ifndef SPACESHIPSTATE_H
#define SPACESHIPSTATE_H
#include <dto/poses/dynamic/kinodynamic/state/State.h>

#include "dto/fuelState/FuelState.h"


class SpaceshipState : public State
{
public:
    SpaceshipState(State state, FuelState fuel) : State(state), fuel(fuel) {}
    const FuelState& getFuel() const { return fuel; }
    void setFuel(FuelState fuel) { this->fuel = fuel; }

    SpaceshipState operator+(const SpaceshipState &other) const; //only for operations with derivative

    SpaceshipState operator*(double factor) const; //only for operations with derivative
    void validate(const std::string& where) const override;

private:
    FuelState fuel;
};



#endif //SPACESHIPSTATE_H
