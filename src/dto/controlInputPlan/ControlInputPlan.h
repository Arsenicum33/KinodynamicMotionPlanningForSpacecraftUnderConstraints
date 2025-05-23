// MIT License
// Copyright (c) 2025 Arseniy Panyukov
//
// See the LICENSE file in the root directory for full license information.


#ifndef CONTROLINPUTPLAN_H
#define CONTROLINPUTPLAN_H
#include <memory>
#include <vector>
#include "dto/poses/dynamic/kinodynamic/burstControlInput/BurstControlInput.h"

class ControlInputPlan
{
public:
    struct Segment
    {
        double duration;
        std::unique_ptr<BurstControlInput> controlInput;
    };

    void addSegment(double duration, std::unique_ptr<BurstControlInput> controlInput) { segments.push_back(Segment(duration, std::move(controlInput))); }
    const std::vector<Segment> &getSegments() const { return segments; }
private:
    std::vector<Segment> segments;
};

#endif //CONTROLINPUTPLAN_H