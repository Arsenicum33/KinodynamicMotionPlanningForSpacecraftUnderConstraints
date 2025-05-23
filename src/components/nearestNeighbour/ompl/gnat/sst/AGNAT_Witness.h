// MIT License
// Copyright (c) 2025 Arseniy Panyukov
//
// See the LICENSE file in the root directory for full license information.


#ifndef AGNAT_WITNESS_H
#define AGNAT_WITNESS_H
#include "components/nearestNeighbour/ompl/gnat/AGNATsearch.h"
#include "components/solvers/SST/Witness.h"

template <typename StateType>
class AGNAT_Witness : public AGNATsearch<Witness<StateType>, StateType> {};

#endif //AGNAT_WITNESS_H
