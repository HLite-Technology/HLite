#include "../include/HLITE/UserInterface.hpp"
#include <cstdio>

namespace HLITE
{
    namespace UI
    {
        /*
         * Primitive Label Class
         */

        void Label::Draw(unsigned char Opacity)
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
                    .a = Opacity
                }
            );
        }

        void Label::DrawWithOutline(int OutlineRange, unsigned char Opacity)
        {
            // Background text (Outline).
            DrawText(
                text.c_str(), 
                static_cast<int>(position.x) - OutlineRange,
                static_cast<int>(position.y) - OutlineRange, 
                size, 
                (Color)
                {
                    .r = textOutline.r,
                    .g = textOutline.g,
                    .b = textOutline.b,
                    .a = Opacity
                }
            );
            // Foreground text.
            DrawText(
                text.c_str(), static_cast<int>(position.x),
                static_cast<int>(position.y), size, 
                (Color)
                {
                    .r = textColor.r,
                    .g = textColor.g,
                    .b = textColor.b,
                    .a = Opacity
                }
            );
        }

        /*
         * Modern Label Class
         */

        void LabelEx::Draw(unsigned char Opacity)
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
                    .a = Opacity
                }
            );
        }

        void LabelEx::DrawWithOutline(float OutlineRange, unsigned char Opacity)
        {

            if (font.texture.id != 0)
            {
                isErrorMessage = false;
                Vector2 size = MeasureTextEx(font, text.data(), fontSize, spacing);
                origin = { size.x/2.0f, size.y/2.0f };

                // Background text (Outline).
                DrawTextPro(
                    font, text.data(),
                    (Vector2)
                    {
                        .x = position.x - OutlineRange,
                        .y = position.y - OutlineRange
                    }
                    , origin, rotation,
                    fontSize, spacing,
                    (Color)
                    {
                        .r = textOutline.r,
                        .g = textOutline.g,
                        .b = textOutline.b,
                        .a = Opacity
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
                        .a = Opacity
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

        Button Button::Update(Button button)
        {
            Vector2 mousePos = GetMousePosition();
        
            if (!CheckCollisionPointRec(mousePos, rect))
            {
                button.isHover = false;
                button.isClicked = false;
                SetMouseCursor(MOUSE_CURSOR_DEFAULT);
                return button;
            } else 
            {
                button.isHover = true;
            
                if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
                {
                    button.isClicked = true;
                    return button;
                }
                else 
                {
                    button.isClicked = false;
                    return button;
                }
            
                SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
                return button;
            }
            return button;
        }

        void Button::Draw(float PosX, float posY)
        {
            int mainPosY = 5;
            int mainPosX = 5;
            int mainWidthX = 10;
        
            rect = (Rectangle)
            {
                .x = PosX - mainPosX,
                .y = posY - mainPosY,
                .width = static_cast<float>(MeasureText(text.GetText().c_str(), text.GetSize())) + mainWidthX,
                .height = 40.0f
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
                        static_cast<int>(rect.x) - 1,
                        static_cast<int>(rect.y) - 1,
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
        
            DrawText(
                text.GetText().c_str(), 
                static_cast<int>(text.GetPosition().x), 
                static_cast<int>(text.GetPosition().y),
                text.GetSize(), text.GetColor()
            );
        }       
    }
}