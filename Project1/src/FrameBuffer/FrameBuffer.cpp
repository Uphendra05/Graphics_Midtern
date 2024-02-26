#include "FrameBuffer.h"

FrameBuffer::FrameBuffer(const FrameBufferSpecs& specs) : m_BufferSpecs(specs)
{
	for (FramebufferTextureSpecification spec : specs.attachments.Attachments)
	{
		if (!IsDepthFormat(spec.textureFormat))
		{
			colorAttachmentSpecifications.emplace_back(spec);
		}
		else
		{
			depthAttachmentSpec = spec;
		}
	}

	GenerateFrameBuffer();
}

FrameBuffer::~FrameBuffer()
{
	GLCALL(glDeleteFramebuffers(1, &m_RendererID));
	GLCALL(glDeleteTextures(colorAttachmentsID.size(), colorAttachmentsID.data()));
	GLCALL(glDeleteTextures(1, &depthAttachmentID));
}

void FrameBuffer::Bind()
{
	GLCALL(glBindFramebuffer(GL_FRAMEBUFFER, m_RendererID));
	GLCALL(glViewport(0, 0, m_BufferSpecs.width, m_BufferSpecs.height));
}

void FrameBuffer::Unbind()
{
	GLCALL(glBindFramebuffer(GL_FRAMEBUFFER, 0));

}



void FrameBuffer::GenerateFrameBuffer()
{

	if (m_RendererID != 0)
	{
		GLCALL(glDeleteFramebuffers(1, &m_RendererID));
		GLCALL(glDeleteTextures(colorAttachmentsID.size(), colorAttachmentsID.data()));
		GLCALL(glDeleteTextures(1, &depthAttachmentID));
	}
	
	GLCALL(glCreateFramebuffers(1, &m_RendererID));
	GLCALL(glBindFramebuffer(GL_FRAMEBUFFER, m_RendererID));

	bool multiSample = m_BufferSpecs.samples > 1;

	if (colorAttachmentSpecifications.size())
	{
		colorAttachmentsID.resize(colorAttachmentSpecifications.size());

		CreateTextures(multiSample, colorAttachmentsID.data(), colorAttachmentsID.size());


		for (size_t i = 0; i < colorAttachmentsID.size(); i++)
		{
			BindTexture(multiSample, colorAttachmentsID[i]);

			switch (colorAttachmentSpecifications[i].textureFormat)
			{
			case FramebufferTextureFormat::RGBA8:
				AttachColorTexture(colorAttachmentsID[i], m_BufferSpecs.samples,
					GL_RGBA8, m_BufferSpecs.width, m_BufferSpecs.height, i);
				break;
			}

		}

		if (depthAttachmentSpec.textureFormat != FramebufferTextureFormat::NONE)
		{
			CreateTextures(multiSample, &depthAttachmentID, 1);
			BindTexture(multiSample, depthAttachmentID);

			switch (depthAttachmentSpec.textureFormat)
			{
			case FramebufferTextureFormat::DEPTH24STENCIL8:
				AttachDepthTexture(depthAttachmentID, m_BufferSpecs.samples,
					GL_DEPTH24_STENCIL8, GL_DEPTH_STENCIL_ATTACHMENT, m_BufferSpecs.width, m_BufferSpecs.height);
				break;
			}
		}
	}

	if (colorAttachmentsID.size() > 1)
	{
		if (colorAttachmentsID.size() <= 4)
		{
			GLenum buffers[4] = {
				 GL_COLOR_ATTACHMENT0,
				 GL_COLOR_ATTACHMENT1,
				 GL_COLOR_ATTACHMENT2,
				 GL_COLOR_ATTACHMENT3 };

			GLCALL(glDrawBuffers(colorAttachmentsID.size(), buffers));

		}
		else if (colorAttachmentsID.empty())
		{
			//Only Depth-pass
			GLCALL(glDrawBuffer(GL_NONE));
		}
	}




	GLCALL(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE);

	GLCALL(glBindFramebuffer(GL_FRAMEBUFFER, 0));

}

void FrameBuffer::Resize(uint32_t width, uint32_t height)
{
	if (width == 0 || height == 0)
	{
		std::cout << "Error : Resize the framebuffers to " << width << " x " << height << std::endl;
		return;
	}

	m_BufferSpecs.width = width;
	m_BufferSpecs.height = height;

	GenerateFrameBuffer();
}

unsigned int& FrameBuffer::GetColorAttachmentID(int index)
{
	if (index < colorAttachmentsID.size());
	{

		return colorAttachmentsID[index];

	}
}

unsigned int& FrameBuffer::GetRendererID()
{
	return m_RendererID;
}

unsigned int& FrameBuffer::GetDepthAttachementID()
{
	return depthAttachmentID;
}
