// MIT License
// Copyright (c) 2025 Arseniy Panyukov
//
// See the LICENSE file in the root directory for full license information.

#ifndef WITNESS_H
#define WITNESS_H
#include <array>
#include <limits>
#include <memory>
#include "components/solvers/SST/SSTnode.h"

template <typename StateType>
class Witness
{
public:
    std::array<double, 3> position;
    std::shared_ptr<SSTnode<StateType>> rep;


    Witness(const std::array<double, 3>& pos, std::shared_ptr<SSTnode<StateType>> rep = nullptr)
        : position(pos), rep(rep) {}

    bool hasRepresentative() const {
        return static_cast<bool>(rep);
    }

    double repCost() const {
        return rep ? rep->cost : std::numeric_limits<double>::infinity();
    }
};

#endif //WITNESS_H
