#include <HLITE/Core.hpp>
#include <HLITE/UserInterface.hpp>

#include <string_view>

using namespace HLITE;

constinit CORE::Window wc({500.0f, 400.0f},
                                 "HLITE - Slider Testing",
                                 WINDOW_COLOR, false, 60);

UI::SliderBar sliderH(100.0f,
                     UI::SliderBarMode::HORIZONTAL,
                     {0.0f, 0.0f},
                     {200.0f, 35.0f}, 
                     1.0f, DARKBLUE, BLUE,
                     DARKGRAY);
UI::SliderBar sliderV(100.0f,
                      UI::SliderBarMode::VERTICAL,
                      {0.0f, 0.0f},
                      {35.0f, 200.0f},
                      1.0f, DARKBLUE, BLUE,
                      DARKGRAY);

UI::Label slideHLabel("", {0.0f, 0.0f}, 20.0f, BLACK, WHITE);
UI::Label slideVLabel("", {0.0f, 0.0f}, 20.0f, BLACK, WHITE);

std::string_view statusH, statusV;

void HLITEMain::Init()
{ 
    wc.Register();
    sliderH.SetPosition(Vector2(GET_CENTER_POSITION_X(sliderH.GetSize().x) - 100.0f, 
                                GET_CENTER_POSITION_Y(sliderH.GetSize().y)));
    sliderV.SetPosition(Vector2(GET_CENTER_POSITION_X(sliderV.GetSize().x) + 100.0f, 
                                GET_CENTER_POSITION_Y(sliderV.GetSize().y - 165.0f)));
}
void HLITEMain::Update()
{ 
    sliderH.Update(); 
    sliderV.Update();

    statusV = TextFormat("Vertical: %.2f", sliderV.GetValue());
    statusH = TextFormat("Horizontal: %.2f", sliderH.GetValue());

    slideHLabel.SetText(statusH.data());
    slideVLabel.SetText(statusV.data());

    slideHLabel.SetPosition({sliderH.GetPosition().x + MeasureTextEx(GetFontDefault(),
                                                                 statusH.data(),
                                                                 slideHLabel.GetSize(),
                                                                 2).x / 2.0f - 75.0f,
                             sliderH.GetPosition().y - MeasureTextEx(GetFontDefault(),
                                                                 statusH.data(),
                                                                 slideHLabel.GetSize(),
                                                                 2).y / 2.0f + 50.0f});
    slideVLabel.SetPosition({sliderV.GetPosition().x + MeasureTextEx(GetFontDefault(),
                                                                 statusV.data(),
                                                                 slideVLabel.GetSize(),
                                                                 2).x / 2.0f - 75.0f,
                             sliderV.GetPosition().y - MeasureTextEx(GetFontDefault(),
                                                                 statusV.data(),
                                                                 slideVLabel.GetSize(),
                                                                 2).y / 2.0f + 214.0f});                                                             
}
void HLITEMain::Render()
{
    sliderH.Draw(); 
    sliderV.Draw();
    slideHLabel.DrawWithOutline(1.0f, 255);
    slideVLabel.DrawWithOutline(1.0f, 255);
}
void HLITEMain::Unload(){}