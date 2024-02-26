#include "CameraManager.h"

int CameraManager::CameraID = 0;

CameraManager& CameraManager::GetInstance()
{
    static CameraManager instance;
	return instance;
}

void CameraManager::AddCamera(Camera* sceneCamera)
{

	CameraID++;
	if (CameraID > 1)
	{
		listOfCameras.push_back(sceneCamera);

		if (sceneCamera->renderTexture == nullptr)
		{
			mainCamera = sceneCamera;
		}
	}

}

void CameraManager::RemoveCamera(Camera* sceneCamera)
{
	std::vector<Camera*> ::iterator it = std::remove(listOfCameras.begin(), listOfCameras.end(), sceneCamera);
	listOfCameras.erase(it, listOfCameras.end());
}

Camera* CameraManager::GetMainCamera()
{
	return nullptr;
}

std::vector<Camera*> CameraManager::GetCameras()
{
	return listOfCameras;
}
