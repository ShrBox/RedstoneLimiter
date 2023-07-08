/**
 * @file plugin.cpp
 * @brief The main file of the plugin
 */

#include <llapi/LoggerAPI.h>

#include "version.h"
#include <llapi/mc/BlockSource.hpp>
#include <llapi/mc/CircuitSystem.hpp>
#include <Nlohmann/json.hpp>
#include "settings.h"
#include <llapi/DynamicCommandAPI.h>

// We recommend using the global logger.
extern Logger logger;
extern ll::Version PLUGIN_VERSION;

/**
 * @brief The entrypoint of the plugin. DO NOT remove or rename this function.
 *        
 */

unsigned short LTick;
unsigned short CTick;

void loadConfig() {
    if (!std::filesystem::exists("plugins/RedstoneLimiter"))
        std::filesystem::create_directories("plugins/RedstoneLimiter");
    if (std::filesystem::exists("plugins/RedstoneLimiter/config.json")) {
        try {
            Settings::LoadConfigFromJson("plugins/RedstoneLimiter/config.json");
        }
        catch (std::exception &e) {
            logger.error("Configuration file is Invalid, Error: {}", e.what());
        }
        catch (...) {
            logger.error("Configuration file is Invalid");
        }
    } else {
        Settings::WriteDefaultConfig("plugins/RedstoneLimiter/config.json");
    }
    LTick = Settings::tickLimitation;
}

void RegisterCommands() {
    using ParamType = DynamicCommand::ParameterType;
    using Param = DynamicCommand::ParameterData;
    DynamicCommand::setup("redstonelimiter", "RedstoneLimiter command", {{"op",  {"set"}},
                                                                         {"op1", {"reload", "info"}}},
                          {Param("operation", ParamType::Enum, false, "op"),
                           Param("operation", ParamType::Enum, false, "op1"), Param("tick", ParamType::Int, true)},
                          {{"op", "tick"},
                           {"op1"}},
                          [](DynamicCommand const &command, CommandOrigin const &origin, CommandOutput &output,
                             std::unordered_map<std::string, DynamicCommand::Result> &results) {
                              auto &action = results["operation"].getEnumValue();
                              switch (do_hash(action.c_str())) {
                                  case do_hash("reload"): {
                                      loadConfig();
                                      output.success("[RedstoneLimiter] Reloaded, current tick limitation is " +
                                                     std::to_string(LTick));
                                      break;
                                  }
                                  case do_hash("set"): {
                                      auto &tick = results["tick"];
                                      if (tick.isSet) {
                                          LTick = tick.get<int>();
                                      }
                                      output.success(
                                              "[RedstoneLimiter] Set tick limitation to " + std::to_string(LTick));
                                      break;
                                  }
                                  case do_hash("info"): {
                                      output.success("[RedstoneLimiter] Current tick: " + std::to_string(CTick) + " Limited tick: " + std::to_string(LTick));
                                  }
                              }
                          });
}

void PluginInit() {
    loadConfig();
    if (Settings::enableCommands) {
        RegisterCommands();
    }
    logger.info("RedstoneLimiter v{} Loaded, current limitation: {}", PLUGIN_VERSION.toString(), std::to_string(LTick));
}

TInstanceHook(void, "?evaluate@CircuitSystem@@QEAAXPEAVBlockSource@@@Z", CircuitSystem, BlockSource *bs) {
    if (!LTick) return original(this, bs);
    CTick++;
    if (CTick % LTick == 0) {
        CTick = 0;
        return original(this, bs);
    }
}