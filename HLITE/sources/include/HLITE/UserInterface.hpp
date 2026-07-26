#pragma once

#include <string>

#include "Preprocessor.hpp"
#include "Utility.hpp"

namespace HLITE
{
    /// @brief User interfaces support.
    namespace UI
    {
        /// @brief Text field all mode input text.
        typedef enum
        {
            DEFAULT,
            STATIC
        } TextFieldMode;

        /// @brief Virtual message box all modification.
        typedef enum
        {
            MB_OK,
            MB_OKCANCEL,
            MB_ABORTRETRYIGNORE,
            MB_YESNOCANCEL,
            MB_YESNO,
            MB_RETRYCANCEL,
            MB_CANCELTRYCONTINUE,
            MB_DEFAULT,
            MB_ICONERROR,
            MB_ICONWARNING,
            MB_ICONQUESTION,
            MB_ICONINFORMATION
        } VMSBoxMod;

        // Primitive label (default).
        class Label
        {
        public:
            /// @brief Creates an empty label.
            Label(){}
            /// @brief Creates a label with default visual settings.
            /// @param text The text displayed by the label.
            Label(const char *text) : 
            text(text), position({0.0f, 0.0f}), size(25), textOutline(BLACK), textColor(WHITE) {}
            /// @brief Creates a label with explicit text and visual settings.
            /// @param text The text displayed by the label.
            /// @param position The label position.
            /// @param size The label font size.
            /// @param textOutline The label outline color.
            /// @param textColor The label text color.
            Label(const char* text, Vector2 position, int size, Color textOutline, Color textColor) :
            text(text), position(position), size(size), textOutline(textOutline), textColor(textColor) {}

            /// @brief To define the text on the label.
            /// @param text holds text in the form of `const char*`.
            void SetText(const char* text) { this->text = text; }
            /// @brief To set the position of the text label.
            /// @param position Position label with `Vector2`.
            void SetPosition(Vector2 position) { this->position = position; }
            /// @brief To set the label font size.
            /// @param size text on the label with `int`.
            void SetSize(int size) { this->size = size; }
            /// @brief To set the label outline color.
            /// @param color Set the outline with `Color`.
            void SetTextOutline(Color color) { textOutline = color; }
            /// @brief To set the label main color.
            /// @param color Set the main color with `Color`.
            void SetTextColor(Color color) { textColor = color; }

            /// @brief To get the text from the label.
            /// @return returns text in the form of `std::string`.
            std::string GetText() const { return text; }
            /// @brief Get the position from the label.
            /// @return Position as `Vector2`.
            Vector2 GetPosition() const { return position; }
            /// @brief Returns the label font size.
            /// @return The label font size.
            int GetSize() const { return size; }
            /// @brief Returns the label outline color.
            /// @return The label outline color.
            Color GetOutlineColor() const { return textOutline; }
            /// @brief Returns the label text color.
            /// @return The label text color.
            Color GetColor() const { return textColor; }

            /// @brief Render text in window.
            /// @param opacity Sets opacity with `unsigned const char`.
            virtual void Draw(unsigned char opacity);
            /// @brief Render text with shadow in window.
            /// @attention Opacity min and min `0` - `255`.
            /// @param shadowRange Set the distance of the text shadow with `float`.
            /// @param opacity Set the opacity of text with `unsigned char*`.
            virtual void DrawWithShadow(float shadowRange, unsigned char opacity);
            /// @brief Render text with outline in window.
            /// @attention thickness can only be 0 - 3.
            /// @attention Opacity min and min `0` - `255`.
            /// @param thick Set the outline thickness with `float`.
            /// @param opacity Set the opacity of text with the data type `unsigned char*`.
            virtual void DrawWithOutline(float thick, unsigned char opacity);

        private:
            std::string text;
            Vector2 position;
            int size;
            Color textOutline;
            Color textColor;
        };

        /// @brief Modern label (primitive label extend)
        class LabelEx : public Label
        {
        public:
            /// @brief Creates an empty extended label.
            explicit LabelEx(){}
            /// @brief Creates an extended label with a font and default visual settings.
            /// @param font The font used to render the label.
            /// @param text The text displayed by the label.
            explicit LabelEx(Font& font, const char *text) : font(font), text(text), position({0.0f, 0.0f}), rotation(0.0f), fontSize(25), spacing(1), textOutline(BLACK), textColor(WHITE) {}
            /// @brief Creates an extended label with explicit font and visual settings.
            /// @param textFont The font used to render the label.
            /// @param text The text displayed by the label.
            /// @param position The label position.
            /// @param rotation The label rotation in degrees.
            /// @param size The label font size.
            /// @param spacing The spacing between label characters.
            /// @param textOutline The label outline color.
            /// @param textColor The label text color.
            explicit LabelEx(Font& textFont, std::string text, Vector2 position, float rotation, int size, float spacing, Color textOutline, Color textColor) :
            font(textFont), text(text), position(position), rotation(rotation), fontSize(size), spacing(spacing), textOutline(textOutline), textColor(textColor) {}

            /// @brief Sets the label font.
            /// @param textFont The new label font.
            void SetFont(Font textFont) { font = textFont; }
            /// @brief Sets the label rotation in degrees.
            /// @param rotation The new rotation in degrees.
            void SetRotation(float rotation) {this->rotation = rotation; }
            /// @brief Sets the spacing between label characters.
            /// @param spacing The new character spacing.
            void SetSpacing(float spacing) { this->spacing = spacing; }
            
            /// @brief Returns the label font.
            /// @return The label font.
            Font GetFont() { return font; }
            /// @brief Returns the label origin.
            /// @return The label origin.
            Vector2 GetOrigin() { return origin; }
            /// @brief Returns the label rotation in degrees.
            /// @return The label rotation in degrees.
            float GetRotation() { return rotation; }
            /// @brief Returns the spacing between label characters.
            /// @return The character spacing.
            float GetSpacing() { return spacing; }

            /// @brief Render text in window.
            /// @param opacity Set the opacity of text with `unsigned char*`.
            void Draw(unsigned char opacity) override;
            /// @brief Render text with shadow in window.
            /// @param shadowRange Set the distance of the text shadow with `float`.
            /// @param opacity Set the opacity of text with `unsigned char*`.
            void DrawWithShadow(float shadowRange, unsigned char opacity) override;
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

        /// @brief Primitive button (default).
        class Button
        {
        public:
            /// @brief Creates an empty button.
            explicit Button(){}
            /// @brief Creates a button with default visual settings.
            /// @param text The label displayed by the button.
            explicit Button(const Label& text) : text(text), position({0.0f, 0.0f}), isHover(false), isClicked(false),
            outlineColorBtn(BLACK), mainColorBtn(WHITE) {}
            /// @brief Creates a button with explicit label, position, and colors.
            /// @param text The label displayed by the button.
            /// @param position The button position.
            /// @param OutlineColorBtn The button outline color.
            /// @param MainColorBtn The button main color.
            explicit Button(
                Label& text,
                Vector2 position,
                Color OutlineColorBtn, 
                Color MainColorBtn
            ) : text(text), position(position), isHover(false), isClicked(false), 
            outlineColorBtn(OutlineColorBtn), mainColorBtn(MainColorBtn) {}

            /// @brief Sets the label displayed by the button.
            /// @param text The new button label.
            virtual void SetTextClass(const Label& text) { this->text = text; }
            /// @brief Sets the button position.
            /// @param position The new button position.
            virtual void SetPosition(Vector2 position) { this->position = position; }
            /// @brief Sets the button main color.
            /// @param mainColor The new button main color.
            virtual void SetMainColorBtn(Color mainColor) { mainColorBtn = mainColor; }
            /// @brief Sets the button outline color.
            /// @param outlineColor The new button outline color.
            virtual void SetOutlineColorBtn(Color outlineColor) { outlineColorBtn = outlineColor; }

            /// @brief Update logic button (return boolean button clicked or not).
            /// @return True or False if the button is pressed.
            /// @return `true` if the button was clicked; otherwise, `false`.
            virtual bool Update();

            /// @brief Render button.
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

        /// @brief Primitive text field (default).
        class TextField
        {
        public:
            /// @brief Creates an editable text field with default settings.
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

            /// @brief Creates a text field with the specified editability.
            /// @param canEditable Whether the text field accepts user input.
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

            /// @brief Creates a text field with placeholder, length, size, and editability settings.
            /// @param placeholders The placeholder text shown when the field is empty.
            /// @param len The maximum input length.
            /// @param size The input text size.
            /// @param canEditable Whether the text field accepts user input.
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

            /// @brief Creates a text field with complete visual and behavior settings.
            /// @param maxLen The maximum input length.
            /// @param textSize The input text size.
            /// @param textBox The text field rectangle.
            /// @param boxPadding The padding inside the text field.
            /// @param mode The text field input mode.
            /// @param textColor The input text color.
            /// @param boxColor The default box color.
            /// @param offHoverBoxColor The box color when the pointer is not over the field.
            /// @param onHoverBoxColor The box color when the pointer is over the field.
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

            /// @brief Sets the current text field contents.
            /// @param text The new text field contents.
            void SetText(const char *text);
            /// @brief Sets the placeholder text.
            /// @param text The new placeholder text.
            void SetPlaceholders(const char *text);
            /// @brief Enables or disables text editing.
            /// @param canEdit Whether editing is enabled.
            void SetEditable(bool canEdit);
            /// @brief Sets the maximum number of input characters.
            /// @param len The maximum input length.
            void SetMaxLength(int len);
            /// @brief Sets the text field rectangle.
            /// @param sizeBox The new text field rectangle.
            void SetSizeBox(Rectangle sizeBox);
            /// @brief Sets the padding inside the text field.
            /// @param padding The new inner padding.
            void SetBoxPadding(int padding);
            /// @brief Sets the text field input mode.
            /// @param mode The new input mode.
            void SetFieldMode(TextFieldMode mode);
            /// @brief Sets the input text size.
            /// @param size The new input text size.
            void SetTextSize(int size);
            /// @brief Sets the input text color.
            /// @param color The new input text color.
            void SetTextColor(Color color);
            /// @brief Sets the base, inactive-hover, and active-hover box colors.
            /// @param mainColor The default box color.
            /// @param offHoverBoxColor The box color when the pointer is not over the field.
            /// @param onHoverBoxColor The box color when the pointer is over the field.
            void SetBoxColor(Color mainColor, Color offHoverBoxColor, Color onHoverBoxColor);

            /// @brief Returns the text field position.
            /// @return The text field position.
            Vector2 GetPosition();
            /// @brief Returns the maximum input length.
            /// @return The maximum number of input characters.
            std::size_t GetMaxLen();
            /// @brief Returns the current input text.
            /// @return The current input text.
            std::string GetText();

            /// @brief Update logic text field input.
            virtual void Update();
            /// @brief Render text field input.
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

        /// @brief Primitive text area (default)
        class TextArea : public TextField
        {
        public:
            /// @brief Creates an editable text area with default settings.
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

            /// @brief Creates a text area with the specified editability.
            /// @param canEditable Whether the text area accepts user input.
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

            /// @brief Creates a text area with placeholder, length, size, and editability settings.
            /// @param placeholders The placeholder text shown when the area is empty.
            /// @param len The maximum input length.
            /// @param size The input text size.
            /// @param canEditable Whether the text area accepts user input.
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

            /// @brief Update logic text area input.
            void Update() override;
            /// @brief Render text area input.
            void Draw() override;
        };

        /// @brief Primitive virtual message box (Default)
        class VMessageBox
        {
        public:
            /// @brief Creates a default virtual message box.
            explicit VMessageBox();
            /// @brief Creates a message box with a title, description, and position.
            /// @param title The message box title.
            /// @param description The message box description.
            /// @param position The message box position.
            explicit VMessageBox(const char *title, const char *description, const Vector2& position);
            /// @brief Creates a message box with a title, description, position, and button mode.
            /// @param title The message box title.
            /// @param description The message box description.
            /// @param position The message box position.
            /// @param btnType The button configuration mode.
            explicit VMessageBox(const char *title, const char *description, const Vector2& position,  const VMSBoxMod& btnType);
            /// @brief Creates a message box with explicit button and message modes.
            /// @param title The message box title.
            /// @param description The message box description.
            /// @param position The message box position.
            /// @param btnType The button configuration mode.
            /// @param mode The message box display mode.
            explicit VMessageBox(const char *title, const char *description, const Vector2& position,  const VMSBoxMod& btnType, const VMSBoxMod& mode);

            /// @brief Set the title of the virtual message box.
            /// @param title The title of the virtual message box uses `const char*`.
            void SetTitle(const char *title);
            /// @brief Set the description of the virtual message box.
            /// @param description The description of the virtual message box uses `const char*`.
            void SetDescribe(const char *description);
            /// @brief Set the position of the virtual message box.
            /// @param position The position of the virtual message box uses `Vector2`.
            void SetPosition(const Vector2& position);
            
            /// @brief Get the title text virtual message box.
            /// @return `const char*` for string title.
            const char *GetTitle();
            /// @brief Get the description text virtual message box.
            /// @return `const char*` for string description.
            const char *GetDescribe();
            /// @brief Get the position of the virtual message box.
            /// @return `Vector2` data type for position.
            Vector2 GetPosition(); 

            /// @brief To trigger the virtual messagebox spawn event.
            void Appear();
            /// @brief To update the virtual message box logic.
            /// @return Value of the button that was pressed.
            std::size_t Update();
            /// @brief Render virtual message box in screen.
            void Draw();

            ~VMessageBox();

        private:
            const char *title;
            const char *description;
            Vector2 position;
            VMSBoxMod btnType = VMSBoxMod::MB_OK;
            VMSBoxMod mode = VMSBoxMod::MB_DEFAULT;
            Rectangle vmbRect{(Rectangle){
                .x = position.x,
                .y = position.y,
                .width = 355,
                .height = 150}};
            static Texture CircleErrorIcon, CircleInformationIcon, CircleQuestionIcon,
                    CircleWarningIcon;
            Button btnOne = Button({"1", {0.0f, 0.0f}, 21, BLACK, WHITE});
            Button btnTwo = Button({"2", {0.0f, 0.0f}, 21, BLACK, WHITE});
            Button btnThree = Button({"3", {0.0f, 0.0f}, 21, BLACK, WHITE});
            bool isAppear = false;
            static bool iconsLoaded;
            /// @brief Private updates the layout of the message box and its controls.
            void UpdateLayout();
            /// @brief Private loads message box icons once when they are first needed.
            static void EnsureIconsLoaded();
            /// @brief Private to close all virtual message box attributes.
            static void Close();
        };
    }
}