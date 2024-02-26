#pragma once

#include "ChromaticAbber.h"
#include "NightVision.h"

class PostProcessing : public Object
{
public:

	PostProcessing();
	PostProcessing(const glm::vec2& cameraWidthAndHeight);
	~PostProcessing();

	void SetCameraWidthAndHeight(const glm::vec2& value);

	void InitializePostProcessing();

	void ApplyPostprocessing(FrameBuffer* framebuffer);

	void AddEffect(BasePPAP* effect);
	void RemoveEffect(BasePPAP* effect);
	bool isPostProccesingEnabled = false;

	// Inherited via Object
	void DrawProperties() override;

	void SceneDraw() override;

private:

	//void DrawEffectsProperties(BasePPAP& effects);

	std::vector<BasePPAP*> listOfeffects;

	ChromaticAbber* chromatic;
	NightVision* nightVision;
	

	Shader* finalShader;

	glm::vec2 cameraWidthAndHeight;
};

