#include <components/distanceMeasurement/IDistanceMetric.h>
#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "components/agentModel/IAgentModel.h"
#include "components/derivator/kinodynamic/KinodynamicDerivator.h"
#include "components/dynamicsSimulators/astrodynamic/RK4_AstrodynamicSimulator.h"
#include "components/dynamicsSimulators/kinodynamic/RK4_KinodynamicSimulator.h"
#include "components/physics/interactions/GravityInteraction.h"
#include "dto/poses/astrodynamic/celestialBody/CelestialBody.h"
#include "dto/poses/dynamic/kinodynamic/state/State.h"
#include "dto/poses/static/poseMath/PoseMath.h"


using ::testing::Return;
using ::testing::_;




class MockDistanceMetric : public IDistanceMetric {
public:
    std::vector<double> getDimensionWeights() const override { return std::vector<double>(); };

    std::vector<double> getDimensionWeightsNoRotation() const override { return std::vector<double>(); };

    MOCK_METHOD(double, getSpatialDistance,
                (const Pose&, const Pose&), (override));
};

class MockAgentModel : public IAgentModel<State> {
public:
    CapabilitySet getCapabilities() const override { return CapabilitySet { Capability::AstrodynamicEnv}; };

    Eigen::Matrix3d getInertiaTensor(const State &state) const override { return Eigen::Matrix3d(); };

    MOCK_METHOD(double, getTotalMass, (const State&), (const, override));
};

class GravityInteractionTest : public ::testing::Test
{
protected:
    void SetUp() override
    {
    }
};

TEST_F(GravityInteractionTest, ComputeForceForSingleBody)
{
    auto distanceMetric = std::make_shared<MockDistanceMetric>();
    auto agentModel = std::make_shared<MockAgentModel>();

    // Set up a celestial body
    std::vector<Keyframe> keyframes {Keyframe({0.0,0.0,0.0}, 0.0)};
    CelestialBody body(std::make_shared<Animation>(keyframes, false), 5.0e12, 1000, "planet");

    std::vector<CelestialBody> bodies = { body };
    GravityInteraction<State> interaction(bodies,distanceMetric, agentModel);

    // Create state
    State s({10000, 0.0,0.0}, Eigen::Quaterniond::Identity(), 0.0, {0.0,0.0,0.0}, {0.0,0.0,0.0});

    // Expectations
    EXPECT_CALL(*agentModel, getTotalMass(_)).WillOnce(Return(2.0e5));
    EXPECT_CALL(*distanceMetric, getSpatialDistance(_, _)).WillOnce(Return(10000.0));

    // Act
    TotalForce f = interaction.computeTotalForce(s);

    // Gravitational force magnitude = G * m1 * m2 / r^2
    double expectedMag = GRAVITATIONAL_CONSTANT * 2.0e5 * 5.0e12 / (10000.0 * 10000.0);
    EXPECT_NEAR(f.getForce()[0], expectedMag, 1e-6);
    EXPECT_NEAR(f.getForce()[1], 0.0, 1e-6);
    EXPECT_NEAR(f.getForce()[2], 0.0, 1e-6);
}

TEST_F(GravityInteractionTest, TwoBodies)
{
    auto distanceMetric = std::make_shared<MockDistanceMetric>();
    auto agentModel = std::make_shared<MockAgentModel>();

    // Set up a celestial body
    std::vector<Keyframe> keyframes1 {Keyframe({10000.0,0.0,0.0}, 0.0)};
    CelestialBody body1(std::make_shared<Animation>(keyframes1, false), 5.0e12, 1000, "planet");
    std::vector<Keyframe> keyframes2 {Keyframe({0.0,20000.0,0.0}, 0.0)};
    CelestialBody body2(std::make_shared<Animation>(keyframes2, false), 7.0e13, 1000, "planet");

    std::vector<CelestialBody> bodies = { body1, body2 };
    GravityInteraction<State> interaction(bodies,distanceMetric, agentModel);

    // Create state
    State s({0, 0.0,0.0}, Eigen::Quaterniond::Identity(), 0.0, {0.0,0.0,0.0}, {0.0,0.0,0.0});

    // Expectations
    EXPECT_CALL(*agentModel, getTotalMass(_)).WillRepeatedly(Return(2.0e5));
    EXPECT_CALL(*distanceMetric, getSpatialDistance(_, _)).WillOnce(Return(10000.0)).WillOnce(Return(20000));

    // Act
    TotalForce f = interaction.computeTotalForce(s);

    // Gravitational force magnitude = G * m1 * m2 / r^2
    double expectedMag1 = GRAVITATIONAL_CONSTANT * 2.0e5 * 5.0e12 / (10000.0 * 10000.0);
    double expectedMag2 = GRAVITATIONAL_CONSTANT * 2.0e5 * 7.0e13 / (20000.0 * 20000.0);
    EXPECT_NEAR(f.getForce()[0], -expectedMag1, 1e-6);
    EXPECT_NEAR(f.getForce()[1], -expectedMag2, 1e-6);
    EXPECT_NEAR(f.getForce()[2], 0.0, 1e-6);
}