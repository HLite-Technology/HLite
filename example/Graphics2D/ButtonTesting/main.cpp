#include <HLITE/Core.hpp>
#include <HLITE/UserInterface.hpp>

#include <format>

using namespace HLITE;

constinit CORE::Window wc(Vector2(400, 250),
                          "HLITE - Button Testing",
                          WINDOW_COLOR, 60);

int pressCount = 0, holdCount = 0;
float delay = 0.0f, maxDelay = 2.0f;

UI::Label pressLabel = "Press: 0";
UI::Label holdLabel = "Hold: 0";

UI::Button btnPress({"Press Me!", {0.0f, 0.0f}, 25, BLACK, WHITE});
UI::Button btnHold({"Hold Me!", {0.0f, 0.0f}, 25, BLACK, WHITE});

void HLITEMain::Init()
{
    wc.Register();

    btnPress.SetPosition({25.0f, 25.0f});
    btnPress.SetMainColorBtn(GRAY);
    btnPress.SetOutlineColorBtn(DARKGRAY);
    btnPress.SetModePress(UI::ButtonPressType::PRESS);

    btnHold.SetPosition({25.0f, 100.0f});
    btnHold.SetMainColorBtn(GRAY);
    btnHold.SetOutlineColorBtn(DARKGRAY);
    btnHold.SetModePress(UI::ButtonPressType::DOWN);

    pressLabel.SetSize(25.0f);
    pressLabel.SetPosition({200.0f, 25.0f});
    pressLabel.SetTextColor(WHITE);
    pressLabel.SetTextOutline(BLACK);

    holdLabel.SetSize(25.0f);
    holdLabel.SetPosition({200.0f, 100.0f});
    holdLabel.SetTextColor(WHITE);
    holdLabel.SetTextOutline(BLACK);
}

void HLITEMain::Update()
{
    if (btnPress.Update())
    {
        pressCount++;
        pressLabel.SetText(std::format("Press: {}", pressCount).data());
    }

    if (btnHold.Update())
    {
        if (delay <= maxDelay)
            delay += 0.8f;
        else
        {
            holdCount++;
            delay = 0.0f;
        }
        holdLabel.SetText(std::format("Hold: {}", holdCount).data());
    }
}

void HLITEMain::Render()
{
    btnPress.DrawWithRounded(0.5f);
    btnHold.DrawWithRounded(0.5f);
    pressLabel.DrawWithOutline(1.0f, 255);
    holdLabel.DrawWithOutline(1.0f, 255);
}

void HLITEMain::Unload()
{

}