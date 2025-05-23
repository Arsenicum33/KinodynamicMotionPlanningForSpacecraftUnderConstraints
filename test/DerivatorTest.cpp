//
// Created by arseniy on 23.5.25.
//
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "components/derivator/kinodynamic/KinodynamicDerivator.h"
#include "components/dynamicsSimulators/astrodynamic/RK4_AstrodynamicSimulator.h"
#include "components/dynamicsSimulators/kinodynamic/RK4_KinodynamicSimulator.h"
#include "dto/poses/dynamic/kinodynamic/state/State.h"
#include "dto/poses/static/poseMath/PoseMath.h"

class DerivatorTest : public ::testing::Test
{
protected:
    void SetUp() override
    {
        derivator = std::make_unique<KinodynamicDerivator>();
    }

    State zeroState()
    {
        return State(
            {0.0, 0.0, 0.0},
            Eigen::Quaterniond::Identity(),
            0.0,
            {0.0, 0.0, 0.0},
            {0.0, 0.0, 0.0}
        );
    }

    std::unique_ptr<KinodynamicDerivator> derivator;
};

class MockPhysicsSimulator : public IPhysicsSimulator<State> {
public:
    CapabilitySet getCapabilities() const override { return CapabilitySet(); };

    MOCK_METHOD(TotalAcceleration, computeAcceleration,
                (const State& state, const BurstControlInput& input),
                (override));
};


TEST_F(DerivatorTest, Coasting)
{
    State initial = zeroState();
    BurstControlInput zeroInput(0,{0.0, 0.0, 0.0}, 0.0, 0.0);
    std::shared_ptr<MockPhysicsSimulator> simulator = std::make_shared<MockPhysicsSimulator>();
    TotalAcceleration acceleration({0.0,0.0,0.0}, {0.0,0.0,0.0});
    EXPECT_CALL(*(simulator.get()), computeAcceleration(testing::_, testing::_))
            .WillOnce(testing::Return(acceleration));
    derivator->setPhysicsSimulator(simulator);
    State next = derivator->derive(initial,zeroInput);


    EXPECT_NEAR(next.translation[0], 0.0, 1e-6);
    EXPECT_NEAR(next.translation[1], 0.0, 1e-6);
    EXPECT_NEAR(next.translation[2], 0.0, 1e-6);
    EXPECT_NEAR(next.velocity[0], 0.0, 1e-6);
    EXPECT_NEAR(next.velocity[1], 0.0, 1e-6);
    EXPECT_NEAR(next.velocity[2], 0.0, 1e-6);

    EXPECT_NEAR(next.angularVelocity[0], 0.0, 1e-6);
    EXPECT_NEAR(next.angularVelocity[1], 0.0, 1e-6);
    EXPECT_NEAR(next.angularVelocity[2], 0.0, 1e-6);

    EXPECT_NEAR(next.time, 1, 1e-6);

    EXPECT_TRUE(next.rotation.isApprox(Eigen::Quaterniond(0,0,0,0), 1e-6));
}

TEST_F(DerivatorTest, zeroInitWithAcceleration)
{
    State initial = zeroState();
    BurstControlInput input(1.0,{0.0, 0.0, 0.0}, 0.0, 0.0);
    std::shared_ptr<MockPhysicsSimulator> simulator = std::make_shared<MockPhysicsSimulator>();
    TotalAcceleration acceleration({0.0,1.0,0.0}, {0.0,0.0,1.0});
    EXPECT_CALL(*(simulator.get()), computeAcceleration(testing::_, testing::_))
            .WillOnce(testing::Return(acceleration));
    derivator->setPhysicsSimulator(simulator);
    State next = derivator->derive(initial,input);

    EXPECT_NEAR(next.translation[0], 0.0, 1e-6);
    EXPECT_NEAR(next.translation[1], 0.0, 1e-6);
    EXPECT_NEAR(next.translation[2], 0.0, 1e-6);
    EXPECT_NEAR(next.velocity[0], 0.0, 1e-6);
    EXPECT_NEAR(next.velocity[1], 1.0, 1e-6);
    EXPECT_NEAR(next.velocity[2], 0.0, 1e-6);

    EXPECT_NEAR(next.angularVelocity[0], 0.0, 1e-6);
    EXPECT_NEAR(next.angularVelocity[1], 0.0, 1e-6);
    EXPECT_NEAR(next.angularVelocity[2], 1.0, 1e-6);

    EXPECT_NEAR(next.time, 1, 1e-6);

    EXPECT_TRUE(next.rotation.isApprox(Eigen::Quaterniond(0,0,0,0), 1e-6));
}

TEST_F(DerivatorTest, nonZeroInitZeroAcceleration)
{
    State initial({0.0,0.0,0.0},Eigen::Quaterniond::Identity(), 5.0, {1.0, 0.0,0.0}, {0.0,1.0,0.0});
    BurstControlInput zeroInput(0.0,{0.0, 0.0, 0.0}, 0.0, 0.0);
    std::shared_ptr<MockPhysicsSimulator> simulator = std::make_shared<MockPhysicsSimulator>();
    TotalAcceleration acceleration({0.0,0.0,0.0}, {0.0,0.0,0.0});
    EXPECT_CALL(*(simulator.get()), computeAcceleration(testing::_, testing::_))
            .WillOnce(testing::Return(acceleration));
    derivator->setPhysicsSimulator(simulator);
    State next = derivator->derive(initial,zeroInput);


    EXPECT_NEAR(next.translation[0], 1.0, 1e-6);
    EXPECT_NEAR(next.translation[1], 0.0, 1e-6);
    EXPECT_NEAR(next.translation[2], 0.0, 1e-6);
    EXPECT_NEAR(next.velocity[0], 0.0, 1e-6);
    EXPECT_NEAR(next.velocity[1], 0.0, 1e-6);
    EXPECT_NEAR(next.velocity[2], 0.0, 1e-6);

    EXPECT_NEAR(next.angularVelocity[0], 0.0, 1e-6);
    EXPECT_NEAR(next.angularVelocity[1], 0.0, 1e-6);
    EXPECT_NEAR(next.angularVelocity[2], 0.0, 1e-6);

    EXPECT_NEAR(next.time, 1, 1e-6);

    EXPECT_TRUE(next.rotation.isApprox(Eigen::Quaterniond(0,0,0.5,0), 1e-6));
}

TEST_F(DerivatorTest, nonZero)
{
    State initial({1.0,0.0,0.0},Eigen::Quaterniond::Identity(), 5.0, {1.0, 0.0,0.0}, {0.0,1.0,0.0});
    BurstControlInput input(1.0,{0.0, 0.0, 1.0}, 3.0, 4.0);
    std::shared_ptr<MockPhysicsSimulator> simulator = std::make_shared<MockPhysicsSimulator>();
    TotalAcceleration acceleration({0.0,1.0,0.0}, {0.0,0.0,1.0});
    EXPECT_CALL(*(simulator.get()), computeAcceleration(testing::_, testing::_))
            .WillOnce(testing::Return(acceleration));
    derivator->setPhysicsSimulator(simulator);
    State next = derivator->derive(initial,input);


    EXPECT_NEAR(next.translation[0], 1.0, 1e-6);
    EXPECT_NEAR(next.translation[1], 0.0, 1e-6);
    EXPECT_NEAR(next.translation[2], 0.0, 1e-6);
    EXPECT_NEAR(next.velocity[0], 0.0, 1e-6);
    EXPECT_NEAR(next.velocity[1], 1.0, 1e-6);
    EXPECT_NEAR(next.velocity[2], 0.0, 1e-6);

    EXPECT_NEAR(next.angularVelocity[0], 0.0, 1e-6);
    EXPECT_NEAR(next.angularVelocity[1], 0.0, 1e-6);
    EXPECT_NEAR(next.angularVelocity[2], 1.0, 1e-6);

    EXPECT_NEAR(next.time, 1, 1e-6);

    EXPECT_TRUE(next.rotation.isApprox(Eigen::Quaterniond(0,0,0.5,0), 1e-6));
}