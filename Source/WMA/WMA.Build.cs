// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class WMA : ModuleRules
{
	public WMA(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicIncludePaths.AddRange(new string[] { "WMA" });

        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput", "EnhancedInput" });
	}
}
