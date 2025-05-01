//
// Created by arseniy on 22.4.25.
//

#include "BiasedSphericalBoundariesSampler.h"

#include <dto/poses/static/poseMath/PoseMath.h>

#include "utils/ScalingUtils.h"

std::unique_ptr<IComponent> BiasedSphericalBoundariesSampler::createComponent(const ComponentConfig &config,
                                                                              const ReaderContext &context)
{
    const auto& configMap = config.config;

    double goalBias = std::any_cast<double>(configMap.at("goalBias"));

    double phiMin = std::any_cast<double>(configMap.at("phiMin"));
    double phiMax = std::any_cast<double>(configMap.at("phiMax"));
    double thetaMin = std::any_cast<double>(configMap.at("thetaMin"));
    double thetaMax = std::any_cast<double>(configMap.at("thetaMax"));
    double rMin = std::any_cast<double>(configMap.at("rMin")) * AU_TO_KM_SCALING_CONSTANT;
    double rMax = std::any_cast<double>(configMap.at("rMax")) * AU_TO_KM_SCALING_CONSTANT;

    ConfigurationSpaceSphericalBoundaries sphericalBoundaries(phiMin, phiMax, thetaMin, thetaMax, rMin, rMax);

    return std::make_unique<BiasedSphericalBoundariesSampler>(sphericalBoundaries, goalBias);
}

Keyframe BiasedSphericalBoundariesSampler::sampleTarget(const CelestialBody &target)
{
    std::vector<Keyframe> keyframes = target.getAnimation()->getKeyframes();
    std::uniform_int_distribution<size_t> distribution(0, keyframes.size() - 1);
    int randomIndex = distribution(gen);
    return keyframes[randomIndex];
}

Keyframe BiasedSphericalBoundariesSampler::sampleRandom()
{
    double r = dis_r(gen);
    double phi = dis_phi(gen);
    double theta = dis_theta(gen);
    if (std::generate_canonical<double, 10>(this->gen) < 0.5)
    {
        phi += std::numbers::pi;
        theta = std::numbers::pi-theta;
    }

    std::array<double, 3> eulerAngles = {dis_yaw(gen), dis_pitch(gen), dis_roll(gen)};
    std::array<std::array<double, 3>, 3> rotation_matrix = PoseMath::eulerToRotationMatrix(eulerAngles);
    Pose pose(std::array<double,3> { r*sin(theta)*cos(phi), r*sin(theta)*sin(phi), r * cos(theta)}, rotation_matrix);
    return Keyframe(pose, -1.0);
}

Keyframe BiasedSphericalBoundariesSampler::sample(const CelestialBody &target)
{
    if (std::generate_canonical<double, 10>(this->gen) < goalBias)
        return sampleTarget(target);
    return sampleRandom();
}
