#include "ViewportPanel.h"

void ViewportPanel::OnRender(float windowWidth, float windowHeight)
{
    if (!isPanelOpen)
    {
        return;
    }

    if (!ImGui::Begin("Scene View", &isPanelOpen) || !isEnable)
    {

        ImGui::End();       
        ImGui::PopStyleVar();
        return;

    }

    ImVec2 viewPortPanelSize = ImGui::GetContentRegionAvail();

    isHovered = ImGui::IsWindowHovered();

    if (viewportSize.x != viewPortPanelSize.x || viewportSize.y != viewPortPanelSize.y)
    {
        viewportSize = viewPortPanelSize;

        frameBuffer->Resize(viewportSize.x, viewportSize.y);
        viewporCam->Resize(viewportSize.x, viewportSize.y);
    }

    ImGui::Image((void*)frameBuffer->GetColorAttachmentID(), viewportSize, ImVec2{ 0,1 }, ImVec2{ 1,0 });

    ImGui::End();



}
