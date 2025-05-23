#include <components/distanceMeasurement/IDistanceMetric.h>
#include <dto/poses/dynamic/kinodynamic/state/State.h>
#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "components/physics/interactions/GravityInteraction.h"
#include "dto/poses/astrodynamic/celestialBody/CelestialBody.h"
#include "dto/spaceshipModel/SpaceshipModel.h"

#define UNIT_TESTING

using ::testing::Return;
using ::testing::_;


class MockDistanceMetric : public IDistanceMetric {
public:
    MOCK_METHOD(double, getSpatialDistance, (const Pose& pose1, const Pose& pose2), (override));
};


class MockCelestialBody : public CelestialBody {
public:
    MOCK_METHOD(double, getMass, (), (const));
    MOCK_METHOD(Animation, getAnimation, (), (const));
};

class AnimationUtilsWrapper {
public:
    virtual ~AnimationUtilsWrapper() = default;
    virtual Keyframe extractKeyframeAtTime(const Animation& animation, double time) const = 0;
};

class MockAnimationUtilsWrapper : public AnimationUtilsWrapper {
public:
    MOCK_METHOD(Keyframe, extractKeyframeAtTime, (const Animation& animation, double time), (const, override));
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
    std::vector<CelestialBody> celestialBodies;
    double dryMass = 1000;

    std::shared_ptr<SpaceshipModel> spaceshipModel = std::make_shared<SpaceshipModel>();
    std::shared_ptr<IDistanceMetric> distanceMetric;

    auto interaction = std::make_unique<GravityInteraction<State>>(celestialBodies, spaceshipModel, distanceMetric);
    State state(Keyframe(std::array<double,3>{1.0, 0.0, 0.0}, 0.0), std::array<double,3>{0.0, 0.0, 0.0},
        std::array<double,3>{0.0, 0.0, 0.0});


    TotalForce totalForce = interaction->computeTotalForce(state);

   // double expectedForceMagnitude = G * spaceshipMass * bodyMass / (distance * distance);
    std::array<double, 3> expectedForce = {expectedForceMagnitude, 0, 0};
    for (int i = 0; i < 3; ++i) {
        EXPECT_NEAR(totalForce.force[i], expectedForce[i], 1e-10 * expectedForceMagnitude);
    }
    EXPECT_EQ(totalForce.getTorque()[0], 0);
    EXPECT_EQ(totalForce.getTorque()[1], 0);
    EXPECT_EQ(totalForce.getTorque()[2], 0);
}
