//
// Created by arseniy on 30.4.25.
//

#ifndef KINODYNAMICPLANNER_H
#define KINODYNAMICPLANNER_H
#include "components/planner/IPlanner.h"


class KinodynamicPlanner : public IPlanner<State>
{
public:
    KinodynamicPlanner(double timeResolution) :
        IPlanner<State>(timeResolution) {}
    static std::unique_ptr<IComponent> createComponent(const ComponentConfig &config, const ReaderContext &context);

    CapabilitySet getCapabilities() const override { return CapabilitySet{Capability::KinodynamicEnv}; };
};



#endif //KINODYNAMICPLANNER_H
