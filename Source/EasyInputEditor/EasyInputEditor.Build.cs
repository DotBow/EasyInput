// Copyright (C) Dreamer's Tail. All Rights Reserved.
// Authors: @DotBow

using UnrealBuildTool;

public class EasyInputEditor : ModuleRules
{
	public EasyInputEditor(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicIncludePaths.AddRange(
			new string[] {
				// ... add public include paths required here ...
			});

		PrivateIncludePaths.AddRange(
			new string[] {
				// ... add other private include paths required here ...
			});

		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				"EasyInput",
				// ... add other public dependencies that you statically link with here ...
			});

		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"CoreUObject",
				"Engine",
				"UnrealEd",
				"SlateCore",
				"Slate",
				"Projects",
				"PropertyEditor",
				"InputCore",
				// ... add private dependencies that you statically link with here ...
			});

		DynamicallyLoadedModuleNames.AddRange(
			new string[]
			{
				// ... add any modules that your module loads dynamically here ...
			});
	}
}
