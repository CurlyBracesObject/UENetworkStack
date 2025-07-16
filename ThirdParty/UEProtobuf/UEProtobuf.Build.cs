// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.IO;

public class UEProtobuf : ModuleRules
{
	public UEProtobuf(ReadOnlyTargetRules Target) : base(Target)
	{
		Type = ModuleType.External;
		
		PublicSystemIncludePaths.Add(Path.Combine(ModuleDirectory, "include"));
		PublicSystemLibraryPaths.Add(Path.Combine(ModuleDirectory, "lib"));
		
		PublicSystemLibraries.Add("libprotobuf.lib");
		PublicSystemLibraries.Add("libprotoc.lib");
	}
}