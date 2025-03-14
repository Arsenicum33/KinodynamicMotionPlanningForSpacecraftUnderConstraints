//
// Created by arseniy on 12.1.25.
//

#include <components/collisionHandlers/static/rapid/RapidCollisionHandler.h>
#include <components/exporters/defaultExporter/DefaultExporter.h>
#include <components/nearestNeighbour/mpnn/MPNNsearch.h>
#include <components/pathGenerator/tree/uniform/UniformPathGenerator.h>
#include <components/sampling/pose/biasedRandom/BiasedRandomSampler.h>
#include <components/solvers/solvers/static/RRT*/RrtStarSolver.h>
#include <components/solvers/solvers/static/RRT/RRTsolver.h>

#include "ComponentRegistry.h"
#include "components/collisionHandlers/dynamic/rapid/RapidDynamicCollisionHandler.h"
#include "components/distanceMeasurement/defaultSpatial/DefaultSpatialDistanceMetric.h"
#include "components/distanceMeasurement/temporalTotal/TemporalTransRotMetric.h"
#include "components/exporters/dynamicExporter/DefaultDynamicExporter.h"
#include "components/nearestNeighbour/temporalMPNN/TemporalMPNNsearch.h"
#include "components/pathGenerator/tree/dynamic/DefaultDynamicPathGenerator.h"
#include "components/sampling/keyframe/biasedRandomMovingTarget/BiasedRandomMovingTargetSampler.h"
#include "components/sampling/pose/defaultRandom/DefaultRandomSampler.h"
#include "components/solvers/solvers/dynamic/movingTarget/MT_TARRTsolver.h"
#include "components/solvers/solvers/dynamic/TARRT/TARRTsolver.h"
#include "components/terminationConditions/movingTarget/MovingTargetTerminationCondition.h"
#include "components/terminationConditions/default/DefaultTerminationCondition.h"


REGISTER_COMPONENT(RapidCollisionHandler);
REGISTER_COMPONENT(RRTsolver);
REGISTER_COMPONENT(RrtStarSolver);
REGISTER_COMPONENT(TARRTsolver);
REGISTER_COMPONENT(MPNNsearch);
REGISTER_COMPONENT(DefaultSpatialDistanceMetric);
REGISTER_COMPONENT(UniformPathGenerator);
REGISTER_COMPONENT(DefaultRandomSampler);
REGISTER_COMPONENT(BiasedRandomSampler);
REGISTER_COMPONENT(DefaultExporter);
REGISTER_COMPONENT(RapidDynamicCollisionHandler);
REGISTER_COMPONENT(DefaultDynamicPathGenerator);
REGISTER_COMPONENT(DefaultDynamicExporter);
REGISTER_COMPONENT(DefaultTerminationCondition);
REGISTER_COMPONENT(MovingTargetTerminationCondition);
REGISTER_COMPONENT(BiasedRandomMovingTargetSampler);
REGISTER_COMPONENT(TemporalMPNNsearch);
REGISTER_COMPONENT(MT_TARRTsolver);
REGISTER_COMPONENT(TemporalTransRotMetric);