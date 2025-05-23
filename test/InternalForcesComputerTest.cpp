#include <gtest/gtest.h>
#include "components/physics/internalForcesComputer/InternalForcesComputer.h"
#include "components/physics/internalForcesComputer/KinodynamicInternalForcesComputer.h"
#include "dto/poses/dynamic/kinodynamic/state/State.h"
#include "dto/poses/dynamic/kinodynamic/burstControlInput/BurstControlInput.h"

TEST(InternalForcesComputerTest, test1)
{
    KinodynamicInternalForcesComputer computer;

    Eigen::Quaterniond rot(1.0, 0.0, 0.0, 0.0);
    State s;
    s.rotation = rot;

    double thrust = 10.0;
    std::array<double, 3> torque = {1.0, 2.0, 3.0};
    BurstControlInput input(thrust, torque, 0.0, 0.0);

    TotalForce result = computer.computeTotalForce(s, input);

    EXPECT_NEAR(result.getForce()[0], 0.0, 1e-6);
    EXPECT_NEAR(result.getForce()[1], thrust, 1e-6);
    EXPECT_NEAR(result.getForce()[2], 0.0, 1e-6);

    EXPECT_NEAR(result.getTorque()[0], torque[0], 1e-6);
    EXPECT_NEAR(result.getTorque()[1], torque[1], 1e-6);
    EXPECT_NEAR(result.getTorque()[2], torque[2], 1e-6);
}

TEST(InternalForcesComputerTest, test2)
{
    KinodynamicInternalForcesComputer computer;

    double angleRad = M_PI / 2.0;
    Eigen::AngleAxisd rotation(angleRad, Eigen::Vector3d::UnitX());
    Eigen::Quaterniond q_rotation(rotation);
    State s;
    s.rotation = q_rotation;
    double thrust = 10.0;
    std::array<double, 3> torque = {1.0, 2.0, 3.0};
    BurstControlInput input(thrust, torque, 0.0, 0.0);

    TotalForce result = computer.computeTotalForce(s, input);

    EXPECT_NEAR(result.getForce()[0], 0.0, 1e-6);
    EXPECT_NEAR(result.getForce()[1], 0.0, 1e-6);
    EXPECT_NEAR(result.getForce()[2], thrust, 1e-6);

    EXPECT_NEAR(result.getTorque()[0], torque[0], 1e-6);
    EXPECT_NEAR(result.getTorque()[1], torque[1], 1e-6);
    EXPECT_NEAR(result.getTorque()[2], torque[2], 1e-6);
}

TEST(InternalForcesComputerTest, test3)
{
    KinodynamicInternalForcesComputer computer;

    double angleRad = M_PI / 4.0;
    Eigen::AngleAxisd rotation(angleRad, Eigen::Vector3d::UnitX());
    Eigen::Quaterniond q_rotation(rotation);
    State s;
    s.rotation = q_rotation;
    double thrust = 10.0;
    std::array<double, 3> torque = {1.0, 2.0, 3.0};
    BurstControlInput input(thrust, torque, 0.0, 0.0);

    TotalForce result = computer.computeTotalForce(s, input);

    EXPECT_NEAR(result.getForce()[0], 0.0, 1e-6);
    EXPECT_NEAR(result.getForce()[1], thrust/std::sqrt(2), 1e-6);
    EXPECT_NEAR(result.getForce()[2], thrust/std::sqrt(2), 1e-6);

    EXPECT_NEAR(result.getTorque()[0], torque[0], 1e-6);
    EXPECT_NEAR(result.getTorque()[1], torque[1], 1e-6);
    EXPECT_NEAR(result.getTorque()[2], torque[2], 1e-6);
}