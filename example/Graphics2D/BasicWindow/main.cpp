#include "HLITE/Core.hpp"
#include "HLITE/UserInterface.hpp"

#include <string_view>

constinit HLITE::CORE::Window wc(Vector2{800, 600},
    "HLITE - Basic Window", DARKBLUE, false, 60);
HLITE::UI::Label txTitle;

void HLITEMain::Init()
{
    constexpr std::string_view text = "HLite its Awesome!";
    wc.Register();

    txTitle.SetText(text.data());
    txTitle.SetSize(50);
    txTitle.SetPosition((Vector2)
    {
        GET_CENTER_DEFAULT_TEXT_FONT_X_FLOAT(text.data(), txTitle.GetSize()), 
        GET_CENTER_DEFAULT_TEXT_FONT_Y_FLOAT(text.data(), txTitle.GetSize())
    });
    txTitle.SetTextColor(ORANGE);
    txTitle.SetTextOutline(RED);
}

void HLITEMain::Update(){}

void HLITEMain::Render()
{
    txTitle.DrawWithOutline(1, 255);
}

void HLITEMain::Unload(){}