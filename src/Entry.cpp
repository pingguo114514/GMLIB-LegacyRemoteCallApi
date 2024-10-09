#include "Entry.h"
#include "Global.h"

ll::Logger logger(PLUGIN_NAME);

namespace GMLIB {

std::unique_ptr<LegacyRemoteCallApi>& LegacyRemoteCallApi::getInstance() {
    static std::unique_ptr<LegacyRemoteCallApi> instance;
    return instance;
}

bool LegacyRemoteCallApi::load() {
    Export_Legacy_GMLib_ModAPI();
    Export_Legacy_GMLib_ServerAPI();
    Export_Compatibility_API();
    ExportPAPI();
    Export_Event_API();
    Export_BinaryStream_API();
    logger.info("GMLIB-LegacyRemoteCallApi Loaded!");
    logger.info(
        "Loaded Version: {} with {}",
        fmt::format(fg(fmt::color::pink), "GMLIB-" + Version::getLibVersionString()),
        fmt::format(fg(fmt::color::light_green), "GMLIB-LegacyRemoteCallApi-" + LIB_VERSION.asString())
    );
    logger.info("Author: GroupMountain");
    logger.info("Repository: https://github.com/GroupMountain/GMLIB-LegacyRemoteCallApi");
    return true;
}

bool LegacyRemoteCallApi::enable() { return true; }

bool LegacyRemoteCallApi::disable() { return true; }

} // namespace GMLIB

LL_REGISTER_MOD(LegacyRemoteCallApi, LegacyRemoteCallApi::getInstance());
