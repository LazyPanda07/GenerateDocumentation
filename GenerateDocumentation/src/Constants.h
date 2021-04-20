#pragma once

#include <string>
#include <array>

inline const std::string settingsFile = "generate_documentation.json";

inline const std::string jsonRootName = "buildConfiguration";

inline const std::array<std::string, 6> buildConfigurations =
{
	"Debug",
	"DebugDLL",
	"ProductionRelease",
	"ProductionReleaseDLL",
	"Release",
	"ReleaseDLL"
};
