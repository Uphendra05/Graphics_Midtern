#pragma once
#include "../ImGui/BasePanel.h"
#include "../FrameBuffer/FrameBuffer.h"

class GameViewportPanel : public BasePanel
{

public:

	// Inherited via BasePanel
	void OnRender(float windowWidth, float windowHeight) override;

	FrameBuffer* frameBuff = nullptr;



	ImVec2 viewportSize;
	ImVec2 resolution;
	ImVec4 windowColor = ImVec4(0.1f, 0.1f, 0.1f, 1.0f);


};

