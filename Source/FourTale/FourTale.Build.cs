// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class FourTale : ModuleRules
{
	public FourTale(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput" });
	}
}
