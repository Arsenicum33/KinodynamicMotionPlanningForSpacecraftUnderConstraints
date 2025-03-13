//
// Created by arseniy on 14.1.25.
//

#ifndef WEIGHTEDTRANSROTMETRICFACTORY_H
#define WEIGHTEDTRANSROTMETRICFACTORY_H
#include "DefaultSpatialDistanceMetric.h"
#include "components/IComponentFactory.h"


class DefaultSpatialDistanceMetricFactory : public IComponentFactory<DefaultSpatialDistanceMetric>
{
public:
    std::unique_ptr<DefaultSpatialDistanceMetric> createComponent(const ComponentConfig &config, const ReaderContext &context) override;


};




#endif //WEIGHTEDTRANSROTMETRICFACTORY_H
