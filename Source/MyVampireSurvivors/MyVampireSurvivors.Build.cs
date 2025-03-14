// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class MyVampireSurvivors : ModuleRules
{
	public MyVampireSurvivors(ReadOnlyTargetRules Target) : base(Target)
    {
		PublicIncludePaths.AddRange(
			new string[] {
				"MyVampireSurvivors"
			}
		);

		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(
			new string[] {
				"Core",
				"CoreUObject",
				"Engine",
				"InputCore",
				"EnhancedInput",
				"NavigationSystem",
				"UMG",
				"CommonUI"
			}
		);

		PrivateDependencyModuleNames.AddRange(new string[] { "UnrealEd" });

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
		
		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
