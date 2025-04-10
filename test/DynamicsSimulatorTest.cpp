#include <gtest/gtest.h>
#include "components/dynamicsSimulators/DynamicsSimulator.h"
#include "dto/poses/dynamic/kinodynamic/state/State.h"
#include "dto/poses/static/poseMath/PoseMath.h"
// Test fixture for DynamicsSimulator
class DynamicsSimulatorTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Initialize simulator with a 0.1s timestep
        simulator = std::make_unique<DynamicsSimulator>();
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
    ForcesProfile<ControlInput> accelerationProfile;
    double duration = 0.1;
    accelerationProfile.addSegment(duration, std::make_unique<ControlInput>(control));

    State next = simulator->computeNextState(initial, accelerationProfile);

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
    ForcesProfile<ControlInput> accelerationProfile;
    double duration = 0.1;
    accelerationProfile.addSegment(duration, std::make_unique<ControlInput>(control));

    State next = simulator->computeNextState(initial, accelerationProfile);

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

TEST_F(DynamicsSimulatorTest, ZeroControlInputWithAngularVelocity) {
    // Set up initial state with angular velocity around y-axis
    State initial(
        {0.0, 0.0, 0.0},                    // Translation
        Eigen::Quaterniond::Identity(),      // Identity rotation
        0.0,                                 // Time
        {0.0, 0.0, 0.0},                    // Linear velocity
        {0.0, 1.0, 0.0}                     // Angular velocity (1 rad/s around y-axis)
    );

    // Zero control input (no acceleration)
    ControlInput control(0.0, {0.0, 0.0, 0.0});
    ForcesProfile<ControlInput> accelerationProfile;
    double duration = 0.1;
    accelerationProfile.addSegment(duration, std::make_unique<ControlInput>(control));
    // Compute next state
    State next = simulator->computeNextState(initial, accelerationProfile);

    // Check translation (should not change)
    EXPECT_NEAR(next.translation[0], 0.0, 1e-6);
    EXPECT_NEAR(next.translation[1], 0.0, 1e-6);
    EXPECT_NEAR(next.translation[2], 0.0, 1e-6);

    // Check linear velocity (should not change)
    EXPECT_NEAR(next.velocity[0], 0.0, 1e-6);
    EXPECT_NEAR(next.velocity[1], 0.0, 1e-6);
    EXPECT_NEAR(next.velocity[2], 0.0, 1e-6);

    // Check angular velocity (should not change, no angular acceleration)
    EXPECT_NEAR(next.angularVelocity[0], 0.0, 1e-6);
    EXPECT_NEAR(next.angularVelocity[1], 1.0, 1e-6);
    EXPECT_NEAR(next.angularVelocity[2], 0.0, 1e-6);

    // Check time (should increase by timestep)
    EXPECT_NEAR(next.time, 0.1, 1e-6);

    // Check rotation
    // Expected rotation: angular velocity of 1 rad/s around y-axis for 0.1 seconds
    // Angle = 1 * 0.1 = 0.1 radians
    // Quaternion: (cos(angle/2), 0, sin(angle/2), 0)
    double angle = 1.0 * 0.1;  // 0.1 radians
    double expectedW = std::cos(angle / 2.0);  // cos(0.05) ≈ 0.99875
    double expectedY = std::sin(angle / 2.0);  // sin(0.05) ≈ 0.04999
    Eigen::Quaterniond expectedRotation(expectedW, 0.0, expectedY, 0.0);
    expectedRotation.normalize();
    Eigen::Quaterniond qrot = PoseMath::rotationMatrixToQuaternion(next.rotation);
    // Compare quaternions
    EXPECT_NEAR(qrot.w(), expectedRotation.w(), 1e-6);
    EXPECT_NEAR(qrot.x(), expectedRotation.x(), 1e-6);
    EXPECT_NEAR(qrot.y(), expectedRotation.y(), 1e-6);
    EXPECT_NEAR(qrot.z(), expectedRotation.z(), 1e-6);
}

// Test 3: Linear acceleration only
TEST_F(DynamicsSimulatorTest, LinearAcceleration) {
    State initial = zeroState();
    ControlInput control(2.0, {0.0, 0.0, 0.0}); // 2 m/s^2 forward
    ForcesProfile<ControlInput> accelerationProfile;
    double duration = 0.1;
    accelerationProfile.addSegment(duration, std::make_unique<ControlInput>(control));
    State next = simulator->computeNextState(initial, accelerationProfile);

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

TEST_F(DynamicsSimulatorTest, LinearAccelerationWithVelocity) {
    State initial = zeroState();
    initial.velocity = {1.0, 0.0, 0.0}; // 1 m/s to the side
    ControlInput control(2.0, {0.0, 0.0, 0.0}); // 2 m/s^2 forward
    ForcesProfile<ControlInput> accelerationProfile;
    double duration = 0.1;
    accelerationProfile.addSegment(duration, std::make_unique<ControlInput>(control));
    State next = simulator->computeNextState(initial, accelerationProfile);

    // Direction vector from identity rotation: [0, 1, 0] (y-axis, based on rotation[1])
    // Acceleration vector: [0, 2, 0]
    // Translation: x = 0.5*a*t^2
    EXPECT_NEAR(next.translation[0], 0.1, 1e-6);
    EXPECT_NEAR(next.translation[1], 0.01, 1e-6); // 0.5 * 2 * 0.1^2
    EXPECT_NEAR(next.translation[2], 0.0, 1e-6);
    // Velocity: v = a*t
    EXPECT_NEAR(next.velocity[0], 1.0, 1e-6);
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
    ForcesProfile<ControlInput> accelerationProfile;
    double duration = 0.1;
    accelerationProfile.addSegment(duration, std::make_unique<ControlInput>(control));
    State next = simulator->computeNextState(initial, accelerationProfile);

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
    ForcesProfile<ControlInput> accelerationProfile;
    double duration = 0.1;
    accelerationProfile.addSegment(duration, std::make_unique<ControlInput>(control));
    State next = simulator->computeNextState(initial, accelerationProfile);

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