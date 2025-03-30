//
// Created by arseniy on 22.3.25.
//

#ifndef IKINODYNAMICINTERPOLATOR_H
#define IKINODYNAMICINTERPOLATOR_H
#include "components/interpolators/IInterpolator.h"
#include "dto/poses/dynamic/kinodynamic/state/State.h"

class IKinodynamicInterpolator : public IInterpolator<State> {};

#endif //IKINODYNAMICINTERPOLATOR_H
