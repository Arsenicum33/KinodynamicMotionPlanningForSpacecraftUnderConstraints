//
// Created by arseniy on 14.1.25.
//

#ifndef DEFAULTRANDOMSAMPLERFACTORY_H
#define DEFAULTRANDOMSAMPLERFACTORY_H
#include "components/IComponentFactory.h"
#include "components/sampling/pose/IPoseSampler.h"


class DefaultRandomSamplerFactory : public IComponentFactory<IPoseSampler<Pose>>
{
public:
    std::unique_ptr<IPoseSampler<Pose>> createComponent(const ComponentConfig &config, const ReaderContext &context) override;


};



#endif //DEFAULTRANDOMSAMPLERFACTORY_H
