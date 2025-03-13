//
// Created by arseniy on 10.3.25.
//

#ifndef TEMPORALMPNNSEARCHFACTORY_H
#define TEMPORALMPNNSEARCHFACTORY_H
#include "TemporalMPNNsearch.h"
#include "components/IComponentFactory.h"


class TemporalMPNNsearchFactory : public IComponentFactory<TemporalMPNNsearch>
{
public:
    std::unique_ptr<TemporalMPNNsearch> createComponent(const ComponentConfig &config, const ReaderContext &context) override;
};




#endif //TEMPORALMPNNSEARCHFACTORY_H
