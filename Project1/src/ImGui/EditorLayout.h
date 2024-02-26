#pragma once

#include "../Object.h"
#include <vector>
#include "Heirachy.h"
#include "Inspector.h"
#include "WindowDockingPanel.h"
#include "ViewportPanel.h"
#include "ToolPanel.h"
#include "GameViewportPanel.h"

class ApplicationRenderer;
class EditorLayout
{
public :
	static EditorLayout& GetInstance();

	Object* GetCurrentSelectedObject();


	void InitializeEditors();

	void SetSelectedObjects(std::vector<Object*> objects);
	void SetSelectedObjectsEnable(bool isEnable);

	bool isHovered();

	std::vector<Object*> GetSelectedObjects();
	

	ApplicationRenderer* applicationRenderer;
private:

	Heirachy* m_HierarchyPanel;
	Inspector* inspectorPanel;
	WindowDockingPanel* windowDockingPanel;
	ViewportPanel* sceneViewportPanel;
	ToolPanel* toolPanel;
	GameViewportPanel* gameviewportPanel;

	Object* currentSelectedObject = nullptr;

	std::vector<Object*> selectedObjectsList;

};

