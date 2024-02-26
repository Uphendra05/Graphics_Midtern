#include "ChromaticAbber.h"
#include"../Time.h"
#include "../Renderer.h"
#include "../GraphicsRender.h"

ChromaticAbber::ChromaticAbber()
{
	name = "Chromatic";
	

	InitializeEffect("Shaders/Chromatic.vert", "Shaders/Chromatic.frag");

}

ChromaticAbber::ChromaticAbber(float width, float height)
{
	name = "Chromatic";

	framebufferWidthAndHeight.x = width;
	framebufferWidthAndHeight.y = height;

	InitializeEffect("Shaders/Chromatic.vert", "Shaders/Chromatic.frag");

}

ChromaticAbber::~ChromaticAbber()
{
}





void ChromaticAbber::DrawProperties()
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
		ImGui::InputFloat("###amount", &aberrationValue);
		ImGui::TreePop();
	}

}

void ChromaticAbber::SceneDraw()
{
}

void ChromaticAbber::InitializeEffect(const std::string& vertex, const std::string& fragment)
{
	shader = new Shader(vertex.c_str(), fragment.c_str());

	FrameBufferSpecs specification;

	specification.width = framebufferWidthAndHeight.x;
	specification.height = framebufferWidthAndHeight.y;

	specification.attachments = { FramebufferTextureFormat::RGBA8, FramebufferTextureFormat::DEPTH };

	singlepassFramebuffer = new FrameBuffer(specification);

}

void ChromaticAbber::SetShaderUniforms()
{
	shader->setInt("sceneTexture", 0);  // Scene texture from framebuffer
	shader->setFloat("aberration", aberrationValue);   // abreation
	shader->setFloat("time", time);   // abreation
}


