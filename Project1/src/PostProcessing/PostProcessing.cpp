#include "PostProcessing.h"

PostProcessing::PostProcessing()
{
}

PostProcessing::PostProcessing(const glm::vec2& cameraWidthAndHeight)
{
	SetCameraWidthAndHeight(cameraWidthAndHeight);
}

PostProcessing::~PostProcessing()
{
}

void PostProcessing::SetCameraWidthAndHeight(const glm::vec2& value)
{
	cameraWidthAndHeight = value;
}

void PostProcessing::InitializePostProcessing()
{
	isPostProccesingEnabled = true;

	finalShader = new Shader("Shaders/FinalOutputShader.vert", "Shaders/FinalOutputShader.frag");

	flickerAndStatic = new FlickerAndStatic(cameraWidthAndHeight.x, cameraWidthAndHeight.y);
	flickerAndStatic->finalShader = finalShader;
	AddEffect(flickerAndStatic);

	staticEffect = new StaticEffect(cameraWidthAndHeight.x, cameraWidthAndHeight.y);
	staticEffect->finalShader = finalShader;
	AddEffect(staticEffect);

	//nightVision = new NightVision(cameraWidthAndHeight.x, cameraWidthAndHeight.y);
	//nightVision->finalShader = finalShader;
	//ddEffect(nightVision);

}

void PostProcessing::ApplyPostprocessing(FrameBuffer* framebuffer)
{
	if (!isPostProccesingEnabled) return;

	for (BasePPAP* effect : listOfeffects)
	{
		if (!effect->isEnabled) continue;

		effect->OnApplyEffect(framebuffer);
	}

}

void PostProcessing::AddEffect(BasePPAP* effect)
{
	listOfeffects.push_back(effect);
}

void PostProcessing::RemoveEffect(BasePPAP* effect)
{
	std::vector<BasePPAP*> ::iterator it = std::remove(listOfeffects.begin(), listOfeffects.end(), effect);

	listOfeffects.erase(it, listOfeffects.end());
}

void PostProcessing::DrawProperties()
{
}

void PostProcessing::SceneDraw()
{
}

//void PostProcessing::DrawEffectsProperties(BasePPAP& effects)
//{
//	ImGui::Checkbox(("###" + std::to_string(effects.ID)).c_str(), &effects.isEnabled);
//	ImGui::SameLine();
//	effects.DrawProperties();
//
//}
