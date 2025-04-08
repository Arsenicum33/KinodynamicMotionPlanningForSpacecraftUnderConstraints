//
// Created by arseniy on 7.4.25.
//

#ifndef BURSTCONTROLINPUT_H
#define BURSTCONTROLINPUT_H
#include <dto/poses/dynamic/kinodynamic/controlInput/ControlInput.h>


class BurstControlInput : public ControlInput
{
public:
    BurstControlInput(double linAcc, std::array<double, 3> angAcc, double burstDuration) :
        ControlInput(linAcc, angAcc), burstDuration(burstDuration) {}
    BurstControlInput(double burstDuration) : burstDuration(burstDuration) {}
    BurstControlInput(const ControlInput& other, double burstDuration) : ControlInput(other), burstDuration(burstDuration) {}
    double getBurstDuration() const { return burstDuration; }
private:
    double burstDuration;
};



#endif //BURSTCONTROLINPUT_H
