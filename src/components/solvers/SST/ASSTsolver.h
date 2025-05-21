//
// Created by arseniy on 3.5.25.
//

#ifndef ASSTSOLVER_H
#define ASSTSOLVER_H
#include <components/collisionHandlers/ICollisionHandler.h>
#include <components/sampling/positionSampling/IPositionSampler.h>
#include <components/terminationConditions/ITerminationCondition.h>
#include <utils/PhysicsUtils.h>

#include "components/constraintsEnforcer/IConstraintsEnforcer.h"
#include "components/costFunctions/ISSTcostFunction.h"
#include "components/nearestNeighbour/ompl/gnat/sst/AGNAT_SST.h"
#include "components/nearestNeighbour/ompl/gnat/sst/AGNAT_Witness.h"
#include "components/pathGenerator/sst/ISSTpathGenerator.h"
#include "components/solvers/ATypedSolver.h"
#include "components/solvers/utils/statePropagators/IStatePropagator.h"
#include <chrono>

template <typename StateType, typename TargetType>
class ASSTsolver : public ATypedSolver<StateType, TargetType>
{
public:
    ASSTsolver(int maxIterations, double selectionRadius, double maxWitnessProximityRadius, int outputPeriod = 1000)
        : maxIterations(maxIterations),
          selectionRadius(selectionRadius),
          maxWitnessProximityRadius(maxWitnessProximityRadius),
          outputPeriod(outputPeriod)
    {}

    int getTotalIterations() const override;

protected:
    std::vector<StateType> solveTyped(const StateType &start, const TargetType &target) override;

    void resolveDependencies(const ComponentConfig &config, ComponentManager *manager) override;
    ComponentType getType() const override { return ComponentType::Solver; }

    virtual void initialize(const StateType& start);
    virtual void outputIteration(int currentIteration);
    virtual std::shared_ptr<SSTnode<StateType>> selectNode(const TargetType &target);
    virtual StateType propagate(const StateType& current);
    virtual double getCost(std::shared_ptr<SSTnode<StateType>> parent, const StateType& newState);
    virtual std::shared_ptr<SSTnode<StateType>> createNode(std::shared_ptr<SSTnode<StateType>> parent,
        const StateType& newState, double cost);
    virtual bool isTransitionValid(std::shared_ptr<SSTnode<StateType>> parent, const StateType& newState);
    virtual bool isLocallyBest(const StateType& newState, double cost);
    virtual bool isTargetReached(const StateType& newState, const TargetType& target);
    virtual std::vector<StateType> extractPath(std::shared_ptr<SSTnode<StateType>> finalNode);
    virtual void pruneDominatedNodes(std::shared_ptr<SSTnode<StateType>> newNode);
    virtual std::vector<StateType> handleSolutionNotFound();
    std::vector<std::shared_ptr<ANode>> getData() override;

    std::unique_ptr<AGNAT_Witness<StateType>> witnessNNsearch;
    std::unique_ptr<AGNAT_SST<StateType>> nnSearch;
    std::shared_ptr<IStatePropagator<StateType>> statePropagator;
    std::shared_ptr<ISSTcostFunction<StateType>> costFunction;
    std::shared_ptr<IPositionSampler<StateType, TargetType>> sampler;
    std::shared_ptr<IConstraintsEnforcer<StateType>> constraintsEnforcer;
    std::shared_ptr<ICollisionHandler<StateType>> collisionHandler;
    std::shared_ptr<ITerminationCondition<StateType, TargetType>> terminationCondition;
    std::shared_ptr<ISSTpathGenerator<StateType>> pathGenerator;


    int maxIterations;
    int outputPeriod;
    double selectionRadius;
    double maxWitnessProximityRadius;

    int nodesPruned=0;

    int totalIterations = -1;

    std::chrono::time_point<std::chrono::steady_clock> timerStart;

};

template<typename StateType, typename TargetType>
int ASSTsolver<StateType, TargetType>::getTotalIterations() const
{
    if (totalIterations < 0)
    {
        spdlog::error("The algorithm hasnt finished, cant call getTotalIterations()");
        throw std::runtime_error("getTotalIterations() failed");
    }
    return totalIterations;
}

template<typename StateType, typename TargetType>
std::vector<StateType> ASSTsolver<StateType, TargetType>::solveTyped(const StateType &start,
    const TargetType &target)
{
    initialize(start);
    for (int i=0;i<maxIterations;i++)
    {
        outputIteration(i);
        std::shared_ptr<SSTnode<StateType>> selectedNode = selectNode(target);
        StateType newState = propagate(selectedNode->state);
        double cost = getCost(selectedNode, newState);
        if (!isLocallyBest(newState, cost))
            continue;
        if (!isTransitionValid(selectedNode, newState))
            continue;
        std::shared_ptr<SSTnode<StateType>> newNode = createNode(selectedNode, newState, cost);
        if (isTargetReached(newState, target))
        {
            totalIterations = i+1;
            return extractPath(newNode);
        }
        pruneDominatedNodes(newNode);
    }
    return handleSolutionNotFound();
}

template<typename StateType, typename TargetType>
void ASSTsolver<StateType, TargetType>::resolveDependencies(const ComponentConfig &config,
    ComponentManager *manager)
{
    ATypedSolver<StateType, TargetType>::resolveDependencies(config, manager);

    std::unique_ptr<IComponent> nnSearchBase = manager->getUniqueComponent(ComponentType::NearestNeighbourSearch, "nn");
    auto nnSearchDerived = dynamic_cast<AGNAT_SST<StateType>*>(nnSearchBase.get());
    if (!nnSearchDerived)
    {
        spdlog::error("nnSearch dependency not resolved");
        throw std::runtime_error("nnSearch dependency not resolved");
    }
    nnSearch = std::unique_ptr<AGNAT_SST<StateType>>(nnSearchDerived);
    nnSearchBase.release();

    std::unique_ptr<IComponent> witnessSearchBase = manager->getUniqueComponent(ComponentType::NearestNeighbourSearch, "nn_witness");
    auto witnessSearchDerived = dynamic_cast<AGNAT_Witness<StateType>*>(witnessSearchBase.get());
    if (!witnessSearchDerived)
    {
        spdlog::error("witnessSearch dependency not resolved");
        throw std::runtime_error("witnessSearch dependency not resolved");
    }
    witnessNNsearch = std::unique_ptr<AGNAT_Witness<StateType>>(witnessSearchDerived);
    witnessSearchBase.release();

    constraintsEnforcer = std::dynamic_pointer_cast<IConstraintsEnforcer<StateType>>(
    manager->getComponent(ComponentType::ConstraintsEnforcer));
    statePropagator = std::dynamic_pointer_cast<IStatePropagator<StateType>>(
        manager->getComponent(ComponentType::StatePropagator));
    collisionHandler = std::dynamic_pointer_cast<ICollisionHandler<StateType>>(
        manager->getComponent(ComponentType::CollisionHandler));
    sampler = std::dynamic_pointer_cast<IPositionSampler<StateType, TargetType>>(
        manager->getComponent(ComponentType::PositionSampler));
    pathGenerator = std::dynamic_pointer_cast<ISSTpathGenerator<StateType>>(
        manager->getComponent(ComponentType::PathGenerator));
    terminationCondition = std::dynamic_pointer_cast<ITerminationCondition<StateType, TargetType>>(
        manager->getComponent(ComponentType::TerminationCondition));
    costFunction = std::dynamic_pointer_cast<ISSTcostFunction<StateType>>(
        manager->getComponent(ComponentType::CostFunction));

}

template<typename StateType, typename TargetType>
void ASSTsolver<StateType, TargetType>::initialize(const StateType &start)
{
    spdlog::info("Solver started!");
    timerStart = std::chrono::steady_clock::now();
    std::shared_ptr<SSTnode<StateType>> initialNode = std::make_shared<SSTnode<StateType>>(start, 0.0);
    nnSearch->add(initialNode);
    std::shared_ptr<Witness<StateType>> witness = std::make_shared<Witness<StateType>>(initialNode->state.translation, initialNode);
    witnessNNsearch->add(witness);
    ++this->totalNodes;
}

template<typename StateType, typename TargetType>
void ASSTsolver<StateType, TargetType>::outputIteration(int currentIteration)
{
    if ((currentIteration+1) % outputPeriod == 0)
    {
        spdlog::info("Iteration {}/{}, Nodes pruned/total: {}/{}", currentIteration+1, maxIterations, nodesPruned, this->totalNodes);
    }
    if ((currentIteration+1) % this->dataOutputPeriod == 0)
    {
        this->iterationsToNodes.push_back(std::make_pair(currentIteration+1, this->totalNodes));
        auto total = std::chrono::steady_clock::now() - timerStart;
        double runtime =  std::chrono::duration_cast<std::chrono::milliseconds>(total).count();
        this->iterationsToRuntime.push_back(std::make_pair(currentIteration+1, runtime));
    }
}

template<typename StateType, typename TargetType>
std::shared_ptr<SSTnode<StateType>> ASSTsolver<StateType, TargetType>::selectNode(const TargetType& target)
{
    StateType sampledState = sampler->sample(target);
    std::vector<std::shared_ptr<SSTnode<StateType>>> nearestNodes = nnSearch->findRnearest(sampledState, selectionRadius);
    if (nearestNodes.empty())
        return nnSearch->findNearest(sampledState);
    double minCost = std::numeric_limits<double>::max();
    std::shared_ptr<SSTnode<StateType>> result = nullptr;
    for (const auto& node : nearestNodes)
    {
        if (node->cost < minCost)
        {
            minCost = node->cost;
            result = node;
        }
    }
    return result;
}

template<typename StateType, typename TargetType>
StateType ASSTsolver<StateType, TargetType>::propagate(const StateType &current)
{
    return statePropagator->propagate(current);
}

template<typename StateType, typename TargetType>
double ASSTsolver<StateType, TargetType>::getCost(std::shared_ptr<SSTnode<StateType>> parent,
    const StateType &newState)
{
    return costFunction->getCost(parent, newState);
}

template<typename StateType, typename TargetType>
std::shared_ptr<SSTnode<StateType>> ASSTsolver<StateType, TargetType>::createNode(
    std::shared_ptr<SSTnode<StateType>> parent, const StateType &newState, double cost)
{
    std::shared_ptr<SSTnode<StateType>> node = std::make_shared<SSTnode<StateType>>(newState, cost, parent);
    nnSearch->add(node);
    ++this->totalNodes;
    return node;
}

template<typename StateType, typename TargetType>
bool ASSTsolver<StateType, TargetType>::isTransitionValid(std::shared_ptr<SSTnode<StateType>> parent,
    const StateType &newState)
{
    return this->constraintsEnforcer->satisfiesConstraints(newState) &&
        this->collisionHandler->isTransitionValid(parent->state, newState);
}

template<typename StateType, typename TargetType>
bool ASSTsolver<StateType, TargetType>::isLocallyBest(const StateType &newState, double cost)
{
    using namespace PhysicsUtils;
    std::shared_ptr<Witness<StateType>> witness = witnessNNsearch->findNearest(newState);
    if (norm(newState.translation - witness->position) > maxWitnessProximityRadius)
    {
        std::shared_ptr<Witness<StateType>> newWitness = std::make_shared<Witness<StateType>>(newState.translation);
        witnessNNsearch->add(newWitness);
        return true;
    }
    std::shared_ptr<SSTnode<StateType>> peer = witness->rep;
    if (peer == nullptr || cost <= peer->cost)
        return true;
    return false;
}

template<typename StateType, typename TargetType>
bool ASSTsolver<StateType, TargetType>::isTargetReached(const StateType &newState, const TargetType &target)
{
    return terminationCondition->isTargetReached(newState, target);
}

template<typename StateType, typename TargetType>
std::vector<StateType> ASSTsolver<StateType, TargetType>::extractPath(
    std::shared_ptr<SSTnode<StateType>> finalNode)
{
    return pathGenerator->generatePath(finalNode);
}

template<typename StateType, typename TargetType>
void ASSTsolver<StateType, TargetType>::pruneDominatedNodes(std::shared_ptr<SSTnode<StateType>> newNode)
{
    std::shared_ptr<Witness<StateType>> newWitness = witnessNNsearch->findNearest(newNode->state);
    std::shared_ptr<SSTnode<StateType>> peer = newWitness->rep;
    if (peer != nullptr)
    {
        peer->active = false;
        nnSearch->remove(peer);
    }
    newWitness->rep = newNode;
    while (peer!=nullptr && peer->children.empty() && !peer->active)
    {
        nnSearch->remove(peer);
        std::shared_ptr<SSTnode<StateType>> parent = peer->parent.lock();
        if (parent!=nullptr)
        {
            parent->removeChild(peer);
        }
        nodesPruned++;
        this->totalNodes--;
        peer = parent;
    }
}

template<typename StateType, typename TargetType>
std::vector<StateType> ASSTsolver<StateType, TargetType>::handleSolutionNotFound()
{
    totalIterations = maxIterations;
    spdlog::error("Solution NOT found!");
    throw std::runtime_error("Solution NOT found!");
}

template<typename StateType, typename TargetType>
std::vector<std::shared_ptr<ANode>> ASSTsolver<StateType, TargetType>::getData()
{
    auto nodes = nnSearch->getNodes();
    std::vector<std::shared_ptr<ANode>> result;
    for (auto node : nodes)
    {
        if (!nnSearch->isRemoved(node))
            result.push_back(node);
    }
    return result;
}



#endif //ASSTSOLVER_H
