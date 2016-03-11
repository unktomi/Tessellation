#include "TessellationPrivatePCH.h"
#include "TessellationBlueprintLibrary.h"

FOutline UTessellationBlueprintLibrary::MakeOutline() 
{
	return FOutline();
}

void UTessellationBlueprintLibrary::MoveTo(const FOutline& Outline0, float x, float y)
{
	FOutline &Outline = const_cast<FOutline&>(Outline0);
	Outline.MoveTo(x, y);
}

void UTessellationBlueprintLibrary::LineTo(const FOutline& Outline0, float x, float y) 
{
	FOutline &Outline = const_cast<FOutline&>(Outline0);
	Outline.LineTo(x, y);
}

void UTessellationBlueprintLibrary::Close(const FOutline& Outline0)
{
	FOutline &Outline = const_cast<FOutline&>(Outline0);
	Outline.Close();
}

void
UTessellationBlueprintLibrary::ExtrudeArrays(const FOutline& Outline0, ETessellationWindingRule WindingRule, float Z, float Height,
	TArray<FVector> &Vertices, TArray<int32> &Triangles, TArray<FVector> &Normals, TArray<FProcMeshTangent> &Tangents)
{
	FOutline &Outline = const_cast<FOutline&>(Outline0);
	Outline.ExtrudeArrays(WindingRule, Z, Height, Vertices, Triangles, Normals, Tangents);
}


