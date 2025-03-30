//
// Created by arseniy on 21.3.25.
//

#ifndef KINODYNAMICPATHGENERATOR_H
#define KINODYNAMICPATHGENERATOR_H
#include "components/pathGenerator/tree/ITreePathGenerator.h"
#include "dto/poses/dynamic/kinodynamic/state/State.h"

class KinodynamicPathGenerator : public ITreePathGenerator<State>
{
public:
    static std::unique_ptr<IComponent> createComponent(const ComponentConfig &config, const ReaderContext &context)
    {
        return std::make_unique<KinodynamicPathGenerator>();
    };

    CapabilitySet getCapabilities() const override { return CapabilitySet{ Capability::KinodynamicEnv}; }

private:
    std::unique_ptr<ITreePathGenerator<Keyframe>> keyframePathGenerator;
};

#endif //KINODYNAMICPATHGENERATOR_H
