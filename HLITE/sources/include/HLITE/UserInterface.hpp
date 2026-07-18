#pragma once

#include <string>

#include "Preprocessor.hpp"
#include "Utility.hpp"

namespace HLITE
{
    // User interfaces support.
    namespace UI
    {
        // Text field all mode input text.
        typedef enum
        {
            DEFAULT,
            STATIC
        } TextFieldMode;

        // Virtual message box all mode.
        typedef enum
        {
            MB_DEFAULT,
            MB_ICONERROR,
            MB_ICONWARNING,
            MB_ICONQUESTION,
            MB_ICONINFORMATION
        } VMessageBoxMode;

        // Primitive label (default).
        class Label
        {
        public:
            Label(){}
            Label(const char *text) : 
            text(text), position({0.0f, 0.0f}), size(25), textOutline(BLACK), textColor(WHITE) {}
            Label(const char* text, Vector2 position, int size, Color textOutline, Color textColor) :
            text(text), position(position), size(size), textOutline(textOutline), textColor(textColor) {}

            void SetText(const char* text) { this->text = text; }
            void SetPosition(Vector2 position) { this->position = position; }
            void SetSize(int size) { this->size = size; }
            void SetTextOutline(Color color) { textOutline = color; }
            void SetTextColor(Color color) { textColor = color; }

            std::string GetText() { return text; }
            Vector2 GetPosition() { return position; }
            int GetSize() { return size; }
            Color GetOutlineColor() { return textOutline; }
            Color GetColor() { return textColor; }

            // Render text in window.
            virtual void Draw(unsigned char opacity);
            // Render text with shadow in window.
            virtual void DrawWithShadow(float shadowRange, unsigned char opacity);
            // Render text with outline in window (thickness can only be 0 - 3).
            virtual void DrawWithOutline(float thick, unsigned char opacity);

        private:
            std::string text;
            Vector2 position;
            int size;
            Color textOutline;
            Color textColor;
        };

        // Modern label (primitive label extend)
        class LabelEx : public Label
        {
        public:
            explicit LabelEx(){}
            explicit LabelEx(Font& font, const char *text) : font(font), text(text), position({0.0f, 0.0f}), rotation(0.0f), fontSize(25), spacing(1), textOutline(BLACK), textColor(WHITE) {}
            explicit LabelEx(Font& textFont, std::string text, Vector2 position, float rotation, int size, float spacing, Color textOutline, Color textColor) :
            font(textFont), text(text), position(position), rotation(rotation), fontSize(size), spacing(spacing), textOutline(textOutline), textColor(textColor) {}

            void SetFont(Font textFont) { font = textFont; }
            void SetRotation(float rotation) {this->rotation = rotation; }
            void SetSpacing(float spacing) { this->spacing = spacing; }
            
            Font GetFont() { return font; }
            Vector2 GetOrigin() { return origin; }
            float GetRotation() { return rotation; }
            float GetSpacing() { return spacing; }

            // Render text in window.
            void Draw(unsigned char opacity) override;
            // Render text with shadow in window.
            void DrawWithShadow(float shadowRange, unsigned char opacity) override;
            // Renter text with outline in window.
        private:
            Font font;
            std::string text;
            Vector2 position;
            float rotation;
            int fontSize;
            float spacing;
            Color textOutline;
            Color textColor;
            Vector2 origin;
            bool isErrorMessage;
        };

        // Primitive button (default).
        class Button
        {
        public:
            explicit Button(){}
            explicit Button(const Label& text) : text(text), position({0.0f, 0.0f}), isHover(false), isClicked(false),
            outlineColorBtn(BLACK), mainColorBtn(WHITE) {}
            explicit Button(
                const Label& text,
                Vector2 position,
                Color OutlineColorBtn, 
                Color MainColorBtn
            ) : text(text), position(position), isHover(false), isClicked(false), 
            outlineColorBtn(OutlineColorBtn), mainColorBtn(MainColorBtn) {}

            virtual void SetTextClass(const Label& text) { this->text = text; }
            virtual void SetPosition(Vector2 position) { this->position = position; }
            virtual void SetMainColorBtn(Color mainColor) { mainColorBtn = mainColor; }
            virtual void SetOutlineColorBtn(Color outlineColor) { outlineColorBtn = outlineColor; }

            // Update logic button (return boolean button clicked or not).
            virtual bool Update();

            // Render button.
            virtual void Draw();
        private:
            Label text;
            Vector2 position;
            bool isHover;
            bool isClicked;
            Color outlineColorBtn;
            Color mainColorBtn;
            Rectangle rect;
        };

        // Primitive text field (default).
        class TextField
        {
        public:
            explicit TextField()
            {
                this->placeholders = "";
                canEditable = true;
                mouseOnText = false;
                isMouseFocusText = false;
                frameCounter = 0;
                textSize = 10;
                maxLength = 9;
                boxPadding = 5;
                hndText.reserve(9);
                texCol = MAROON;
                boxCol = GRAY;
                offHoverBoxCol = DARKGRAY;
                onHoverBoxCol = RED;
                delay.SetDuration(0.1f);
                mode = TextFieldMode::DEFAULT;
            }

            explicit TextField(const bool canEditable)
            {
                this->placeholders = "";
                this->canEditable = canEditable;
                mouseOnText = false;
                isMouseFocusText = false;
                frameCounter = 0;
                this->textBox = {0.0f, 0.0f, 0.0f, 0.0f};
                this->textSize = 10;
                this->boxPadding = 5;
                this->mode = TextFieldMode::DEFAULT;
                maxLength = 9;
                hndText.reserve(9);
                texCol = BLACK;
                boxCol = WHITE;
                offHoverBoxCol = DARKGRAY;
                onHoverBoxCol = YELLOW;
                delay.SetDuration(0.1f);
            }

            explicit TextField(const char *placeholders, const int len, const int size, const bool canEditable)
            {
                this->placeholders = placeholders;
                this->canEditable = canEditable;
                mouseOnText = false;
                isMouseFocusText = false;
                frameCounter = 0;
                this->textBox = {0.0f, 0.0f, 0.0f, 0.0f};
                this->textSize = size;
                this->boxPadding = 5;
                this->mode = TextFieldMode::DEFAULT;
                maxLength = len;
                hndText.reserve(len);
                texCol = BLACK;
                boxCol = WHITE;
                offHoverBoxCol = DARKGRAY;
                onHoverBoxCol = YELLOW;
                delay.SetDuration(0.1f);
            }

            explicit TextField(const int maxLen, const int textSize,
                const Rectangle textBox,
                const int boxPadding,
                const TextFieldMode& mode, 
                const Color textColor,
                const Color boxColor,
                const Color offHoverBoxColor,
                const Color onHoverBoxColor)
            {
                canEditable = true;
                mouseOnText = false;
                isMouseFocusText = false;
                frameCounter = 0;
                this->textBox = textBox;
                this->textSize = textSize;
                this->boxPadding = boxPadding;
                this->mode = mode;
                hndText.reserve(maxLen);
                texCol = textColor;
                boxCol = boxColor;
                offHoverBoxCol = offHoverBoxColor;
                onHoverBoxCol = onHoverBoxColor;
                delay.SetDuration(0.1f);
            }

            void SetText(const char *text);
            void SetPlaceholders(const char *text);
            void SetEditable(bool canEdit);
            void SetMaxLength(int len);
            void SetSizeBox(Rectangle sizeBox);
            void SetBoxPadding(int padding);
            void SetFieldMode(TextFieldMode mode);
            void SetTextSize(int size);
            void SetTextColor(Color color);
            void SetBoxColor(Color mainColor, Color offHoverBoxColor, Color onHoverBoxColor);

            Vector2 GetPosition();
            std::size_t GetMaxLen();
            std::string GetText();

            // Update logic text field input.
            virtual void Update();
            // Render text field input.
            virtual void Draw();
        protected:
            bool canEditable;
            bool mouseOnText;
            bool isMouseFocusText;
            int maxLength;
            int frameCounter;
            int textSize;
            int boxPadding;
            TextFieldMode mode;
            Rectangle textBox;
            std::string hndText;
            std::string placeholders;
            Color texCol;
            Color boxCol;
            Color offHoverBoxCol;
            Color onHoverBoxCol;
            HLITE::UTIL::Delay delay;
        };

        // Primitive text area (default)
        class TextArea : public TextField
        {
        public:
            explicit TextArea()
            {
                this->placeholders = "";
                canEditable = true;
                mouseOnText = false;
                isMouseFocusText = false;
                frameCounter = 0;
                textSize = 10;
                maxLength = 255;
                boxPadding = 5;
                hndText.reserve(9);
                texCol = MAROON;
                boxCol = GRAY;
                offHoverBoxCol = DARKGRAY;
                onHoverBoxCol = RED;
                delay.SetDuration(0.1f);
                mode = TextFieldMode::DEFAULT;
            }

            explicit TextArea(const bool canEditable)
            {
                this->placeholders = "";
                this->canEditable = canEditable;
                mouseOnText = false;
                isMouseFocusText = false;
                frameCounter = 0;
                this->textBox = {0.0f, 0.0f, 0.0f, 0.0f};
                this->textSize = 10;
                this->boxPadding = 5;
                this->mode = TextFieldMode::DEFAULT;
                maxLength = 255;
                hndText.reserve(9);
                texCol = BLACK;
                boxCol = WHITE;
                offHoverBoxCol = DARKGRAY;
                onHoverBoxCol = YELLOW;
                delay.SetDuration(0.1f);
            }

            explicit TextArea(const char *placeholders, const int len, const int size, const bool canEditable)
            {
                this->placeholders = placeholders;
                this->canEditable = canEditable;
                mouseOnText = false;
                isMouseFocusText = false;
                frameCounter = 0;
                this->textBox = {0.0f, 0.0f, 0.0f, 0.0f};
                this->textSize = size;
                this->boxPadding = 5;
                this->mode = TextFieldMode::DEFAULT;
                maxLength = len;
                hndText.reserve(len);
                texCol = BLACK;
                boxCol = WHITE;
                offHoverBoxCol = DARKGRAY;
                onHoverBoxCol = YELLOW;
                delay.SetDuration(0.1f);
            }

            void Update() override;
            void Draw() override;
        };

        // Primitive virtual message box (Default, Todo...)
        class VMessageBox
        {
        public:
            explicit constexpr VMessageBox(){}
            explicit constexpr VMessageBox(const char *title, const char *description, const Vector2& position)
            : title(title), description(description), position(position){}
            explicit constexpr VMessageBox(const char *title, const char *description, const Vector2& position,  const std::size_t& btnType)
            : title(title), description(description), position(position), btnType(btnType){}
            explicit constexpr VMessageBox(const char *title, const char *description, const Vector2& position,  const std::size_t& btnType, const VMessageBoxMode& mode)
            : title(title), description(description), position(position), btnType(btnType), mode(mode){}

            void SetTitle(const char *title);
            void SetDescribe(const char *description);
            void SetPosition(Vector2& position);
            
            const char *GetTitle();
            const char *GetDescribe();
            Vector2 GetPosition(); 

            std::size_t Update();
            void Draw();

        private:
            const char *title;
            const char *description;
            Vector2 position;
            std::size_t btnType;
            VMessageBoxMode mode;
        };
    }
}