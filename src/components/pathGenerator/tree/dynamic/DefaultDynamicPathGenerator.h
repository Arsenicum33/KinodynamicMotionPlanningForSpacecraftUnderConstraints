// MIT License
// Copyright (c) 2025 Arseniy Panyukov
//
// See the LICENSE file in the root directory for full license information.


#ifndef DEFAULTDYNAMICPATHGENERATOR_H
#define DEFAULTDYNAMICPATHGENERATOR_H
#include "components/pathGenerator/tree/ITreePathGenerator.h"


class DefaultDynamicPathGenerator : public ITreePathGenerator<Keyframe>
{
public:
    static std::unique_ptr<IComponent> createComponent(const ComponentConfig &config, const ReaderContext &context)
    {
        return std::make_unique<DefaultDynamicPathGenerator>();
    };

    CapabilitySet getCapabilities() const override { return CapabilitySet { Capability::StaticEnv, Capability::DynamicEnv, Capability::MovingTarget}; }
};



#endif //DEFAULTDYNAMICPATHGENERATOR_H
