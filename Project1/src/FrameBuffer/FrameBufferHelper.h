#pragma once
#include "../Renderer.h"
enum class FramebufferTextureFormat
{
	NONE = 0,

	//Color
	RGBA8,

	//Depth/Stencil
	DEPTH24STENCIL8,

	//Default
	DEPTH = DEPTH24STENCIL8

};


static bool IsDepthFormat(FramebufferTextureFormat format)
{
	switch (format)
	{
	case FramebufferTextureFormat::DEPTH24STENCIL8: return true;
		break;
	}
	return false;
}


static GLenum TextureTarget(bool multiSampled)
{
	return multiSampled ? GL_TEXTURE_2D_MULTISAMPLE : GL_TEXTURE_2D;
}

static void CreateTextures(bool multiSample, uint32_t* outID, uint32_t count)
{

	GLCALL(glCreateTextures(TextureTarget(multiSample), count, outID));
}


static void BindTexture(bool multiSampled, uint32_t id)
{
	GLCALL(glBindTexture(TextureTarget(multiSampled), id));
}


static void AttachColorTexture(uint32_t id, int samples, GLenum format, uint32_t width, uint32_t height, int index)
{
	bool multiSampled = samples > 1;

	if (multiSampled)
	{
		GLCALL(glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, samples, format, width, height, index));
	}
	else
	{
		GLCALL(glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr));

		//GLCALL(glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_FLOAT, nullptr));

		GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
		GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));


		GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE));
		GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
		GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

	}

	GLCALL(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + index, TextureTarget(multiSampled), id, 0));
}


static void AttachDepthTexture(uint32_t id, int samples, GLenum format, GLenum attachmentType, uint32_t width, uint32_t height)
{
	bool multiSampled = samples > 1;

	if (multiSampled)
	{
		GLCALL(glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, samples, format, width, height, GL_FALSE));
	}
	else
	{
		GLCALL(glTexStorage2D(GL_TEXTURE_2D, 1, format, width, height));

		GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
		GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));


		GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE));
		GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
		GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

	}

	GLCALL(glFramebufferTexture2D(GL_FRAMEBUFFER, attachmentType, TextureTarget(multiSampled), id, 0));
}