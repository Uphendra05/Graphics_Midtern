#include "FlickerAndStatic.h"
#include"../Time.h"
#include "../Renderer.h"
#include "../GraphicsRender.h"

FlickerAndStatic::FlickerAndStatic()
{
	name = "Chromatic";
	

	InitializeEffect("Shaders/FlickerAndStatic.vert", "Shaders/FlickerAndStatic.frag");

}

FlickerAndStatic::FlickerAndStatic(float width, float height)
{
	name = "Chromatic";

	framebufferWidthAndHeight.x = width;
	framebufferWidthAndHeight.y = height;

	InitializeEffect("Shaders/FlickerAndStatic.vert", "Shaders/FlickerAndStatic.frag");

}

FlickerAndStatic::~FlickerAndStatic()
{
}





void FlickerAndStatic::DrawProperties()
{
	SinglePassEffect::DrawProperties();

	if (isEnabled)
	{
		if (!ImGui::TreeNodeEx("properties", ImGuiTreeNodeFlags_DefaultOpen))
		{
			return;
		}
		ImGui::Text("Aberration Amount");
		ImGui::SameLine();
		ImGui::InputFloat("###amount", &effectAmount);
		ImGui::TreePop();
	}

}

void FlickerAndStatic::SceneDraw()
{
}

void FlickerAndStatic::InitializeEffect(const std::string& vertex, const std::string& fragment)
{
	shader = new Shader(vertex.c_str(), fragment.c_str());

	FrameBufferSpecs specification;

	specification.width = framebufferWidthAndHeight.x;
	specification.height = framebufferWidthAndHeight.y;

	specification.attachments = { FramebufferTextureFormat::RGBA8, FramebufferTextureFormat::DEPTH };

	singlepassFramebuffer = new FrameBuffer(specification);

}

void FlickerAndStatic::SetShaderUniforms()
{
	shader->setInt("sceneTexture", 0);  // Scene texture from framebuffer
	shader->setFloat("aberration", effectAmount);   // abreation
	shader->setFloat("time", time);   // abreation
}


