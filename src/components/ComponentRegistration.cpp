//
// Created by arseniy on 12.1.25.
//

#include "collisionHandlers/dynamic/RapidDynamicCollisionHandlerFactory.h"
#include "components/collisionHandlers/RapidCollisionHandler.h"
#include "costFunctions/DistanceTimeFunctionFactory.h"
#include "distanceMeasurement/WeightedTransRotMetricFactory.h"
#include "exporters/DefaultExporterFactory.h"
#include "nearestNeighbour/MPNNsearchFactory.h"
#include "pathGenerator/UniformPathGeneratorFactory.h"
#include "poses/static/sampling/BiasedRandomSamplerFactory.h"
#include "poses/static/sampling/DefaultRandomSamplerFactory.h"
#include "solvers/dynamic/treeSolvers/TRRT/TRRTsolverFactory.h"
#include "solvers/treeSolvers/RRT*/RrtStarSolverFactory.h"
#include "solvers/treeSolvers/RRT/RRTsolverFactory.h"

REGISTER_COMPONENT(RapidCollisionHandler, RapidCollisionHandlerFactory);
REGISTER_COMPONENT(RRTsolver, RRTsolverFactory);
REGISTER_COMPONENT(RrtStarSolver, RrtStarSolverFactory);
REGISTER_COMPONENT(TRRTsolver, TRRTsolverFactory);
REGISTER_COMPONENT(MPNNsearch, MPNNsearchFactory);
REGISTER_COMPONENT(WeightedTranslationRotationMetric, WeightedTransRotMetricFactory);
REGISTER_COMPONENT(UniformPathGenerator, UniformPathGeneratorFactory);
REGISTER_COMPONENT(DefaultRandomSampler, DefaultRandomSamplerFactory);
REGISTER_COMPONENT(BiasedRandomSampler, BiasedRandomSamplerFactory);
REGISTER_COMPONENT(DefaultExporter, DefaultExporterFactory);
REGISTER_COMPONENT(RapidDynamicCollisionHandler, RapidDynamicCollisionHandlerFactory);