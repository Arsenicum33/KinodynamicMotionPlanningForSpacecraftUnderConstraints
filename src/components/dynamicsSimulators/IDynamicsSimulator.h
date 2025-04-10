//
// Created by arseniy on 21.3.25.
//

#ifndef IDYNAMICSSIMULATOR_H
#define IDYNAMICSSIMULATOR_H
#include <dto/poses/dynamic/kinodynamic/controlInput/ControlInput.h>

#include "components/IComponent.h"
#include "dto/forcesProfile/ForcesProfile.h"

template <typename StateType, typename ControlInputType>
class IDynamicsSimulator : public IComponent
{
public:
    StateType computeNextState(const StateType& currentState, const ForcesProfile<ControlInputType>& controlInput);

    ComponentType getType() const override { return ComponentType::DynamicsSimulator; }
protected:
    virtual StateType computeSegmentTransition(const StateType& currentState, const typename ForcesProfile<ControlInputType>::Segment& segment) = 0;

};

template<typename StateType, typename ControlInputType>
StateType IDynamicsSimulator<StateType, ControlInputType>::computeNextState(const StateType &currentState,
    const ForcesProfile<ControlInputType> &controlInput)
{
    const std::vector<typename ForcesProfile<ControlInputType>::Segment>& segments = controlInput.getSegments();
    StateType nextState = currentState;
    for (const auto &segment : segments)
    {
        nextState = computeSegmentTransition(nextState, segment);
    }
    return nextState;
}

#endif //IDYNAMICSSIMULATOR_H
