//
// Created by arseniy on 8.3.25.
//

#ifndef ITERMINATIONCONDITION_H
#define ITERMINATIONCONDITION_H
#include "components/IComponent.h"
#include "utils/AnimationUtils.h"
#define PRINT_THRESHOLD 0.98

template <typename Current, typename Target>
class ITerminationCondition : public IComponent
{
public:
    explicit ITerminationCondition(double threshold)
        : threshold(threshold)
    {}

    bool isTargetReached(const Current& currentPosition, const Target& target);

    ComponentType getType() const override {return ComponentType::TerminationCondition; };
protected:
    virtual double computeDistance(const Current& currentPosition, const Target& target) = 0;
    virtual void outputDebugInfo(const Current &currentPosition);
    double minDistToGoal = std::numeric_limits<double>::max();
    double threshold;
};

template<typename Current, typename Target>
bool ITerminationCondition<Current, Target>::isTargetReached(const Current &currentPosition, const Target &target)
{
    double distance = computeDistance(currentPosition, target);
    if (distance < minDistToGoal * PRINT_THRESHOLD)
    {
        minDistToGoal = distance;
        outputDebugInfo(currentPosition);
    }
    return distance <= threshold;
}

template<typename Current, typename Target>
void ITerminationCondition<Current, Target>::outputDebugInfo(const Current &currentPosition)
{
    spdlog::info("Min dist to goal: {}, Trans: {}, {}, {}", minDistToGoal, currentPosition.translation[0],
    currentPosition.translation[1], currentPosition.translation[2]);
}


#endif //ITERMINATIONCONDITION_H
