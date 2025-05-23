// MIT License
// Copyright (c) 2025 Arseniy Panyukov
//
// See the LICENSE file in the root directory for full license information.

#ifndef INEARESTNEIGHBORSEARCH_H
#define INEARESTNEIGHBORSEARCH_H
#include <components/IComponent.h>

template <typename StoredType, typename SearchedType>
class INearestNeighborSearch : public IComponent
{
public:
    ComponentType getType() const override { return ComponentType::NearestNeighbourSearch; };

    virtual std::shared_ptr<StoredType> findNearest(const SearchedType& state) = 0;
    virtual void add(std::shared_ptr<StoredType> state) = 0;
    virtual std::vector<std::shared_ptr<StoredType>> getNodes() = 0;
};

#endif //INEARESTNEIGHBORSEARCH_H
