// ToonOutlinePassRendering.h
#pragma once  

#include "DataDrivenShaderPlatformInfo.h"  
#include "MeshPassProcessor.h"  
#include "CoreMinimal.h"  
#include "MeshMaterialShader.h"  

class FToonOutlineMeshPassProcessor : public FMeshPassProcessor  
{  
public:  
	//const FScene* InScene, ERHIFeatureLevel::Type InFeatureLevel, const FSceneView* InViewIfDynamicMeshCommand, FMeshPassDrawListContext* InDrawListContext  
	FToonOutlineMeshPassProcessor(  
	   const FScene* Scene,  
	   const FSceneView* InViewIfDynamicMeshCommand,  
	   const FMeshPassProcessorRenderState& InPassDrawRenderState,  
	   FMeshPassDrawListContext* InDrawListContext  
	);  
	virtual void AddMeshBatch(  
	   const FMeshBatch& RESTRICT MeshBatch,  
	   uint64 BatchElementMask,  
	   const FPrimitiveSceneProxy* RESTRICT PrimitiveSceneProxy,  
	   int32 StaticMeshId = -1  
	) override final;  

private:  
	bool Process(  
	   const FMeshBatch& MeshBatch,  
	   uint64 BatchElementMask,  
	   int32 StaticMeshId,  
	   const FPrimitiveSceneProxy* RESTRICT PrimitiveSceneProxy,  
	   const FMaterialRenderProxy& RESTRICT MaterialRenderProxy,  
	   const FMaterial& RESTRICT MaterialResource,  
	   ERasterizerFillMode MeshFillMode,  
	   ERasterizerCullMode MeshCullMode  
	);  
private:  
	FMeshPassProcessorRenderState PassDrawRenderState;  
};