#include "Global.h"

void Export_Compatibility_API() {
    RemoteCall::exportAs("GMLIB_API", "getServerMspt", []() -> float {
        auto level = GMLIB_Level::getLevel();
        if (!level) {
            return 0.0f;
        }
        return level->getServerMspt();
    });
    RemoteCall::exportAs("GMLIB_API", "getServerCurrentTps", []() -> float {
        auto level = GMLIB_Level::getLevel();
        if (!level) {
            return 0.0f;
        }
        return level->getServerCurrentTps();
    });
    RemoteCall::exportAs("GMLIB_API", "getServerAverageTps", []() -> float {
        auto level = GMLIB_Level::getLevel();
        if (!level) {
            return 0.0f;
        }
        return level->getServerAverageTps();
    });
    RemoteCall::exportAs("GMLIB_API", "getAllPlayerUuids", []() -> std::vector<std::string> {
        return GMLIB_Player::getAllUuids();
    });
    RemoteCall::exportAs("GMLIB_API", "getPlayerNbt", [](std::string uuid) -> std::string {
        auto uid = mce::UUID::fromString(uuid);
        return GMLIB_Player::getPlayerNbt(uid)->toSnbt();
    });
    RemoteCall::exportAs("GMLIB_API", "setPlayerNbt", [](std::string uuid, std::string snbt) -> bool {
        auto uid = mce::UUID::fromString(uuid);
        auto nbt = CompoundTag::fromSnbt(snbt);
        return GMLIB_Player::setPlayerNbt(uid, *nbt);
    });
    RemoteCall::exportAs(
        "GMLIB_API",
        "setPlayerNbtTags",
        [](std::string uuid, std::string snbt, std::vector<std::string> tags) -> bool {
            auto uid = mce::UUID::fromString(uuid);
            auto nbt = CompoundTag::fromSnbt(snbt);
            return GMLIB_Player::setPlayerNbtTags(uid, *nbt, tags);
        }
    );
    RemoteCall::exportAs("GMLIB_API", "tryGetNameFormUuid", [](std::string uuid) -> std::string {
        auto uid  = mce::UUID::fromString(uuid);
        auto info = ll::service::PlayerInfo::getInstance().fromUuid(uid);
        if (info) {
            return info->name;
        }
        return "";
    });
    RemoteCall::exportAs("GMLIB_API", "getAllExperiments", []() -> std::vector<int> {
        auto             map = GMLIB_Level::getAllExperiments();
        std::vector<int> result;
        for (auto& key : map) {
            result.push_back(key.first);
        }
        return result;
    });
    RemoteCall::exportAs("GMLIB_API", "getExperimentTranslatedName", [](int id) -> std::string {
        auto map = GMLIB_Level::getAllExperimentsTranslateKeys();
        if (map.count(id)) {
            return std::string(map[id]);
        }
        return "";
    });
    RemoteCall::exportAs(
        "GMLIB_API",
        "createFloatingText",
        [](std::pair<Vec3, int> pos, std::string text, bool papi) -> int {
            auto ft = new GMLIB::Server::FloatingText(text, pos.first, pos.second, papi);
            return ft->getRuntimeID();
        }
    );
    RemoteCall::exportAs("GMLIB_API", "setFloatingTextData", [](int id, std::string text) -> bool {
        auto ft = GMLIB::Server::FloatingText::getFloatingText(id);
        if (ft) {
            ft->setText(text);
            return true;
        }
        return false;
    });
    RemoteCall::exportAs("GMLIB_API", "deleteFloatingText", [](int id) -> bool {
        return GMLIB::Server::FloatingText::deleteFloatingText(id);
    });
    RemoteCall::exportAs("GMLIB_API", "sendFloatingTextToPlayer", [](int id, Player* pl) -> bool {
        auto ft = GMLIB::Server::FloatingText::getFloatingText(id);
        if (ft) {
            ft->sendToClient(pl);
            return true;
        }
        return false;
    });
    RemoteCall::exportAs("GMLIB_API", "sendFloatingText", [](int id) -> bool {
        auto ft = GMLIB::Server::FloatingText::getFloatingText(id);
        if (ft) {
            ft->sendToAllClients();
            return true;
        }
        return false;
    });
    RemoteCall::exportAs("GMLIB_API", "removeFloatingTextFromPlayer", [](int id, Player* pl) -> bool {
        auto ft = GMLIB::Server::FloatingText::getFloatingText(id);
        if (ft) {
            ft->removeFromClient(pl);
            return true;
        }
        return false;
    });
    RemoteCall::exportAs("GMLIB_API", "removeFloatingText", [](int id) -> bool {
        auto ft = GMLIB::Server::FloatingText::getFloatingText(id);
        if (ft) {
            ft->removeFromAllClients();
            return true;
        }
        return false;
    });
    RemoteCall::exportAs("GMLIB_API", "updateClientFloatingTextData", [](int id, Player* pl) -> bool {
        auto ft = GMLIB::Server::FloatingText::getFloatingText(id);
        if (ft) {
            ft->updateClient(pl);
            return true;
        }
        return false;
    });
    RemoteCall::exportAs("GMLIB_API", "updateAllClientsFloatingTextData", [](int id) -> bool {
        auto ft = GMLIB::Server::FloatingText::getFloatingText(id);
        if (ft) {
            ft->updateAllClients();
            return true;
        }
        return false;
    });
    RemoteCall::exportAs("GMLIB_API", "isVersionMatched", [](int a, int b, int c) -> bool {
        auto version = SemVersion(a, b, c, "", "");
        return LIB_VERSION.satisfies(version);
    });
    RemoteCall::exportAs("GMLIB_API", "getVersion_LRCA", []() -> std::string { return LIB_VERSION.asString(); });
    RemoteCall::exportAs("GMLIB_API", "getVersion_GMLIB", []() -> std::string {
        return GMLIB::Version::getLibVersionString();
    });
}