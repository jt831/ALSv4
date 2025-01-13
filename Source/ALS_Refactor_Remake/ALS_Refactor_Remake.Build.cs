// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;

public class ALS_Refactor_Remake : ModuleRules
{
	public ALS_Refactor_Remake(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
		IncludeOrderVersion = EngineIncludeOrderVersion.Unreal5_5;
	
		PublicDependencyModuleNames.AddRange(new[]
		{
			"Core", "CoreUObject", "Engine", "GameplayTags"
		});

		PrivateDependencyModuleNames.AddRange(new[]
		{
			"EnhancedInput"
		});
	}
}
