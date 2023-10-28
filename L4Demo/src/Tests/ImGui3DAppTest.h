#pragma once

#include "Core/ImGui3DApplication.h"



class ImGui3DAppTest : public ImGui3DApplication
{
public:

    ImGui3DAppTest(const WindowSettings& window_settings);

protected:

    void onUpdate(const float& dt) override;

    void onImGuiUpdate() override;

};

