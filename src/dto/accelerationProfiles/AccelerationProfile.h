//
// Created by arseniy on 7.4.25.
//

#ifndef ACCELERATIONPROFILE_H
#define ACCELERATIONPROFILE_H
#include <memory>
#include <vector>

template <typename ControlInput>
class AccelerationProfile
{
public:
    struct Segment
    {
        double duration;
        std::unique_ptr<ControlInput> controlInput;
    };

    void addSegment(double duration, std::unique_ptr<ControlInput> controlInput) { segments.push_back(Segment(duration, std::move(controlInput))); }
    const std::vector<Segment> &getSegments() const { return segments; }
private:
    std::vector<Segment> segments;
};

#endif //ACCELERATIONPROFILE_H
