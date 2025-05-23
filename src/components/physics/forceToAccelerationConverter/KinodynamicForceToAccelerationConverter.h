// MIT License
// Copyright (c) 2025 Arseniy Panyukov
//
// See the LICENSE file in the root directory for full license information.


#ifndef KINODYNAMICFORCETOACCELERATIONCONVERTER_H
#define KINODYNAMICFORCETOACCELERATIONCONVERTER_H
#include <dto/poses/dynamic/kinodynamic/state/State.h>

#include "ForceToAccelerationConverter.h"

class KinodynamicForceToAccelerationConverter : public ForceToAccelerationConverter<State>
{
public:

    static std::unique_ptr<IComponent> createComponent(const ComponentConfig &config, const ReaderContext &context);

    CapabilitySet getCapabilities() const override { return CapabilitySet { Capability::KinodynamicEnv};}
};

inline std::unique_ptr<IComponent> KinodynamicForceToAccelerationConverter::createComponent(
    const ComponentConfig &config, const ReaderContext &context)
{
    return std::make_unique<KinodynamicForceToAccelerationConverter>();
}

#endif //KINODYNAMICFORCETOACCELERATIONCONVERTER_H
