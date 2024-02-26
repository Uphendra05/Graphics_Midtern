#pragma once
#include "BaseTexture.h"
#include "../FrameBuffer/FrameBuffer.h"
#include "../FrameBuffer/FrameBufferHelper.h"
class RenderTexture : public BaseTexture
{
public: 

	RenderTexture() = default;

	RenderTexture(FrameBufferSpecs framebufferSpec);
	~RenderTexture();

	// Inherited via BaseTexture
	void Bind() override;
	void Unbind() override;
	void SetTextureSlot(int place) override;
	void DrawProperties() override;
	void SceneDraw() override;

	void CreateRenderTexture(FrameBufferSpecs framebufferSpec);


	FrameBuffer* frameBuffer = nullptr;
};

