#pragma once

#include <utility>
#include <Windows.h>

class Mouse
{
	Mouse (const Mouse&) = delete;
	Mouse& operator=(const Mouse&) = delete;

private:
	int x, y;
	bool leftIsPressed, rightIsPressed, middleIsPressed;
	bool isInsideClientArea;
	int deltaScroll;

public:

	void whenMouseMove(POINTS pos);
	void whenLeftDown() { leftIsPressed = true; };
	void whenLeftUp() { leftIsPressed = false; };
	void whenRightDown() { rightIsPressed = true; };
	void whenRightUp() { rightIsPressed = false; };
	void whenMiddleDown() { middleIsPressed = true; };
	void whenMiddleUp() { middleIsPressed = false; };
	void whenMiddleScroll(int delta) { deltaScroll = delta; };

	Mouse();
	
	int GetMouseX();
	int GetMouseY();
	std::pair<int, int> GetMousePos();
	bool isLeftPressed();
	bool isRightPressed();
	bool isMiddlePressed();
	int lastScroll();
};