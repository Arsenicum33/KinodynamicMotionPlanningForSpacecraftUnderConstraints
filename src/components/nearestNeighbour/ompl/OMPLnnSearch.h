// MIT License
// Copyright (c) 2025 Arseniy Panyukov
//
// See the LICENSE file in the root directory for full license information.

#ifndef OMPLNNSEARCH_H
#define OMPLNNSEARCH_H
#include "components/nearestNeighbour/INearestNeighborSearch.h"

template <typename StoredType, typename SearchedType>
class OMPLnnSearch : public INearestNeighborSearch<StoredType, SearchedType> {
public:
    virtual void remove(std::shared_ptr<StoredType> state) = 0;
    virtual std::vector<std::shared_ptr<StoredType>> findRnearest(const SearchedType& state, double r) = 0;
    virtual ~OMPLnnSearch() = default;
};

#endif //OMPLNNSEARCH_H
