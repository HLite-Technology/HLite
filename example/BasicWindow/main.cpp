#include "HLITE/Core.hpp"
#include "HLITE/UserInterface.hpp"

#include <string_view>

HLITE::CORE::Window hWnd;
HLITE::UI::Label txTitle;

void HLITEMain::Init()
{
    constexpr std::string_view text = "HLite its Awesome!";

    hWnd.SetWindowTitle("HLite - Basic Window");
    hWnd.SetWindowSize(800, 600);
    hWnd.SetWindowFPS(60);
    hWnd.SetWindowBackgroundColor(BLACK);
    hWnd.Register();

    txTitle.SetText(text.data());
    txTitle.SetPosition((Vector2)
    {
        GET_CENTER_TEXT_X_FLOAT(text.data(), text.size()), 
        GET_CENTER_TEXT_Y_FLOAT(text.size())
    });
    txTitle.SetSize(35);
    txTitle.SetTextColor(ORANGE);
    txTitle.SetTextOutline(RED);
}

void HLITEMain::Update(){}

void HLITEMain::Render()
{
    txTitle.DrawWithOutline(1, 255);
}

void HLITEMain::Unload(){}