//
// Created by arseniy on 28.10.24.
//

#ifndef DEFAULTRANDOMSAMPLER_H
#define DEFAULTRANDOMSAMPLER_H
#include <random>

#include "components/sampling/pose/IPoseSampler.h"
#include "poses/static/PoseMath.h"

class DefaultRandomSampler : public IPoseSampler<Pose>
{
public:
    DefaultRandomSampler(ConfigurationSpaceBoundaries boundaries)
       : dis_x(boundaries.xMin, boundaries.xMax),
         dis_y(boundaries.yMin, boundaries.yMax),
         dis_z(boundaries.zMin, boundaries.zMax),
         dis_yaw(boundaries.yaw_min, boundaries.yaw_max),
         dis_pitch(boundaries.pitch_min, boundaries.pitch_max),
         dis_roll(boundaries.roll_min, boundaries.roll_max) {}
    Pose samplePose(Pose target) override;

    CapabilitySet getCapabilities() const override { return CapabilitySet { Capability::StaticEnv, Capability::DynamicEnv};}

    void resolveDependencies(const ComponentConfig &config, ComponentManager *manager) override;

    std::mt19937& getGenerator() { return gen; }

protected:
    std::mt19937 gen{std::random_device{}()};
    std::uniform_real_distribution<double> dis_x;
    std::uniform_real_distribution<double> dis_y;
    std::uniform_real_distribution<double> dis_z;
    std::uniform_real_distribution<double> dis_yaw;
    std::uniform_real_distribution<double> dis_pitch;
    std::uniform_real_distribution<double> dis_roll;


};



#endif //DEFAULTRANDOMSAMPLER_H
