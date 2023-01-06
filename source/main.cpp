#include <wups.h>
#include <array>
// #include <string.h>

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



// OLD
// #include <wups.h>
// #include <string.h>


// #include "patches.h"

// // WUPS_PLUGIN_NAME("rce_patches");
// // WUPS_PLUGIN_DESCRIPTION("Patches security issues in WiiU games that could be triggered remotely");
// // WUPS_PLUGIN_VERSION("v1.0");
// // WUPS_PLUGIN_AUTHOR("Rambo6Glaz");
// // WUPS_PLUGIN_LICENSE("");

// std::optional<rplinfo> gRPLInfo;

// ON_APPLICATION_START()
// {

// 	// If this is not a supported title, no need to do anything
// 	uint64_t titleId = OSGetTitleID();
// 	GamePatches *gamePatch = nullptr;
// 	for (auto &patch : sGamePatchList)
// 	{
// 		for (int i = 0; i < 3; i++)
// 		{
// 			if (patch.mRegionalTIDs[i] == titleId)
// 			{
// 				gamePatch = &patch;
// 				break;
// 			}
// 		}
// 	}

// 	if (!gamePatch)
// 		return;

// 	// Init logging
// 	if (!WHBLogModuleInit())
// 	{
// 		WHBLogCafeInit();
// 		WHBLogUdpInit();
// 	}

// 	WHBLogPrintf("rce_patches: applying patches for %s...", gamePatch->mTitleName);

// 	// Patch the dynload functions so GetRPLInfo works
// 	if (!PatchDynLoadFunctions())
// 	{
// 		WHBLogPrintf("rce_patches: Failed to patch dynload functions");
// 		return;
// 	}

// 	// Get the RPLInfo
// 	gRPLInfo = TryGetRPLInfo();
// 	if (!gRPLInfo)
// 	{
// 		WHBLogPrintf("rce_patches: Failed to get RPL info");
// 		return;
// 	}

// 	// For each patch type, call apply patch func (terrible design lol)
// 	for (auto &patch : gamePatch->mPatchTypes)
// 	{
// 		gamePatch->mPatchFunc(patch);
// 	}
// }
