#include "../include/HLITE/UserInterface.hpp"

#include <cstdio>
#include <algorithm>

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
                    static_cast<int>(rect.x) - 1,
                    static_cast<int>(rect.y) - 1,
                    static_cast<int>(rect.width) + 2,
                    static_cast<int>(rect.height) + 2,
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
                        static_cast<int>(rect.x) - 1,
                        static_cast<int>(rect.y) - 1,
                        static_cast<int>(rect.width) + 2,
                        static_cast<int>(rect.height) + 2,
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
                        static_cast<int>(rect.x) - 2,
                        static_cast<int>(rect.y) - 2,
                        static_cast<int>(rect.width) + 2,
                        static_cast<int>(rect.height) + 2,
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
                if (isMouseFocusText)
                    DrawRectangleLines((int)textBox.x, (int)textBox.y, (int)textBox.width, (int)textBox.height, onHoverBoxCol);
                else
                    DrawRectangleLines((int)textBox.x, (int)textBox.y, (int)textBox.width, (int)textBox.height, offHoverBoxCol);

                if (mode == TextFieldMode::DEFAULT)
                    BeginScissorMode((int)textBox.x + boxPadding, (int)textBox.y, (int)textBox.width - (boxPadding * 2), (int)textBox.height);

                if (hndText.empty())
                    DrawText(placeholders.data(), (int)textBox.x + boxPadding, (int)textBox.y + boxPadding, textSize, (Color){200, 200, 200, 155});

                DrawText(hndText.data(), (int)textBox.x + boxPadding, (int)textBox.y + boxPadding, textSize, texCol);

                if (mode == TextFieldMode::DEFAULT)
                    EndScissorMode();
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

        /*
         * Primitive Text Area Class
         */

        void TextArea::Update()
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
                {
                    if (hndText.length() < maxLength)
                        hndText.push_back('\n');
                }
            
                int key = GetCharPressed();
                while (key > 0)
                {
                    if ((key >= 32) && (key <= 125) && (hndText.length() < maxLength))
                    {
                        if (mode == TextFieldMode::STATIC)
                        {
                            // [PERUBAHAN]: Hanya ukur panjang teks pada baris terakhir untuk pembatasan input
                            std::size_t lastNewline = hndText.find_last_of('\n');
                            std::string lastLine = (lastNewline == std::string::npos) ? hndText : hndText.substr(lastNewline + 1);

                            std::string nextText = lastLine + static_cast<char>(key);
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

        void TextArea::Draw()
        {
            if (!canEditable)
            {
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
            
                if (mode == TextFieldMode::DEFAULT)
                    EndScissorMode();
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
                    if (((frameCounter / 20) % 2) == 0)
                    {
                        int lineCount = 0;
                        std::size_t lastNewline = hndText.find_last_of('\n');
                        std::string lastLine = (lastNewline == std::string::npos) ? hndText : hndText.substr(lastNewline + 1);

                        for (char c : hndText) {
                            if (c == '\n') lineCount++;
                        }
                    
                        int cursorX;
                        int cursorY = (int)textBox.y + boxPadding + (lineCount * textSize);
                    
                        if (mode == TextFieldMode::DEFAULT)
                        {
                            cursorX = (int)textBox.x + boxPadding + MeasureText(lastLine.c_str(), textSize);
                            DrawText("_", cursorX, cursorY, textSize, texCol);
                        }
                        else 
                        {
                            cursorX = (int)textBox.x + (12 - boxPadding) + MeasureText(lastLine.c_str(), textSize);
                            cursorY = (int)textBox.y + (10 - boxPadding) + (lineCount * textSize);
                            DrawText("_", cursorX, cursorY, textSize, texCol);
                        }
                    }
                }
            }
        
            if (mode == TextFieldMode::DEFAULT)
                EndScissorMode();
        }

        /*
         * Primitive Virtual Message Box Class
         */

        constexpr const unsigned char CircleError_bin[517] = {
            0x89, 0x50, 0x4e, 0x47, 0x0d, 0x0a, 0x1a, 0x0a, 0x00, 0x00, 0x00, 0x0d,
            0x49, 0x48, 0x44, 0x52, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x40,
            0x08, 0x06, 0x00, 0x00, 0x00, 0xaa, 0x69, 0x71, 0xde, 0x00, 0x00, 0x00,
            0x01, 0x73, 0x52, 0x47, 0x42, 0x00, 0xae, 0xce, 0x1c, 0xe9, 0x00, 0x00,
            0x01, 0xbf, 0x49, 0x44, 0x41, 0x54, 0x78, 0x9c, 0xed, 0x9a, 0x59, 0x92,
            0x83, 0x30, 0x0c, 0x44, 0x95, 0xa9, 0x39, 0x0f, 0x73, 0xff, 0x63, 0x84,
            0x0b, 0x69, 0x7e, 0xe2, 0x94, 0xe2, 0xb2, 0xe3, 0x45, 0x2d, 0x03, 0x45,
            0xbf, 0xbf, 0x04, 0x6f, 0xdd, 0xc8, 0x3b, 0x22, 0x84, 0x10, 0x42, 0x08,
            0x21, 0x84, 0x10, 0x72, 0x43, 0x1e, 0x07, 0xd4, 0xa9, 0x8d, 0xe7, 0x4b,
            0xdb, 0xb4, 0xaa, 0xb2, 0xb7, 0xe8, 0x67, 0x23, 0xe1, 0xdf, 0xe7, 0xcf,
            0xf0, 0xf6, 0x45, 0x57, 0xa0, 0x22, 0x6d, 0xd1, 0x35, 0x8c, 0x19, 0x61,
            0xed, 0x8c, 0x34, 0x40, 0x93, 0xf0, 0xad, 0xf0, 0x70, 0x1f, 0x28, 0xe8,
            0x65, 0x44, 0x48, 0x5b, 0x23, 0x0a, 0xfd, 0x78, 0xeb, 0xb9, 0xf8, 0x11,
            0xe1, 0x96, 0xa8, 0x68, 0x40, 0x1b, 0xa0, 0x36, 0xdc, 0xad, 0xf8, 0x59,
            0xe1, 0x39, 0xe8, 0x68, 0x40, 0x1a, 0x10, 0x2e, 0x3e, 0x81, 0x34, 0x01,
            0x65, 0xc0, 0x32, 0xf1, 0x09, 0x94, 0x09, 0x3f, 0xde, 0x02, 0x72, 0x6a,
            0xe2, 0x37, 0x6d, 0x4d, 0xff, 0xc7, 0x80, 0x30, 0x40, 0xbf, 0x4d, 0x73,
            0x9b, 0xea, 0x5b, 0x3c, 0xd2, 0x84, 0x57, 0x9d, 0xee, 0x02, 0xbd, 0x21,
            0x54, 0x9d, 0xea, 0x76, 0xa9, 0x0b, 0xde, 0x1f, 0xfd, 0xd5, 0xa6, 0x32,
            0x6a, 0x79, 0xbc, 0x5d, 0x01, 0xd2, 0x05, 0x46, 0xc4, 0x4b, 0xe3, 0x99,
            0x4d, 0x63, 0xd3, 0x45, 0x75, 0x21, 0x8f, 0x01, 0xc5, 0xd0, 0x4f, 0xfd,
            0xbe, 0xf5, 0x96, 0x67, 0x0c, 0x2a, 0xfd, 0xef, 0xed, 0x0a, 0xee, 0x08,
            0xf8, 0x36, 0xe2, 0x8f, 0x9a, 0x90, 0xbf, 0xf5, 0x15, 0xc0, 0x67, 0x81,
            0x9c, 0x5e, 0x13, 0x7a, 0x85, 0xa3, 0x0d, 0x9a, 0x1d, 0x3c, 0xf4, 0x29,
            0x63, 0xcb, 0x5c, 0x54, 0xc3, 0xd1, 0x83, 0x21, 0x2c, 0x02, 0x5a, 0x0b,
            0x9e, 0x91, 0x91, 0xbf, 0x96, 0xdf, 0x5b, 0x46, 0x89, 0xf0, 0x2e, 0x60,
            0x99, 0x15, 0x10, 0x21, 0x3c, 0xf1, 0xeb, 0xc9, 0xbc, 0x4b, 0x79, 0xab,
            0x8b, 0x22, 0x52, 0x78, 0xc2, 0x65, 0x40, 0xa2, 0x67, 0xbd, 0x3f, 0x3a,
            0x06, 0xac, 0x10, 0x2f, 0xb2, 0xa8, 0x0b, 0x9c, 0x75, 0x1f, 0x20, 0x02,
            0x30, 0xa0, 0x35, 0xf2, 0xcf, 0x8a, 0x5f, 0x65, 0x5a, 0x58, 0x04, 0x20,
            0x04, 0xac, 0x30, 0xc1, 0xd3, 0xd1, 0x8a, 0x4b, 0xe1, 0x99, 0xbe, 0xde,
            0xca, 0xd3, 0x1a, 0x0f, 0x3c, 0x1b, 0x22, 0x68, 0x04, 0x8c, 0x88, 0xb7,
            0xf3, 0xba, 0x67, 0xdf, 0xe0, 0x05, 0x6a, 0x40, 0xef, 0x62, 0xa5, 0x94,
            0xe6, 0x28, 0x13, 0x60, 0xe7, 0x01, 0x16, 0xcf, 0x39, 0xc0, 0x68, 0xde,
            0x53, 0x9c, 0x07, 0xe4, 0xcc, 0xbc, 0xe1, 0x5a, 0xba, 0xa8, 0x25, 0x70,
            0x02, 0x51, 0x72, 0xf5, 0x48, 0x6c, 0x53, 0x9d, 0x6e, 0x7c, 0x4f, 0x5e,
            0xc4, 0xc1, 0x68, 0xc8, 0xa9, 0xf0, 0x0a, 0x4e, 0x7b, 0x2a, 0x7c, 0x35,
            0xc2, 0x2e, 0x46, 0x22, 0x39, 0xe3, 0xc5, 0x48, 0x22, 0xdc, 0x84, 0x33,
            0x5f, 0x8d, 0x25, 0x5c, 0x57, 0xe2, 0x35, 0xae, 0x72, 0x39, 0x6a, 0x81,
            0x45, 0xc3, 0xd5, 0xae, 0xc7, 0x2d, 0xb7, 0xfe, 0x40, 0xc2, 0x72, 0xdb,
            0x4f, 0x64, 0x4a, 0x9c, 0xea, 0x23, 0x29, 0x42, 0x08, 0x21, 0x84, 0x10,
            0x42, 0x08, 0xb9, 0x25, 0xff, 0x0f, 0xd5, 0xa7, 0xcc, 0xea, 0xc0, 0x5a,
            0x29, 0x00, 0x00, 0x00, 0x00, 0x49, 0x45, 0x4e, 0x44, 0xae, 0x42, 0x60,
            0x82
        };

        constexpr const unsigned char CircleInformation_bin[431] = {
            0x89, 0x50, 0x4e, 0x47, 0x0d, 0x0a, 0x1a, 0x0a, 0x00, 0x00, 0x00, 0x0d,
            0x49, 0x48, 0x44, 0x52, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x40,
            0x08, 0x06, 0x00, 0x00, 0x00, 0xaa, 0x69, 0x71, 0xde, 0x00, 0x00, 0x00,
            0x01, 0x73, 0x52, 0x47, 0x42, 0x00, 0xae, 0xce, 0x1c, 0xe9, 0x00, 0x00,
            0x01, 0x69, 0x49, 0x44, 0x41, 0x54, 0x78, 0x9c, 0xed, 0x9a, 0xeb, 0x0e,
            0x83, 0x20, 0x0c, 0x85, 0xcb, 0xb2, 0x97, 0xf4, 0x09, 0xf7, 0x98, 0xdd,
            0x0f, 0x13, 0xa3, 0x72, 0x51, 0xe8, 0x29, 0xdd, 0xe2, 0xf9, 0x12, 0x37,
            0x37, 0x37, 0x0a, 0x87, 0x16, 0x91, 0x22, 0x42, 0x08, 0x21, 0x84, 0x10,
            0x42, 0x08, 0x21, 0x0f, 0x24, 0x05, 0xd8, 0xd4, 0x8b, 0xeb, 0x53, 0xeb,
            0x34, 0xcb, 0x98, 0x16, 0x4f, 0x8b, 0xa4, 0xea, 0x07, 0x0f, 0xbc, 0x0d,
            0xe8, 0xe1, 0xad, 0x9b, 0x94, 0x9d, 0xa0, 0xf1, 0x14, 0x40, 0xc7, 0x1b,
            0x7e, 0x26, 0x6d, 0x2f, 0x68, 0x3c, 0x0a, 0xbd, 0xd5, 0xeb, 0x5a, 0xb8,
            0x9c, 0x9a, 0xb5, 0xf1, 0xf1, 0x86, 0x17, 0xb2, 0x30, 0xd9, 0x7a, 0x5d,
            0x45, 0x96, 0xc6, 0x8f, 0x2a, 0xda, 0xd4, 0xbe, 0xdf, 0x8a, 0x5e, 0x45,
            0x45, 0xb9, 0x95, 0x88, 0x60, 0x05, 0xc8, 0x5d, 0xbe, 0x21, 0x82, 0xc9,
            0x0c, 0x50, 0x04, 0x94, 0x00, 0xc7, 0xc6, 0xbb, 0x34, 0xfc, 0x64, 0x0e,
            0x24, 0x02, 0x3a, 0x04, 0x26, 0x34, 0x1e, 0x0b, 0x42, 0x00, 0xe0, 0x68,
            0xdf, 0x69, 0x16, 0x60, 0xd8, 0x2a, 0x40, 0xdb, 0xf5, 0x3f, 0xc6, 0xd2,
            0xef, 0x98, 0x37, 0x8a, 0x80, 0x0f, 0x81, 0x3f, 0xc3, 0x22, 0x40, 0x70,
            0xef, 0xef, 0xaa, 0x61, 0xf0, 0x02, 0x7a, 0x00, 0xa4, 0x94, 0xb0, 0xde,
            0xb7, 0x33, 0x2a, 0x40, 0x7d, 0xe4, 0x0f, 0x69, 0xfc, 0x78, 0x18, 0x30,
            0x04, 0xa2, 0x2b, 0x10, 0x0d, 0x05, 0x88, 0xae, 0x40, 0x34, 0x21, 0x02,
            0xd4, 0x9e, 0xfb, 0xdb, 0xeb, 0x01, 0x3e, 0xbc, 0xe7, 0x9b, 0x5c, 0x89,
            0x68, 0x6c, 0x09, 0x86, 0xc0, 0xe0, 0xff, 0x52, 0x75, 0x65, 0x2a, 0xe4,
            0x71, 0x78, 0x7c, 0xcd, 0x10, 0xe3, 0x01, 0x03, 0x93, 0x1f, 0xd5, 0xfc,
            0x88, 0xc0, 0x27, 0x04, 0x2e, 0xbc, 0x60, 0x6c, 0x4d, 0xd0, 0x07, 0x8b,
            0x00, 0xc7, 0x30, 0x08, 0x9b, 0xff, 0xdb, 0x96, 0xcc, 0xfd, 0x06, 0xc1,
            0x3f, 0x59, 0x1a, 0xb3, 0x0a, 0x10, 0xec, 0x05, 0xf6, 0x84, 0x09, 0xc2,
            0x03, 0xba, 0x45, 0xc0, 0x4c, 0x84, 0x30, 0xd9, 0x22, 0xd4, 0x74, 0xa4,
            0x9e, 0x13, 0x70, 0xf3, 0x0a, 0x8c, 0x00, 0xa8, 0x31, 0x60, 0xf2, 0xbc,
            0xc0, 0x2f, 0x57, 0x68, 0x25, 0xbf, 0xbb, 0x2f, 0xa5, 0x3b, 0xbe, 0xe5,
            0xc0, 0xae, 0xc1, 0x87, 0x25, 0x47, 0xfb, 0xf1, 0x49, 0x8e, 0x32, 0x3d,
            0xee, 0x51, 0xe8, 0x8e, 0x47, 0x6f, 0x90, 0xd8, 0xf3, 0xd8, 0x2d, 0x32,
            0x25, 0x7e, 0x6a, 0x93, 0x14, 0x21, 0x84, 0x10, 0x42, 0x08, 0x21, 0x84,
            0x3c, 0x92, 0x2f, 0x65, 0x93, 0x82, 0x62, 0x3f, 0x71, 0x71, 0x34, 0x00,
            0x00, 0x00, 0x00, 0x49, 0x45, 0x4e, 0x44, 0xae, 0x42, 0x60, 0x82
        };

        constexpr const unsigned char CircleQuestion_bin[491] = {
            0x89, 0x50, 0x4e, 0x47, 0x0d, 0x0a, 0x1a, 0x0a, 0x00, 0x00, 0x00, 0x0d,
            0x49, 0x48, 0x44, 0x52, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x40,
            0x08, 0x06, 0x00, 0x00, 0x00, 0xaa, 0x69, 0x71, 0xde, 0x00, 0x00, 0x00,
            0x01, 0x73, 0x52, 0x47, 0x42, 0x00, 0xae, 0xce, 0x1c, 0xe9, 0x00, 0x00,
            0x01, 0xa5, 0x49, 0x44, 0x41, 0x54, 0x78, 0x9c, 0xed, 0x9a, 0xc1, 0x72,
            0xc3, 0x20, 0x0c, 0x44, 0xe5, 0x4e, 0x27, 0xe7, 0xf6, 0xb3, 0xd2, 0x0f,
            0x4e, 0x3f, 0xab, 0x3d, 0xf7, 0xe2, 0x1e, 0x5c, 0x62, 0x42, 0x01, 0x63,
            0x58, 0x09, 0x32, 0xec, 0xbb, 0x65, 0xec, 0x60, 0x6b, 0xb5, 0xc2, 0x58,
            0x58, 0x84, 0x10, 0x42, 0x08, 0x21, 0x84, 0x10, 0x42, 0x26, 0x64, 0xe9,
            0x70, 0xcd, 0xf5, 0xe0, 0xb8, 0xe9, 0x3d, 0x59, 0x5d, 0x6c, 0x0f, 0xfa,
            0xed, 0x96, 0x3f, 0xf3, 0xfb, 0xc3, 0xff, 0xa5, 0x7e, 0x7f, 0xda, 0x17,
            0xd8, 0x02, 0x3f, 0x0a, 0x3a, 0xc5, 0x2e, 0x86, 0xda, 0x7d, 0x6a, 0x0a,
            0xb0, 0x56, 0x07, 0x1e, 0xb2, 0x09, 0xa1, 0x72, 0xaf, 0x1a, 0x83, 0xb6,
            0x65, 0x3d, 0x85, 0x92, 0x1b, 0xd0, 0x02, 0xec, 0x59, 0xbf, 0x5c, 0x45,
            0x7e, 0x3e, 0xc1, 0xc3, 0x0b, 0xdc, 0x0d, 0x2f, 0xa8, 0x81, 0x24, 0x66,
            0xf9, 0xcb, 0x15, 0x38, 0xfc, 0x1f, 0xdb, 0x35, 0x8e, 0x9e, 0x24, 0xc5,
            0xa0, 0x94, 0x7c, 0x0c, 0xde, 0x0f, 0x3c, 0xe1, 0x82, 0xf5, 0x2b, 0x2e,
            0xce, 0xf2, 0x5e, 0xe8, 0x1a, 0x90, 0x13, 0x5e, 0x5b, 0x07, 0xf8, 0x47,
            0x26, 0xeb, 0xa9, 0xa0, 0xc3, 0x73, 0x8a, 0x45, 0x00, 0x80, 0x28, 0x81,
            0xa2, 0xd9, 0x3e, 0x97, 0xf1, 0x30, 0xe0, 0x12, 0xa1, 0x50, 0xa5, 0xd0,
            0x6a, 0xa1, 0xb4, 0xf5, 0x45, 0xee, 0xf6, 0x8f, 0x05, 0x14, 0xcb, 0xb2,
            0x7f, 0x9e, 0x55, 0x29, 0x20, 0x27, 0xc1, 0x22, 0x62, 0x19, 0xf7, 0x8f,
            0x39, 0x8a, 0x5c, 0x00, 0xa0, 0x45, 0x80, 0xa2, 0xec, 0xfb, 0xa8, 0xd4,
            0x76, 0x63, 0x29, 0x98, 0x39, 0xa0, 0x34, 0x78, 0xcb, 0x09, 0x50, 0x04,
            0x25, 0xc0, 0x41, 0xf6, 0xad, 0x83, 0x3a, 0x43, 0xad, 0x00, 0xe9, 0x99,
            0xbf, 0x71, 0xf5, 0x57, 0x55, 0xfb, 0x0d, 0x65, 0x60, 0x3e, 0x09, 0xe6,
            0xa8, 0x7a, 0x0a, 0x34, 0x32, 0x8c, 0x00, 0x3d, 0x82, 0x17, 0x19, 0x48,
            0x00, 0x87, 0xf5, 0x7c, 0x81, 0x5f, 0x0a, 0x9f, 0xa4, 0x57, 0xe6, 0x1d,
            0x5d, 0x1d, 0xd0, 0x3b, 0x78, 0x91, 0x01, 0x4b, 0xc0, 0x1a, 0x0a, 0x50,
            0xf9, 0xbf, 0x25, 0xe8, 0xde, 0xee, 0x68, 0x34, 0x41, 0x8e, 0x68, 0x78,
            0x21, 0xc2, 0x38, 0x40, 0xa3, 0xf5, 0x65, 0x84, 0x4e, 0x09, 0xf4, 0x70,
            0x41, 0x25, 0x7a, 0xfd, 0x00, 0x2b, 0x57, 0x0c, 0xdb, 0x0f, 0x78, 0x12,
            0x17, 0x20, 0x9a, 0xa2, 0xd5, 0x2e, 0x68, 0x5e, 0x07, 0x00, 0x1a, 0xa3,
            0x08, 0x07, 0x3c, 0x3e, 0x11, 0x0a, 0xad, 0x1f, 0xbe, 0xf5, 0x9d, 0x7e,
            0x0b, 0x04, 0x75, 0x85, 0x75, 0x4a, 0xc0, 0x89, 0xf0, 0x04, 0x65, 0x80,
            0x12, 0xc0, 0x76, 0x5d, 0x00, 0xdc, 0x1d, 0xd2, 0xdb, 0x1a, 0x73, 0x64,
            0xb6, 0xc8, 0x7a, 0x74, 0x81, 0x43, 0xb8, 0x39, 0x8a, 0x1c, 0x2c, 0x60,
            0xda, 0xed, 0x71, 0x9f, 0xa9, 0x3f, 0x90, 0xf0, 0x99, 0xf6, 0x13, 0x99,
            0x18, 0x43, 0x7d, 0x24, 0x45, 0x08, 0x21, 0x84, 0x10, 0x42, 0x08, 0x21,
            0x53, 0xf2, 0x0b, 0xf7, 0xc4, 0x90, 0x13, 0x26, 0x7c, 0xe7, 0x50, 0x00,
            0x00, 0x00, 0x00, 0x49, 0x45, 0x4e, 0x44, 0xae, 0x42, 0x60, 0x82
        };

        constexpr const unsigned char CircleWarning_bin[450] = {
            0x89, 0x50, 0x4e, 0x47, 0x0d, 0x0a, 0x1a, 0x0a, 0x00, 0x00, 0x00, 0x0d,
            0x49, 0x48, 0x44, 0x52, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x40,
            0x08, 0x06, 0x00, 0x00, 0x00, 0xaa, 0x69, 0x71, 0xde, 0x00, 0x00, 0x00,
            0x01, 0x73, 0x52, 0x47, 0x42, 0x00, 0xae, 0xce, 0x1c, 0xe9, 0x00, 0x00,
            0x01, 0x7c, 0x49, 0x44, 0x41, 0x54, 0x78, 0x9c, 0xed, 0x9a, 0x6f, 0x0e,
            0x82, 0x30, 0x0c, 0xc5, 0x8b, 0xf1, 0x28, 0x78, 0x05, 0x13, 0xbd, 0x7f,
            0x34, 0xe1, 0x0a, 0x72, 0x17, 0xfc, 0x02, 0x64, 0xe0, 0xfe, 0x30, 0xf6,
            0x4a, 0x25, 0x7b, 0xbf, 0x6f, 0x46, 0xdc, 0xda, 0xb7, 0xb6, 0x42, 0x8b,
            0x08, 0x21, 0x84, 0x10, 0x42, 0x08, 0x21, 0x84, 0x54, 0x48, 0x63, 0xb0,
            0xe7, 0x90, 0xf8, 0xfe, 0x50, 0x9b, 0x8e, 0xda, 0x6c, 0x76, 0xfa, 0xf3,
            0x88, 0x5f, 0x78, 0x7b, 0x2f, 0x3e, 0xaa, 0xdb, 0xa7, 0xbd, 0xc1, 0x20,
            0x92, 0x76, 0x3a, 0x84, 0x23, 0x86, 0x9a, 0x9d, 0x9a, 0x02, 0x0c, 0x7b,
            0x1d, 0x5f, 0x33, 0x0a, 0xa1, 0x62, 0xab, 0xc6, 0xa2, 0x9b, 0x4e, 0xbd,
            0x7d, 0xfd, 0x96, 0x82, 0xfe, 0x19, 0x36, 0x47, 0x2b, 0x1a, 0xd0, 0x02,
            0xcc, 0xa7, 0xde, 0xde, 0x45, 0xfa, 0xce, 0x7f, 0x91, 0xcf, 0xf9, 0x89,
            0x98, 0x08, 0x22, 0xf8, 0x68, 0xb8, 0xa0, 0x16, 0x12, 0x4f, 0xc8, 0xb7,
            0x77, 0xe0, 0xea, 0x23, 0xe3, 0x1e, 0xa9, 0x7f, 0x92, 0xcd, 0xa0, 0x04,
            0x58, 0x38, 0xaf, 0xe1, 0xb8, 0x0b, 0x52, 0x04, 0x64, 0x04, 0x88, 0x88,
            0xbe, 0xf3, 0x68, 0x10, 0x02, 0xc0, 0xaa, 0x7d, 0x0e, 0xa8, 0x28, 0x28,
            0x15, 0x20, 0x1a, 0xfa, 0xa1, 0x22, 0x88, 0x02, 0x21, 0x02, 0x3c, 0x05,
            0xce, 0x46, 0x89, 0x00, 0xa6, 0xa7, 0x3f, 0x51, 0x1a, 0x05, 0x8c, 0x00,
            0xc4, 0x22, 0x56, 0xa7, 0x8f, 0x60, 0xaf, 0x00, 0xc1, 0xca, 0x6f, 0xe1,
            0x7c, 0x49, 0x1a, 0x30, 0x05, 0xac, 0x0d, 0xb0, 0x86, 0x02, 0x58, 0x1b,
            0x60, 0x8d, 0x89, 0x00, 0xa1, 0x47, 0xde, 0xd4, 0xa3, 0xb0, 0x06, 0xd7,
            0xc3, 0x77, 0x1c, 0xb1, 0x70, 0xd6, 0x07, 0x53, 0x60, 0xe7, 0xef, 0x9a,
            0x55, 0xf7, 0x76, 0xc6, 0xe2, 0x71, 0xb8, 0xa4, 0x4b, 0x04, 0x49, 0x81,
            0xbe, 0xcb, 0x77, 0x3c, 0xb7, 0x27, 0xa8, 0x85, 0x4a, 0x0a, 0xa4, 0xc4,
            0x08, 0xf5, 0x04, 0x63, 0xbd, 0x42, 0x2d, 0x4a, 0x04, 0x58, 0xa4, 0x81,
            0xd5, 0xfd, 0x7f, 0x69, 0x93, 0x54, 0xad, 0x08, 0x9e, 0xa5, 0x35, 0x56,
            0x2a, 0x80, 0x69, 0x14, 0x20, 0x5a, 0xe4, 0x88, 0x08, 0xc8, 0x16, 0x01,
            0x71, 0x23, 0x84, 0x9a, 0x0f, 0xa0, 0xca, 0x6e, 0x70, 0x26, 0xa0, 0x15,
            0x15, 0x28, 0x01, 0x50, 0x35, 0xe0, 0xd0, 0xfb, 0x02, 0xe4, 0x74, 0x48,
            0x6d, 0x34, 0x36, 0x11, 0x1b, 0x91, 0xed, 0x01, 0x3d, 0x1a, 0x33, 0x1b,
            0x8e, 0xe6, 0x72, 0x96, 0xe1, 0xa8, 0x4b, 0xb5, 0xe3, 0x71, 0x97, 0xaa,
            0x5f, 0x90, 0x70, 0xa9, 0xf6, 0x15, 0x19, 0x1f, 0x7f, 0xf5, 0x92, 0x14,
            0x21, 0x84, 0x10, 0x42, 0x08, 0x21, 0x84, 0x54, 0xc9, 0x17, 0x8c, 0x09,
            0x6e, 0xbd, 0x41, 0x41, 0x12, 0x2c, 0x00, 0x00, 0x00, 0x00, 0x49, 0x45,
            0x4e, 0x44, 0xae, 0x42, 0x60, 0x82
        };

        VMessageBox::VMessageBox()
        {
            btnOne.SetPosition({vmbRect.x, vmbRect.y});
            btnTwo.SetPosition({vmbRect.x, vmbRect.y});
            btnThree.SetPosition({vmbRect.x, vmbRect.y});

            btnOne.SetMainColorBtn(GRAY);
            btnTwo.SetMainColorBtn(GRAY);
            btnThree.SetMainColorBtn(GRAY);
            btnOne.SetOutlineColorBtn(DARKGRAY);
            btnTwo.SetOutlineColorBtn(DARKGRAY);
            btnThree.SetOutlineColorBtn(DARKGRAY);
        }

        VMessageBox::VMessageBox(const char *title, const char *description, const Vector2& position)
        : title(title), description(description), position(position)
        {
            btnOne.SetPosition({vmbRect.x, vmbRect.y});
            btnTwo.SetPosition({vmbRect.x, vmbRect.y});
            btnThree.SetPosition({vmbRect.x, vmbRect.y});

            btnOne.SetMainColorBtn(GRAY);
            btnTwo.SetMainColorBtn(GRAY);
            btnThree.SetMainColorBtn(GRAY);
            btnOne.SetOutlineColorBtn(DARKGRAY);
            btnTwo.SetOutlineColorBtn(DARKGRAY);
            btnThree.SetOutlineColorBtn(DARKGRAY);
        }

        VMessageBox::VMessageBox(const char *title, const char *description, const Vector2& position,  const VMSBoxMod& btnType)
        : title(title), description(description), position(position), btnType(btnType)
        {   
            btnOne.SetPosition({vmbRect.x, vmbRect.y});
            btnTwo.SetPosition({vmbRect.x, vmbRect.y});
            btnThree.SetPosition({vmbRect.x, vmbRect.y});

            btnOne.SetMainColorBtn(GRAY);
            btnTwo.SetMainColorBtn(GRAY);
            btnThree.SetMainColorBtn(GRAY);
            btnOne.SetOutlineColorBtn(DARKGRAY);
            btnTwo.SetOutlineColorBtn(DARKGRAY);
            btnThree.SetOutlineColorBtn(DARKGRAY);
        }

        VMessageBox::VMessageBox(const char *title, const char *description, const Vector2& position,  const VMSBoxMod& btnType, const VMSBoxMod& mode)
        : title(title), description(description), position(position), btnType(btnType), mode(mode)
        {
            btnOne.SetPosition({vmbRect.x, vmbRect.y});
            btnTwo.SetPosition({vmbRect.x, vmbRect.y});
            btnThree.SetPosition({vmbRect.x, vmbRect.y});

            btnOne.SetMainColorBtn(GRAY);
            btnTwo.SetMainColorBtn(GRAY);
            btnThree.SetMainColorBtn(GRAY);
            btnOne.SetOutlineColorBtn(DARKGRAY);
            btnTwo.SetOutlineColorBtn(DARKGRAY);
            btnThree.SetOutlineColorBtn(DARKGRAY);
        }

        VMessageBox::~VMessageBox() { Close(); }

        Texture VMessageBox::CircleErrorIcon = {0};
        Texture VMessageBox::CircleQuestionIcon = {0};
        Texture VMessageBox::CircleWarningIcon = {0};
        Texture VMessageBox::CircleInformationIcon = {0};
        bool VMessageBox::iconsLoaded = false;

        void VMessageBox::EnsureIconsLoaded()
        {
            if (iconsLoaded) return;

            Image imgError = LoadImageFromMemory(".png", CircleError_bin, sizeof(CircleError_bin));
            Image imgQuestion = LoadImageFromMemory(".png", CircleQuestion_bin, sizeof(CircleQuestion_bin));
            Image imgWarning = LoadImageFromMemory(".png", CircleWarning_bin, sizeof(CircleWarning_bin));
            Image imgInfo = LoadImageFromMemory(".png", CircleInformation_bin, sizeof(CircleInformation_bin));

            CircleErrorIcon = LoadTextureFromImage(imgError);
            CircleQuestionIcon = LoadTextureFromImage(imgQuestion);
            CircleWarningIcon = LoadTextureFromImage(imgWarning);
            CircleInformationIcon = LoadTextureFromImage(imgInfo);

            UnloadImage(imgError);
            UnloadImage(imgQuestion);
            UnloadImage(imgWarning);
            UnloadImage(imgInfo);

            iconsLoaded = true;
        }

        void VMessageBox::Close()
        {
            if (!iconsLoaded) return;
            UnloadTexture(CircleErrorIcon);
            UnloadTexture(CircleQuestionIcon);
            UnloadTexture(CircleWarningIcon);
            UnloadTexture(CircleInformationIcon);
            iconsLoaded = false;
        }

        void VMessageBox::UpdateLayout()
        {
            Label lbl1("OK", {0, 0}, 18, BLACK, WHITE);
            Label lbl2("Cancel", {0, 0}, 18, BLACK, WHITE);
            Label lbl3("Ignore", {0, 0}, 18, BLACK, WHITE);

            int activeButtons = 1;

            switch (btnType)
            {
            case VMSBoxMod::MB_OK:
                lbl1.SetText("OK");
                activeButtons = 1;
                break;
            case VMSBoxMod::MB_OKCANCEL:
                lbl1.SetText("OK");
                lbl2.SetText("Cancel");
                activeButtons = 2;
                break;
            case VMSBoxMod::MB_YESNO:
                lbl1.SetText("Yes");
                lbl2.SetText("No");
                activeButtons = 2;
                break;
            case VMSBoxMod::MB_RETRYCANCEL:
                lbl1.SetText("Retry");
                lbl2.SetText("Cancel");
                activeButtons = 2;
                break;
            case VMSBoxMod::MB_ABORTRETRYIGNORE:
                lbl1.SetText("Abort");
                lbl2.SetText("Retry");
                lbl3.SetText("Ignore");
                activeButtons = 3;
                break;
            case VMSBoxMod::MB_YESNOCANCEL:
                lbl1.SetText("Yes");
                lbl2.SetText("No");
                lbl3.SetText("Cancel");
                activeButtons = 3;
                break;
            case VMSBoxMod::MB_CANCELTRYCONTINUE:
                lbl1.SetText("Cancel");
                lbl2.SetText("Try Again");
                lbl3.SetText("Continue");
                activeButtons = 3;
                break;
            default:
                lbl1.SetText("OK");
                activeButtons = 1;
                break;
            }

            btnOne.SetTextClass(lbl1);
            btnTwo.SetTextClass(lbl2);
            btnThree.SetTextClass(lbl3);

            auto GetBtnWidth = [](const Label& lbl) {
                return static_cast<float>(GET_DEFAULT_TEXT_WIDTH(lbl.GetText().c_str(), lbl.GetSize()) + 10);
            };
            auto GetBtnHeight = [](const Label& lbl) {
                return static_cast<float>(GET_DEFAULT_TEXT_HEIGHT(lbl.GetText().c_str(), lbl.GetSize()) + 5);
            };

            float w1 = GetBtnWidth(lbl1);
            float w2 = GetBtnWidth(lbl2);
            float w3 = GetBtnWidth(lbl3);
            float btnH = GetBtnHeight(lbl1);

            float btnSpacing = 12.0f;
            float totalBtnWidth = w1;

            if (activeButtons == 2) totalBtnWidth = w1 + btnSpacing + w2;
            else if (activeButtons == 3) totalBtnWidth = w1 + btnSpacing + w2 + btnSpacing + w3;

            float titleW = static_cast<float>(MeasureText(title ? title : "", 20)) + 40.0f;
            float descW  = static_cast<float>(MeasureText(description ? description : "", 16)) + 40.0f;
            float minReqWidth = totalBtnWidth + 40.0f;

            vmbRect.width = std::max({ 355.0f, titleW, descW, minReqWidth });
            
            vmbRect.height = 150.0f; 

            float paddingBottom = 15.0f;
            float targetY = vmbRect.y + vmbRect.height - paddingBottom - btnH;

            float posOffsetY = targetY + 5.0f;

            float startX = vmbRect.x + (vmbRect.width - totalBtnWidth) / 2.0f;

            if (activeButtons == 1)
            {
                btnOne.SetPosition({ startX + 5.0f, posOffsetY });
            }
            else if (activeButtons == 2)
            {
                btnOne.SetPosition({ startX + 5.0f, posOffsetY });
                btnTwo.SetPosition({ startX + w1 + btnSpacing + 5.0f, posOffsetY });
            }
            else if (activeButtons == 3)
            {
                btnOne.SetPosition({ startX + 5.0f, posOffsetY });
                btnTwo.SetPosition({ startX + w1 + btnSpacing + 5.0f, posOffsetY });
                btnThree.SetPosition({ startX + w1 + btnSpacing + w2 + (btnSpacing * 2.0f) + 5.0f, posOffsetY });
            }
        }

        void VMessageBox::SetTitle(const char *title){this->title = title;}
        void VMessageBox::SetDescribe(const char *description){this->description = description;}
        void VMessageBox::SetPosition(const Vector2& position){this->position = position;}
        const char *VMessageBox::GetTitle(){return title;}
        const char *VMessageBox::GetDescribe(){return description;}
        Vector2 VMessageBox::GetPosition(){return position;}
        void VMessageBox::Appear(){isAppear = true;}
        std::size_t VMessageBox::Update()
        { 
            Vector2 mousePos = GetMousePosition();
            if (CheckCollisionPointRec(mousePos, vmbRect))
            {
                if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
                {
                    vmbRect.x = mousePos.x - (vmbRect.width / 2.0f);
                    vmbRect.y = mousePos.y - (vmbRect.height / 2.0f);
                    btnOne.SetPosition({vmbRect.x, vmbRect.y});
                    btnTwo.SetPosition({vmbRect.x, vmbRect.y});
                    btnThree.SetPosition({vmbRect.x, vmbRect.y});
                    UpdateLayout();
                }
            }

            if (btnOne.Update()) isAppear = false;
            if (btnTwo.Update()) isAppear = false;
            if (btnThree.Update()) isAppear = false;

            if (btnType == VMSBoxMod::MB_OK)
            {
                if (btnOne.Update())
                    return MB_BTN_OK;
            }
            if (btnType == VMSBoxMod::MB_OKCANCEL)
            {
                if (btnOne.Update())
                    return MB_BTN_OK;
                if (btnTwo.Update())
                    return MB_BTN_CANCEL;
            }
            if (btnType == VMSBoxMod::MB_YESNO)
            {
                if (btnOne.Update())
                    return MB_BTN_YES;
                if (btnTwo.Update())
                    return MB_BTN_NO;
            }
            if (btnType == VMSBoxMod::MB_RETRYCANCEL)
            {
                if (btnOne.Update())
                    return MB_BTN_RETRY;
                if (btnTwo.Update())
                    return MB_BTN_CANCEL;
            }
            if (btnType == VMSBoxMod::MB_ABORTRETRYIGNORE)
            {
                if (btnOne.Update())
                    return MB_BTN_ABORT;
                if (btnTwo.Update())
                    return MB_BTN_RETRY;
                if (btnThree.Update())
                    return MB_BTN_IGNORE;
            }
            if (btnType == VMSBoxMod::MB_YESNOCANCEL)
            {
                if (btnOne.Update())
                    return MB_BTN_YES;
                if (btnTwo.Update())
                    return MB_BTN_NO;
                if (btnThree.Update())
                    return MB_BTN_CANCEL;
            }
            if (btnType == VMSBoxMod::MB_CANCELTRYCONTINUE)
            {
                if (btnOne.Update())
                    return MB_BTN_CANCEL;
                if (btnTwo.Update())
                    return MB_BTN_TRY;
                if (btnThree.Update())
                    return MB_BTN_CONTINUE;
            }
            
            return 0; 
        }
        void VMessageBox::Draw()
        {
            if (!isAppear) return;

            EnsureIconsLoaded();

            UpdateLayout();

            DrawRectangleRec({vmbRect.x - 1.5f, vmbRect.y - 1.5f, vmbRect.width + 3.5f, vmbRect.height + 3.5f}, BLACK);
            DrawRectangleRec(vmbRect, WHITE);

            if (btnType == VMSBoxMod::MB_OK)
            {
                btnOne.Draw();
            }
            if (btnType == VMSBoxMod::MB_OKCANCEL ||
                btnType == VMSBoxMod::MB_YESNO ||
                btnType == VMSBoxMod::MB_RETRYCANCEL)
            {
                btnOne.Draw();
                btnTwo.Draw();
            }
            if (btnType == VMSBoxMod::MB_ABORTRETRYIGNORE ||
                btnType == VMSBoxMod::MB_YESNOCANCEL ||
                btnType == VMSBoxMod::MB_CANCELTRYCONTINUE)
            {
                btnOne.Draw();
                btnTwo.Draw();
                btnThree.Draw();
            }

            int titleFontSize = 20;
            int descFontSize = 16;
            float paddingX = 20.0f;
            float paddingTop = 15.0f;
            float spacingBetweenText = 8.0f;

            float titleX = vmbRect.x + paddingX;
            float titleY = vmbRect.y + paddingTop;

            if (title && title[0] != '\0')
                DrawText(title, static_cast<int>(titleX), static_cast<int>(titleY), titleFontSize, BLACK);

            float titleH = static_cast<float>(GET_DEFAULT_TEXT_HEIGHT(title ? title : "", titleFontSize));
            float descX = vmbRect.x + paddingX;
            float descY = titleY + titleH + spacingBetweenText;

            if (description && description[0] != '\0')
                DrawText(description, static_cast<int>(descX), static_cast<int>(descY), descFontSize, DARKGRAY);

            float padding = 1.0f;
            float iconSize = 42.0f;
            Vector2 iconPos = {
                (vmbRect.x + vmbRect.width) - iconSize - padding,
                vmbRect.y + padding
            };

            Texture *iconToDraw = nullptr;

            switch (mode)
            {
            case VMSBoxMod::MB_ICONWARNING: {
                iconToDraw = &CircleWarningIcon;
                break;
                }
            case VMSBoxMod::MB_ICONINFORMATION: {
                iconToDraw = &CircleInformationIcon;
                break;
                }
            case VMSBoxMod::MB_ICONQUESTION: {
                iconToDraw = &CircleQuestionIcon;
                break;
                }
            case VMSBoxMod::MB_ICONERROR: {
                iconToDraw = &CircleErrorIcon;
                break;
                }
            }

            if (iconToDraw->id > 0)
            {
                float scale = iconSize / static_cast<float>(iconToDraw->width);
                DrawTextureEx(*iconToDraw, iconPos, 0.0f, scale, WHITE);
            }
        }
    }
}