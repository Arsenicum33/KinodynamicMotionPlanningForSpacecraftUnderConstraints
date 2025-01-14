//
// Created by arseniy on 14.1.25.
//

#ifndef MPNNSEARCHFACTORY_H
#define MPNNSEARCHFACTORY_H
#include "AbstractNearestNeighbourSearch.h"
#include "components/IComponentFactory.h"


class MPNNsearchFactory : public IComponentFactory<AbstractNearestNeighbourSearch>
{
public:
    std::shared_ptr<AbstractNearestNeighbourSearch> createComponent(ComponentConfig &config, ReaderContext &context) override;
};


#endif //MPNNSEARCHFACTORY_H
