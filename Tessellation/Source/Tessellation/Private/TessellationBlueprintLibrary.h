#pragma once

#include "Outline.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "ProceduralMeshComponent.h"
#include "TessellationBlueprintLibrary.generated.h"


/**
 * A blueprint library class to expose the functionality of the Tessellation plugin to blueprints
 * in all blueprint contexts.
 */
UCLASS()
class TESSELLATION_API UTessellationBlueprintLibrary : public UBlueprintFunctionLibrary {
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, Category = "Tessellation")
		static FOutline MakeOutline();

	UFUNCTION(BlueprintCallable, Category = "Tessellation")
		static void MoveTo(const FOutline& Outline, float x, float y);

	UFUNCTION(BlueprintCallable, Category = "Tessellation")
		static void LineTo(const FOutline& Outline, float x, float y);

	UFUNCTION(BlueprintCallable, Category = "Tessellation")
		static void Close(const FOutline& Outline);

	UFUNCTION(BlueprintCallable, Category = "Tessellation")
		static void ExtrudeArrays(const FOutline& Outline, ETessellationWindingRule WindingRule, float Z, float Height, TArray<FVector> &Vertices, TArray<int32> &Triangles,
			TArray<FVector> &Normals, TArray<FProcMeshTangent> &Tangents);

};
