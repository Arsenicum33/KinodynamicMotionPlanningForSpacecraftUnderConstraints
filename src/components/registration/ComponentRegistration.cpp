//
// Created by arseniy on 12.1.25.
//

#include "ComponentRegistry.h"
#include "components/collisionHandlers/RapidCollisionHandler.h"
#include "components/collisionHandlers/dynamic/RapidDynamicCollisionHandlerFactory.h"
#include "components/distanceMeasurement/WeightedTransRotMetricFactory.h"
#include "components/exporters/DefaultDynamicExporterFactory.h"
#include "components/exporters/DefaultExporterFactory.h"
#include "components/nearestNeighbour/MPNNsearchFactory.h"
#include "components/pathGenerator/DefaultDynamicPathGeneratorFactory.h"
#include "components/pathGenerator/TreeConnectPathGeneratorFactory.h"
#include "components/pathGenerator/UniformPathGeneratorFactory.h"
#include "components/sampling/BiasedRandomSamplerFactory.h"
#include "components/sampling/DefaultRandomSamplerFactory.h"
#include "components/solvers/solvers/dynamic/TARRT-Connect/TARRTconnectSolverFactory.h"
#include "components/solvers/solvers/dynamic/TARRT/TARRTsolverFactory.h"
#include "components/solvers/solvers/static/RRT*/RrtStarSolverFactory.h"
#include "components/solvers/solvers/static/RRT/RRTsolverFactory.h"


REGISTER_COMPONENT(RapidCollisionHandler, RapidCollisionHandlerFactory);
REGISTER_COMPONENT(RRTsolver, RRTsolverFactory);
REGISTER_COMPONENT(RrtStarSolver, RrtStarSolverFactory);
REGISTER_COMPONENT(TARRTsolver, TARRTsolverFactory);
REGISTER_COMPONENT(MPNNsearch, MPNNsearchFactory);
REGISTER_COMPONENT(WeightedTranslationRotationMetric, WeightedTransRotMetricFactory);
REGISTER_COMPONENT(UniformPathGenerator, UniformPathGeneratorFactory);
REGISTER_COMPONENT(DefaultRandomSampler, DefaultRandomSamplerFactory);
REGISTER_COMPONENT(BiasedRandomSampler, BiasedRandomSamplerFactory);
REGISTER_COMPONENT(DefaultExporter, DefaultExporterFactory);
REGISTER_COMPONENT(RapidDynamicCollisionHandler, RapidDynamicCollisionHandlerFactory);
REGISTER_COMPONENT(DefaultDynamicPathGenerator, DefaultDynamicPathGeneratorFactory);
REGISTER_COMPONENT(DefaultDynamicExporter, DefaultDynamicExporterFactory);
REGISTER_COMPONENT(TARRTconnectSolver, TARRTconnectSolverFactory);
REGISTER_COMPONENT(TreeConnectPathGenerator, TreeConnectPathGeneratorFactory);