#include"ApplicationRenderer.h"
#include "Threading/SoftBodyThread.h"

void StartThreadSumma()
{
   
    
    double currentTime = glfwGetTime();
    double lastTime = currentTime;
    double deltaTime = 0.0f;

    double timeStep = 0.0f;

    while (true)
    {
        std::cout << "Thread Started :" <<  std::endl;
        currentTime = glfwGetTime();
        deltaTime = currentTime - lastTime;
        lastTime = currentTime;

        
            Time::GetInstance().SetCurrentTime(glfwGetTime());

            PhysicsEngine::GetInstance().UpdateVerlet(deltaTime);

            std::cout << "DeltaTime :" << deltaTime << std::endl;

    }
    
        

   
    
}

SoftBodyThread* sbThread = sbInfo;

ApplicationRenderer::ApplicationRenderer()
{
    sceneCamera = new Camera();

    gameScenecamera = new Camera();
    gameScenecamera->name = "GameScene Camera";

    renderTextureCamera = new Camera();
    renderTextureCamera->name = "RenderTexture Camera";
}

ApplicationRenderer::~ApplicationRenderer()
{

}



void ApplicationRenderer::WindowInitialize(int width, int height, std::string windowName)
{
    windowWidth = width;
    windowHeight = height;
    lastX = windowWidth / 2.0f;
    lastY = windowHeight / 2.0f;

    glfwInit();



    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    window = glfwCreateWindow(width, height, windowName.c_str(), NULL, NULL);

    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return;
    }
    glfwMakeContextCurrent(window);
    glfwSetWindowUserPointer(window, this);
    glfwSetFramebufferSizeCallback(window, [](GLFWwindow* w, int x, int y)
        {
            static_cast<ApplicationRenderer*>(glfwGetWindowUserPointer(w))->SetViewPort(w, x, y);
        });

    glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
        {
            static_cast<ApplicationRenderer*>(glfwGetWindowUserPointer(window))->KeyCallBack(window, key, scancode, action, mods);
        });


    glfwSetCursorPosCallback(window, [](GLFWwindow* window, double xposIn, double yposIn)
        {
            static_cast<ApplicationRenderer*>(glfwGetWindowUserPointer(window))->MouseCallBack(window, xposIn, yposIn);
        });

    glfwSetScrollCallback(window, [](GLFWwindow* window, double xoffset, double yoffset)
        {
            static_cast<ApplicationRenderer*>(glfwGetWindowUserPointer(window))->MouseScroll(window, xoffset, yoffset);
        });



    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.FontGlobalScale = 2.0f;
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(this->window, true);
    ImGui_ImplOpenGL3_Init("#version 450");

    //Init GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return;
    }

    // Query and print OpenGL version
    const GLubyte* version = glGetString(GL_VERSION);
    if (version) {
        std::cout << "OpenGL Version: " << version << std::endl;
    }
    else
    {
        std::cerr << "Failed to retrieve OpenGL version\n";

    }


    FrameBufferSpecs specs;

    specs.width = windowWidth;
    specs.height = windowHeight;
    specs.attachments = { FramebufferTextureFormat::RGBA8, FramebufferTextureFormat::DEPTH };


    sceneViewframeBuffer = new FrameBuffer(specs);

    gameframeBuffer = new FrameBuffer(specs);

    EditorLayout::GetInstance().applicationRenderer = this;


    InitializeShaders();

    GraphicsRender::GetInstance().InitializeGraphics();

    DebugModels::GetInstance().defaultCube = new Model("Models/DefaultCube/DefaultCube.fbx", false, true);
    DebugModels::GetInstance().defaultSphere = new Model("Models/DefaultSphere/DefaultSphere.fbx", false, true);
    DebugModels::GetInstance().defaultQuad = new Model("Models/DefaultQuad/DefaultQuad.fbx", false, true);

    InitializeSkybox();

    GraphicsRender::GetInstance().SetCamera(sceneCamera);

    sceneCamera->InitializeCamera(CameraType::PERSPECTIVE, 45.0f, 0.1f, 100.0f);
    sceneCamera->transform.position = glm::vec3(0, 0, -1.0f);

    gameScenecamera->InitializeCamera(CameraType::PERSPECTIVE, 45.0f, 0.1f, 100.0f);
    gameScenecamera->transform.position = glm::vec3(0, 0, -1.0f);

    renderTextureCamera->InitializeCamera(CameraType::PERSPECTIVE, 45.0f, 0.1f, 100.0f);
    renderTextureCamera->transform.position = glm::vec3(5, 0, 0);

    renderTextureCamera->IntializeRenderTexture(specs);
    // renderTextureCamera->IntializeRenderTexture(new RenderTexture());

    isImguiPanelsEnable = true;
}

void ApplicationRenderer::InitializeShaders()
{
    defaultShader = new Shader("Shaders/DefaultShader_Vertex.vert", "Shaders/DefaultShader_Fragment.frag");
    solidColorShader = new Shader("Shaders/SolidColor_Vertex.vert", "Shaders/SolidColor_Fragment.frag", SOLID);
    stencilShader = new Shader("Shaders/StencilOutline.vert", "Shaders/StencilOutline.frag");
    //ScrollShader = new Shader("Shaders/ScrollTexture.vert", "Shaders/ScrollTexture.frag");

    alphaBlendShader = new Shader("Shaders/DefaultShader_Vertex.vert", "Shaders/DefaultShader_Fragment.frag", ALPHA_BLEND);
    alphaBlendShader->blendMode = ALPHA_BLEND;

    alphaCutoutShader = new Shader("Shaders/DefaultShader_Vertex.vert", "Shaders/DefaultShader_Fragment.frag", ALPHA_CUTOUT);
    alphaCutoutShader->blendMode = ALPHA_CUTOUT;

    skyboxShader = new Shader("Shaders/SkyboxShader.vert", "Shaders/SkyboxShader.frag");
    skyboxShader->modelUniform = false;

    GraphicsRender::GetInstance().defaultShader = defaultShader;
    GraphicsRender::GetInstance().solidColorShader = solidColorShader;
    GraphicsRender::GetInstance().stencilShader = stencilShader;



}

void ApplicationRenderer::InitializeSkybox()
{
    skyBoxModel = new Model("Models/DefaultCube/DefaultCube.fbx", false, true);
    skyBoxModel->meshes[0]->meshMaterial = new SkyboxMaterial();

    skyBoxMaterial = skyBoxModel->meshes[0]->meshMaterial->skyboxMaterial();

    std::vector<std::string> faces
    {
       ("Textures/skybox/right.jpg"),
       ("Textures/skybox/left.jpg"),
       ("Textures/skybox/top.jpg"),
       ("Textures/skybox/bottom.jpg"),
       ("Textures/skybox/front.jpg"),
       ("Textures/skybox/back.jpg")
    };

    skyBoxMaterial->skyBoxTexture->LoadTexture(faces);

    GraphicsRender::GetInstance().SkyBoxModel = skyBoxModel;
}



void ApplicationRenderer::Start()
{
   
   StartThreadForSoftBody(0.01f);

    sceneCamera->postprocessing->InitializePostProcessing();

    gameScenecamera->postprocessing->InitializePostProcessing();

    Model* floor = new Model((char*)"Models/Floor/Floor.fbx");
    floor->transform.SetRotation(glm::vec3(90, 0, 0));
    floor->transform.SetPosition(glm::vec3(0, -2, 0));

    Model* floor2 = new Model(*floor);
    floor2->transform.SetRotation(glm::vec3(90, 0, 0));
    floor2->transform.SetPosition(glm::vec3(0, 2, 0));


    Model* floor3 = new Model(*floor);

    floor3->transform.SetPosition(glm::vec3(-2, 0, 0));
    Model* floor4 = new Model(*floor);
    floor4->transform.SetPosition(glm::vec3(2, 0, 0));
    floor4->meshes[0]->meshMaterial->material()->useMaskTexture = false;
    floor4->meshes[0]->meshMaterial->material()->SetBaseColor(glm::vec4(1, 1, 1, 0.5f));





    Model* directionLightModel = new Model("Models/DefaultSphere/Sphere_1_unit_Radius.ply", false, true);
    directionLightModel->transform.SetScale(glm::vec3(0.5f));
    // Model* spotlight = new Model(*Sphere);
     //spotlight->transform.SetPosition(glm::vec3(-2.0f, 0.0f, -3.0f));

    Light* directionLight = new Light();
    directionLight->Initialize(LightType::DIRECTION_LIGHT, 1);
    directionLight->SetAmbientColor(glm::vec4(0.2f, 0.2f, 0.2f, 1.0f));

    directionLight->SetColor(glm::vec4(1, 1, 1, 1.0f));
    directionLight->SetAttenuation(1, 1, 0.01f);
    directionLight->SetInnerAndOuterCutoffAngle(11, 12);

    directionLight->transform.SetRotation(glm::vec3(0, 0, 5));
    directionLight->transform.SetPosition(glm::vec3(0, 0, 5));


    Model* plant = new Model("Models/Plant.fbm/Plant.fbx");
    Texture* plantAlphaTexture = new Texture();

    Model* quadWithTexture = new Model("Models/DefaultQuad/DefaultQuad.fbx");
    quadWithTexture->transform.SetPosition(glm::vec3(5, 0, 0));
    quadWithTexture->meshes[0]->meshMaterial->material()->diffuseTexture = renderTextureCamera->renderTexture;

    Model* window = new Model("Models/Window/Window.obj");
    window->transform.SetPosition(glm::vec3(-5, 0, 0));
    window->transform.SetRotation(glm::vec3(90, 0, 0));
    window->meshes[0]->meshMaterial->material()->useMaskTexture = false;
    window->meshes[0]->meshMaterial->material()->SetBaseColor(glm::vec4(1, 1, 1, 0.5f));



    GraphicsRender::GetInstance().AddModelAndShader(plant, alphaCutoutShader);
    GraphicsRender::GetInstance().AddModelAndShader(quadWithTexture, alphaCutoutShader);
    GraphicsRender::GetInstance().AddModelAndShader(floor, defaultShader);
    GraphicsRender::GetInstance().AddModelAndShader(floor2, defaultShader);
    GraphicsRender::GetInstance().AddModelAndShader(floor3, defaultShader);
    GraphicsRender::GetInstance().AddModelAndShader(floor4, alphaBlendShader);
    GraphicsRender::GetInstance().AddModelAndShader(window, alphaBlendShader);

   


    SoftBodyObjs* softBodyTest1 = new SoftBodyObjs();
    softBodyTest1->LoadModel("Models/Plane/Plane.ply");
    softBodyTest1->name = "MY PLANE";

    softBodyTest1->transform.SetPosition(glm::vec3(0, 1, 0));
    softBodyTest1->transform.SetScale(glm::vec3(5));
    GraphicsRender::GetInstance().AddModelAndShader(softBodyTest1, defaultShader);
    softBodyTest1->InitializeSoftBody();

   


    //LightRenderer
    //LightManager::GetInstance().AddLight(directionLight);
   // lightManager.AddLight(directionLight);
  //  lightManager.AddNewLight(spot);
  //  lightManager.SetUniforms(defaultShader->ID);
  //  PhysicsObject* SpherePhyiscs = new PhysicsObject(Sphere);
  //  SpherePhyiscs->Initialize(false, true, DYNAMIC);

  //  PhysicsEngine.AddPhysicsObjects(SpherePhyiscs);

    sbThread->bRun = true;
   
}

void ApplicationRenderer::PreRender()
{
    projection = sceneCamera->GetProjectionMatrix();

    view = sceneCamera->GetViewMatrix();

    skyBoxView = glm::mat4(glm::mat3(sceneCamera->GetViewMatrix()));


    defaultShader->Bind();
    LightManager::GetInstance().UpdateUniformValuesToShader(defaultShader);

    defaultShader->setMat4("projection", projection);
    defaultShader->setMat4("view", view);
    defaultShader->setVec3("viewPos", sceneCamera->transform.position.x, sceneCamera->transform.position.y, sceneCamera->transform.position.z);
    defaultShader->setFloat("time", scrollTime);
    defaultShader->setBool("isDepthBuffer", false);

    alphaBlendShader->Bind();
    LightManager::GetInstance().UpdateUniformValuesToShader(alphaBlendShader);
    alphaBlendShader->setMat4("projection", projection);
    alphaBlendShader->setMat4("view", view);
    alphaBlendShader->setVec3("viewPos", sceneCamera->transform.position.x, sceneCamera->transform.position.y, sceneCamera->transform.position.z);
    alphaBlendShader->setFloat("time", scrollTime);
    alphaBlendShader->setBool("isDepthBuffer", false);

    alphaCutoutShader->Bind();
    LightManager::GetInstance().UpdateUniformValuesToShader(alphaCutoutShader);
    alphaCutoutShader->setMat4("projection", projection);
    alphaCutoutShader->setMat4("view", view);
    alphaCutoutShader->setVec3("viewPos", sceneCamera->transform.position.x, sceneCamera->transform.position.y, sceneCamera->transform.position.z);
    alphaCutoutShader->setFloat("time", scrollTime);
    alphaCutoutShader->setBool("isDepthBuffer", false);

    solidColorShader->Bind();
    solidColorShader->setMat4("projection", projection);
    solidColorShader->setMat4("view", view);

    stencilShader->Bind();
    stencilShader->setMat4("projection", projection);
    stencilShader->setMat4("view", view);

    glDepthFunc(GL_LEQUAL);
    skyboxShader->Bind();
    skyboxShader->setMat4("projection", projection);
    skyboxShader->setMat4("view", skyBoxView);

    GraphicsRender::GetInstance().SkyBoxModel->Draw(*skyboxShader);
    glDepthFunc(GL_LESS);


    /* ScrollShader->Bind();
       ScrollShader->setMat4("ProjectionMatrix", _projection);*/

}



void ApplicationRenderer::Render()
{

    Start();

    EditorLayout::GetInstance().InitializeEditors();

    Time::GetInstance().lastFrame = glfwGetTime();
    // glEnable(GL_BLEND);
   //  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    while (!glfwWindowShouldClose(window))
    {

        Time::GetInstance().SetCurrentTime(glfwGetTime());


        // scrollTime += Time::GetInstance().deltaTime;

       
        //CustomThread<void(*)()> threader(EngineGameLoop);
           //CustomThread<decltype(&ApplicationRenderer::EngineGameLoop) > gameLoopThread(&ApplicationRenderer::EngineGameLoop);
           //gameLoopThread.StartSingleThread();

        EngineGameLoop();

        EngineGraphicsRender();


        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();
}


void ApplicationRenderer::EngineGraphicsRender()
{

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    if (isImguiPanelsEnable)
    {
        PanelManager::GetInstance().Update((float)windowWidth, (float)windowHeight);
    }

    ImGui::Render();


    /*sceneViewframeBuffer->Bind();

    GraphicsRender::GetInstance().Clear();
    PreRender();
    GraphicsRender::GetInstance().Draw();

    sceneViewframeBuffer->Unbind();*/
    RenderForCamera(sceneCamera, sceneViewframeBuffer);


    /*  RenderForCamera(gameScenecamera, gameframeBuffer);

      RenderForCamera(renderTextureCamera, renderTextureCamera->renderTexture->framebuffer);*/


    for (Camera* sceneCamera : CameraManager::GetInstance().GetCameras())
    {
        if (sceneCamera->renderTexture == nullptr)
        {
            RenderForCamera(sceneCamera, gameframeBuffer);                  // GAME SCENE CAMERA

          
        }
        else
        {
            RenderForCamera(sceneCamera, sceneCamera->renderTexture->frameBuffer);
        }

    }

    //gameframeBuffer->Bind();
    //GraphicsRender::GetInstance().Clear();
    //PreRender();
    //GraphicsRender::GetInstance().Draw();

    //gameframeBuffer->Unbind();

    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

}

void ApplicationRenderer::EngineGameLoop()
{
    ProcessInput(window);

    if (isPlayMode)
    {
        EntityManager::GetInstance().Update(Time::GetInstance().deltaTime);
    }

    PostRender();
}
void ApplicationRenderer::RenderForCamera(Camera* sceneCamera, FrameBuffer* framebuffer)
{

    /*  sceneViewframeBuffer->Bind();

      GraphicsRender::GetInstance().Clear();
      PreRender();
      GraphicsRender::GetInstance().Draw();*/


    framebuffer->Bind();

    GraphicsRender::GetInstance().Clear();

    projection = sceneCamera->GetProjectionMatrix();

    view = sceneCamera->GetViewMatrix();

    skyBoxView = glm::mat4(glm::mat3(sceneCamera->GetViewMatrix()));


    defaultShader->Bind();
    LightManager::GetInstance().UpdateUniformValuesToShader(defaultShader);

    defaultShader->setMat4("projection", projection);
    defaultShader->setMat4("view", view);
    defaultShader->setVec3("viewPos", sceneCamera->transform.position.x, sceneCamera->transform.position.y, sceneCamera->transform.position.z);
    defaultShader->setFloat("time", scrollTime);
    defaultShader->setBool("isDepthBuffer", false);

    alphaBlendShader->Bind();
    LightManager::GetInstance().UpdateUniformValuesToShader(alphaBlendShader);
    alphaBlendShader->setMat4("projection", projection);
    alphaBlendShader->setMat4("view", view);
    alphaBlendShader->setVec3("viewPos", sceneCamera->transform.position.x, sceneCamera->transform.position.y, sceneCamera->transform.position.z);
    alphaBlendShader->setFloat("time", scrollTime);
    alphaBlendShader->setBool("isDepthBuffer", false);

    alphaCutoutShader->Bind();
    LightManager::GetInstance().UpdateUniformValuesToShader(alphaCutoutShader);
    alphaCutoutShader->setMat4("projection", projection);
    alphaCutoutShader->setMat4("view", view);
    alphaCutoutShader->setVec3("viewPos", sceneCamera->transform.position.x, sceneCamera->transform.position.y, sceneCamera->transform.position.z);
    alphaCutoutShader->setFloat("time", scrollTime);
    alphaCutoutShader->setBool("isDepthBuffer", false);

    solidColorShader->Bind();
    solidColorShader->setMat4("projection", projection);
    solidColorShader->setMat4("view", view);

    stencilShader->Bind();
    stencilShader->setMat4("projection", projection);
    stencilShader->setMat4("view", view);

    glDepthFunc(GL_LEQUAL);
    skyboxShader->Bind();
    skyboxShader->setMat4("projection", projection);
    skyboxShader->setMat4("view", skyBoxView);

    GraphicsRender::GetInstance().SkyBoxModel->Draw(*skyboxShader);
    glDepthFunc(GL_LESS);


    /* ScrollShader->Bind();
       ScrollShader->setMat4("ProjectionMatrix", _projection);*/

    GraphicsRender::GetInstance().Draw();

    framebuffer->Unbind();

    if (sceneCamera->isPostprocessing)
    {
        // if (camera->postprocessing.isPostProccesingEnabled)
        {
            sceneCamera->postprocessing->ApplyPostprocessing(framebuffer);
        }
    }

}
void ApplicationRenderer::PostRender()
{
    
        PhysicsEngine::GetInstance().Update(Time::GetInstance().deltaTime);
}

void ApplicationRenderer::Clear()
{
    GLCALL(glClearColor(0.1f, 0.1f, 0.1f, 0.1f));
    GLCALL(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT));
    //glStencilMask(0x00);
}

void ApplicationRenderer::ProcessInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    float cameraSpeed = 25;

    if (EditorLayout::GetInstance().isHovered())
    {
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        {
            sceneCamera->ProcessKeyboard(FORWARD, Time::GetInstance().deltaTime * cameraSpeed);
        }
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        {
            sceneCamera->ProcessKeyboard(BACKWARD, Time::GetInstance().deltaTime * cameraSpeed);
        }

        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        {
            sceneCamera->ProcessKeyboard(LEFT, Time::GetInstance().deltaTime * cameraSpeed);

        }
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        {
            sceneCamera->ProcessKeyboard(RIGHT, Time::GetInstance().deltaTime * cameraSpeed);

        }
    }

}


void ApplicationRenderer::SetViewPort(GLFWwindow* window, int width, int height)
{
    //   glViewport(0, 0, width, height);
}

void ApplicationRenderer::KeyCallBack(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_V && action == GLFW_PRESS)
    {


        std::cout << "V pressed" << std::endl;

        std::vector<Model*> listOfModels = GraphicsRender::GetInstance().GetModelList();



        selectedModelCount++;

        if (selectedModelCount > listOfModels.size() - 1)
        {
            selectedModelCount = 0;
        }


        GraphicsRender::GetInstance().selectedModel = listOfModels[selectedModelCount];


    }

    if (key == GLFW_KEY_F && action == GLFW_PRESS)
    {
        gameScenecamera->transform.position = sceneCamera->transform.position;
        gameScenecamera->transform.quaternionRotation = sceneCamera->transform.quaternionRotation;
    }


    if (action == GLFW_PRESS)
    {
        InputManager::GetInstance().OnKeyPressed(key);
    }
    else if (action == GLFW_RELEASE)
    {
        InputManager::GetInstance().OnKeyReleased(key);
    }
    else if (action == GLFW_REPEAT)
    {
        InputManager::GetInstance().OnKeyHeld(key);
    }

}

void ApplicationRenderer::MouseCallBack(GLFWwindow* window, double xposIn, double yposIn)
{

    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    if (firstMouse)
    {

    }

    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;

    lastX = xpos;
    lastY = ypos;

    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS && EditorLayout::GetInstance().isHovered())
    {
        sceneCamera->ProcessMouseMovement(xoffset, yoffset);
    }
}

void ApplicationRenderer::MouseScroll(GLFWwindow* window, double xoffset, double yoffset)
{
    sceneCamera->ProcessMouseScroll(static_cast<float>(yoffset));
}
