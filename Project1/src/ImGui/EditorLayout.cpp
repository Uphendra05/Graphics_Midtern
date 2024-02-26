#include "EditorLayout.h"
#include "../ApplicationRenderer.h"

EditorLayout& EditorLayout::GetInstance()
{
    static EditorLayout editorInstance;

    return editorInstance;
}

Object* EditorLayout::GetCurrentSelectedObject()
{
    return currentSelectedObject;
}



void EditorLayout::InitializeEditors()
{
    m_HierarchyPanel = new Heirachy();
    inspectorPanel = new Inspector();
    windowDockingPanel = new WindowDockingPanel();
    sceneViewportPanel = new ViewportPanel();

    sceneViewportPanel->frameBuffer = applicationRenderer->sceneViewframeBuffer;
    sceneViewportPanel->viewporCam = applicationRenderer->sceneCamera;

    gameviewportPanel = new GameViewportPanel();
    toolPanel = new ToolPanel();
    toolPanel->isApplicationPlayMode = &applicationRenderer->isPlayMode;

    gameviewportPanel->frameBuff = applicationRenderer->gameframeBuffer;
    gameviewportPanel->resolution = ImVec2(1920, 1080);
}

void EditorLayout::SetSelectedObjects(std::vector<Object*> objects)
{
    if (!selectedObjectsList.empty())
    {
        SetSelectedObjectsEnable(false);
    }

    selectedObjectsList.clear();

    selectedObjectsList = objects;

    SetSelectedObjectsEnable(true);

}

void EditorLayout::SetSelectedObjectsEnable(bool isEnable)
{
    for (Object* object:  selectedObjectsList)
    {
        object->isEnabled = isEnable;
    }
}

bool EditorLayout::isHovered()
{
    return sceneViewportPanel->isHovered;
}

std::vector<Object*> EditorLayout::GetSelectedObjects()
{
    return selectedObjectsList;
}
