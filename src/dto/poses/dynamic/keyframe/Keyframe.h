//
// Created by arseniy on 2.1.25.
//

#ifndef KEYFRAME_H
#define KEYFRAME_H
#include <dto/poses/static/pose/Pose.h>


class Keyframe : public Pose
{
public:
    Keyframe()
        : Pose(), time(-1.0) {}

    Keyframe(std::array<double, 3> trans, double rot[3][3], double time)
        : Pose(trans, rot), time(time) {}

    Keyframe(std::array<double, 3> trans, std::array<std::array<double, 3>, 3> rot, double time)
        : Pose(trans, rot), time(time) {}

    Keyframe(std::array<double, 3> trans, Eigen::Quaterniond rot, double time)
        : Pose(trans, rot), time(time) {}

    Keyframe(std::array<double, 3> trans, double time)
        : Pose(trans), time(time) {}

    Keyframe(Pose pose, double time) : Pose(pose), time(time) {}

    Keyframe(double t) : Pose(), time(t) {}

    Keyframe operator+(const Keyframe &other) const; //only for operations with derivative

    Keyframe operator*(double factor) const; //only for operations with derivative

    std::string toString() const override;

    std::vector<double> flatten() const override;

    std::vector<double> flattenNoRot() const override;

    double time;


};



#endif //KEYFRAME_H
