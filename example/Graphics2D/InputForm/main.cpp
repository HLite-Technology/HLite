#include "HLITE/Core.hpp"
#include "HLITE/UserInterface.hpp"

HLITE::CORE::Window wc;

HLITE::UI::Label txTitle("HLITE FORM");
HLITE::UI::Label txPrompName("Name");
HLITE::UI::Label txPrompAge("Age");

HLITE::UI::TextField usernameField;
HLITE::UI::TextField ageField;

HLITE::UI::Button submitBtn({"submit", {0.0f, 0.0f}, 20, BLACK, WHITE});
HLITE::UI::Button clearBtn({"clear", {0.0f, 0.0f}, 21, BLACK, WHITE});

void HLITEMain::Init()
{
    wc.SetWindowTitle("HLITE - Input Form");
    wc.SetWindowSize(400, 300);
    wc.SetWindowResizeable(false);
    wc.SetWindowFPS(60);
    wc.SetWindowBackgroundColor({210, 210, 210, 210});
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

    usernameField.SetPlaceholders("Enter name here...");
    usernameField.SetSizeBox((Rectangle){
        .x = 100.0f,
        .y = 95.0f,
        .width = 150.0f,
        .height = 25.0f
    });
    usernameField.SetBoxPadding(5);
    usernameField.SetFieldMode(HLITE::UI::TextFieldMode::STATIC);
    usernameField.SetMaxLength(19);
    usernameField.SetTextSize(15);
    usernameField.SetTextColor(BLACK);
    usernameField.SetBoxColor(WHITE, DARKGRAY, LIME);

    ageField.SetPlaceholders("Enter age here...");
    ageField.SetSizeBox((Rectangle){
        .x = 100.0f,
        .y = 125.0f,
        .width = 150.0f,
        .height = 25.0f
    });
    ageField.SetBoxPadding(5);
    ageField.SetFieldMode(HLITE::UI::TextFieldMode::STATIC);
    ageField.SetMaxLength(19);
    ageField.SetTextSize(15);
    ageField.SetTextColor(BLACK);
    ageField.SetBoxColor(WHITE, DARKGRAY, LIME);

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

    submitBtn.Update();
    
    if (clearBtn.Update())
    {
        if (!usernameField.GetText().empty()) usernameField.SetText("");
        if (!ageField.GetText().empty()) ageField.SetText("");
    }
}

void HLITEMain::Render()
{
    txTitle.DrawWithOutline(1, 255);
    txPrompName.Draw(255);
    txPrompAge.Draw(255);

    usernameField.Draw();
    ageField.Draw();

    submitBtn.Draw();
    clearBtn.Draw();
}

void HLITEMain::Unload()
{
    
}