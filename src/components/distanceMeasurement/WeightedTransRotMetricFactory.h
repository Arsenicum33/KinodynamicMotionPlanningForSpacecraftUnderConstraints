//
// Created by arseniy on 14.1.25.
//

#ifndef WEIGHTEDTRANSROTMETRICFACTORY_H
#define WEIGHTEDTRANSROTMETRICFACTORY_H
#include "IDistanceMetric.h"
#include "components/IComponentFactory.h"


class WeightedTransRotMetricFactory : public IComponentFactory<IDistanceMetric>
{
public:
    std::unique_ptr<IDistanceMetric> createComponent(const ComponentConfig &config, const ReaderContext &context) override;


};




#endif //WEIGHTEDTRANSROTMETRICFACTORY_H
