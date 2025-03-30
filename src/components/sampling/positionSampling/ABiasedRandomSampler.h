//
// Created by arseniy on 18.3.25.
//

#ifndef ABIASEDRANDOMSAMPLER_H
#define ABIASEDRANDOMSAMPLER_H
#include "ARandomSampler.h"

template <typename SampledType, typename TargetType>
class ABiasedRandomSampler : public ARandomSampler<SampledType, TargetType>
{
public:
    ABiasedRandomSampler(const ConfigurationSpaceBoundaries &boundaries, double goalBias)
        : ARandomSampler<SampledType, TargetType>(boundaries),
          goalBias(goalBias)
    { validateGoalBias(); }


protected:
    double goalBias;

private:
    void validateGoalBias() const;
};


template<typename SampledType, typename TargetType>
void ABiasedRandomSampler<SampledType, TargetType>::validateGoalBias() const
{
    if (goalBias < 0.0 || goalBias > 1.0)
    {
        spdlog::error("Goal bias must be between 0.0 and 1.0");
        throw std::invalid_argument("goal bias must be between 0 and 1.");
    }
}

#endif //ABIASEDRANDOMSAMPLER_H
