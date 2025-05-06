//
// Created by arseniy on 3.5.25.
//

#ifndef OMPLNNSEARCH_H
#define OMPLNNSEARCH_H
#include "components/nearestNeighbour/INearestNeighborSearch.h"

template <typename StoredType, typename SearchedType>
class OMPLnnSearch : public INearestNeighborSearch {
public:
    virtual std::shared_ptr<StoredType> findNearest(const SearchedType& state) = 0;
    virtual std::vector<std::shared_ptr<StoredType>> findRnearest(const SearchedType& state, double r) = 0;
    virtual void add(std::shared_ptr<StoredType> state) = 0;
    virtual void remove(std::shared_ptr<StoredType> state) = 0;

    virtual ~OMPLnnSearch() = default;
};

#endif //OMPLNNSEARCH_H
