#pragma once
#include "Renderer.h"
class RenderQuad
{
  public:
	  static RenderQuad& GetInstance();
   unsigned int quadVAO = 0;
   unsigned int quadVBO;
   void RenderQuadForPostProcess();
   
};

