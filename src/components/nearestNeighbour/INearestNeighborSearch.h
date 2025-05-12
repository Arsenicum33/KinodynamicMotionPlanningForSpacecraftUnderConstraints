//
// Created by arseniy on 3.5.25.
//

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
};

#endif //INEARESTNEIGHBORSEARCH_H
