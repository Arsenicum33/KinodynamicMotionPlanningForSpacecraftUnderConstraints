//
// Created by arseniy on 22.3.25.
//

#ifndef POSITIONUTILS_H
#define POSITIONUTILS_H
#include <dto/poses/dynamic/keyframe/Keyframe.h>
#include <dto/poses/static/pose/Pose.h>
#include <dto/poses/static/poseMath/PoseMath.h>
#include <spdlog/spdlog.h>

#include "dto/poses/astrodynamic/spaceshipState/SpaceshipState.h"
#include "dto/poses/dynamic/kinodynamic/state/State.h"

class PositionUtils
{
public:

    static Pose interpolatePoses(const Pose &start, const Pose &end, double factor)
    {
        checkFactorValidity(factor);
        std::array<double, 3> trans;
        for (int i = 0; i < 3; ++i)
        {
            trans[i] = start.translation[i] + factor * (end.translation[i] - start.translation[i]);
        }
        Eigen::Quaterniond qInterp = start.rotation.slerp(factor, end.rotation);
        return Pose(trans, qInterp);
    }

    static Keyframe interpolateKeyframes(const Keyframe &start, const Keyframe &end, double factor)
    {
        Pose interpolatedPose = interpolatePoses(start, end, factor);
        double time = start.time + factor * (end.time - start.time);
        return Keyframe(interpolatedPose.translation, interpolatedPose.rotation, time);
    }

    static State interpolateStates(const State &start, const State &end, double factor)
    {
        Keyframe interpolatedKeyframe = interpolateKeyframes(start, end, factor);
        std::array<double, 3> vel;
        for (int i = 0; i < 3; ++i)
        {
            vel[i] = start.velocity[i] + factor * (end.velocity[i] - start.velocity[i]);
        }

        std::array<double, 3> angVel;
        for (int i = 0; i < 3; ++i)
        {
            angVel[i] = start.angularVelocity[i] + factor * (end.angularVelocity[i] - start.angularVelocity[i]);
        }

        return State(interpolatedKeyframe, vel, angVel);
    }

    static SpaceshipState interpolateSpaceshipStates(const SpaceshipState &start, const SpaceshipState &end, double factor)
    {
        State interpolatedState = interpolateStates(start, end, factor);
        FuelState fuel(start.getFuel().getMainThrusterFuel() + factor * (end.getFuel().getMainThrusterFuel() - start.getFuel().getMainThrusterFuel()),
            start.getFuel().getRotationThrustersFuel() + factor * (end.getFuel().getRotationThrustersFuel() - start.getFuel().getRotationThrustersFuel()));
        return SpaceshipState(interpolatedState, fuel);
    }

private:
    static void checkFactorValidity(double factor)
    {
        if (factor < 0 || factor > 1)
        {
            spdlog::error("Interpolation factor must be between 0 and 1");
            throw std::invalid_argument("Interpolation factor must be between 0 and 1");
        }
    }
};

#endif //POSITIONUTILS_H
