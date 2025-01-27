// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Sensitivity_tool : ModuleRules
{
	public Sensitivity_tool(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput", "UMG" });
 
    }
}
