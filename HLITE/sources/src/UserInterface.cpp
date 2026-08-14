#include "../include/HLITE/Metadata.hpp"
#include "../include/HLITE/UserInterface.hpp"

#include <cstdio>
#include <algorithm>
#include <string>

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

        void Button::SetTextClass(const Label& text) { this->text = text; }
        void Button::SetPosition(Vector2 position) { this->position = position; }
        void Button::SetMainColorBtn(Color mainColor) { mainColorBtn = mainColor; }
        void Button::SetOutlineColorBtn(Color outlineColor) { outlineColorBtn = outlineColor; }
        void Button::SetModePress(ButtonPressType type) {modePress = type;}

        bool Button::Update()
        {
            Vector2 mousePos = GetMousePosition();
            int touchCount = GetTouchPointCount();
        
            bool touched = false;

            for (int i = 0; i < touchCount; ++i)
            {
                Vector2 touchPos = GetTouchPosition(i);
                if (CheckCollisionPointRec(touchPos, rect))
                {
                    touched = true;
                    break;
                }
            }

            if (modePress == ButtonPressType::DOWN)
            {
                if (touched) {
                    isClicked = true;
                    isTouched = true;
                    return true;
                }
            }
            else
            {
                if (touched && !isTouched) {
                    isClicked = true;
                    isTouched = true;
                    return true;
                }
            }

            if (!touched) {
                isTouched = false;
                isClicked = false;
            }

            if (!CheckCollisionPointRec(mousePos, rect))
            {
                isHover = false;
                isClicked = false;
            }
            else 
            {
                isHover = true;
                if (modePress == ButtonPressType::DOWN)
                {
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
                else{
                    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
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
                if (!isClicked || !isTouched)
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

        void Button::DrawWithRounded(float roundess)
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
                DrawRectangleRounded({rect.x - 1,
                    rect.y- 1,
                    rect.width + 2,
                    rect.height + 2},
                    roundess, 0, 
                    outlineColorBtn);
            
                // Foreground button
                DrawRectangleRounded({rect.x,
                    rect.y,
                    rect.width,
                    rect.height},
                    roundess, 0, 
                    mainColorBtn);
            }
            else
            {
                if (!isClicked)
                {
                    // Background button
                    DrawRectangleRounded({rect.x - 1,
                                          rect.y- 1,
                                          rect.width + 2,
                                          rect.height + 2},
                                          roundess, 0,
                                              (Color){.r = static_cast<unsigned char>(outlineColorBtn.r + 15),
                                                      .g = static_cast<unsigned char>(outlineColorBtn.g + 15),
                                                      .b = static_cast<unsigned char>(outlineColorBtn.b + 15),
                                                      .a = static_cast<unsigned char>(outlineColorBtn.a)});
                
                    // Foreground button
                    DrawRectangleRounded({rect.x,
                                          rect.y,
                                          rect.width,
                                          rect.height},
                                          roundess, 0, 
                                          (Color){.r = static_cast<unsigned char>(mainColorBtn.r + 10),
                                                  .g = static_cast<unsigned char>(mainColorBtn.g + 10),
                                                  .b = static_cast<unsigned char>(mainColorBtn.b + 10),
                                                  .a = static_cast<unsigned char>(mainColorBtn.a)});
                }
                else
                {
                    // Background button
                    DrawRectangleRounded({rect.x - 2,
                                          rect.y- 2,
                                          rect.width + 2,
                                          rect.height + 2},
                                          roundess, 0,
                                          (Color){.r = static_cast<unsigned char>(outlineColorBtn.r + 15),
                                                  .g = static_cast<unsigned char>(outlineColorBtn.g + 15),
                                                  .b = static_cast<unsigned char>(outlineColorBtn.b + 15),
                                                  .a = static_cast<unsigned char>(outlineColorBtn.a)});
                
                    // Foreground button
                    DrawRectangleRounded({rect.x,
                                          rect.y,
                                          rect.width,
                                          rect.height},
                                          roundess, 0,
                                          (Color){.r = static_cast<unsigned char>(outlineColorBtn.r + 15),
                                                  .g = static_cast<unsigned char>(outlineColorBtn.g + 15),
                                                  .b = static_cast<unsigned char>(outlineColorBtn.b + 15),
                                                  .a = static_cast<unsigned char>(outlineColorBtn.a)});
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

        void TextField::ClearSelection()
        {
            selectionStart = 0;
            selectionEnd = 0;
            selectionAnchor = 0;
            hasSelection = false;
            isSelectingText = false;
        }

        void TextField::SetSelection(int start, int end)
        {
            if (start < 0) start = 0;
            if (end < 0) end = 0;
            if (start > static_cast<int>(hndText.size())) start = static_cast<int>(hndText.size());
            if (end > static_cast<int>(hndText.size())) end = static_cast<int>(hndText.size());

            selectionStart = std::min(start, end);
            selectionEnd = std::max(start, end);
            hasSelection = selectionStart != selectionEnd;
        }

        int TextField::GetTextIndexAtPoint(float x) const
        {
            const int textStartX = static_cast<int>(textBox.x + boxPadding);
            int relativeX = static_cast<int>(x - textStartX);
            if (relativeX <= 0) return 0;

            for (std::size_t i = 0; i < hndText.size(); ++i)
            {
                std::string prefix = hndText.substr(0, i + 1);
                int prefixWidth = MeasureText(prefix.c_str(), textSize);
                if (relativeX <= prefixWidth)
                    return static_cast<int>(i + 1);
            }

            return static_cast<int>(hndText.size());
        }

        std::string TextField::GetSelectedText() const
        {
            if (!hasSelection) return "";

            int start = std::min(selectionStart, selectionEnd);
            int end = std::max(selectionStart, selectionEnd);
            return hndText.substr(start, end - start);
        }

        void TextField::Update()
        {
            if (!canEditable) return;

            Vector2 mousePos = GetMousePosition();
            if (CheckCollisionPointRec(mousePos, textBox)) mouseOnText = true;
            else mouseOnText = false;

            const bool ctrlPressed = IsKeyDown(KEY_LEFT_CONTROL) || IsKeyDown(KEY_RIGHT_CONTROL);

            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            {
                if (mouseOnText)
                {
                    isMouseFocusText = true;
                    int clickedIndex = GetTextIndexAtPoint(mousePos.x);
                    selectionAnchor = clickedIndex;

                    if (IsKeyDown(KEY_LEFT_SHIFT) || IsKeyDown(KEY_RIGHT_SHIFT))
                        SetSelection(selectionStart, clickedIndex);
                    else
                        SetSelection(clickedIndex, clickedIndex);

                    isSelectingText = true;
                }
                else
                {
                    isMouseFocusText = false;
                    ClearSelection();
                }
            }

            if (isMouseFocusText && IsMouseButtonDown(MOUSE_BUTTON_LEFT) && mouseOnText)
            {
                int dragIndex = GetTextIndexAtPoint(mousePos.x);
                SetSelection(selectionAnchor, dragIndex);
            }
            else if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
            {
                isSelectingText = false;
            }

            if (isMouseFocusText)
            {
                if (IsKeyPressed(KEY_ENTER))
                    isMouseFocusText = false;

                if (ctrlPressed && IsKeyPressed(KEY_A))
                {
                    SetSelection(0, static_cast<int>(hndText.size()));
                }

                if (ctrlPressed && IsKeyPressed(KEY_C) && hasSelection)
                {
                    SetClipboardText(GetSelectedText().c_str());
                }

                if ((ctrlPressed) && IsKeyPressed(KEY_V))
                {
                    const char *clipboardText = GetClipboardText();
                    if (clipboardText != nullptr && clipboardText[0] != '\0')
                    {
                        std::string pastedText = clipboardText;
                        if (hasSelection)
                        {
                            int start = std::min(selectionStart, selectionEnd);
                            int end = std::max(selectionStart, selectionEnd);
                            std::string updatedText = hndText.substr(0, start) + pastedText + hndText.substr(end);
                            if (static_cast<int>(updatedText.size()) > maxLength)
                                updatedText = updatedText.substr(0, maxLength);

                            hndText = updatedText;
                            selectionAnchor = start + static_cast<int>(pastedText.size());
                            SetSelection(selectionAnchor, selectionAnchor);
                        }
                        else
                        {
                            for (char ch : pastedText)
                            {
                                if (hndText.length() >= maxLength) break;

                                if ((ch >= 32) && (ch <= 125))
                                {
                                    if (mode == TextFieldMode::STATIC)
                                    {
                                        std::string nextText = hndText + ch;

                                        int nextTextWidth = MeasureText(nextText.c_str(), textSize);
                                        int cursorWidth = MeasureText("_", textSize);
                                        int maxAllowedWidth = (int)textBox.width - (boxPadding * 2) - cursorWidth;

                                        if (nextTextWidth < maxAllowedWidth)
                                            hndText.push_back(ch);
                                    }

                                    if (mode == TextFieldMode::DEFAULT)
                                        hndText.push_back(ch);
                                }
                            }
                        }
                    }
                }

                int key = GetCharPressed();
                while (key > 0)
                {
                    if ((key >= 32) && (key <= 125) && (hndText.length() < maxLength))
                    {
                        if (hasSelection)
                        {
                            int start = std::min(selectionStart, selectionEnd);
                            int end = std::max(selectionStart, selectionEnd);
                            std::string updatedText = hndText.substr(0, start) + static_cast<char>(key) + hndText.substr(end);
                            if (static_cast<int>(updatedText.size()) > maxLength)
                                updatedText = updatedText.substr(0, maxLength);

                            hndText = updatedText;
                            selectionAnchor = start + 1;
                            SetSelection(selectionAnchor, selectionAnchor);
                        }
                        else
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
                    }
                
                    key = GetCharPressed();
                }
            
                if (IsKeyDown(KEY_BACKSPACE))
                {
                    if (IsKeyPressed(KEY_BACKSPACE))
                    {
                        if (hasSelection)
                        {
                            int start = std::min(selectionStart, selectionEnd);
                            int end = std::max(selectionStart, selectionEnd);
                            hndText = hndText.substr(0, start) + hndText.substr(end);
                            selectionAnchor = start;
                            SetSelection(selectionAnchor, selectionAnchor);
                        }
                        else if (!hndText.empty())
                            hndText.pop_back();
                        return;
                    }

                    if (delay.GetIsDone()) delay.Reset();

                    if (delay.Update())
                    {
                        if (hasSelection)
                        {
                            int start = std::min(selectionStart, selectionEnd);
                            int end = std::max(selectionStart, selectionEnd);
                            hndText = hndText.substr(0, start) + hndText.substr(end);
                            selectionAnchor = start;
                            SetSelection(selectionAnchor, selectionAnchor);
                        }
                        else if (!hndText.empty())
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

            if (hasSelection)
            {
                int start = std::min(selectionStart, selectionEnd);
                int end = std::max(selectionStart, selectionEnd);
                int baseX = (int)textBox.x + boxPadding;
                int baseY = (int)textBox.y + boxPadding;

                for (int i = start; i < end; ++i)
                {
                    std::string prefix = hndText.substr(0, i);
                    int charStartX = baseX + MeasureText(prefix.c_str(), textSize);
                    std::string nextPrefix = hndText.substr(0, i + 1);
                    int charEndX = baseX + MeasureText(nextPrefix.c_str(), textSize);
                    int charWidth = std::max(1, charEndX - charStartX);

                    DrawRectangleRec((Rectangle){(float)charStartX, (float)baseY, (float)charWidth, (float)textSize + 2}, (Color){180, 200, 255, 180});
                }
            }
            
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

            Vector2 mousePos = GetMousePosition();
            if (CheckCollisionPointRec(mousePos, textBox)) mouseOnText = true;
            else mouseOnText = false;

            const bool ctrlPressed = IsKeyDown(KEY_LEFT_CONTROL) || IsKeyDown(KEY_RIGHT_CONTROL);

            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            {
                if (mouseOnText)
                {
                    isMouseFocusText = true;

                    int clickedIndex = static_cast<int>(hndText.size());
                    int lineHeight = textSize + 2;
                    int lineIndex = (textBox.height > 0) ? std::max(0, static_cast<int>((mousePos.y - (textBox.y + boxPadding)) / lineHeight)) : 0;

                    int currentLine = 0;
                    int lineStart = 0;
                    for (std::size_t i = 0; i <= hndText.size(); ++i)
                    {
                        if (i == hndText.size() || hndText[i] == '\n')
                        {
                            if (currentLine == lineIndex)
                            {
                                std::string line = hndText.substr(lineStart, i - lineStart);
                                int relativeX = static_cast<int>(mousePos.x - (textBox.x + boxPadding));
                                if (relativeX <= 0) { clickedIndex = lineStart; }
                                else
                                {
                                    for (std::size_t j = 0; j < line.size(); ++j)
                                    {
                                        std::string prefix = line.substr(0, j + 1);
                                        int prefixWidth = MeasureText(prefix.c_str(), textSize);
                                        if (relativeX <= prefixWidth)
                                        {
                                            clickedIndex = lineStart + static_cast<int>(j + 1);
                                            break;
                                        }
                                    }
                                    if (clickedIndex == static_cast<int>(hndText.size()))
                                        clickedIndex = lineStart + static_cast<int>(line.size());
                                }
                                break;
                            }

                            currentLine++;
                            lineStart = static_cast<int>(i + 1);
                        }
                    }

                    selectionAnchor = clickedIndex;
                    if (IsKeyDown(KEY_LEFT_SHIFT) || IsKeyDown(KEY_RIGHT_SHIFT))
                        SetSelection(selectionStart, clickedIndex);
                    else
                        SetSelection(clickedIndex, clickedIndex);

                    isSelectingText = true;
                }
                else
                {
                    isMouseFocusText = false;
                    ClearSelection();
                }
            }

            if (isMouseFocusText && IsMouseButtonDown(MOUSE_BUTTON_LEFT) && mouseOnText)
            {
                int dragIndex = static_cast<int>(hndText.size());
                int lineHeight = textSize + 2;
                int lineIndex = (textBox.height > 0) ? std::max(0, static_cast<int>((mousePos.y - (textBox.y + boxPadding)) / lineHeight)) : 0;

                int currentLine = 0;
                int lineStart = 0;
                for (std::size_t i = 0; i <= hndText.size(); ++i)
                {
                    if (i == hndText.size() || hndText[i] == '\n')
                    {
                        if (currentLine == lineIndex)
                        {
                            std::string line = hndText.substr(lineStart, i - lineStart);
                            int relativeX = static_cast<int>(mousePos.x - (textBox.x + boxPadding));
                            if (relativeX <= 0) { dragIndex = lineStart; }
                            else
                            {
                                for (std::size_t j = 0; j < line.size(); ++j)
                                {
                                    std::string prefix = line.substr(0, j + 1);
                                    int prefixWidth = MeasureText(prefix.c_str(), textSize);
                                    if (relativeX <= prefixWidth)
                                    {
                                        dragIndex = lineStart + static_cast<int>(j + 1);
                                        break;
                                    }
                                }
                                if (dragIndex == static_cast<int>(hndText.size()))
                                    dragIndex = lineStart + static_cast<int>(line.size());
                            }
                            break;
                        }

                        currentLine++;
                        lineStart = static_cast<int>(i + 1);
                    }
                }

                SetSelection(selectionAnchor, dragIndex);
            }
            else if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
            {
                isSelectingText = false;
            }

            if (isMouseFocusText)
            {
                if (IsKeyPressed(KEY_ENTER))
                {
                    if (hndText.length() < maxLength)
                        hndText.push_back('\n');
                }

                if (ctrlPressed && IsKeyPressed(KEY_A))
                {
                    SetSelection(0, static_cast<int>(hndText.size()));
                }

                if (ctrlPressed && IsKeyPressed(KEY_C) && hasSelection)
                {
                    SetClipboardText(GetSelectedText().c_str());
                }

                if (ctrlPressed && IsKeyPressed(KEY_V))
                {
                    const char *clipboardText = GetClipboardText();
                    if (clipboardText != nullptr && clipboardText[0] != '\0')
                    {
                        std::string pastedText = clipboardText;
                        if (hasSelection)
                        {
                            int start = std::min(selectionStart, selectionEnd);
                            int end = std::max(selectionStart, selectionEnd);
                            std::string updatedText = hndText.substr(0, start) + pastedText + hndText.substr(end);
                            if (static_cast<int>(updatedText.size()) > maxLength)
                                updatedText = updatedText.substr(0, maxLength);

                            hndText = updatedText;
                            selectionAnchor = start + static_cast<int>(pastedText.size());
                            SetSelection(selectionAnchor, selectionAnchor);
                        }
                        else
                        {
                            for (char ch : pastedText)
                            {
                                if (hndText.length() >= maxLength) break;

                                if ((ch >= 32) && (ch <= 125))
                                {
                                    if (mode == TextFieldMode::STATIC)
                                    {
                                        std::size_t lastNewline = hndText.find_last_of('\n');
                                        std::string lastLine = (lastNewline == std::string::npos) ? hndText : hndText.substr(lastNewline + 1);

                                        std::string nextText = lastLine + ch;
                                        int nextTextWidth = MeasureText(nextText.c_str(), textSize);
                                        int cursorWidth = MeasureText("_", textSize);
                                        int maxAllowedWidth = (int)textBox.width - (boxPadding * 2) - cursorWidth;

                                        if (nextTextWidth < maxAllowedWidth)
                                            hndText.push_back(ch);
                                    }

                                    if (mode == TextFieldMode::DEFAULT)
                                        hndText.push_back(ch);
                                }
                            }
                        }
                    }
                }
            
                int key = GetCharPressed();
                while (key > 0)
                {
                    if ((key >= 32) && (key <= 125) && (hndText.length() < maxLength))
                    {
                        if (hasSelection)
                        {
                            int start = std::min(selectionStart, selectionEnd);
                            int end = std::max(selectionStart, selectionEnd);
                            std::string updatedText = hndText.substr(0, start) + static_cast<char>(key) + hndText.substr(end);
                            if (static_cast<int>(updatedText.size()) > maxLength)
                                updatedText = updatedText.substr(0, maxLength);

                            hndText = updatedText;
                            selectionAnchor = start + 1;
                            SetSelection(selectionAnchor, selectionAnchor);
                        }
                        else
                        {
                            if (mode == TextFieldMode::STATIC)
                            {
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
                    }
                
                    key = GetCharPressed();
                }
            
                if (IsKeyDown(KEY_BACKSPACE))
                {
                    if (IsKeyPressed(KEY_BACKSPACE))
                    {
                        if (hasSelection)
                        {
                            int start = std::min(selectionStart, selectionEnd);
                            int end = std::max(selectionStart, selectionEnd);
                            hndText = hndText.substr(0, start) + hndText.substr(end);
                            selectionAnchor = start;
                            SetSelection(selectionAnchor, selectionAnchor);
                        }
                        else if (!hndText.empty())
                            hndText.pop_back();
                        return;
                    }
                
                    if (delay.GetIsDone()) delay.Reset();
                
                    if (delay.Update())
                    {
                        if (hasSelection)
                        {
                            int start = std::min(selectionStart, selectionEnd);
                            int end = std::max(selectionStart, selectionEnd);
                            hndText = hndText.substr(0, start) + hndText.substr(end);
                            selectionAnchor = start;
                            SetSelection(selectionAnchor, selectionAnchor);
                        }
                        else if (!hndText.empty())
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

            if (hasSelection)
            {
                int start = std::min(selectionStart, selectionEnd);
                int end = std::max(selectionStart, selectionEnd);
                int baseX = (int)textBox.x + boxPadding;
                int baseY = (int)textBox.y + boxPadding;

                for (int i = start; i < end; ++i)
                {
                    int line = 0;
                    int lineStart = 0;
                    bool found = false;

                    for (std::size_t j = 0; j <= hndText.size(); ++j)
                    {
                        if (j == hndText.size() || hndText[j] == '\n')
                        {
                            if (i >= lineStart && i < static_cast<int>(j))
                            {
                                std::string lineText = hndText.substr(lineStart, j - lineStart);
                                std::string prefix = lineText.substr(0, i - lineStart);
                                int charStartX = baseX + MeasureText(prefix.c_str(), textSize);
                                int charEndX = charStartX + std::max(1, MeasureText(lineText.substr(i - lineStart, 1).c_str(), textSize));
                                int charY = baseY + (line * (textSize + 2));
                                DrawRectangleRec((Rectangle){(float)charStartX, (float)charY, (float)(charEndX - charStartX), (float)textSize + 2}, (Color){180, 200, 255, 180});
                                found = true;
                                break;
                            }

                            line++;
                            lineStart = static_cast<int>(j + 1);
                        }
                    }

                    if (found)
                        continue;
                }
            }

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

        VMessageBox::VMessageBox(const char *title, const char *description, const Vector2& position,  const VMSBoxMod& btnType, const VMSBoxMod& icon)
        : title(title), description(description), position(position), btnType(btnType), mode(icon)
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
        void VMessageBox::SetButtonType(const VMSBoxMod& btnType){this->btnType = btnType;}
        void VMessageBox::SetIconType(const VMSBoxMod& icon){this->mode = icon;}
        const char *VMessageBox::GetTitle(){return title;}
        const char *VMessageBox::GetDescribe(){return description;}
        Vector2 VMessageBox::GetPosition(){return position;}
        Rectangle VMessageBox::GetRect(){return vmbRect;}
        bool VMessageBox::IsMBXApear(){return isAppear;}
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

        /*
         * SliderBar Class
        */

        SliderBar::SliderBar(float value) : value(value), isDragging(false){}
        SliderBar::SliderBar(float value, SliderBarMode mode) : value(value), mode(mode){}
        SliderBar::SliderBar(float value, SliderBarMode mode, Vector2 pos)
        {this->value = value; this->mode = mode; this->rect = {pos.x, pos.y, 0.0f, 0.0f}; this->isDragging = false;}
        SliderBar::SliderBar(float value, SliderBarMode mode, Vector2 pos, Vector2 size)
        {this->value = value; this->mode = mode; this->rect = {pos.x, pos.y, size.x, size.y}; this->isDragging = false;}
        SliderBar::SliderBar(float value, SliderBarMode mode, Vector2 pos, Vector2 size, Color rectCol)
        {this->value = value; this->mode = mode; this->rect = {pos.x, pos.y, size.x, size.y}; this->rectCol = rectCol; this->isDragging = false;}
        SliderBar::SliderBar(float value, SliderBarMode mode, Vector2 pos, Vector2 size, Color rectCol, Color sliderBarCol)
        {this->value = value; this->mode = mode; this->rect = {pos.x, pos.y, size.x, size.y}; this->rectCol = rectCol; this->sliderBarCol = sliderBarCol; this->isDragging = false;}
        SliderBar::SliderBar(float value, SliderBarMode mode, Vector2 pos, Vector2 size, float thickness, Color rectCol, Color sliderBarCol, Color outlineCol)
        {this->value = value; this->mode = mode; this->rect = {pos.x, pos.y, size.x, size.y}; this->thickness = thickness; this->rectCol = rectCol; this->sliderBarCol = sliderBarCol; this->outlineCol = outlineCol; this->isDragging = false;}

        void SliderBar::SetValue(float value){this->value = value;}
        void SliderBar::SetMode(SliderBarMode mode){this->mode = mode;}
        void SliderBar::SetPosition(Vector2 pos){this->rect.x = pos.x; this->rect.y = pos.y;}
        void SliderBar::SetSize(Vector2 size){this->rect.width = size.x; this->rect.height = size.y;}
        void SliderBar::SetThicknessLine(float thickness){this->thickness = thickness;}
        void SliderBar::SetColorBar(Color color){this->rectCol = color;}
        void SliderBar::SetSlidebarColor(Color color){this->sliderBarCol = color;}
        void SliderBar::SetOutlineCol(Color color){this->outlineCol = color;}
        float SliderBar::GetValue(){return value;}
        Vector2 SliderBar::GetPosition(){return Vector2(rect.x, rect.y);}
        Vector2 SliderBar::GetSize(){return Vector2(rect.width, rect.height);}
        void SliderBar::Update()
        {
            if (mode == SliderBarMode::VERTICAL)
            {
                const Vector2 mousePos = GetMousePosition();
                const float innerPadding = 3.0f;
                const float barWidth = rect.width - 7.0f;
                const float maxHeight = rect.height - (innerPadding * 2.0f);
                const float minY = rect.y + innerPadding;
                const float maxY = rect.y + rect.height - innerPadding;

                if (maxHeight <= 0.0f)
                {
                    value = 0.0f;
                    sliderBar = (Rectangle){.x = rect.x + innerPadding, .y = minY, .width = barWidth, .height = 0.0f};
                    isDragging = false;
                    return;
                }

                sliderBar = (Rectangle){.x = rect.x + innerPadding,
                                        .y = minY,
                                        .width = barWidth,
                                        .height = value};

                const bool hoveredTrack = CheckCollisionPointRec(mousePos, rect);
                const bool hoveredFill = CheckCollisionPointRec(mousePos, sliderBar);

                if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && (hoveredTrack || hoveredFill))
                    isDragging = true;

                if (isDragging && IsMouseButtonDown(MOUSE_BUTTON_LEFT))
                {
                    float nextValue = mousePos.y - minY;
                    if (nextValue < 0.0f) nextValue = 0.0f;
                    if (nextValue > maxHeight) nextValue = maxHeight;
                    value = nextValue;
                }
                else if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
                {
                    isDragging = false;
                }

                if (!isDragging)
                {
                    const float wheelMove = GetMouseWheelMove();
                    if (hoveredTrack && wheelMove != 0.0f)
                    {
                        value += wheelMove * 10.0f;
                        if (value < 0.0f) value = 0.0f;
                        if (value > maxHeight) value = maxHeight;
                    }
                }

                sliderBar = (Rectangle){.x = rect.x + innerPadding,
                                        .y = minY,
                                        .width = barWidth,
                                        .height = value};
            }
            else
            {
                const Vector2 mousePos = GetMousePosition();
                const float innerPadding = 3.0f;
                const float barHeight = rect.height - 7.0f;
                const float maxWidth = rect.width - (innerPadding * 2.0f);
                const float minX = rect.x + innerPadding;
                const float maxX = rect.x + rect.width - innerPadding;

                if (maxWidth <= 0.0f)
                {
                    value = 0.0f;
                    sliderBar = (Rectangle){.x = minX, .y = rect.y + innerPadding, .width = 0.0f, .height = barHeight};
                    isDragging = false;
                    return;
                }

                const bool hoveredTrack = CheckCollisionPointRec(mousePos, rect);
                const bool hoveredFill = CheckCollisionPointRec(mousePos, sliderBar);

                if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && (hoveredTrack || hoveredFill))
                    isDragging = true;

                if (isDragging && IsMouseButtonDown(MOUSE_BUTTON_LEFT))
                {
                    float nextValue = mousePos.x - minX;
                    if (nextValue < 0.0f) nextValue = 0.0f;
                    if (nextValue > maxWidth) nextValue = maxWidth;
                    value = nextValue;
                }
                else if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
                {
                    isDragging = false;
                }

                if (!isDragging)
                {
                    const float wheelMove = GetMouseWheelMove();
                    if (hoveredTrack && wheelMove != 0.0f)
                    {
                        value += wheelMove * 10.0f;
                        if (value < 0.0f) value = 0.0f;
                        if (value > maxWidth) value = maxWidth;
                    }
                }

                sliderBar = (Rectangle){.x = minX,
                                        .y = rect.y + innerPadding,
                                        .width = value,
                                        .height = barHeight};
            }
        }
        void SliderBar::Draw()
        {
            Rectangle rectLines;
            if (mode == SliderBarMode::VERTICAL)
            {
                sliderBar = (Rectangle){.x = rect.x + 3.0f,
                                        .y = rect.y + 3.0f,
                                        .width = rect.width - 7.0f,
                                        .height = (value < (rect.height - 4.0f)) ? value : rect.height - 4.0f};

                rectLines = (Rectangle){.x = rect.x - 1.0f,
                                                  .y = rect.y - 1.0f,
                                                  .width = rect.width + 1.0f,
                                                  .height = rect.height + 1.0f};
            }
            else
            {
                sliderBar = (Rectangle){.x = rect.x + 3.0f,
                                        .y = rect.y + 3.0f,
                                        .width = (value < (rect.width - 4.0f)) ? value : rect.width - 4.0f,
                                        .height = rect.height - 7.0f};

                rectLines = (Rectangle){.x = rect.x - 1.0f,
                                                  .y = rect.y - 1.0f,
                                                  .width = rect.width + 1.0f,
                                                  .height = rect.height + 1.0f};
            }

            DrawRectangleRec(rect, rectCol);
            DrawRectangleRec(sliderBar, sliderBarCol);

            Vector2 mousePos = GetMousePosition();
            if (CheckCollisionPointRec(mousePos, rect))
                DrawRectangleLinesEx(rectLines, thickness, outlineCol);
        }
    }
}