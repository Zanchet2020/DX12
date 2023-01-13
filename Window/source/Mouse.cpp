#include "Mouse.h"

void Mouse::whenMouseMove(POINTS pos)
{
	x = static_cast<int>(pos.x);
	y = static_cast<int>(pos.y);
}

Mouse::Mouse()
{
	leftIsPressed = false;
	rightIsPressed = false;
	middleIsPressed = false;
	isInsideClientArea = false;
	deltaScroll = 0;
	x = 0;
	y = 0;
}

int Mouse::GetMouseX()
{
	return x;
}

int Mouse::GetMouseY()
{
	return y;
}

std::pair<int, int> Mouse::GetMousePos()
{
	return std::pair<int, int>(x, y);
}

bool Mouse::isLeftPressed()
{
	return leftIsPressed;
}

bool Mouse::isRightPressed()
{
	return rightIsPressed;
}

bool Mouse::isMiddlePressed()
{
	return middleIsPressed;
}

int Mouse::lastScroll()
{
	return deltaScroll;
}


