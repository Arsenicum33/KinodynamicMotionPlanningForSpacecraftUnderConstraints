#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "components/derivator/kinodynamic/KinodynamicDerivator.h"
#include "components/dynamicsSimulators/astrodynamic/RK4_AstrodynamicSimulator.h"
#include "components/dynamicsSimulators/kinodynamic/RK4_KinodynamicSimulator.h"
#include "dto/poses/dynamic/kinodynamic/state/State.h"
#include "dto/poses/static/poseMath/PoseMath.h"

class DynamicsSimulatorTest : public ::testing::Test
{
protected:
    void SetUp() override
    {
        simulator = std::make_unique<RK4_KinodynamicSimulator>();
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

    State zeroStateTime1()
    {
        return State(
            {0.0, 0.0, 0.0},
            Eigen::Quaterniond::Identity(),
            1.0,
            {0.0, 0.0, 0.0},
            {0.0, 0.0, 0.0}
        );
    }

    std::unique_ptr<RK4_KinodynamicSimulator> simulator;
};

class MockDerivator : public IDerivator<State> {
public:
    CapabilitySet getCapabilities() const override { return CapabilitySet(); };

    MOCK_METHOD(State, derive,
                (const State& state, const BurstControlInput& input),
                (override));
};

TEST_F(DynamicsSimulatorTest, zero)
{
    State initial = zeroState();
    auto derivator = std::make_shared<MockDerivator>();
    BurstControlInput zeroInput(0.0,{0.0, 0.0, 0.0}, 0.0, 0.0);
    simulator->setDerivator(derivator);
    State derivedState = zeroStateTime1();
    double timestep = 1;
    EXPECT_CALL(*(derivator.get()), derive(testing::_, testing::_))
        .WillRepeatedly(testing::Return(derivedState));

    State next = simulator->integrate(initial, zeroInput, timestep);

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

    EXPECT_TRUE(next.rotation.isApprox(Eigen::Quaterniond(1,0,0,0), 1e-6));

}

TEST_F(DynamicsSimulatorTest, velocity)
{
    State initial({0.0,0.0,0.0},Eigen::Quaterniond::Identity(), 0.0, {1.0, 0.0,0.0}, {0.0,1.0,0.0});
    auto derivator = std::make_shared<MockDerivator>();
    BurstControlInput zeroInput(0.0,{0.0, 0.0, 0.0}, 0.0, 0.0);
    simulator->setDerivator(derivator);
    State k1({0.0,0.0,0.0},Eigen::Quaterniond::Identity(), 1.0, {0.0, 1.0,0.0}, {0.0,1.0,0.0});
    State k2({0.0,0.0,0.0},Eigen::Quaterniond::Identity(), 1.0, {0.0, 2.0,0.0}, {0.0,1.0,0.0});
    State k3({0.0,0.0,0.0},Eigen::Quaterniond::Identity(), 1.0, {0.0, 3.0,0.0}, {0.0,1.0,0.0});
    State k4({0.0,0.0,0.0},Eigen::Quaterniond::Identity(), 1.0, {0.0, 7.0,0.0}, {0.0,1.0,0.0});
    double timestep = 1;
    EXPECT_CALL(*derivator, derive(testing::_, testing::_))
        .WillOnce(testing::Return(k1))
        .WillOnce(testing::Return(k2))
        .WillOnce(testing::Return(k3))
        .WillOnce(testing::Return(k4));

    State next = simulator->integrate(initial, zeroInput, timestep);

    EXPECT_NEAR(next.translation[0], 0.0, 1e-6);
    EXPECT_NEAR(next.translation[1], 0.0, 1e-6);
    EXPECT_NEAR(next.translation[2], 0.0, 1e-6);
    EXPECT_NEAR(next.velocity[0], 1.0, 1e-6);
    EXPECT_NEAR(next.velocity[1], 3.0, 1e-6);
    EXPECT_NEAR(next.velocity[2], 0.0, 1e-6);

    EXPECT_NEAR(next.angularVelocity[0], 0.0, 1e-6);
    EXPECT_NEAR(next.angularVelocity[1],2.0, 1e-6);
    EXPECT_NEAR(next.angularVelocity[2], 0.0, 1e-6);

    EXPECT_NEAR(next.time, 1, 1e-6);

    EXPECT_TRUE(next.rotation.isApprox(Eigen::Quaterniond(1,0,0,0), 1e-6));

}

TEST_F(DynamicsSimulatorTest, total)
{
    State initial({1.0,1.0,1.0},Eigen::Quaterniond::Identity(), 5.0, {1.0, 2.0, 3.0}, {0.0,1.0,0.0});
    auto derivator = std::make_shared<MockDerivator>();
    BurstControlInput zeroInput(0.0,{0.0, 0.0, 0.0}, 0.0, 0.0);
    simulator->setDerivator(derivator);
    State k1({1.0,2.0,3.0},Eigen::Quaterniond::Identity(), 1.0, {0.0, 1.0,0.0}, {0.0,1.0,1.0});
    State k2({1.0,2.0,3.0},Eigen::Quaterniond::Identity(), 1.0, {0.0, 2.0,0.0}, {0.0,1.0,0.0});
    State k3({1.0,2.0,3.0},Eigen::Quaterniond::Identity(), 1.0, {0.0, 3.0,0.0}, {0.0,1.0,1.0});
    State k4({1.0,2.0,3.0},Eigen::Quaterniond::Identity(), 1.0, {0.0, 7.0,0.0}, {0.0,1.0,0.0});
    double timestep = 1;
    EXPECT_CALL(*derivator, derive(testing::_, testing::_))
        .WillOnce(testing::Return(k1))
        .WillOnce(testing::Return(k2))
        .WillOnce(testing::Return(k3))
        .WillOnce(testing::Return(k4));

    State next = simulator->integrate(initial, zeroInput, timestep);

    EXPECT_NEAR(next.translation[0], 2.0, 1e-6);
    EXPECT_NEAR(next.translation[1], 3.0, 1e-6);
    EXPECT_NEAR(next.translation[2], 4.0, 1e-6);
    EXPECT_NEAR(next.velocity[0], 1.0, 1e-6);
    EXPECT_NEAR(next.velocity[1], 5.0, 1e-6);
    EXPECT_NEAR(next.velocity[2], 3.0, 1e-6);

    EXPECT_NEAR(next.angularVelocity[0], 0.0, 1e-6);
    EXPECT_NEAR(next.angularVelocity[1],2.0, 1e-6);
    EXPECT_NEAR(next.angularVelocity[2], 0.5, 1e-6);

    EXPECT_NEAR(next.time, 6, 1e-6);

    EXPECT_TRUE(next.rotation.isApprox(Eigen::Quaterniond(1,0,0,0), 1e-6));

}