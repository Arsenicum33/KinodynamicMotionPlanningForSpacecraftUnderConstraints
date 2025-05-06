//
// Created by arseniy on 3.5.25.
//

#ifndef INEARESTNEIGHBORSEARCH_H
#define INEARESTNEIGHBORSEARCH_H
#include <components/IComponent.h>

class INearestNeighborSearch : public IComponent
{
public:
    ComponentType getType() const override { return ComponentType::NearestNeighbourSearch; };
};

#endif //INEARESTNEIGHBORSEARCH_H
