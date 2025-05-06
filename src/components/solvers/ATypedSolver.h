//
// Created by arseniy on 3.5.25.
//

#ifndef ATYPEDSOLVER_H
#define ATYPEDSOLVER_H
#include "ISolver.h"

template <typename PositionType, typename TargetType>
class ATypedSolver : public ISolver
{
public:
    std::vector<std::any> solve(const std::any &start, const std::any &target) final;
protected:
    virtual std::vector<PositionType> solveTyped(const PositionType& start, const TargetType& target) = 0;
private:
    std::vector<std::any> toAnyVector(std::vector<PositionType> result);
};

template<typename PositionType, typename TargetType>
std::vector<std::any> ATypedSolver<PositionType, TargetType>::solve(const std::any &start, const std::any &target)
{
    try
    {
        std::vector<PositionType> result = solveTyped(std::any_cast<const PositionType&>(start), std::any_cast<const TargetType&>(target));
        return toAnyVector(result);
    }
    catch (std::bad_any_cast e)
    {
        spdlog::error("ARRTsolver::solve(): bad any cast.");
        throw;
    }
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
