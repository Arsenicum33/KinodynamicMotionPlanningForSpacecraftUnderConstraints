//
// Created by arseniy on 3.5.25.
//

#ifndef GNATSEARCH_H
#define GNATSEARCH_H

#include <ompl/datastructures/NearestNeighborsGNAT.h>

#include "components/nearestNeighbour/ompl/OMPLnnSearch.h"

template <typename StoredType, typename SearchedType>
class AGNATsearch : public OMPLnnSearch<StoredType, SearchedType>
{
public:
    std::shared_ptr<StoredType> findNearest(const SearchedType& state) override;
    std::vector<std::shared_ptr<StoredType>> findRnearest(const SearchedType& state, double r) override;

    void add(std::shared_ptr<StoredType> state) override;

    void remove(std::shared_ptr<StoredType> state) override;

protected:
    ompl::NearestNeighborsGNAT<std::shared_ptr<StoredType>> gnat;

    virtual std::shared_ptr<StoredType> searchedTypeToStoredType(const SearchedType& state) const = 0;


};

template <typename StoredType, typename SearchedType>
std::shared_ptr<StoredType> AGNATsearch<StoredType, SearchedType>::findNearest(const SearchedType& state)
{
    std::shared_ptr<StoredType> stateAsStored = searchedTypeToStoredType(state);
    return gnat.nearest(stateAsStored);
}

template <typename StoredType, typename SearchedType>
std::vector<std::shared_ptr<StoredType>> AGNATsearch<StoredType, SearchedType>::findRnearest(const SearchedType& state, double r)
{
    std::vector<std::shared_ptr<StoredType>> result;
    std::shared_ptr<StoredType> stateAsStored = searchedTypeToStoredType(state);
    gnat.nearestR(stateAsStored, r, result);
    return result;
}

template <typename StoredType, typename SearchedType>
void AGNATsearch<StoredType, SearchedType>::add(std::shared_ptr<StoredType> state)
{
    gnat.add(state);
}

template <typename StoredType, typename SearchedType>
void AGNATsearch<StoredType, SearchedType>::remove(std::shared_ptr<StoredType> state)
{
    gnat.remove(state);
}


#endif //GNATSEARCH_H
