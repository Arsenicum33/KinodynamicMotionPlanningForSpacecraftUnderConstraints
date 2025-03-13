//
// Created by arseniy on 10.3.25.
//

#ifndef TEMPORALTRANSROTMETRICFACTORY_H
#define TEMPORALTRANSROTMETRICFACTORY_H
#include "TemporalTransRotMetric.h"
#include "components/IComponentFactory.h"


class TemporalTransRotMetricFactory : public IComponentFactory<TemporalTransRotMetric>
{
    public:
    std::unique_ptr<TemporalTransRotMetric> createComponent(const ComponentConfig &config, const ReaderContext &context) override;


};





#endif //TEMPORALTRANSROTMETRICFACTORY_H
