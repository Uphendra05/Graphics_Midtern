#pragma once
#include "../FrameBuffer/FrameBuffer.h"
#include "BasePanel.h"
#include "../Camera.h"

class ViewportPanel : public BasePanel
{
public:
	 void OnRender(float windowWidth, float windowHeight) override;

	 FrameBuffer* frameBuffer = nullptr;

	 ImVec2 viewportSize;

	 Camera* viewporCam;

};

