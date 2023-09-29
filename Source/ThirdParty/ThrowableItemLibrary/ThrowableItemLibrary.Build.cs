// Fill out your copyright notice in the Description page of Project Settings.

using System.IO;
using Internal;
using UnrealBuildTool;

public class ThrowableItemLibrary : ModuleRules
{
	public ThrowableItemLibrary(ReadOnlyTargetRules target) : base(target)
	{
		Type = ModuleType.External;

		if (Target.Platform == UnrealTargetPlatform.Win64)
		{
			// Add the compile-time import library
			PublicAdditionalLibraries.Add(Path.Combine("$(ModuleDir)", "x64", "Release", "JoyShockLibrary.lib"));

			#region "Stop using dynamic DLLs" TODO
			// TODO: Maybe stop using DLLs and use the compile-time lib?
			//       It appears to search for a DLL for some reason, getting the following error when i don't include it:
			
			//	Failed to load 'E:/Unreal Projects/SisterLocationRuin/Binaries/Win64/UnrealEditor-SisterLocationRuin.dll' 	(GetLastError=126)
			//	  Missing import: JoyShockLibrary.dll
			//	  Looked in: ../../../Engine/Binaries/Win64
			//	  Looked in: ../../../../../Unreal Projects/SisterLocationRuin/Binaries/Win64
			//	  Looked in: E:\Unreal Projects\SisterLocationRuin\Binaries\Win64
			//	  Looked in: E:\Software\UE_5.3\Engine\Plugins\*
			//	  Looked in: E:\Software\UE_5.3\Engine\Binaries\Win64\*
			//
			//	Message dialog closed, result: Ok, title: Message, text: The game module 'SisterLocationRuin' could not be loaded. There may be an operating system error, the module may not be properly set up, or a plugin which has been included into the build has not been turned on.
			#endregion
			
			// Delay-load the DLL, so we can load it from the right place first
			PublicDelayLoadDLLs.Add("JoyShockLibrary.dll");
			
			// Ensure that the DLL is staged along with the executable
			RuntimeDependencies.Add("$(PluginDir)/Binaries/ThirdParty/ThrowableItemLibrary/Win64/JoyShockLibrary.dll");
		}
		else if (Target.Platform == UnrealTargetPlatform.Mac)
		{
			Console.WriteLine("Error: Mac not supported");
		}
		else if (Target.Platform == UnrealTargetPlatform.Linux)
		{
			// TODO: Check if this works
			string soPath = Path.Combine("$(PluginDir)", "Binaries", "ThirdParty", "ThrowableItemLibrary", "Linux", "x86_64-unknown-linux-gnu", "libJoyShockLibrary.so");
			PublicAdditionalLibraries.Add(soPath);
			PublicDelayLoadDLLs.Add(soPath);
			RuntimeDependencies.Add(soPath);
		}
	}
}
