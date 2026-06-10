#include "../include/HLITE/UserInterface.hpp"
#include <cstdio>

#define GET_DEFAULT_TEXT_WIDTH(text, fontSize) (MeasureTextEx(GetFontDefault(), text, (float)(fontSize), GET_DEFAULT_FONT_SPACING).x)
#define GET_DEFAULT_TEXT_HEIGHT(text, fontSize) (MeasureTextEx(GetFontDefault(), text, (float)(fontSize), GET_DEFAULT_FONT_SPACING).y)

namespace HLITE
{
    namespace UI
    {
        /*
         * Primitive Label Class
         */

        void Label::Draw(unsigned char opacity)
        {
            // Render text.
            DrawText(
                text.c_str(), static_cast<int>(position.x),
                static_cast<int>(position.y), size, 
                (Color)
                {
                    .r = textColor.r,
                    .g = textColor.g,
                    .b = textColor.b,
                    .a = opacity
                }
            );
        }

        void Label::DrawWithShadow(float shadowRange, unsigned char opacity)
        {
            // Background text (shadow).
            DrawText(
                text.data(), 
                static_cast<int>(position.x) - shadowRange,
                static_cast<int>(position.y) - shadowRange, 
                size, 
                (Color)
                {
                    .r = textOutline.r,
                    .g = textOutline.g,
                    .b = textOutline.b,
                    .a = opacity
                }
            );
            // Foreground text.
            DrawText(
                text.data(), static_cast<int>(position.x),
                static_cast<int>(position.y), size, 
                (Color)
                {
                    .r = textColor.r,
                    .g = textColor.g,
                    .b = textColor.b,
                    .a = opacity
                }
            );
        }

        void Label::DrawWithOutline(float thick, unsigned char opacity)
        {
            if (thick > 3.0f) thick = 1;
            
            // Background text (shadow).
            DrawText(text.data(), position.x - thick, position.y, size, (Color){textOutline.r, textOutline.g, textOutline.b, opacity});
            DrawText(text.data(), position.x + thick, position.y, size, (Color){textOutline.r, textOutline.g, textOutline.b, opacity});
            DrawText(text.data(), position.x, position.y - thick, size, (Color){textOutline.r, textOutline.g, textOutline.b, opacity});
            DrawText(text.data(), position.x, position.y + thick, size, (Color){textOutline.r, textOutline.g, textOutline.b, opacity});

            DrawText(text.data(), position.x - thick, position.y - thick, size, (Color){textOutline.r, textOutline.g, textOutline.b, opacity});
            DrawText(text.data(), position.x + thick, position.y - thick, size, (Color){textOutline.r, textOutline.g, textOutline.b, opacity});
            DrawText(text.data(), position.x - thick, position.y + thick, size, (Color){textOutline.r, textOutline.g, textOutline.b, opacity});
            DrawText(text.data(), position.x + thick, position.y + thick, size, (Color){textOutline.r, textOutline.g, textOutline.b, opacity});

            // Foreground text.
            DrawText(text.data(), position.x, position.y, size, (Color){textColor.r, textColor.g, textColor.b, opacity});
        }

        /*
         * Modern Label Class
         */

        void LabelEx::Draw(unsigned char opacity)
        {
            Vector2 size = MeasureTextEx(font, text.data(), fontSize, spacing);
            origin = { size.x/2.0f, size.y/2.0f };

            DrawTextPro(
                font, text.data(),
                position, origin, rotation,
                fontSize, spacing, 
                (Color)
                {
                    .r = textColor.r,
                    .g = textColor.g,
                    .b = textColor.b,
                    .a = opacity
                }
            );
        }

        void LabelEx::DrawWithShadow(float shadowRange, unsigned char opacity)
        {

            if (font.texture.id != 0)
            {
                isErrorMessage = false;
                Vector2 size = MeasureTextEx(font, text.data(), fontSize, spacing);
                origin = { size.x/2.0f, size.y/2.0f };

                // Background text (shadow).
                DrawTextPro(
                    font, text.data(),
                    (Vector2)
                    {
                        .x = position.x - shadowRange,
                        .y = position.y - shadowRange
                    }
                    , origin, rotation,
                    fontSize, spacing,
                    (Color)
                    {
                        .r = textOutline.r,
                        .g = textOutline.g,
                        .b = textOutline.b,
                        .a = opacity
                    }
                );
                // Foreground text.
                DrawTextPro(
                    font, text.data(),
                    position, origin, rotation,
                    fontSize, spacing,
                    (Color)
                    {
                        .r = textColor.r,
                        .g = textColor.g,
                        .b = textColor.b,
                        .a = opacity
                    }
                );
            }
            else
            {
                if (!isErrorMessage) 
                {
                    std::fprintf(stderr, "[HLITE] Failed draw text, TextEx class need load font!\n");
                    isErrorMessage = true;
                }
            }
        }

        /*
         * Primitive Button Class
         */

        bool Button::Update()
        {
            Vector2 mousePos = GetMousePosition();
        
            if (!CheckCollisionPointRec(mousePos, rect))
            {
                isHover = false;
                isClicked = false;
            }
            else 
            {
                isHover = true;
                if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
                {
                    isClicked = true;
                    return true;
                }
                else
                {
                    isClicked = false;
                    return false;
                }
            }
            return false;
        }

        void Button::Draw()
        {
            int mainPosY = 5;
            int mainPosX = 5;
            int mainWidthX = 10;
            int mainHeightY = 5;
        
            rect = (Rectangle)
            {
                .x = position.x - mainPosX,
                .y = position.y - mainPosY,
                .width = static_cast<float>(GET_DEFAULT_TEXT_WIDTH(text.GetText().data(), text.GetSize()) + mainWidthX),
                .height = static_cast<float>(GET_DEFAULT_TEXT_HEIGHT(text.GetText().data(), text.GetSize()) + mainHeightY)
            };
        
            if (!isHover)
            {
                // Background button
                DrawRectangle(
                    static_cast<int>(rect.x) - 3,
                    static_cast<int>(rect.y) - 3,
                    static_cast<int>(rect.width),
                    static_cast<int>(rect.height),
                    outlineColorBtn
                );
            
                // Foreground button
                DrawRectangle(
                    static_cast<int>(rect.x),
                    static_cast<int>(rect.y),
                    static_cast<int>(rect.width),
                    static_cast<int>(rect.height),
                    mainColorBtn
                );
            }
            else
            {
                if (!isClicked)
                {
                    // Background button
                    DrawRectangle(
                        static_cast<int>(rect.x) - 3,
                        static_cast<int>(rect.y) - 3,
                        static_cast<int>(rect.width),
                        static_cast<int>(rect.height),
                        (Color)
                        {
                            .r = static_cast<unsigned char>(outlineColorBtn.r + 15),
                            .g = static_cast<unsigned char>(outlineColorBtn.g + 15),
                            .b = static_cast<unsigned char>(outlineColorBtn.b + 15),
                            .a = static_cast<unsigned char>(outlineColorBtn.a)
                        }
                    );
                
                    // Foreground button
                    DrawRectangle(
                        static_cast<int>(rect.x),
                        static_cast<int>(rect.y),
                        static_cast<int>(rect.width),
                        static_cast<int>(rect.height),
                        (Color)
                        {
                            .r = static_cast<unsigned char>(mainColorBtn.r + 10),
                            .g = static_cast<unsigned char>(mainColorBtn.g + 10),
                            .b = static_cast<unsigned char>(mainColorBtn.b + 10),
                            .a = static_cast<unsigned char>(mainColorBtn.a)
                        }
                    );
                }
                else
                {
                    // Background button
                    DrawRectangle(
                        static_cast<int>(rect.x),
                        static_cast<int>(rect.y),
                        static_cast<int>(rect.width),
                        static_cast<int>(rect.height),
                        (Color)
                        {
                            .r = static_cast<unsigned char>(outlineColorBtn.r + 15),
                            .g = static_cast<unsigned char>(outlineColorBtn.g + 15),
                            .b = static_cast<unsigned char>(outlineColorBtn.b + 15),
                            .a = static_cast<unsigned char>(outlineColorBtn.a)
                        }
                    );
                
                    // Foreground button
                    DrawRectangle(
                        static_cast<int>(rect.x),
                        static_cast<int>(rect.y),
                        static_cast<int>(rect.width),
                        static_cast<int>(rect.height),
                        (Color)
                        {
                            .r = static_cast<unsigned char>(mainColorBtn.r + 10),
                            .g = static_cast<unsigned char>(mainColorBtn.g + 10),
                            .b = static_cast<unsigned char>(mainColorBtn.b + 10),
                            .a = static_cast<unsigned char>(mainColorBtn.a)
                        }
                    );
                }
            }
        
            float textPosWidth = rect.x + (rect.width - GET_DEFAULT_TEXT_WIDTH(text.GetText().data(), text.GetSize())) / 2;
            float textPosHeight = rect.y + (rect.height - GET_DEFAULT_TEXT_HEIGHT(text.GetText().data(), text.GetSize())) / 2;

            // Background text (shadow).
            // DrawText(text.GetText().data(), textPosWidth - 1, textPosHeight, text.GetSize(), text.GetOutlineColor());
            // DrawText(text.GetText().data(), textPosWidth + 1, textPosHeight, text.GetSize(), text.GetOutlineColor());
            // DrawText(text.GetText().data(), textPosWidth, textPosHeight - 1, text.GetSize(), text.GetOutlineColor());
            // DrawText(text.GetText().data(), textPosWidth, textPosHeight + 1, text.GetSize(), text.GetOutlineColor());

            DrawText(text.GetText().data(), textPosWidth - 1, textPosHeight - 1, text.GetSize(), text.GetOutlineColor());
            DrawText(text.GetText().data(), textPosWidth + 1, textPosHeight - 1, text.GetSize(), text.GetOutlineColor());
            DrawText(text.GetText().data(), textPosWidth - 1, textPosHeight + 1, text.GetSize(), text.GetOutlineColor());
            DrawText(text.GetText().data(), textPosWidth + 1, textPosHeight + 1, text.GetSize(), text.GetOutlineColor());

            // Foreground text.

            DrawText(
                text.GetText().data(), 
                textPosWidth,
                textPosHeight,
                text.GetSize(), text.GetColor()
            );
        }
        
        /*
         * Primitive Text Field Class
         */

        void TextField::SetText(const char *text) { hndText = text; }
        void TextField::SetPlaceholders(const char *text)
        {
            placeholders = text;
            placeholders.shrink_to_fit();
        }
        void TextField::SetEditable(bool canEdit) { canEditable = canEdit; }
        void TextField::SetMaxLength(int len)
        {
            maxLength = len;
            hndText.reserve(maxLength);
        }
        void TextField::SetSizeBox(Rectangle sizeBox) { textBox = sizeBox; }
        void TextField::SetBoxPadding(int padding) { boxPadding = padding; }
        void TextField::SetFieldMode(TextFieldMode mode) { this->mode = mode; }
        void TextField::SetTextSize(int size) { textSize = size; }
        void TextField::SetTextColor(Color color) { texCol = color; }
        void TextField::SetBoxColor(Color mainColor, Color offHoverColor, Color onHoverColor)
        { 
            boxCol = mainColor; 
            offHoverBoxCol = offHoverColor;
            onHoverBoxCol = onHoverColor;
        }

        Vector2 TextField::GetPosition() { return (Vector2){textBox.x, textBox.y}; }
        std::size_t TextField::GetMaxLen() { return hndText.capacity(); }
        std::string TextField::GetText() { return hndText; }

        void TextField::Update()
        {
            if (!canEditable) return;

            if (CheckCollisionPointRec(GetMousePosition(), textBox)) mouseOnText = true;
            else mouseOnText = false;

            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            {
                if (mouseOnText) isMouseFocusText = true;
                else isMouseFocusText = false;
            }

            if (isMouseFocusText)
            {
                if (IsKeyPressed(KEY_ENTER))
                    isMouseFocusText = false;

                int key = GetCharPressed();
                while (key > 0)
                {
                    if ((key >= 32) && (key <= 125) && (hndText.length() < maxLength))
                    {
                        if (mode == TextFieldMode::STATIC)
                        {
                            std::string nextText = hndText + static_cast<char>(key);

                            int nextTextWidth = MeasureText(nextText.c_str(), textSize);
                            int cursorWidth = MeasureText("_", textSize);
                            int maxAllowedWidth = (int)textBox.width - (boxPadding * 2) - cursorWidth;

                            if (nextTextWidth < maxAllowedWidth)
                                hndText.push_back(static_cast<char>(key));
                        }

                        if (mode == TextFieldMode::DEFAULT)
                            hndText.push_back(static_cast<char>(key));
                    }
                
                    key = GetCharPressed();
                }
            
                if (IsKeyDown(KEY_BACKSPACE))
                {
                    if (IsKeyPressed(KEY_BACKSPACE))
                    {
                        if (!hndText.empty())
                            hndText.pop_back();
                        return;
                    }

                    if (delay.GetIsDone()) delay.Reset();

                    if (delay.Update())
                    {
                        if (!hndText.empty())
                            hndText.pop_back();
                    }
                }

                frameCounter++;
            }
            else frameCounter = 0;
        }

        void TextField::Draw()
        {
            if (!canEditable)
            {
                DrawRectangleRec(textBox, boxCol);
                DrawRectangleLines((int)textBox.x, (int)textBox.y, (int)textBox.width, (int)textBox.height, offHoverBoxCol);
                DrawText(hndText.data(), (int)textBox.x + boxPadding, (int)textBox.y + boxPadding, textSize, texCol);
                return;
            }

            DrawRectangleRec(textBox, boxCol);
            if (isMouseFocusText)
                DrawRectangleLines((int)textBox.x, (int)textBox.y, (int)textBox.width, (int)textBox.height, onHoverBoxCol);
            else
                DrawRectangleLines((int)textBox.x, (int)textBox.y, (int)textBox.width, (int)textBox.height, offHoverBoxCol);

            if (mode == TextFieldMode::DEFAULT)
                BeginScissorMode((int)textBox.x + boxPadding, (int)textBox.y, (int)textBox.width - (boxPadding * 2), (int)textBox.height);

            if (hndText.empty())
                DrawText(placeholders.data(), (int)textBox.x + boxPadding, (int)textBox.y + boxPadding, textSize, (Color){200, 200, 200, 155});
            
            DrawText(hndText.data(), (int)textBox.x + boxPadding, (int)textBox.y + boxPadding, textSize, texCol);

            if (isMouseFocusText)
            {
                if (hndText.length() < maxLength)
                {
                    int cursorX;
                    if (((frameCounter / 20) % 2) == 0)
                    {
                        if (mode == TextFieldMode::DEFAULT)
                        {
                            cursorX = (int)textBox.x + boxPadding + MeasureText(hndText.data(), textSize);
                            DrawText("_", cursorX, (int)textBox.y + boxPadding, textSize, texCol);
                        }
                        else DrawText("_", (int)textBox.x + (12 - boxPadding) + MeasureText(hndText.data(), textSize), (int)textBox.y + (10 - boxPadding), textSize, texCol);
                    }
                }
            }

            if (mode == TextFieldMode::DEFAULT)
                EndScissorMode();
        }
    }
}