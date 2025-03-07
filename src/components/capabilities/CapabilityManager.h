//
// Created by arseniy on 7.3.25.
//

#ifndef CAPABILITYMANAGER_H
#define CAPABILITYMANAGER_H
#include "Capability.h"
#include "core/reader/IReader.h"

class CapabilityManager
{
public:
    const CapabilitySet& getRequiredCapabilities() const;
    static void build(const ReaderContext& context);
    static std::shared_ptr<CapabilityManager> getInstance();
    static void reset();
private:
    void deduceCapabilities(const ReaderContext& context);
    CapabilityManager(const CapabilityManager& capabilityManager) = delete;
    CapabilityManager& operator=(const CapabilityManager& capabilityManager) = delete;
    CapabilityManager() = default;

    friend std::shared_ptr<CapabilityManager> std::make_shared<CapabilityManager>();
    static std::shared_ptr<CapabilityManager> instance;

    CapabilitySet capabilities;
};



#endif //CAPABILITYMANAGER_H
