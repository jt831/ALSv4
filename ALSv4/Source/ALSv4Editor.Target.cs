

using UnrealBuildTool;
using System.Collections.Generic;

public class ALSv4EditorTarget : TargetRules
{
	public ALSv4EditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V2;

		ExtraModuleNames.AddRange( new string[] { "ALSv4" } );
	}
}
