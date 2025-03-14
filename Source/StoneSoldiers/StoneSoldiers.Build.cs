// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class StoneSoldiers : ModuleRules
{
    public StoneSoldiers(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[] 
        { 
            "Core", 
            "CoreUObject", 
            "Engine", 
            "InputCore", 
            "EnhancedInput", 
            "UMG", 
            "FMODStudio",
            "OnlineSubsystem", 
            "OnlineSubsystemUtils", 
            "Networking", 
            "Sockets", 
            "AdvancedSessions", 
            "AdvancedSteamSessions",
            "OnlineSubsystemSteam"
        });

        PrivateDependencyModuleNames.AddRange(new string[] {
            "Slate",
            "SlateCore",
            "OnlineSubsystem",
            "OnlineSubsystemUtils",
            "Json"// Add this here
        });

        // To include OnlineSubsystemSteam, add it to the plugins section in your uproject file 
        // with the Enabled attribute set to true.
    }
}