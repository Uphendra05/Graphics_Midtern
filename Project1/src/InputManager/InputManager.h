#pragma once
#include "iInputHandler.h"
#include <vector>
#include <glm/fwd.hpp>
#include <glm/glm.hpp>


class InputManager 
{
public:

	InputManager();
	~InputManager();

	static InputManager& GetInstance();


	void AddListener(InputHandler* listenr);
	void RemoveListener(InputHandler* listenr);

	
	void OnKeyPressed(const int& key);
	void OnKeyReleased(const int& key);
	void OnKeyHeld(const int& key);

	float GetMouseX();
	float GetMouseY();

	float GetAxisX();
	float GetAxisY();


private:

	std::vector<InputHandler*> m_Listeners;

	float mouseX = 0;
	float mouseY = 0;
	float axisX = 0;
	float axisY = 0;


	bool isUpPressed = false;
	bool isDownPressed = false;
	bool isLeftPressed = false;
	bool isRightPressed = false;


};

