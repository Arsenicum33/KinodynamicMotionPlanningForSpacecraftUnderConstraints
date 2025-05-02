//
// Created by arseniy on 9.4.25.
//

#include "SpaceshipState.h"

#include <spdlog/spdlog.h>

SpaceshipState SpaceshipState::operator+(const SpaceshipState &other) const
{
    State stateSum = State::operator+(other);
    return SpaceshipState(stateSum, fuel + other.fuel);
}

SpaceshipState SpaceshipState::operator*(double factor) const
{
    State stateSum = State::operator*(factor);
    return SpaceshipState(stateSum, fuel * factor);
}

void SpaceshipState::validate(const std::string& where) const
{
    State::validate(where);
    if (!std::isfinite(fuel.getMainThrusterFuel()) || !std::isfinite(fuel.getRotationThrustersFuel()))
        spdlog::debug("SpaceshipState fuel invalid in {}", where);

}
