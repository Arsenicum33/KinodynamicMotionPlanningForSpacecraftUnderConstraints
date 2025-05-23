// MIT License
// Copyright (c) 2025 Arseniy Panyukov
//
// See the LICENSE file in the root directory for full license information.

#ifndef AGNAT_SST_H
#define AGNAT_SST_H
#include "components/nearestNeighbour/ompl/gnat/AGNATsearch.h"
#include "components/solvers/SST/SSTnode.h"

template <typename StateType>
class AGNAT_SST : public AGNATsearch<SSTnode<StateType>, StateType>
{
public:
    virtual bool isRemoved(const std::shared_ptr<SSTnode<StateType>>& node) const { return this->gnat.isRemoved(node); }

    void remove(std::shared_ptr<SSTnode<StateType>> state) override;

    void add(std::shared_ptr<SSTnode<StateType>> state) override;;
};

template<typename StateType>
void AGNAT_SST<StateType>::remove(std::shared_ptr<SSTnode<StateType>> state)
{
    //if (!state->parent.expired())
    //{
    //    state->parent.lock()->removeChild(state);
    //}
    //else
    //{
    //    spdlog::debug("Parent expired, node ", state->getIndex());
    //}
    AGNATsearch<SSTnode<StateType>, StateType>::remove(state);
}

template<typename StateType>
void AGNAT_SST<StateType>::add(std::shared_ptr<SSTnode<StateType>> state)
{
    if (!state->parent.expired())
        state->parent.lock()->children.push_back(state);
    AGNATsearch<SSTnode<StateType>, StateType>::add(state);
}

#endif //AGNAT_SST_H
