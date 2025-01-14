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
    std::shared_ptr<IDistanceMetric> createComponent(ComponentConfig& config, ReaderContext& context) override;


};




#endif //WEIGHTEDTRANSROTMETRICFACTORY_H
