// Copyright (c) 2024 lee wood
//
// This file is licensed under the MIT License.

using UnrealBuildTool;

public class UEFSM : ModuleRules
{
	public UEFSM(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
		
		PublicIncludePaths.AddRange(
			new string[] {
				"UEFSM"
			});
				
		
		PrivateIncludePaths.AddRange(PublicIncludePaths);
			
		
		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core"
			});
			
		
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"CoreUObject",
				"Engine",
				"Slate",
				"SlateCore"
			});
		
		
		DynamicallyLoadedModuleNames.AddRange(
			new string[]
			{
			});
	}
}
