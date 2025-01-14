//
// Created by arseniy on 14.1.25.
//

#ifndef DEFAULTRANDOMSAMPLERFACTORY_H
#define DEFAULTRANDOMSAMPLERFACTORY_H
#include "IPoseSampler.h"
#include "components/IComponentFactory.h"


class DefaultRandomSamplerFactory : public IComponentFactory<IPoseSampler>
{
public:
    std::shared_ptr<IPoseSampler> createComponent(ComponentConfig& config, ReaderContext& context) override;


};



#endif //DEFAULTRANDOMSAMPLERFACTORY_H
