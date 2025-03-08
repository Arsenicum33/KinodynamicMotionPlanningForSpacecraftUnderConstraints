//
// Created by arseniy on 8.3.25.
//

#ifndef ITERMINATIONCONDITION_H
#define ITERMINATIONCONDITION_H
#include "components/IComponent.h"

template <typename Current, typename Target>
class ITerminationCondition : public IComponent
{
public:
    virtual bool isTargetReached(const Current& currentPosition, const Target& target) const = 0;

    std::string getName() const override { return "TerminationCondition"; }
};

#endif //ITERMINATIONCONDITION_H
