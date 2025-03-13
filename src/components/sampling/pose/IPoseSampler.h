//
// Created by arseniy on 15.1.25.
//

#ifndef IPOSESAMPLER_H
#define IPOSESAMPLER_H
#include <poses/static/Pose.h>

#include "components/sampling/ISampler.h"

template <typename T>
class IPoseSampler : public ISampler<Pose, T>{};

#endif //IPOSESAMPLER_H
