// MIT License
// Copyright (c) 2025 Arseniy Panyukov
//
// See the LICENSE file in the root directory for full license information.


#ifndef BURSTCONTROLINPUT_H
#define BURSTCONTROLINPUT_H
#include <dto/poses/dynamic/kinodynamic/controlInput/ControlInput.h>


class BurstControlInput : public ControlInput
{
public:
    BurstControlInput(double thrust, std::array<double, 3> torque, double thrustBurstDuration, double torqueBurstDuration) :
        ControlInput(thrust, torque), thrustBurstDuration(thrustBurstDuration), torqueBurstDuration(torqueBurstDuration) {}
    BurstControlInput(double thrustBurstDuration, double torqueBurstDuration) : thrustBurstDuration(thrustBurstDuration),
        torqueBurstDuration(torqueBurstDuration) {}
    BurstControlInput(const ControlInput& other, double thrustBurstDuration, double torqueBurstDuration) :
        ControlInput(other), thrustBurstDuration(thrustBurstDuration), torqueBurstDuration(torqueBurstDuration) {}
    double getThrustBurstDuration() const { return thrustBurstDuration; }
    double getTorqueBurstDuration() const { return torqueBurstDuration; }
private:
    double thrustBurstDuration;
    double torqueBurstDuration;
};



#endif //BURSTCONTROLINPUT_H
