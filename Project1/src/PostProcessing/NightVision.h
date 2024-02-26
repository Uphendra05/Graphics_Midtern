#pragma once
#include "../PostProcessing/BasePPAP.h"
#include "SinglePassEffect.h"
#include "../RenderQuad.h"



class NightVision : public SinglePassEffect
{


public:

	NightVision();
	NightVision(float width, float height);
	~NightVision();

	


	// Inherited via BasePPAP
	void DrawProperties() override;
	void SceneDraw() override;
	void InitializeEffect(const std::string& vertex, const std::string& fragment) override;

	

	void SetShaderUniforms() override;
	FrameBuffer* nightVisionFramebuffer;
private:
	

	// Inherited via SinglePassEffect
	//void OnApplyEffect(FrameBuffer* sceneBuffer) override;

};

