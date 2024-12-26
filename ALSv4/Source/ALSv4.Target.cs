

using UnrealBuildTool;
using System.Collections.Generic;

public class ALSv4Target : TargetRules
{
	public ALSv4Target(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V2;

		ExtraModuleNames.AddRange( new string[] { "ALSv4" } );
	}
}
