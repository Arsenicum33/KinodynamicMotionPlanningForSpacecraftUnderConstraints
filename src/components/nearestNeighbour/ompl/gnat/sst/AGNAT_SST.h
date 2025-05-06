//
// Created by arseniy on 4.5.25.
//

#ifndef AGNAT_SST_H
#define AGNAT_SST_H
#include "components/nearestNeighbour/ompl/gnat/AGNATsearch.h"
#include "components/solvers/SST/SSTnode.h"

template <typename StateType>
class AGNAT_SST : public AGNATsearch<SSTnode<StateType>, StateType> {};

#endif //AGNAT_SST_H
