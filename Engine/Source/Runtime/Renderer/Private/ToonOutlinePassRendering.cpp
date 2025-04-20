// ToonOutlinePassRendering.cpp
#include "ToonOutlinePassRendering.h"  

#include "DeferredShadingRenderer.h"  
#include "ScenePrivate.h"  
#include "MeshPassProcessor.inl"  
#include "SimpleMeshDrawCommandPass.h"  
#include "ProfilingDebugging/CsvProfiler.h"

FToonOutlineMeshPassProcessor::FToonOutlineMeshPassProcessor(  
	const FScene* Scene,   
	const FSceneView* InViewIfDynamicMeshCommand,   
	const FMeshPassProcessorRenderState& InPassDrawRenderState,   
	FMeshPassDrawListContext* InDrawListContext)  
	:FMeshPassProcessor(EMeshPass::ToonOutlinePass, Scene, Scene->GetFeatureLevel(), InViewIfDynamicMeshCommand, InDrawListContext),  
	PassDrawRenderState(InPassDrawRenderState)  
{  
	if (PassDrawRenderState.GetDepthStencilState() == nullptr)  
	{       
		PassDrawRenderState.SetDepthStencilState(TStaticDepthStencilState<false, CF_DepthNearOrEqual>().GetRHI());  
	}    
	if (PassDrawRenderState.GetBlendState() == nullptr)  
	{       
		PassDrawRenderState.SetBlendState(TStaticBlendState<>().GetRHI());  
	}
}

// ToonOutlinePassRendering.cpp
void FToonOutlineMeshPassProcessor::AddMeshBatch(  
	const FMeshBatch& MeshBatch,  
	uint64 BatchElementMask,  
	const FPrimitiveSceneProxy* PrimitiveSceneProxy,  
	int32 StaticMeshId)  
{  
	const FMaterialRenderProxy* MaterialRenderProxy = MeshBatch.MaterialRenderProxy;  
	const FMaterial* Material = MaterialRenderProxy->GetMaterialNoFallback(FeatureLevel);  

	if (Material != nullptr && Material->GetRenderingThreadShaderMap())  
	{       
		const FMaterialShadingModelField ShadingModels = Material->GetShadingModels();  
		// Only Toon shading model and enable render toon outline can render this pass  
		if (ShadingModels.HasShadingModel(MSM_Toon) && Material->ShouldRenderToonOutline())  
		{          
			const EBlendMode BlendMode = Material->GetBlendMode();  
			bool bResult = true;  
			if (BlendMode == BLEND_Opaque)  
			{             
				Process(  
					MeshBatch,                
					BatchElementMask,                
					StaticMeshId,                
					PrimitiveSceneProxy,                
					*MaterialRenderProxy,                
					*Material,                
					FM_Solid,  
					CM_CCW); // Cull back  
			}  
		}    
	}
}
// ToonOutlinePassRendering.cpp
bool FToonOutlineMeshPassProcessor::Process(  
    const FMeshBatch& MeshBatch,  
    uint64 BatchElementMask,  
    int32 StaticMeshId,  
    const FPrimitiveSceneProxy* PrimitiveSceneProxy,  
    const FMaterialRenderProxy& MaterialRenderProxy,  
    const FMaterial& MaterialResource,  
    ERasterizerFillMode MeshFillMode,  
    ERasterizerCullMode MeshCullMode)  
{  
    return false;
}