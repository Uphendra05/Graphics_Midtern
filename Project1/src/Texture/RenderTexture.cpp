#include "RenderTexture.h"

RenderTexture::RenderTexture(FrameBufferSpecs framebufferSpec)
{
	frameBuffer = new FrameBuffer(framebufferSpec);
}

	

RenderTexture::~RenderTexture()
{
}

void RenderTexture::Bind()
{
	GLCALL(glBindTexture(GL_TEXTURE_2D, frameBuffer->GetColorAttachmentID()));
}

void RenderTexture::Unbind()
{
	GLCALL(glBindTexture(GL_TEXTURE_2D, 0));
}

void RenderTexture::SetTextureSlot(int place)
{
	GLCALL(glActiveTexture(GL_TEXTURE0 + place));
}

void RenderTexture::DrawProperties()
{
}

void RenderTexture::SceneDraw()
{
}

void RenderTexture::CreateRenderTexture(FrameBufferSpecs framebufferSpec)
{
	frameBuffer = new FrameBuffer(framebufferSpec);
}
