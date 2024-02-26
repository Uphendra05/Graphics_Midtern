#pragma once
#include "Shader.h"
#include "Camera.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "Renderer.h"
#include "VertexArray.h"
#include  "model.h"
#include "material.h"
#include "Light.h"
#include "Transform.h"
#include"LightManager.h"
#include "Random.h"
#include "Physics/PhysicsEngine.h"
#include "Time.h"
#include "SkyboxMaterial.h"
#include "GraphicsRender.h"
#include "DebugModels.h"
#include "ImGui/PanelManager.h" 
#include "ImGui/EditorLayout.h"

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include "FrameBuffer/FrameBuffer.h"

#include "EntityManager/EntityManager.h"
#include "InputManager/InputManager.h"
#include "CameraManager/CameraManager.h"

class ApplicationRenderer
{
public:
	ApplicationRenderer();
	~ApplicationRenderer();

	static void SetViewPort(GLFWwindow* window, int width, int height);
	void KeyCallBack(GLFWwindow* window, int key, int scancode, int action, int mods);
	void MouseCallBack(GLFWwindow* window, double xposIn, double yposIn);
	void MouseScroll(GLFWwindow* window, double xoffset, double yoffset);
	
	void WindowInitialize(int width, int height,  std::string windowName ="Window");

	void InitializeShaders();
	void InitializeSkybox();
	
	void Start();
	void PreRender();
	void Render();
	void PostRender();
	void Clear();
	void SpaceStation();
	void ScreenTextureCycle();

	void ProcessInput(GLFWwindow* window);

	void EngineGraphicsRender();
	void EngineGameLoop();
	void RenderForCamera(Camera* sceneCamera, FrameBuffer* framebuffer);
	
	FrameBufferSpecs specis;
	FrameBuffer* sceneViewframeBuffer;
	FrameBuffer* gameframeBuffer;
	Camera* sceneCamera;
	Camera* gameScenecamera;

	//Screen Render Texture Cameras
	Camera* screenMidTextureCam;
	Camera* screenOneMidTextureCam;

	Camera* screenRightTextureCam;

	Camera* screenLeftTextureCam;


	bool isPlayMode = false;

	glm::mat4 projection;
	glm::mat4 view;
	glm::mat4 skyBoxView;
	int windowWidth;
	int  windowHeight;

private:
	GLFWwindow* window;
	
	std::vector<BaseTexture*> m_listOfScreenTextuers;

	GraphicsRender render;
	LightManager lightManager;

	Shader* defaultShader;
	Shader* solidColorShader;
	Shader* alphaBlendShader;
	Shader* alphaCutoutShader;

	Shader* stencilShader;
	Shader* skyboxShader;

	SkyboxMaterial* skyBoxMaterial;

	Model* skyBoxModel;

	Model* Screen_Right;
	Model* Screen_Left;

	PhysicsEngine PhysicsEngine;
	PanelManager* panelManager;

	 
	 int selectedModelCount = 0;
	 float waitSec = 5.0f;
	 float lastX;
	 float lastY;
	 float deltaTime;
	 double lastTime;
	 float lastFrame;

	 float scrollTime;

	 bool firstMouse;
	 bool isImguiPanelsEnable = false;

};

