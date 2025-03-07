//
// Created by arseniy on 23.10.24.
//

#ifndef ABSTRACTSOLVERCONFIG_H
#define ABSTRACTSOLVERCONFIG_H
#include <jsoncpp/json/value.h>
#include <jsoncpp/json/json.h>
#include <stdexcept>

class ASolverConfig
{
public:
    double rotationScalingFactor;
    static ASolverConfig fromJson(const Json::Value &json);
protected:
    ASolverConfig(double rotationScalingFactor): rotationScalingFactor(rotationScalingFactor) {}
};



#endif //ABSTRACTSOLVERCONFIG_H
