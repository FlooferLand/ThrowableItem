#include "ThrowableItemModule.h"

#include "ThrowableItem.h"
#include "Misc/MessageDialog.h"
#include "Modules/ModuleManager.h"
#include "Misc/Paths.h"
#include "HAL/PlatformProcess.h"
#include "Interfaces/IPluginManager.h"
#define LOCTEXT_NAMESPACE "FThrowableItemModule"

void FThrowableItemModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module

	// Get the base directory of this plugin
	FString BaseDir = IPluginManager::Get().FindPlugin("ThrowableItem")->GetBaseDir();

	// Compile-time wizardry
	// TODO: Move this to be global
	#ifdef PLATFORM_64BITS
		constexpr int BUILD_ARCH = 64;
		constexpr char BUILD_ARCH_STR[] = "x64";
	#else
		constexpr int BUILD_ARCH = 32;
		constexpr char BUILD_ARCH_STR[] = "x32";
	#endif

	#if UE_BUILD_DEBUG or UE_BUILD_DEVELOPMENT
		constexpr char BUILD_TYPE[] = "Debug";
	#else
		constexpr char BUILD_TYPE[] = "Release";
	#endif
	
	// Add on the relative location of the third party dll and load it
	FString LibraryPath;
#if PLATFORM_WINDOWS
	LibraryPath = FPaths::Combine(
		*BaseDir,
		TEXT("Source/ThirdParty/ThrowableItemLibrary/") + FString(BUILD_ARCH_STR) + "/" + BUILD_TYPE + TEXT("/JoyShockLibrary.dll"));
#elif PLATFORM_LINUX
	// FIXME: Don't know where the .so file is!
	LibraryPath = FPaths::Combine(*BaseDir, TEXT("Source/ThirdParty/ThrowableItemLibrary/Linux/x86_64-unknown-linux-gnu/libJoyShockLibrary.so"));
#endif

	// Getting the handle to the DLL methods
	JoyShockHandle = !LibraryPath.IsEmpty() ? FPlatformProcess::GetDllHandle(*LibraryPath) : nullptr;
	if (JoyShockHandle)
	{
		// Do something when the DLL is first loaded
	}
	else
	{
		FMessageDialog::Open(EAppMsgType::Ok, LOCTEXT("ThirdPartyLibraryError", "Failed to load DualSense third party library"));
	}
}

void FThrowableItemModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
	
	// Free the dll handle
	FPlatformProcess::FreeDllHandle(JoyShockHandle);
	JoyShockHandle = nullptr;
}

#undef LOCTEXT_NAMESPACE
IMPLEMENT_MODULE(FThrowableItemModule, ThrowableItem)
