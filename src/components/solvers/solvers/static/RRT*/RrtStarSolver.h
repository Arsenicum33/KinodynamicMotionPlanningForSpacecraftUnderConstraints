//
// Created by arseniy on 12.10.24.
//

#ifndef RRTSTARSOLVER_H
#define RRTSTARSOLVER_H
#include <components/nearestNeighbour/AbstractNearestNeighbourSearch.h>

#include "components/pathGenerator/tree/ITreePathGenerator.h"
#include "components/sampling/pose/IPoseSampler.h"
#include "components/solvers/solvers/ARRTsolver.h"
#include "components/solvers/solvers/static/IStaticSolver.h"
#include "components/solvers/treeUtils/ATreeSolver.h"


class RrtStarSolver : public ARRTsolver<Pose, Pose>, public IStaticSolver
{
public:
    static std::unique_ptr<IComponent> createComponent(const ComponentConfig &config, const ReaderContext &context);

    RrtStarSolver(int maxIterations, double maxStepSize) : ARRTsolver(maxIterations, maxStepSize) {}

    CapabilitySet getCapabilities() const override { return CapabilitySet { Capability::StaticEnv}; }

    std::vector<Pose> solve(const Pose &startPosition, const Pose &goalPosition) override;

    void resolveDependencies(const ComponentConfig &config, ComponentManager *manager) override;

protected:
    std::shared_ptr<AbstractNearestNeighbourSearch<Pose>> nnSearch;
    std::shared_ptr<IPoseSampler<Pose>> poseSampler;
    std::shared_ptr<ICollisionHandler> collisionHandler;
    std::shared_ptr<ITreePathGenerator<Pose>> pathGenerator;

private:
    int findMinCostParent(const Pose& pose, std::vector<int>& collisionFreeNeighboursIndexes);



};



#endif //RRTSTARSOLVER_H
