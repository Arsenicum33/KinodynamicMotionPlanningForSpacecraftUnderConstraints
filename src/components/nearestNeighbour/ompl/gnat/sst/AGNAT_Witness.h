//
// Created by arseniy on 4.5.25.
//

#ifndef AGNAT_WITNESS_H
#define AGNAT_WITNESS_H
#include "components/nearestNeighbour/ompl/gnat/AGNATsearch.h"
#include "components/solvers/SST/Witness.h"

template <typename StateType>
class AGNAT_Witness : public AGNATsearch<Witness<StateType>, StateType> {};

#endif //AGNAT_WITNESS_H
