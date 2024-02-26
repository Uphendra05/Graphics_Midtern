#pragma once
#include "../Shader.h"
#include "../Object.h"
#include "../FrameBuffer/FrameBuffer.h"



class BasePPAP : public Object
{

public:
	

	int effectOrder = 0;
	std::string name = "baseeffect";

	// Inherited via Object
	virtual void DrawProperties() = 0;
	virtual void SceneDraw() = 0;

	virtual void OnApplyEffect(FrameBuffer* sceneBuffer) = 0;

	

};

