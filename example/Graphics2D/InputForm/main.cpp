#include "HLITE/Core.hpp"
#include "HLITE/UserInterface.hpp"

#include <array>
#include <format>

constinit HLITE::CORE::Window wc(Vector2{400, 300},
    "HLITE - Input Form", {210, 210, 210, 210}, false, 60);

HLITE::UI::Label txTitle = "HLITE FORM";
HLITE::UI::Label txPrompName = "Name";
HLITE::UI::Label txPrompAge = "Age";

HLITE::UI::TextField usernameField("Enter name here...", 19, 15, true);
HLITE::UI::TextField ageField("Enter age here...", 19, 15, true);
HLITE::UI::TextArea resultArea("Result output...", 100, 15, false);

HLITE::UI::Button submitBtn({"submit", {0.0f, 0.0f}, 20, BLACK, WHITE});
HLITE::UI::Button clearBtn({"clear", {0.0f, 0.0f}, 21, BLACK, WHITE});

void HLITEMain::Init()
{
    wc.Register();

    txTitle.SetSize(35);
    txTitle.SetPosition((Vector2){
        GET_CENTER_DEFAULT_TEXT_FONT_X_FLOAT(txTitle.GetText().data(), txTitle.GetSize()),
        20.0f});
    txTitle.SetTextColor(WHITE);
    txTitle.SetTextOutline(DARKGRAY);

    txPrompName.SetSize(15);
    txPrompName.SetPosition((Vector2){
        20.0f,
        100.0f});
    txPrompName.SetTextColor(BLACK);

    txPrompAge.SetSize(15);
    txPrompAge.SetPosition((Vector2){
        20.0f,
        130.0f});
    txPrompAge.SetTextColor(BLACK);

    usernameField.SetSizeBox((Rectangle){
        .x = 100.0f,
        .y = 95.0f,
        .width = 150.0f,
        .height = 25.0f
    });
    usernameField.SetBoxPadding(5);
    usernameField.SetFieldMode(HLITE::UI::TextFieldMode::STATIC);
    usernameField.SetTextColor(BLACK);
    usernameField.SetBoxColor(WHITE, DARKGRAY, LIME);

    ageField.SetSizeBox((Rectangle){
        .x = 100.0f,
        .y = 125.0f,
        .width = 150.0f,
        .height = 25.0f
    });
    ageField.SetBoxPadding(5);
    ageField.SetFieldMode(HLITE::UI::TextFieldMode::STATIC);
    ageField.SetTextColor(BLACK);
    ageField.SetBoxColor(WHITE, DARKGRAY, LIME);

    resultArea.SetSizeBox((Rectangle){
        .x = 20.0f,
        .y = 240.0f,
        .width = 365.0f,
        .height = 50.0f
    });
    resultArea.SetBoxPadding(5);
    resultArea.SetFieldMode(HLITE::UI::TextFieldMode::DEFAULT);
    resultArea.SetTextColor(BLACK);
    resultArea.SetBoxColor(WHITE, DARKGRAY, LIME);

    submitBtn.SetPosition((Vector2){100.0f, 200.0f});
    submitBtn.SetMainColorBtn(GRAY);
    submitBtn.SetOutlineColorBtn(DARKGRAY);

    clearBtn.SetPosition((Vector2){240.0f, 199.0f});
    clearBtn.SetMainColorBtn(GRAY);
    clearBtn.SetOutlineColorBtn(DARKGRAY);
}

void HLITEMain::Update()
{
    usernameField.Update();
    ageField.Update();
    resultArea.Update();

    if (submitBtn.Update())
    {
        std::array<char, 255> buffer;

        auto results = std::format_to(buffer.data(),
                                      "My name is {}. I\'am {} years old.", 
                                      usernameField.GetText(), 
                                      ageField.GetText());
        *results = '\0';

        resultArea.SetText(buffer.data());
    }
    
    if (clearBtn.Update())
    {
        if (!usernameField.GetText().empty()) usernameField.SetText("");
        if (!ageField.GetText().empty()) ageField.SetText("");
        if (!resultArea.GetText().empty()) resultArea.SetText("");
    }
}

void HLITEMain::Render()
{
    txTitle.DrawWithOutline(1, 255);
    txPrompName.Draw(255);
    txPrompAge.Draw(255);

    usernameField.Draw();
    ageField.Draw();
    resultArea.Draw();

    submitBtn.Draw();
    clearBtn.Draw();
}

void HLITEMain::Unload()
{
    
}