#pragma once
#include "FrameBufferHelper.h"



struct FramebufferTextureSpecification
{
	FramebufferTextureSpecification() = default;
	FramebufferTextureSpecification(FramebufferTextureFormat format)
		:textureFormat(format)
	{
	}

	FramebufferTextureFormat textureFormat = FramebufferTextureFormat::NONE;
};

struct FramebufferAttachmentSpecification
{
	FramebufferAttachmentSpecification() = default;
	FramebufferAttachmentSpecification(std::initializer_list<FramebufferTextureSpecification> attachments)
		: Attachments(attachments)
	{
	}

	std::vector<FramebufferTextureSpecification> Attachments;
};

struct FrameBufferSpecs
{
	uint32_t  width;
	uint32_t  height;
	uint32_t  samples = 1;
	FramebufferAttachmentSpecification attachments;
	bool swapChainTarget = false;

};
class FrameBuffer
{
public:

	FrameBuffer(const FrameBufferSpecs& specs);
	~FrameBuffer();

	void GenerateFrameBuffer();

	void Bind();
	void Unbind();

	void Resize(uint32_t width, uint32_t height);

	uint32_t& GetColorAttachmentID(int index = 0);
	unsigned int& GetRendererID();
	uint32_t& GetDepthAttachementID();
	FrameBufferSpecs m_BufferSpecs;


private:

	unsigned int m_RendererID = 0;

	std::vector<FramebufferTextureSpecification> colorAttachmentSpecifications;
	FramebufferTextureSpecification depthAttachmentSpec;

	std::vector<uint32_t> colorAttachmentsID;
	uint32_t depthAttachmentID = 0;


};

