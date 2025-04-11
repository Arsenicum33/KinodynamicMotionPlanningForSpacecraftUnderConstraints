//
// Created by arseniy on 11.4.25.
//

#ifndef ASTRODYNAMICPATHGENERATOR_H
#define ASTRODYNAMICPATHGENERATOR_H
#include <components/pathGenerator/tree/ITreePathGenerator.h>

#include "dto/poses/astrodynamic/spaceshipState/SpaceshipState.h"

class AstrodynamicPathGenerator : public ITreePathGenerator<SpaceshipState>
{
public:
    static std::unique_ptr<IComponent> createComponent(const ComponentConfig &config, const ReaderContext &context)
    {
        return std::make_unique<AstrodynamicPathGenerator>();
    };

    CapabilitySet getCapabilities() const override { return CapabilitySet{ Capability::KinodynamicEnv}; }

private:
    std::unique_ptr<ITreePathGenerator<Keyframe>> keyframePathGenerator;
};

#endif //ASTRODYNAMICPATHGENERATOR_H
