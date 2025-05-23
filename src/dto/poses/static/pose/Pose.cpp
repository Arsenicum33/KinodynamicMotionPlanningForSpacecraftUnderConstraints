// MIT License
// Copyright (c) 2025 Arseniy Panyukov
//
// See the LICENSE file in the root directory for full license information.

#include "Pose.h"

#include <dto/poses/static/poseMath/PoseMath.h>
#include <spdlog/spdlog.h>


Pose::Pose() : translation{0.0, 0.0, 0.0}, rotation(1,0,0,0)
{}

Pose::Pose(std::array<double, 3> trans, std::array<double, 3> rot) : Pose(trans, PoseMath::eulerToRotationMatrix(rot))
{}

Pose::Pose(std::array<double, 3> trans, std::array<std::array<double, 3>, 3> rot):
    translation(trans), rotation(PoseMath::rotationMatrixToQuaternion(rot))
{}

Pose::Pose(std::array<double, 3> trans, Eigen::Quaterniond rot):
    translation(trans), rotation(rot)
{}

Pose::Pose(std::array<double, 3> trans) : translation(trans),  rotation(1,0,0,0)
{}

std::vector<double> Pose::flatten() const
{
    return flattenNoRot();
    //auto eulersAngles = PoseMath::rotationMatrixToEuler(rotation);
    //std::vector<double> configuration = {translation[0], translation[1], translation[2],
    //eulersAngles[0], eulersAngles[1], eulersAngles[2]};
    //return configuration;
}

std::vector<double> Pose::flattenNoRot() const
{
    std::vector<double> configuration = {translation[0], translation[1], translation[2]};
    return configuration;
}

std::string Pose::toString() const
{
    std::vector<double> configuration = Pose::flatten();
    std::ostringstream oss;
    oss << "Translation: (" << configuration[0] << ", " << configuration[1] << ", " << configuration[2] << ") ";
      //  << "Rotation: (" << configuration[3] << ", " << configuration[4] << ", " << configuration[5] << ")";
    return oss.str();
}

Pose Pose::operator+(const Pose &other) const
{

    Eigen::Quaterniond newRotationChange(rotation.w()+other.rotation.w(), rotation.x()+other.rotation.x(),
    rotation.y()+other.rotation.y(), rotation.z()+other.rotation.z());
    return Pose(std::array<double,3> {translation[0] +other.translation[0],translation[1] +other.translation[1],
        translation[2] +other.translation[2]},newRotationChange);
}

Pose Pose::operator*(double factor) const
{
    Eigen::Quaterniond newRotationChange(rotation.w()*factor, rotation.x()*factor,
        rotation.y()*factor, rotation.z()*factor);
    return Pose(std::array<double,3> {translation[0] * factor, translation[1] * factor, translation[2] * factor},newRotationChange);
}

void Pose::validate(const std::string& where) const {
    // Check translation
    for (int i = 0; i < 3; ++i) {
        if (!std::isfinite(translation[i])) {
            spdlog::debug("Pose translation invalid in {}", where);
            break;
        }
    }

    if (!std::isfinite(rotation.w()) ||
        !std::isfinite(rotation.x()) ||
        !std::isfinite(rotation.y()) ||
        !std::isfinite(rotation.z()))
    {
        spdlog::debug("Pose rotation invalid in {}", where);
    }
}