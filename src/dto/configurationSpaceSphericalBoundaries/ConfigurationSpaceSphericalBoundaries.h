// MIT License
// Copyright (c) 2025 Arseniy Panyukov
//
// See the LICENSE file in the root directory for full license information.


#ifndef CONFIGURATIONSPACESPHERICALBOUNDARIES_H
#define CONFIGURATIONSPACESPHERICALBOUNDARIES_H
#include <numbers>


class ConfigurationSpaceSphericalBoundaries
{
public:
    double phiMin, phiMax, thetaMin, thetaMax, rMin, rMax; // phi - azimuthal angle, theta - polar angle
    double yaw_min = -std::numbers::pi, yaw_max = std::numbers::pi, pitch_min = -std::numbers::pi/2, pitch_max = std::numbers::pi/2,
    roll_min = -std::numbers::pi, roll_max = std::numbers::pi;

    ConfigurationSpaceSphericalBoundaries(double phiMin, double phiMax, double thetaMin, double thetaMax, double rMin, double rMax,
        double yaw_min = -std::numbers::pi, double yaw_max = std::numbers::pi, double pitch_min = -std::numbers::pi/2, double pitch_max = std::numbers::pi/2,
        double roll_min = -std::numbers::pi, double roll_max = std::numbers::pi) : phiMin(phiMin), phiMax(phiMax),
    thetaMin(thetaMin), thetaMax(thetaMax), rMin(rMin), rMax(rMax), yaw_min(yaw_min), yaw_max(yaw_max),
    pitch_min(pitch_min), pitch_max(pitch_max), roll_min(roll_min), roll_max(roll_max){}

};



#endif //CONFIGURATIONSPACESPHERICALBOUNDARIES_H
