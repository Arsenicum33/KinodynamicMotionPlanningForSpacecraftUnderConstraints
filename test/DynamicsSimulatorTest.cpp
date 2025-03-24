#include <gtest/gtest.h>
#include "components/dynamicsSimulators/DynamicsSimulator.h"
#include "dto/poses/dynamic/kinodynamic/state/State.h"
#include "dto/poses/dynamic/kinodynamic/controlInput/ControlInput.h"
#include "dto/poses/static/poseMath/PoseMath.h"
#include <Eigen/Geometry>
#include <array>

// Test fixture for DynamicsSimulator
class DynamicsSimulatorTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Initialize simulator with a 0.1s timestep
        simulator = std::make_unique<DynamicsSimulator>(0.1);
    }

    // Helper to create a zero-initialized state
    State zeroState() {
        return State(
            {0.0, 0.0, 0.0},           // translation
            Eigen::Quaterniond::Identity(), // rotation
            0.0,                       // time
            {0.0, 0.0, 0.0},          // velocity
            {0.0, 0.0, 0.0}           // angular velocity
        );
    }

    std::unique_ptr<DynamicsSimulator> simulator;
};

// Test 1: Zero control input, zero initial velocity
TEST_F(DynamicsSimulatorTest, ZeroControlInputZeroVelocity) {
    State initial = zeroState();
    ControlInput control(0.0, {0.0, 0.0, 0.0}); // No acceleration

    State next = simulator->computeNextState(initial, control);

    // Expect no change in translation or velocity
    EXPECT_NEAR(next.translation[0], 0.0, 1e-6);
    EXPECT_NEAR(next.translation[1], 0.0, 1e-6);
    EXPECT_NEAR(next.translation[2], 0.0, 1e-6);
    EXPECT_NEAR(next.velocity[0], 0.0, 1e-6);
    EXPECT_NEAR(next.velocity[1], 0.0, 1e-6);
    EXPECT_NEAR(next.velocity[2], 0.0, 1e-6);
    // Angular velocity unchanged
    EXPECT_NEAR(next.angularVelocity[0], 0.0, 1e-6);
    EXPECT_NEAR(next.angularVelocity[1], 0.0, 1e-6);
    EXPECT_NEAR(next.angularVelocity[2], 0.0, 1e-6);
    // Time advances by timestep
    EXPECT_NEAR(next.time, 0.1, 1e-6);
    // Rotation unchanged
    Eigen::Quaterniond rot = PoseMath::rotationMatrixToQuaternion(next.rotation);
    EXPECT_TRUE(rot.isApprox(Eigen::Quaterniond::Identity(), 1e-6));
}

// Test 2: Zero control input, non-zero initial velocity
TEST_F(DynamicsSimulatorTest, ZeroControlInputWithVelocity) {
    State initial(
        {0.0, 0.0, 0.0},
        Eigen::Quaterniond::Identity(),
        0.0,
        {1.0, 2.0, 0.0}, // Initial velocity
        {0.0, 0.0, 0.0}
    );
    ControlInput control(0.0, {0.0, 0.0, 0.0});

    State next = simulator->computeNextState(initial, control);

    // Translation: x = x0 + v0*t
    EXPECT_NEAR(next.translation[0], 0.1, 1e-6); // 1.0 * 0.1
    EXPECT_NEAR(next.translation[1], 0.2, 1e-6); // 2.0 * 0.1
    EXPECT_NEAR(next.translation[2], 0.0, 1e-6);
    // Velocity unchanged
    EXPECT_NEAR(next.velocity[0], 1.0, 1e-6);
    EXPECT_NEAR(next.velocity[1], 2.0, 1e-6);
    EXPECT_NEAR(next.velocity[2], 0.0, 1e-6);
    // Time advances
    EXPECT_NEAR(next.time, 0.1, 1e-6);
}

// Test 3: Linear acceleration only
TEST_F(DynamicsSimulatorTest, LinearAcceleration) {
    State initial = zeroState();
    ControlInput control(2.0, {0.0, 0.0, 0.0}); // 2 m/s^2 forward

    State next = simulator->computeNextState(initial, control);

    // Direction vector from identity rotation: [0, 1, 0] (y-axis, based on rotation[1])
    // Acceleration vector: [0, 2, 0]
    // Translation: x = 0.5*a*t^2
    EXPECT_NEAR(next.translation[0], 0.0, 1e-6);
    EXPECT_NEAR(next.translation[1], 0.01, 1e-6); // 0.5 * 2 * 0.1^2
    EXPECT_NEAR(next.translation[2], 0.0, 1e-6);
    // Velocity: v = a*t
    EXPECT_NEAR(next.velocity[0], 0.0, 1e-6);
    EXPECT_NEAR(next.velocity[1], 0.2, 1e-6); // 2 * 0.1
    EXPECT_NEAR(next.velocity[2], 0.0, 1e-6);
    // Angular velocity unchanged
    EXPECT_NEAR(next.angularVelocity[0], 0.0, 1e-6);
    EXPECT_NEAR(next.angularVelocity[1], 0.0, 1e-6);
    EXPECT_NEAR(next.angularVelocity[2], 0.0, 1e-6);
    // Time advances
    EXPECT_NEAR(next.time, 0.1, 1e-6);
}

// Test 4: Angular acceleration only
TEST_F(DynamicsSimulatorTest, AngularAcceleration) {
    State initial = zeroState();
    ControlInput control(0.0, {0.0, 0.0, 1.0}); // 1 rad/s^2 around z

    State next = simulator->computeNextState(initial, control);

    // Translation and velocity unchanged
    EXPECT_NEAR(next.translation[0], 0.0, 1e-6);
    EXPECT_NEAR(next.translation[1], 0.0, 1e-6);
    EXPECT_NEAR(next.translation[2], 0.0, 1e-6);
    EXPECT_NEAR(next.velocity[0], 0.0, 1e-6);
    EXPECT_NEAR(next.velocity[1], 0.0, 1e-6);
    EXPECT_NEAR(next.velocity[2], 0.0, 1e-6);
    // Angular velocity: ω = ω0 + α*t
    EXPECT_NEAR(next.angularVelocity[0], 0.0, 1e-6);
    EXPECT_NEAR(next.angularVelocity[1], 0.0, 1e-6);
    EXPECT_NEAR(next.angularVelocity[2], 0.1, 1e-6); // 1 * 0.1
    // Time advances
    EXPECT_NEAR(next.time, 0.1, 1e-6);
    // Rotation: small change via quaternion integration
    Eigen::Quaterniond rot = PoseMath::rotationMatrixToQuaternion(next.rotation);
    // Approximate rotation: θ = 0.5 * ω * t = 0.5 * 0.1 * 0.1 = 0.005 rad around z
    Eigen::Quaterniond expected(Eigen::AngleAxisd(0.005, Eigen::Vector3d::UnitZ()));
    EXPECT_TRUE(rot.isApprox(expected, 1e-3));
}

// Test 5: Combined linear and angular acceleration
TEST_F(DynamicsSimulatorTest, CombinedAcceleration) {
    State initial = zeroState();
    ControlInput control(1.0, {0.0, 1.0, 0.0}); // 1 m/s^2 forward, 1 rad/s^2 around y

    State next = simulator->computeNextState(initial, control);

    // Linear: a = [0, 1, 0]
    EXPECT_NEAR(next.translation[0], 0.0, 1e-6);
    EXPECT_NEAR(next.translation[1], 0.005, 1e-6); // 0.5 * 1 * 0.1^2
    EXPECT_NEAR(next.translation[2], 0.0, 1e-6);
    EXPECT_NEAR(next.velocity[0], 0.0, 1e-6);
    EXPECT_NEAR(next.velocity[1], 0.1, 1e-6); // 1 * 0.1
    EXPECT_NEAR(next.velocity[2], 0.0, 1e-6);
    // Angular: ω = [0, 0.1, 0]
    EXPECT_NEAR(next.angularVelocity[0], 0.0, 1e-6);
    EXPECT_NEAR(next.angularVelocity[1], 0.1, 1e-6); // 1 * 0.1
    EXPECT_NEAR(next.angularVelocity[2], 0.0, 1e-6);
    // Time
    EXPECT_NEAR(next.time, 0.1, 1e-6);
    // Rotation: θ = 0.5 * 0.1 * 0.1 = 0.005 rad around y
    Eigen::Quaterniond rot = PoseMath::rotationMatrixToQuaternion(next.rotation);
    Eigen::Quaterniond expected(Eigen::AngleAxisd(0.005, Eigen::Vector3d::UnitY()));
    EXPECT_TRUE(rot.isApprox(expected, 1e-3));
}