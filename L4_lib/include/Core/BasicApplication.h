#pragma once
#include "Application.h"




class BasicApplication : public Application
{
public:

    BasicApplication(const WindowSettings& window_settings);

    void run();

protected:

    void loop();

    virtual void onUpdate(const float& dt) = 0;

};

