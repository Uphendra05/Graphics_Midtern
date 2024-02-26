#pragma once
#include "BasePPAP.h"
#include "../RenderQuad.h"
#include "../FrameBuffer/FrameBuffer.h"
class SinglePassEffect : public BasePPAP
{
public:
	SinglePassEffect();

	virtual ~SinglePassEffect() {  };

	
	virtual void InitializeEffect(const std::string& vertex, const std::string& fragment) = 0;
	// Inherited via BaseEffect
	virtual void OnApplyEffect(FrameBuffer* frameBuffer);
	virtual void DrawProperties();
	virtual void SceneDraw();

	virtual void SetShaderUniforms() = 0;

	Shader* shader;
	Shader* finalShader;
	FrameBuffer* singlepassFramebuffer;
	glm::vec2 framebufferWidthAndHeight = { 1920,1080 };
	float time;


};

