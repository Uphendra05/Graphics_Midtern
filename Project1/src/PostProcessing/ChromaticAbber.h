#pragma once
#include "../PostProcessing/BasePPAP.h"
#include "../RenderQuad.h"
#include "SinglePassEffect.h"


class ChromaticAbber : public SinglePassEffect
{

public:

	ChromaticAbber();
	ChromaticAbber(float width, float height);
	~ChromaticAbber();

	


	// Inherited via BasePPAP
	void DrawProperties() override;
	void SceneDraw() override;
	void InitializeEffect(const std::string& vertex, const std::string& fragment) override;

	
	void SetShaderUniforms() override;
	FrameBuffer* chromaticFramebuffer;
private:
	float aberrationValue = 10;

	// Inherited via SinglePassEffect
	//void OnApplyEffect(FrameBuffer* sceneBuffer) override;
};

