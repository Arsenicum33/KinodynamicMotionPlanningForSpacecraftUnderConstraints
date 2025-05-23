// MIT License
// Copyright (c) 2025 Arseniy Panyukov
//
// See the LICENSE file in the root directory for full license information.


#ifndef KINODYNAMICSSTPATHGENERATOR_H
#define KINODYNAMICSSTPATHGENERATOR_H
#include <dto/poses/dynamic/kinodynamic/state/State.h>

#include "components/pathGenerator/sst/ISSTpathGenerator.h"


class KinodynamicSSTpathGenerator : public ISSTpathGenerator<State>
{
public:
    static std::unique_ptr<IComponent> createComponent(const ComponentConfig &config, const ReaderContext &context)
    {
        return std::make_unique<KinodynamicSSTpathGenerator>();
    }
    CapabilitySet getCapabilities() const override { return CapabilitySet{ Capability::KinodynamicEnv }; };

};



#endif //KINODYNAMICSSTPATHGENERATOR_H
