//
// Created by arseniy on 7.4.25.
//

#ifndef CONTROLINPUTPLAN_H
#define CONTROLINPUTPLAN_H
#include <memory>
#include <vector>

template <typename ControlInputType>
class ControlInputPlan
{
public:
    struct Segment
    {
        double duration;
        std::unique_ptr<ControlInputType> controlInput;
    };

    void addSegment(double duration, std::unique_ptr<ControlInputType> controlInput) { segments.push_back(Segment(duration, std::move(controlInput))); }
    const std::vector<Segment> &getSegments() const { return segments; }
private:
    std::vector<Segment> segments;
};

#endif //CONTROLINPUTPLAN_H
