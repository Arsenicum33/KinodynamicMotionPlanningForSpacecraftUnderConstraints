//
// Created by arseniy on 22.3.25.
//

#ifndef ANIMATIONUTILS_H
#define ANIMATIONUTILS_H
#include <dto/poses/dynamic/animation/Animation.h>
#include <spdlog/spdlog.h>

#include "PositionUtils.h"
#include "dto/poses/astrodynamic/spaceshipState/SpaceshipState.h"

class SpaceshipState;

class AnimationUtils
{
public:
    static Keyframe extractKeyframeAtTime(const Animation* animation, double time)
    {
        std::vector<Keyframe> keyframes = animation->getKeyframes();
        if (animation->isCyclic())
        {
            spdlog::error("AnimationUtils::extractKeyframeAtTime - Keyframe cycle not implemented");
            throw std::runtime_error("AnimationUtils::extractKeyframeAtTime: Keyframe cycle not implemented");
        }
        for (int i=1;i<keyframes.size(); i++)
        {
            if (keyframes[i].time >= time)
            {
                Keyframe& beforeTime = keyframes[i-1];
                Keyframe& afterTime = keyframes[i];
                double factor = (time - beforeTime.time) / (afterTime.time - beforeTime.time);
                return PositionUtils::interpolateKeyframes(beforeTime, afterTime, factor);
            }
        }
        Keyframe lastKeyframe = keyframes[keyframes.size()-1];
        return Keyframe(lastKeyframe.translation, lastKeyframe.rotation, time);
    }

    static Keyframe getInterpolatedKeyframeAtTime(const Keyframe& before,const Keyframe& after, double time)
    {
        double factor = (time - before.time) / (after.time - before.time);
        return PositionUtils::interpolateKeyframes(before, after, factor);
    }

    static State getInterpolatedStatesAtTime(const State& before,const State& after, double time)
    {
        double factor = (time - before.time) / (after.time - before.time);
        return PositionUtils::interpolateStates(before, after, factor);
    }

    static SpaceshipState getInterpolatedSpaceshipStatesAtTime(const SpaceshipState& before,const SpaceshipState& after, double time)
    {
        double factor = (time - before.time) / (after.time - before.time);
        return PositionUtils::interpolateSpaceshipStates(before, after, factor);
    }

    static std::vector<Keyframe> getInterpolatedKeyframesAtRate(const std::vector<Keyframe> &keyframes,
                                                                           int fps)
    {
        std::vector<Keyframe> interpolatedKeyframes;
        for (int i=0; i<keyframes.size()-1; i++)
        {
            const Keyframe& firstKeyframe = keyframes[i];
            interpolatedKeyframes.push_back(firstKeyframe);
            const Keyframe& secondKeyframe = keyframes[i+1];
            double dt = secondKeyframe.time - firstKeyframe.time;
            int numberOfFrames = round(dt*fps);
            int numberOfInbetweenFrames = numberOfFrames-2;
            if (numberOfInbetweenFrames <= 0)
                continue;
            int numberOfTimeIntervals = numberOfInbetweenFrames + 1;
            double lengthOfInterval = dt / numberOfTimeIntervals;
            for (int j=1; j<=numberOfInbetweenFrames; j++)
            {
                double frameTime = firstKeyframe.time + j * lengthOfInterval;
                Keyframe keyframe = getInterpolatedKeyframeAtTime(firstKeyframe, secondKeyframe, frameTime);
                interpolatedKeyframes.push_back(keyframe);
            }
        }
        interpolatedKeyframes.push_back(keyframes.back());
        return interpolatedKeyframes;
    }

    static std::vector<State> getInterpolatedStatesAtRate(const std::vector<State> &states,
                                                                          double fps)
    {
        std::vector<State> interpolatedStates;
        for (int i=0; i<states.size()-1; i++)
        {
            const State& firstState = states[i];
            interpolatedStates.push_back(firstState);
            const State& secondState= states[i+1];
            double dt = secondState.time - firstState.time;
            int numberOfFrames = round(dt*fps);
            int numberOfInbetweenFrames = numberOfFrames-2;
            if (numberOfInbetweenFrames <= 0)
                continue;
            int numberOfTimeIntervals = numberOfInbetweenFrames + 1;
            double lengthOfInterval = dt / numberOfTimeIntervals;
            for (int j=1; j<=numberOfInbetweenFrames; j++)
            {
                double frameTime = firstState.time + j * lengthOfInterval;
                State state = getInterpolatedStatesAtTime(firstState, secondState, frameTime);
                interpolatedStates.push_back(state);
            }
        }
        interpolatedStates.push_back(states.back());
        return interpolatedStates;
    }

    static std::vector<SpaceshipState> getInterpolatedSpaceshipStatesAtRate(const std::vector<SpaceshipState> &states,
                                                                      double fps)
    {
        std::vector<SpaceshipState> interpolatedStates;
        for (int i=0; i<states.size()-1; i++)
        {
            const SpaceshipState& firstState = states[i];
            interpolatedStates.push_back(firstState);
            const SpaceshipState& secondState= states[i+1];
            double dt = secondState.time - firstState.time;
            int numberOfFrames = round(dt*fps);
            int numberOfInbetweenFrames = numberOfFrames-2;
            if (numberOfInbetweenFrames <= 0)
                continue;
            int numberOfTimeIntervals = numberOfInbetweenFrames + 1;
            double lengthOfInterval = dt / numberOfTimeIntervals;
            for (int j=1; j<=numberOfInbetweenFrames; j++)
            {
                double frameTime = firstState.time + j * lengthOfInterval;
                SpaceshipState state = getInterpolatedSpaceshipStatesAtTime(firstState, secondState, frameTime);
                interpolatedStates.push_back(state);
            }
        }
        interpolatedStates.push_back(states.back());
        return interpolatedStates;
    }

};
#endif //ANIMATIONUTILS_H
