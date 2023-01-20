#include <wups.h>
#include <array>

#include "types.h"
#include "SplatPatches.hpp"

WUPS_PLUGIN_NAME("splatoon_test_patches");
WUPS_PLUGIN_DESCRIPTION("Nothing in particular");
WUPS_PLUGIN_VERSION("v1.0");
WUPS_PLUGIN_AUTHOR("Sheldon10095");
WUPS_PLUGIN_LICENSE("");

std::optional<rplinfo> gRPLInfo;

ON_APPLICATION_START()
{
	u64 tid = OSGetTitleID();
	std::array<uint64_t, 3> splatoonTIDs = { SPLATOON_TID };
	if (!(std::find(splatoonTIDs.begin(), splatoonTIDs.end(), tid) != splatoonTIDs.end())) // if not splatoon
		return;

	// Init logging
	if (!WHBLogModuleInit())
	{
		WHBLogCafeInit();
		WHBLogUdpInit();
	}

	WHBLogPrintf("splatoon_test_patches: applying patches for %s...", "Splatoon");

	// Patch the dynload functions so GetRPLInfo works
	if (!PatchDynLoadFunctions())
	{
		WHBLogPrintf("splatoon_test_patches: Failed to patch dynload functions");
		return;
	}

	// Get the RPLInfo
	gRPLInfo = TryGetRPLInfo();
	if (!gRPLInfo)
	{
		WHBLogPrintf("splatoon_test_patches: Failed to get RPL info");
		return;
	}

	Splatoon::ApplyPatches();
}