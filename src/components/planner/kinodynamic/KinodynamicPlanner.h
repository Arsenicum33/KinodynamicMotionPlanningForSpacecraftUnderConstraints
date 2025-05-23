// MIT License
// Copyright (c) 2025 Arseniy Panyukov
//
// See the LICENSE file in the root directory for full license information.


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
