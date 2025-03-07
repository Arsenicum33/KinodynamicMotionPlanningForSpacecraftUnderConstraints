//
// Created by arseniy on 7.3.25.
//

#ifndef MT_TARRT_H
#define MT_TARRT_H
#include "IMovingTargetSolver.h"
#include "components/solvers/solvers/dynamic/TARRT/TARRTsolver.h"


class MT_TARRT : public TARRTsolver, IMovingTargetSolver
{
public:
    MT_TARRT(const TARRTsolverConfig &config, const EnvSettings &envSettings)
        : TARRTsolver(config, envSettings) {}

    std::vector<Keyframe> solve(const Pose &startPosition, const Animation &target) override;
};



#endif //MT_TARRT_H
