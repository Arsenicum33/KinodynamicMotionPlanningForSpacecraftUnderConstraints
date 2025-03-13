//
// Created by arseniy on 12.1.25.
//

#include "ComponentRegistry.h"
#include "components/collisionHandlers/dynamic/rapid/RapidDynamicCollisionHandlerFactory.h"
#include "components/collisionHandlers/static/rapid/RapidCollisionHandlerFactory.h"
#include "components/distanceMeasurement/defaultSpatial/DefaultSpatialDistanceMetricFactory.h"
#include "components/distanceMeasurement/temporalTotal/TemporalTransRotMetricFactory.h"
#include "components/exporters/defaultExporter/DefaultExporterFactory.h"
#include "components/exporters/dynamicExporter/DefaultDynamicExporterFactory.h"
#include "components/nearestNeighbour/mpnn/MPNNsearchFactory.h"
#include "components/nearestNeighbour/temporalMPNN/TemporalMPNNsearchFactory.h"
#include "components/pathGenerator/tree/dynamic/DefaultDynamicPathGeneratorFactory.h"
#include "components/pathGenerator/tree/uniform/UniformPathGeneratorFactory.h"
#include "components/sampling/keyframe/biasedRandomMovingTarget/BiasedRandomMovingTargetSamplerFactory.h"
#include "components/sampling/pose/biasedRandom/BiasedRandomSamplerFactory.h"
#include "components/sampling/pose/defaultRandom/DefaultRandomSamplerFactory.h"
#include "components/solvers/solvers/dynamic/TARRT/TARRTsolverFactory.h"
#include "components/solvers/solvers/static/RRT*/RrtStarSolverFactory.h"
#include "components/solvers/solvers/static/RRT/RRTsolverFactory.h"
#include "components/solvers/solvers/dynamic/movingTarget/MT_TARRTsolverFactory.h"
#include "components/terminationConditions/default/DefaultTerminationConditionFactory.h"
#include "components/terminationConditions/movingTarget/MovingTargetTerminationConditionFactory.h"

REGISTER_COMPONENT(RapidCollisionHandler, RapidCollisionHandlerFactory);
REGISTER_COMPONENT(RRTsolver, RRTsolverFactory);
REGISTER_COMPONENT(RrtStarSolver, RrtStarSolverFactory);
REGISTER_COMPONENT(TARRTsolver, TARRTsolverFactory);
REGISTER_COMPONENT(MPNNsearch, MPNNsearchFactory);
REGISTER_COMPONENT(DefaultSpatialDistanceMetric, DefaultSpatialDistanceMetricFactory);
REGISTER_COMPONENT(UniformPathGenerator, UniformPathGeneratorFactory);
REGISTER_COMPONENT(DefaultRandomSampler, DefaultRandomSamplerFactory);
REGISTER_COMPONENT(BiasedRandomSampler, BiasedRandomSamplerFactory);
REGISTER_COMPONENT(DefaultExporter, DefaultExporterFactory);
REGISTER_COMPONENT(RapidDynamicCollisionHandler, RapidDynamicCollisionHandlerFactory);
REGISTER_COMPONENT(DefaultDynamicPathGenerator, DefaultDynamicPathGeneratorFactory);
REGISTER_COMPONENT(DefaultDynamicExporter, DefaultDynamicExporterFactory);
REGISTER_COMPONENT(DefaultStaticTerminationCondition, DefaultTerminationConditionFactory);
REGISTER_COMPONENT(MovingTargetTerminationCondition, MovingTargetTerminationConditionFactory);
REGISTER_COMPONENT(BiasedRandomMovingTargetSampler, BiasedRandomMovingTargetSamplerFactory);
REGISTER_COMPONENT(TemporalMPNNsearch, TemporalMPNNsearchFactory);
REGISTER_COMPONENT(MT_TARRTsolver, MT_TARRTsolverFactory);
REGISTER_COMPONENT(TemporalTransRotMetric, TemporalTransRotMetricFactory);