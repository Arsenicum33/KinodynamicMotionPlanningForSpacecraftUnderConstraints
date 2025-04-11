//
// Created by arseniy on 9.4.25.
//

#ifndef SPACESHIPSTATE_H
#define SPACESHIPSTATE_H
#include <dto/poses/dynamic/kinodynamic/state/State.h>


class SpaceshipState : public State
{
public:
    double getFuel() const { return fuel; }
private:
    double fuel;
};



#endif //SPACESHIPSTATE_H
