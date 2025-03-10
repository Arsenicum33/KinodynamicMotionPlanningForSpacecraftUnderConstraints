//
// Created by arseniy on 14.1.25.
//

#ifndef MPNNSEARCHFACTORY_H
#define MPNNSEARCHFACTORY_H
#include "AbstractNearestNeighbourSearch.h"
#include "components/IComponentFactory.h"


class MPNNsearchFactory : public IComponentFactory<AbstractNearestNeighbourSearch<Pose>>
{
public:
    std::unique_ptr<AbstractNearestNeighbourSearch<Pose>> createComponent(const ComponentConfig &config, const ReaderContext &context) override;
};


#endif //MPNNSEARCHFACTORY_H
