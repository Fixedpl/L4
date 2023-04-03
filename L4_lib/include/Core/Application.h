#pragma once
#include "Window.h"



class Application
{
public:

	Application(const WindowSettings& window_settings);

	virtual void run() = 0;

protected:

	virtual void onUpdate(const float& dt) = 0;

	virtual void loop() = 0;

protected:
	
	Window m_window;

};

