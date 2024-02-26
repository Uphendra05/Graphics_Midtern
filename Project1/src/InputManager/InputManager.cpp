#include "InputManager.h"
#include "../Renderer.h"
InputManager::InputManager()
{
}

InputManager::~InputManager()
{
}

InputManager& InputManager::GetInstance()
{
	static InputManager instance;
     return instance;
	
}

void InputManager::AddListener(InputHandler* listenr)
{
	m_Listeners.push_back(listenr);

}

void InputManager::RemoveListener(InputHandler* listenr)
{
	std::vector<InputHandler*>::iterator it = std::remove(m_Listeners.begin(), m_Listeners.end(), listenr);
	m_Listeners.erase(it, m_Listeners.end());
}

void InputManager::OnKeyPressed(const int& key)
{
	for (InputHandler* handler : m_Listeners)
	{
		handler->OnKeyPressed(key);
	}

	if (key == GLFW_KEY_W)
	{
		isUpPressed = true;
	}
	else if (key == GLFW_KEY_S)
	{
		isDownPressed = true;
	}
	else if (key == GLFW_KEY_A)
	{
		isLeftPressed = true;
	}
	else if (key == GLFW_KEY_D)
	{
		isRightPressed = true;
	}


}

void InputManager::OnKeyReleased(const int& key)
{
	for (InputHandler* handler : m_Listeners)
	{
		handler->OnKeyReleased(key);
	}

	if (key == GLFW_KEY_W)
	{
		isUpPressed = false;
	}
	else if (key == GLFW_KEY_S)
	{
		isDownPressed = false;
	}
	else if (key == GLFW_KEY_A)
	{
		isLeftPressed = false;
	}
	else if (key == GLFW_KEY_D)
	{
		isRightPressed = false;
	}


}

void InputManager::OnKeyHeld(const int& key)
{
	for (InputHandler* handler : m_Listeners)
	{
		handler->OnKeyHeld(key);
	}


}

float InputManager::GetMouseX()
{
	return mouseX;
}

float InputManager::GetMouseY()
{
	return mouseY;
}

float InputManager::GetAxisX()
{
	return axisX;
}

float InputManager::GetAxisY()
{
	return axisY;
}
