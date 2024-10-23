//
// Created by arseniy on 22.10.24.
//

#ifndef CONFIGURATIONBOUNDARIES_H
#define CONFIGURATIONBOUNDARIES_H
#include <numbers>
#include <jsoncpp/json/value.h>
#include <jsoncpp/json/json.h>

class ConfigurationSpaceBoundaries
{
public:
    double xMin, xMax, yMin, yMax, zMin, zMax;
    double yaw_min = -std::numbers::pi, yaw_max = std::numbers::pi, pitch_min = -std::numbers::pi/2, pitch_max = std::numbers::pi/2,
    roll_min = -std::numbers::pi, roll_max = std::numbers::pi;

    static ConfigurationSpaceBoundaries fromJson(const Json::Value& json);
private:
    ConfigurationSpaceBoundaries(double xMin, double xMax, double yMin, double yMax, double zMin, double zMax,
        double yaw_min = -std::numbers::pi, double yaw_max = std::numbers::pi, double pitch_min = -std::numbers::pi/2, double pitch_max = std::numbers::pi/2,
        double roll_min = -std::numbers::pi, double roll_max = std::numbers::pi);

};



#endif //CONFIGURATIONBOUNDARIES_H
