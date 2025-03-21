//
// Created by arseniy on 12.1.25.
//

#include <components/exporters/defaultExporter/DefaultExporter.h>
#include <components/nearestNeighbour/mpnn/AMPNNsearch.h>
#include <components/pathGenerator/tree/uniform/UniformPathGenerator.h>

#include "ComponentRegistry.h"
#include "components/collisionHandlers/dynamic/DynamicCollisionHandler.h"
#include "components/collisionHandlers/static/StaticCollisionHandler.h"
#include "components/distanceMeasurement/defaultSpatial/DefaultSpatialDistanceMetric.h"
#include "components/distanceMeasurement/temporalTotal/TemporalTransRotMetric.h"
#include "components/exporters/dynamicExporter/DefaultDynamicExporter.h"
#include "components/interpolators/dynamic/DynamicInterpolator.h"
#include "components/interpolators/static/StaticInterpolator.h"
#include "components/nearestNeighbour/mpnn/dynamic/DynamicMPNNsearch.h"
#include "components/nearestNeighbour/mpnn/static/StaticMPNNsearch.h"
#include "components/nearestNeighbour/temporalMPNN/TemporalMPNNsearch.h"
#include "components/pathGenerator/tree/dynamic/DefaultDynamicPathGenerator.h"
#include "components/sampling/positionSampling/dynamic/biased/DynamicBiasedRandomSampler.h"
#include "components/sampling/positionSampling/dynamic/default/DynamicRandomSampler.h"
#include "components/sampling/positionSampling/dynamic/movingTarget/MovingTargetBiasedSampler.h"
#include "components/sampling/positionSampling/static/biased/StaticBiasedRandomSampler.h"
#include "components/sampling/positionSampling/static/default/StaticRandomSampler.h"
#include "components/terminationConditions/dynamic/DynamicTerminationCondition.h"
#include "components/terminationConditions/movingTarget/MovingTargetTerminationCondition.h"
#include "components/terminationConditions/static/StaticTerminationCondition.h"
#include "components/solvers/static/RRT/RRTsolver.h"
#include "components/solvers/dynamic/TARRT/TARRTsolver.h"
#include "components/solvers/dynamic/movingTarget/MT_TARRTsolver.h"

REGISTER_COMPONENT(StaticCollisionHandler);
REGISTER_COMPONENT(RRTsolver);
REGISTER_COMPONENT(TAGeometricRRTsolver);
REGISTER_COMPONENT(StaticMPNNsearch);
REGISTER_COMPONENT(DynamicMPNNsearch);
REGISTER_COMPONENT(DefaultSpatialDistanceMetric);
REGISTER_COMPONENT(UniformPathGenerator);
REGISTER_COMPONENT(StaticRandomSampler);
REGISTER_COMPONENT(DynamicRandomSampler);
REGISTER_COMPONENT(DefaultExporter);
REGISTER_COMPONENT(DynamicCollisionHandler);
REGISTER_COMPONENT(DefaultDynamicPathGenerator);
REGISTER_COMPONENT(DefaultDynamicExporter);
REGISTER_COMPONENT(StaticTerminationCondition);
REGISTER_COMPONENT(MovingTargetTerminationCondition);
REGISTER_COMPONENT(StaticBiasedRandomSampler);
REGISTER_COMPONENT(DynamicBiasedRandomSampler);
REGISTER_COMPONENT(MovingTargetBiasedSampler);
REGISTER_COMPONENT(TemporalMPNNsearch);
REGISTER_COMPONENT(MT_TARRTsolver);
REGISTER_COMPONENT(TemporalTransRotMetric);
REGISTER_COMPONENT(StaticInterpolator);
REGISTER_COMPONENT(DynamicInterpolator);
REGISTER_COMPONENT(DynamicTerminationCondition);
