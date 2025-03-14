//
// Created by arseniy on 28.10.24.
//

#include "DefaultRandomSampler.h"


std::unique_ptr<IComponent> DefaultRandomSampler::createComponent(const ComponentConfig &config,
    const ReaderContext &context)
{
    return std::make_unique<DefaultRandomSampler>(context.envSettings.boundaries);
}

Pose DefaultRandomSampler::samplePose(Pose target)
{
    std::array<double, 3> translation = {dis_x(gen), dis_y(gen), dis_z(gen)};
    std::array<double, 3> eulerAngles = {dis_yaw(gen), dis_pitch(gen), dis_roll(gen)};
    std::array<std::array<double, 3>, 3> rotation_matrix = PoseMath::eulerToRotationMatrix(eulerAngles);
    Pose pose(translation, rotation_matrix);
    return pose;
}

void DefaultRandomSampler::resolveDependencies(const ComponentConfig &config, ComponentManager *manager)
{
    return;
}
