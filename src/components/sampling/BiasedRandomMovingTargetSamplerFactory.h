//
// Created by arseniy on 10.3.25.
//

#ifndef BIASEDRANDOMMOVINGTARGETSAMPLERFACTORY_H
#define BIASEDRANDOMMOVINGTARGETSAMPLERFACTORY_H
#include "BiasedRandomMovingTargetSampler.h"
#include "components/IComponentFactory.h"


class BiasedRandomMovingTargetSamplerFactory : public IComponentFactory<BiasedRandomMovingTargetSampler>
{
public:
    std::unique_ptr<BiasedRandomMovingTargetSampler> createComponent(const ComponentConfig &config, const ReaderContext &context) override;
};



#endif //BIASEDRANDOMMOVINGTARGETSAMPLERFACTORY_H
