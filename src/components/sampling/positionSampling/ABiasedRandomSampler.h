// MIT License
// Copyright (c) 2025 Arseniy Panyukov
//
// See the LICENSE file in the root directory for full license information.


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
    SampledType sample(const TargetType& target) final;

protected:
    double goalBias;
    virtual SampledType sampleTarget(const TargetType& target) = 0;
    virtual SampledType sampleRandom() = 0;
private:
    void validateGoalBias() const;

};


template<typename SampledType, typename TargetType>
SampledType ABiasedRandomSampler<SampledType, TargetType>::sample(const TargetType& target)
{
    if (std::generate_canonical<double, 10>(this->gen) < goalBias)
        return sampleTarget(target);
    return sampleRandom();
}

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
