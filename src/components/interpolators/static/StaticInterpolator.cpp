//
// Created by arseniy on 14.3.25.
//

#include "StaticInterpolator.h"

#include <dto/poses/static/poseMath/PoseMath.h>


std::unique_ptr<IComponent> StaticInterpolator::createComponent(const ComponentConfig &config,
                                                                const ReaderContext &context)
{
    const auto& configMap = config.config;

    double interpolationThreshold = std::any_cast<double>(configMap.at("threshold"));

    return std::make_unique<StaticInterpolator>(interpolationThreshold);
}

std::vector<Pose> StaticInterpolator::interpolate(const Pose &start, const Pose &end)
{
    double dx = end.translation[0] - start.translation[0];
    double dy = end.translation[1] - start.translation[1];
    double dz = end.translation[2] - start.translation[2];
    double distance = sqrt(dx * dx + dy * dy + dz * dz);
    int translationSteps = static_cast<int>(distance / interpolationThreshold);


    Eigen::Quaterniond rotationStart = PoseMath::rotationMatrixToQuaternion(start.rotation);
    Eigen::Quaterniond rotationEnd = PoseMath::rotationMatrixToQuaternion(end.rotation);
    double angle = 2 * acos(std::abs(rotationStart.dot(rotationEnd))); // Angle between quaternions
    int rotationSteps = static_cast<int>(angle / interpolationThreshold);

    int maxSteps = std::max(translationSteps, rotationSteps);

    std::vector<Pose> poses { start };

    for (int i = 1; i <= maxSteps; i++)
    {
        double t = static_cast<double>(i) / static_cast<double>(maxSteps);
        std::array<double, 3> newTranslation =
        {
            start.translation[0] + t * dx,
            start.translation[1] + t * dy,
            start.translation[2] + t * dz
        };
        Eigen::Quaterniond newRotation = rotationStart.slerp(t, rotationEnd);
        Pose p(newTranslation, newRotation);
        poses.push_back(p);
    }
    poses.push_back(end);
    return poses;
}

Pose StaticInterpolator::getIntermediatePosition(const Pose &from, const Pose &to, double stepSize)
{
    double distance = distanceMetric->getSpatialDistance(from, to);
    if (distance <= stepSize)
    {
        return to;
    }

    double scale = stepSize / distance;

    std::array<double, 3> newTranslation;
    for (int i = 0; i < 3; ++i)
    {
        newTranslation[i] = from.translation[i] + scale * (to.translation[i] - from.translation[i]);
    }

    Eigen::Quaterniond rotationFrom = PoseMath::rotationMatrixToQuaternion(from.rotation);
    Eigen::Quaterniond rotationTo = PoseMath::rotationMatrixToQuaternion(to.rotation);
    Eigen::Quaterniond newRotation = rotationFrom.slerp(scale, rotationTo);
    Pose newPose(newTranslation, newRotation);

    return newPose;
}

void StaticInterpolator::resolveDependencies(const ComponentConfig &config, ComponentManager *manager)
{
    IStaticInterpolator::resolveDependencies(config, manager);
    this->distanceMetric = std::dynamic_pointer_cast<IDistanceMetric>(manager->getComponent(ComponentType::DistanceMetric));
}
