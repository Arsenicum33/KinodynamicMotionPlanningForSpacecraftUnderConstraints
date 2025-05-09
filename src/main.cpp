#include <filesystem>
#include "core/Program.h"
#include "core/creator/ComponentManager.h"
#include "core/creator/IComponentManager.h"
#include "core/executor/Executor.h"
#include "core/exporter/HighLevelExporter.h"
#include "core/reader/Reader.h"
#include "core/reader/readerFactory/DefaultReaderFactory.h"
#include "core/reader/readerFactory/IReaderFactory.h"
#include "core/validator/Validator.h"
#include "components/registration/ComponentRegistration.h"
#include <csignal>
#include <spdlog/spdlog.h>

#include "core/exporter/HighLevelExporterTesting.h"

void setupLogging(int runId = -1)
{
    std::string name = "logger";
    if (runId >= 0)
        name = "logger" + std::to_string(runId);

    auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
    auto file_sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>("spdlog.txt", false);
    auto logger = std::make_shared<spdlog::logger>(name, spdlog::sinks_init_list{console_sink, file_sink});
    logger->set_level(spdlog::level::debug);
    spdlog::set_default_logger(logger);
    spdlog::flush_on(spdlog::level::err);
}

void signalHandler(int signal) {
    spdlog::error("Received signal: {}", signal);
    spdlog::get("multiLogger")->flush();
    std::exit(signal);
}

void setupSignalHandling() {
    std::signal(SIGSEGV, signalHandler);  // Segmentation fault
    std::signal(SIGABRT, signalHandler);  // Abort
    std::signal(SIGFPE, signalHandler);   // Floating-point exception
    std::signal(SIGINT, signalHandler);   // Interrupt (Ctrl+C)
}

int main(int argc, char* argv[])
{
    if (argc == 4)
    {
        setupLogging(std::stoi(argv[3]));
    }
    else
    {
        setupLogging();
    }

    setupSignalHandling();
    std::unique_ptr<IReaderFactory> readerFactory = std::make_unique<DefaultReaderFactory>();
    std::unique_ptr<IReader> reader = readerFactory->createReader(argc, argv);
    std::unique_ptr<IComponentManager> componentManager = std::make_unique<ComponentManager>();
    std::unique_ptr<IExecutor> executor = std::make_unique<Executor>();
    std::unique_ptr<IValidator> validator = std::make_unique<Validator>();
    std::unique_ptr<IHighLevelExporter> exporter;
    if (argc != 4)
    {
        exporter = std::make_unique<HighLevelExporter>();
    }
    else
    {
        exporter = std::make_unique<HighLevelExporterTesting>(argv[2]);
    }

    Program program((std::move(reader)),
                    (std::move(componentManager)),
                    (std::move(executor)),
                    (std::move(validator)),
                    (std::move(exporter)));

    program.run();
    return 0;
}

