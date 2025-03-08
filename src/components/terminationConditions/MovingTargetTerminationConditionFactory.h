//
// Created by arseniy on 8.3.25.
//

#ifndef MOVINGTARGETTERMINATIONCONDITIONFACTORY_H
#define MOVINGTARGETTERMINATIONCONDITIONFACTORY_H
#include "ITerminationCondition.h"
#include "components/IComponentFactory.h"


class MovingTargetTerminationConditionFactory : public IComponentFactory<ITerminationCondition<Keyframe,Animation>>
{
public:
    std::unique_ptr<ITerminationCondition<Keyframe,Animation>> createComponent(const ComponentConfig &config, const ReaderContext &context) override;
};



#endif //MOVINGTARGETTERMINATIONCONDITIONFACTORY_H
