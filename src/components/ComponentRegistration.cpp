//
// Created by arseniy on 12.1.25.
//

#include "components/collisionHandlers/RapidCollisionHandler.h"
#include "distanceMeasurement/WeightedTransRotMetricFactory.h"
#include "nearestNeighbour/MPNNsearchFactory.h"
#include "pathGenerator/UniformPathGeneratorFactory.h"
#include "poses/static/sampling/BiasedRandomSamplerFactory.h"
#include "poses/static/sampling/DefaultRandomSamplerFactory.h"
#include "solvers/treeSolvers/RRT/RRTsolverFactory.h"

REGISTER_COMPONENT(RapidCollisionHandler, RapidCollisionHandlerFactory);
REGISTER_COMPONENT(RRTsolver, RRTsolverFactory);
REGISTER_COMPONENT(MPNNsearch, MPNNsearchFactory);
REGISTER_COMPONENT(WeightedTranslationRotationMetric, WeightedTransRotMetricFactory);
REGISTER_COMPONENT(UniformPathGenerator, UniformPathGeneratorFactory);
REGISTER_COMPONENT(DefaultRandomSampler, DefaultRandomSamplerFactory);
REGISTER_COMPONENT(BiasedRandomSampler, BiasedRandomSamplerFactory);