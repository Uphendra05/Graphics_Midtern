#include "StaticEffect.h"

StaticEffect::StaticEffect()
{
	name = "Static";

	InitializeEffect("Shaders/Static.vert", "Shaders/Static.frag");
}

StaticEffect::StaticEffect(float width, float height)
{
	name = "Static";
	
	framebufferWidthAndHeight.x = width;
	framebufferWidthAndHeight.y = height;

	InitializeEffect("Shaders/Static.vert", "Shaders/Static.frag");
}

void StaticEffect::InitializeEffect(const std::string& vertex, const std::string& fragment)
{
	shader = new Shader(vertex.c_str(), fragment.c_str());

	FrameBufferSpecs specification;

	specification.width = framebufferWidthAndHeight.x;
	specification.height = framebufferWidthAndHeight.y;

	specification.attachments = { FramebufferTextureFormat::RGBA8, FramebufferTextureFormat::DEPTH };

	singlepassFramebuffer = new FrameBuffer(specification);
}

void StaticEffect::SetShaderUniforms()
{

	shader->setInt("sceneTexture", 0);  
	shader->setFloat("intensity", intensity);
	shader->setFloat("time", time);

}

void StaticEffect::DrawProperties()
{
	SinglePassEffect::DrawProperties();

	if (isEnabled)
	{
		if (!ImGui::TreeNodeEx("properties", ImGuiTreeNodeFlags_DefaultOpen))
		{
			return;
		}

		//ImGui::Checkbox("IsFlickering", &isFlicker);

		ImGui::TreePop();
	}
}

void StaticEffect::SceneDraw()
{
}
