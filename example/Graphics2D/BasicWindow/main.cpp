#include <HLITE/Core.hpp>
#include <HLITE/File.hpp>
#include <HLITE/Utility.hpp>
#include <HLITE/UserInterface.hpp>

#include <string_view>

using namespace HLITE;

constinit CORE::Window wc(Vector2{800, 600},
    "HLITE - Basic Window", WINDOW_COLOR, false, 60);

UI::Label txTitle;
UI::Label txtSubTitle = "Powered by Raylib";
UI::Label txtHint = "Can you press ALT + R?";
unsigned char opacityHint = 0;

bool isShowSubTitle = false;
UTIL::CombineKey combine(0.25f);

void HLITEMain::Init()
{
    constexpr std::string_view text = "HLite its Awesome!";
    wc.Register();

    txTitle.SetText(text.data());
    txTitle.SetSize(50);
    txTitle.SetPosition((Vector2){
        GET_CENTER_DEFAULT_TEXT_FONT_X_FLOAT(text.data(), txTitle.GetSize()), 
        GET_CENTER_DEFAULT_TEXT_FONT_Y_FLOAT(text.data(), txTitle.GetSize())});
    txTitle.SetTextColor(BLUE);
    txTitle.SetTextOutline(SKYBLUE);

    txtSubTitle.SetSize(25);
    txtSubTitle.SetPosition((Vector2){
        txTitle.GetPosition().x, txTitle.GetPosition().y + 45});
    txtSubTitle.SetTextColor(SKYBLUE);
    txtSubTitle.SetTextOutline(BLUE);

    txtHint.SetSize(20);
    txtHint.SetPosition({20.0f, 20.0f});
    txtHint.SetTextColor(YELLOW);
    txtHint.SetTextOutline(BLACK);

    combine.SetMaxDelay(0.23f);
}

void HLITEMain::Update()
{
    if (opacityHint < 255)
        opacityHint++;

    if (combine.Check2(IsKeyDown(KEY_LEFT_ALT),
                       IsKeyDown(KEY_R)))
        isShowSubTitle = true;
}

void HLITEMain::Render()
{
    txTitle.DrawWithOutline(1, 255); 

    if (isShowSubTitle)
        txtSubTitle.DrawWithOutline(1, 255);

    txtHint.DrawWithOutline(1.0f, opacityHint);
}

void HLITEMain::Unload(){}