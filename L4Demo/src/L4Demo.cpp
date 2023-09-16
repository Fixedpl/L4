#include <iostream>

#include "Core/Basic3DApplication.h"


class TestApp : public Basic3DApplication
{
public:

    TestApp(const WindowSettings& window_settings)
    :
        Basic3DApplication(window_settings)
    {

    }

    void onUpdate(const float& dt) {

    }

};

int main()
{
    TestApp app = TestApp(WindowSettings());
    app.run();
}


