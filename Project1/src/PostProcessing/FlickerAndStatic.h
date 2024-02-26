#pragma once
#include "../PostProcessing/BasePPAP.h"
#include "../RenderQuad.h"
#include "SinglePassEffect.h"


class FlickerAndStatic : public SinglePassEffect
{

public:

	FlickerAndStatic();
	FlickerAndStatic(float width, float height);
	~FlickerAndStatic();

	


	// Inherited via BasePPAP
	void DrawProperties() override;
	void SceneDraw() override;
	void InitializeEffect(const std::string& vertex, const std::string& fragment) override;

	
	void SetShaderUniforms() override;
	FrameBuffer* chromaticFramebuffer;
private: 
	float effectAmount = 10;

	// Inherited via SinglePassEffect
	//void OnApplyEffect(FrameBuffer* sceneBuffer) override;
};

