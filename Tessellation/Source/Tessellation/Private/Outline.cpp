#include "TessellationPrivatePCH.h"
#include "Outline.h"
#include "tesselator.h"

void FOutline::Flush(struct TESStesselator *tess, int32 start, int32 count)
{
	if (count == 0) return;
	tessAddContour(tess, 2,
		&points.GetData()[start * 2],
		points.GetTypeSize() * 2,
		count);
}


void FOutline::MoveTo(float x, float y) {
	this->x = x;
	this->y = y;
	pointTypes.Push(EOutlinePointType::MOVETO);
	points.Push(x);
	points.Push(y);
}

void FOutline::LineTo(float x, float y) {
	pointTypes.Push(EOutlinePointType::LINETO);
	points.Push(x);
	points.Push(y);
}

void FOutline::Close() {
	pointTypes.Push(EOutlinePointType::CLOSE);
	points.Push(this->x);
	points.Push(this->y);
}

void FOutline::Apply(IOutline &target) 
{
	for (int i = 0; i < pointTypes.Num(); i++) 
	{
		switch (pointTypes[i]) {
		case EOutlinePointType::MOVETO:
			target.MoveTo(points[i * 2], points[i * 2 + 1]);
			break;
		case EOutlinePointType::LINETO:
			target.LineTo(points[i * 2], points[i * 2 + 1]);
			break;
		case EOutlinePointType::CLOSE:
			target.Close();
			break;
		}
	}
}

void FOutline::Tessellate(TArray<FVector> &Vertices, ETessellationWindingRule WindingRule, float Z, float NormZ)
{
	int last = 0;
	TESStesselator *tess = tessNewTess(nullptr);
	for (int i = 0; i < pointTypes.Num(); i++)
	{
		switch (pointTypes[i]) {
		case EOutlinePointType::MOVETO:
			Flush(tess, last, i - last);
			last = i;
			break;
		case EOutlinePointType::LINETO:
			break;
		case EOutlinePointType::CLOSE:
			break;
		}
	}
	Flush(tess, last, pointTypes.Num() - last);
	float normal[3] = { 0.0f, 0.0f, NormZ };
	const int vertexSize = 2;
	const int polySize = 3;
	tessTesselate(tess, (int)WindingRule, TESS_POLYGONS, polySize, vertexSize, normal);
	const int nelems = tessGetElementCount(tess);
	const TESSindex* elems = tessGetElements(tess);
	const float *verts = tessGetVertices(tess);
	for (int i = 0; i < nelems; i++)
	{
		const TESSindex* poly = &elems[i * polySize];
		for (int j = 0; j < polySize; j++)
		{
			if (poly[j] == TESS_UNDEF) break;
			const float *v = (&verts[poly[j] * vertexSize]);
			Vertices.Push(FVector(v[0], v[1], Z));
		}
	}
	tessDeleteTess(tess);
}

void FOutline::ExtrudeArrays(ETessellationWindingRule WindingRule, float Z, float Height,
	TArray<FVector> &Vertices, TArray<int32> &Triangles, TArray<FVector> &Normals, TArray<FProcMeshTangent> &Tangents)
{
	FOutline &Outline = *this;

	FVector normal(0, 0, -1.0f);
	// bottom
	Outline.Tessellate(Vertices, WindingRule, Z, 1.0f);
	for (int i = 0; i <Vertices.Num(); i++)
	{
		Normals.Push(normal);
	}

	struct DrawSides : public IOutline
	{
		TArray<FVector> &target;
		TArray<FVector> &normals;
		TArray<FProcMeshTangent> &tangents;
		const float Height;
		float x0;
		float y0;
		float x1;
		float y1;
		float z;
		DrawSides(TArray<FVector> &Result, TArray<FVector> &ResultNormals, TArray<FProcMeshTangent> &ResultTangents, float Z, float h) :
			target(Result), normals(ResultNormals), tangents(ResultTangents), z(Z), Height(h)
		{
		}

		virtual void MoveTo(float x, float y)
		{
			x0 = x1 = x;
			y0 = y1 = y;
		}

		virtual void LineTo(float x, float y)
		{
			FVector A(x1, y1, z);
			FVector B(x1, y1, z + Height);
			FVector C(x, y, z + Height);
			target.Push(A);
			target.Push(B);
			target.Push(C);
			target.Push(FVector(x, y, z));
			target.Push(FVector(x1, y1, z));
			target.Push(FVector(x, y, z + Height));
			//FVector Tangent = A - C;
			FVector Normal = FVector::CrossProduct(FVector(x - x1, y - y1, 0), FVector(0, 0, 1)).GetSafeNormal();
			for (int i = 0; i < 6; i++)
			{
				normals.Push(Normal);
			}
			x1 = x;
			y1 = y;
		}
		virtual void Close()
		{
			LineTo(x0, y0);
		}
	};
	DrawSides App(Vertices, Normals, Tangents, Z, Height);
	Outline.Apply(App);
	normal.Z = 1.0f;
	int Count = Vertices.Num();
	Outline.Tessellate(Vertices, WindingRule, Z + Height, -1.0f);
	for (int i = Count; i < Vertices.Num(); i++)
	{
		Normals.Push(normal);
	}
	for (int i = 0; i < Vertices.Num(); i++)
	{
		Triangles.Push(i);
	}
}


