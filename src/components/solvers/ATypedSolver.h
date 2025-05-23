// MIT License
// Copyright (c) 2025 Arseniy Panyukov
//
// See the LICENSE file in the root directory for full license information.


#ifndef ATYPEDSOLVER_H
#define ATYPEDSOLVER_H
#include "ISolver.h"
#include <chrono>

template <typename PositionType, typename TargetType>
class ATypedSolver : public ISolver
{
public:
    std::vector<std::any> solve(const std::any &start, const std::any &target) final;

    int getTotalRuntime() const override;
protected:
    virtual std::vector<PositionType> solveTyped(const PositionType& start, const TargetType& target) = 0;
private:
    std::vector<std::any> toAnyVector(std::vector<PositionType> result);

    long runtimeMilliseconds = -1;

};

template<typename PositionType, typename TargetType>
std::vector<std::any> ATypedSolver<PositionType, TargetType>::solve(const std::any &start, const std::any &target)
{
    try
    {
        using clock = std::chrono::steady_clock;
        const auto timerStart = clock::now();
        std::vector<PositionType> result = solveTyped(std::any_cast<const PositionType&>(start), std::any_cast<const TargetType&>(target));
        const auto timerEnd = clock::now();
        const auto total = timerEnd - timerStart;
        runtimeMilliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(total).count();
        return toAnyVector(result);
    }
    catch (std::bad_any_cast e)
    {
        spdlog::error("ARRTsolver::solve(): bad any cast.");
        throw;
    }
}

template<typename PositionType, typename TargetType>
int ATypedSolver<PositionType, TargetType>::getTotalRuntime() const
{
    if (runtimeMilliseconds<0)
    {
        spdlog::error("The algorithm hasnt finished, cant call getTotalRuntime()");
        throw std::runtime_error("getTotalRuntime() failed");
    }
    return runtimeMilliseconds;
}

template<typename PositionType, typename TargetType>
std::vector<std::any> ATypedSolver<PositionType, TargetType>::toAnyVector(std::vector<PositionType> result)
{
    std::vector<std::any> resultAsAny;
    resultAsAny.reserve(result.size());
    for (const auto& item : result)
    {
        resultAsAny.push_back(item);
    }
    return resultAsAny;
}

#endif //ATYPEDSOLVER_H
