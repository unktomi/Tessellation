// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

namespace UnrealBuildTool.Rules
{
    using System.IO;
    public class Tessellation : ModuleRules
    {

        private string ModulePath
        {
            get { return Path.GetDirectoryName(RulesCompiler.GetModuleFilename(this.GetType().Name)); }
        }

        private string ThirdPartyPath
        {
            get { return Path.GetFullPath(Path.Combine(ModulePath, "../../ThirdParty/")); }
        }
        public Tessellation(TargetInfo Target)
        {
            PublicIncludePaths.AddRange(
                new string[] {				
					// ... add public include paths required here ...
				}
                );

            PrivateIncludePaths.AddRange(
                new string[] {
					"Tessellation/Private",
					// ... add other private include paths required here ...
				}
                );

            PublicDependencyModuleNames.AddRange(
                new string[]
				{
					"Core",
					"Engine",
					"Kismet",
					"CoreUObject",
					"ProceduralMeshComponent"	
					// ... add other public dependencies that you statically link with here ...
				}
                );

            PrivateDependencyModuleNames.AddRange(
                new string[]
				{
					// ... add private dependencies that you statically link with here ...
				}
                );

            DynamicallyLoadedModuleNames.AddRange(
                new string[]
				{
					// ... add any modules that your module loads dynamically here ...
				}
                );
            LoadTessLib(Target);
        }


        public bool LoadTessLib(TargetInfo Target)
        {
            bool isLibrarySupported = false;

            if ((Target.Platform == UnrealTargetPlatform.Win64) || (Target.Platform == UnrealTargetPlatform.Win32))
            {
                isLibrarySupported = true;

                string PlatformString = (Target.Platform == UnrealTargetPlatform.Win64) ? "Win64" : "Win32";
                string LibrariesPath = Path.Combine(ThirdPartyPath, "Tess2", "Lib");

                PublicAdditionalLibraries.Add(Path.Combine(LibrariesPath, PlatformString, "tess2.lib"));
            }

            if (isLibrarySupported)
            {
                // Include path
                PublicIncludePaths.Add(Path.Combine(ThirdPartyPath, "Tess2", "Include"));
            }

            Definitions.Add(string.Format("WITH_TESS2_BINDING={0}", isLibrarySupported ? 1 : 0));

            return isLibrarySupported;
        }
    }
}
