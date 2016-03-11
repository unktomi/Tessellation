#pragma once
#include "Core.h"
#include "Engine.h"
#include "ProceduralMeshComponent.h"
#include "Outline.generated.h"

class ITessellation;
UENUM(BlueprintType)
enum class ETessellationWindingRule : uint8
{
	WINDING_ODD UMETA(DisplayName = "Odd"),
	WINDING_NONZERO UMETA(DisplayName = "Non-zero"),
	WINDING_POSITIVE UMETA(DisplayName = "Positive"),
	WINDING_ABS_GEQ_TWO UMETA(DisplayName = "Absolute value >= 2")
};

UENUM(BlueprintType)
enum class EOutlinePointType : uint8 
{
	MOVETO UMETA(DisplayName = "Move to point"),
	LINETO UMETA(DisplayName = "Draw line to point"),
	CLOSE UMETA(DisplayName = "Close outline"),
};

struct IOutline 
{
	virtual void MoveTo(float x, float y) = 0;
	virtual void LineTo(float x, float y) = 0;
	virtual void Close() = 0;
};

USTRUCT(BlueprintType)
struct TESSELLATION_API FOutline
{
	GENERATED_USTRUCT_BODY()
private:
	TArray<EOutlinePointType> pointTypes;
	TArray<float> points;
	float x, y;
	void Flush(struct TESStesselator *tess, int32 start, int32 count);
public:

	void MoveTo(float x, float y);

	void LineTo(float x, float y);

	void Close();

	void Apply(IOutline &target);

	void Tessellate(TArray<FVector> &Vertices, ETessellationWindingRule WindingRule, float Z = 0.0, float NormZ = 1.0f);

	void ExtrudeArrays(ETessellationWindingRule WindingRule, float Z, float Height,
		TArray<FVector> &Vertices, TArray<int32> &Triangles, TArray<FVector> &Normals, TArray<FProcMeshTangent> &Tangents);

	void Reset()
	{
		pointTypes.Reset();
		points.Reset();
		x = y = 0;
	}
};
