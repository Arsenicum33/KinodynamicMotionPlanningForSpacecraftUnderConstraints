//
// Created by arseniy on 7.3.25.
//
#include "CapabilityManager.h"

#include <spdlog/spdlog.h>

#include "components/ComponentType.h"
#include "dto/envSettings/EnvSettingsAstro.h"

std::shared_ptr<CapabilityManager> CapabilityManager::instance = nullptr;

const CapabilitySet &CapabilityManager::getRequiredCapabilities() const
{
    return capabilities;
}

void CapabilityManager::build(const ReaderContext &context)
{
    if (instance)
    {
        spdlog::warn("CapabilityManager::build(): instance already exists");
        return;
    }
    instance = std::shared_ptr<CapabilityManager>(new CapabilityManager());
    instance->deduceCapabilities(context);
}

std::shared_ptr<CapabilityManager> CapabilityManager::getInstance()
{
    if (!instance)
    {
        spdlog::error("CapabilityManager::getInstance(): instance is null. You must call build() before getInstance()");
        throw std::runtime_error("CapabilityManager::getInstance(): instance is null");
    }
    return instance;
}

void CapabilityManager::reset()
{
    instance.reset();
}

void CapabilityManager::deduceCapabilities(const ReaderContext &context)
{
    if (std::dynamic_pointer_cast<EnvSettingsAstro>(context.envSettings) != nullptr)
    {
        capabilities.insert(Capability::AstrodynamicEnv);
        spdlog::info("Deduced capability requirements: {}", capabilitySetToString(capabilities));
        return;
    }
    if (checkDynamicsSimulatorComponent(context.componentConfigs))
    {
        capabilities.insert(Capability::KinodynamicEnv);
        spdlog::info("Deduced capability requirements: {}", capabilitySetToString(capabilities));
        return;
    }
    if (context.envSettings->dynamicObjects.empty())
        capabilities.insert(Capability::StaticEnv);
    else
        capabilities.insert(Capability::DynamicEnv);
    try
    {
        std::any_cast<std::shared_ptr<DynamicObject<RAPID_model>>>(context.envSettings->target);
        capabilities.insert(Capability::MovingTarget);
    }
    catch (std::bad_any_cast e) {}

    spdlog::info("Deduced capability requirements: {}", capabilitySetToString(capabilities));
}

bool CapabilityManager::checkDynamicsSimulatorComponent(const std::vector<ComponentConfig> &components)
{
    for (auto componentConfig : components)
    {
        if (componentConfig.name == componentTypeToString(ComponentType::DynamicsSimulator))
            return true;
    }
    return false;
}
