#include <HLITE/Core.hpp>
#include <HLITE/UserInterface.hpp>

#include <string_view>

using namespace HLITE;
using namespace HLITEMain;

constinit CORE::Window wc(Vector2{800, 600},
    "HLITE - Virtual Message Box", WINDOW_COLOR, false, 60);

UI::Label hintLabel(std::string_view("Hint -> Press A or B to show message box.").data(),
                                     {20.0f, 20.0f}, 25, BLACK, WHITE);
UI::Label statusLabel(std::string_view("Status button : No Interaction").data(),
                      {20.0f, 60.0f}, 25, BLACK, WHITE);

UI::VMessageBox PassOkey("About",
                         "HLite Framework created by Zach Noland (@MuzakyGood).", 
                         {100.0f, 100.0f}, UI::VMSBoxMod::MB_OK,
                         UI::VMSBoxMod::MB_ICONINFORMATION);
UI::VMessageBox PassYesNo("MB_TEST_YES_NO", 
                          "Just Testing Only Concept in Programming.", 
                          {100.0f, 100.0f}, 
                          UI::VMSBoxMod::MB_YESNO, 
                          UI::VMSBoxMod::MB_ICONINFORMATION);

void HLITEMain::Init(){wc.Register();}
void HLITEMain::Update()
{
    if (IsKeyPressed(KEY_A))
        PassOkey.Appear();
    if (IsKeyPressed(KEY_B))
        PassYesNo.Appear();

    if (PassOkey.Update() == MB_BTN_OK)
        statusLabel.SetText(TextFormat("Status button : %s", "OKEY"));

    if (PassYesNo.Update() == MB_BTN_YES)
        statusLabel.SetText(TextFormat("Status button : %s", "YES"));
    else if (PassYesNo.Update() == MB_BTN_NO)
        statusLabel.SetText(TextFormat("Status button : %s", "NO"));
}

void HLITEMain::Render()
{
    hintLabel.DrawWithOutline(1.0f, 255);
    statusLabel.DrawWithOutline(1.0f, 255);
    PassOkey.Draw();
    PassYesNo.Draw();
}

void HLITEMain::Unload(){}