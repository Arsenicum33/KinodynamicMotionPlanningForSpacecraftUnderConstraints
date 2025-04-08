//
// Created by arseniy on 7.4.25.
//

#ifndef BURSTDYNAMICSSIMULATORADAPTER_H
#define BURSTDYNAMICSSIMULATORADAPTER_H
#include <components/dynamicsSimulators/DynamicsSimulator.h>
#include <components/dynamicsSimulators/IDynamicsSimulator.h>
#include <dto/poses/dynamic/kinodynamic/state/State.h>

#include "dto/poses/dynamic/kinodynamic/burstControlInput/BurstControlInput.h"


class BurstDynamicsSimulatorAdapter : public IDynamicsSimulator<State, BurstControlInput>
{
public:
    BurstDynamicsSimulatorAdapter(std::unique_ptr<DynamicsSimulator> dynamicsSimulator) :
        dynamicsSimulator(std::move(dynamicsSimulator)) {}
    CapabilitySet getCapabilities() const override { return dynamicsSimulator->getCapabilities(); };
    static std::unique_ptr<IComponent> createComponent(const ComponentConfig &config, const ReaderContext &context);

protected:
    State computeSegmentTransition(const State &currentState,
        const AccelerationProfile<BurstControlInput>::Segment &segment) override;

private:
    std::unique_ptr<DynamicsSimulator> dynamicsSimulator;
};

inline std::unique_ptr<IComponent> BurstDynamicsSimulatorAdapter::createComponent(const ComponentConfig &config,
    const ReaderContext &context)
{
    auto dynamicsSimulatorComponent = DynamicsSimulator::createComponent(config, context);

    if (auto* castPtr = dynamic_cast<DynamicsSimulator*>(dynamicsSimulatorComponent.get()))
    {
        dynamicsSimulatorComponent.release();
        std::unique_ptr<DynamicsSimulator> dynamicsSimulator(castPtr);
        return std::make_unique<BurstDynamicsSimulatorAdapter>(std::move(dynamicsSimulator));
    }
    spdlog::error("Error when creating StateCollisionHandlerAdapter. Provided DynamicCollisionHandler is invalid");
    throw std::runtime_error("Error when creating StateCollisionHandlerAdapter. Provided DynamicCollisionHandler is invalid");
}

inline State BurstDynamicsSimulatorAdapter::computeSegmentTransition(const State &currentState,
                                                                     const AccelerationProfile<BurstControlInput>::Segment &segment)
{
    AccelerationProfile<ControlInput>::Segment adaptedSegment;
    adaptedSegment.controlInput = std::make_unique<ControlInput>(*segment.controlInput);
    adaptedSegment.duration = segment.duration;
    return dynamicsSimulator->computeSegmentTransition(currentState, adaptedSegment);
}


#endif //BURSTDYNAMICSSIMULATORADAPTER_H
