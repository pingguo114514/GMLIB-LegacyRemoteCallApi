#pragma once
#include <include_all.h>

#include <RemoteCallAPI.h>

#define PLUGIN_NAME fmt::format(fg(fmt::color::light_green), "GMLIB-LRCA")

#define LIB_VERSION GMLIB::Version(0, 12, 1)

extern ll::Logger logger;

extern void Export_Legacy_GMLib_ModAPI();
extern void Export_Legacy_GMLib_ServerAPI();
extern void Export_Compatibility_API();
extern void ExportPAPI();
extern void Export_Event_API();