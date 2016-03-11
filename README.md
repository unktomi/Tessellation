# Tessellation
UE-4 Tessellation Plugin

Tessellates and/or extrudes 2D polygons to a 3D mesh. Provides a class <code>FOutline</code> with the following functions:

    void MoveTo(int32 X, int32 Y)
  
    void LineTo(int32 X, int32 Y)
  
    void Close()
    
    void Tessellate(TArray<FVector> &Vertices, ETessellationWindingRule WindingRule, float Z, float NormZ)
    
    void ExtrudeArrays(ETessellationWindingRule WindingRule, float Z, float Height, 
                       TArray<FVector> &Vertices, TArray<int32> &Triangles,
                       TArray<FVector> &Normals, TArray<FProcMeshTangent> &Tangents)

Call the first three functions repeatedly to draw a 2d outline - then use the one of the latter two to produce 3d vertex data which can be supplied to a <code>UProceduralMeshComponent</code>.
