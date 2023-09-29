// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class ThrowableItem : ModuleRules
{
	public ThrowableItem(ReadOnlyTargetRules target) : base(target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
		
		PublicIncludePaths.AddRange(
			new[] {
				$"{PluginDirectory}/Source/ThirdParty/ThrowableItemLibrary",
				$"{PluginDirectory}/Source/ThirdParty/ThrowableItemLibrary/Public"
			}
		);
		
		PublicDependencyModuleNames.AddRange(
			new[]
			{
				"Core",
				"CoreUObject",
				"Engine",
				"ThrowableItemLibrary",
				"ThrowableItem", // FIXME: unnecessary?
				"Projects",
				"InputCore",
				"InputDevice"
			}
		);
	}
}
