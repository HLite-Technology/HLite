#pragma once

#include <string>

#include "Preprocessor.hpp"

namespace HLITE
{
    // User interfaces support.
    namespace UI
    {
        // Primitive label (default).
        class Label
        {
        public:
            Label(){}
            Label(std::string Text, Vector2 Position, int Size, Color TextOutline, Color TextColor) :
            text(Text), position(Position), size(Size), textOutline(TextOutline), textColor(TextColor) {}

            void SetText(std::string Text) { text = Text; }
            void SetPosition(Vector2 Position) { position = Position; }
            void SetSize(int Size) { size = Size; }
            void SetTextOutline(Color color) { textOutline = color; }
            void SetTextColor(Color color) { textColor = color; }

            std::string GetText() { return text; }
            Vector2 GetPosition() { return position; }
            int GetSize() { return size; }
            Color GetOutlineColor() { return textOutline; }
            Color GetColor() { return textColor; }

            // Render text in window.
            virtual void Draw(unsigned char Opacity);
            // Render text with outline in window.
            void DrawWithOutline(int OutlineRange, unsigned char Opacity);

        private:
            std::string text;
            Vector2 position;
            int size;
            Color textOutline;
            Color textColor;
        };

        // Modern label (primitive label extend)
        class LabelEx : Label
        {
        public:
            LabelEx(){}
            LabelEx(Font TextFont, std::string Text, Vector2 Position, float Rotation, int Size, float Spacing, Color TextOutline, Color TextColor) :
            font(TextFont), text(Text), position(Position), rotation(Rotation), fontSize(Size), spacing(Spacing), textOutline(TextOutline), textColor(TextColor) {}

            void SetFont(Font TextFont) { font = TextFont; }
            void SetText(std::string Text) { text = Text; }
            void SetPosition(Vector2 Position) { position = Position; }
            void SetSize(int Size) { fontSize = Size; }
            void SetRotation(float Rotation) {rotation = Rotation; }
            void SetSpacing(float Spacing) { spacing = Spacing; }
            void SetTextOutline(Color color) { textOutline = color; }
            void SetTextColor(Color color) { textColor = color; }

            Font GetFont() { return font; }
            std::string GetText() { return text; }
            Vector2 GetPosition() { return position; }
            int GetSize() { return fontSize; }
            Vector2 GetOrigin() { return origin; }
            float GetRotation() { return rotation; }
            float GetSpacing() { return spacing; }
            Color GetOutlineColor() { return textOutline; }
            Color GetColor() { return textColor; }

            // Render text in window.
            void Draw(unsigned char Opacity) override;
            // Render text with outline in window.
            void DrawWithOutline(float OutlineRange, unsigned char Opacity);

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
            Button(
                Label Text,
                bool IsHover, 
                bool IsClicked, 
                Color OutlineColorBtn, 
                Color MainColorBtn
            ) : text(Text), isHover(IsHover), isClicked(IsClicked), 
            outlineColorBtn(OutlineColorBtn), mainColorBtn(MainColorBtn) {}

            Button(){}

            virtual void SetTextClass(Label Text) { this->text = Text; }
            virtual void SetIsHover(bool condition) { isHover = condition; }
            virtual void SetIsClicked(bool condition) { isClicked = condition; }
            virtual void SetMainColorBtn(Color MainColor) { mainColorBtn = MainColor; }
            virtual void SetOutlineColorBtn(Color OutlineColor) { outlineColorBtn = OutlineColor; }

            // Update logic button.
            virtual Button Update(Button button);

            // Render button.
            virtual void Draw(float PosX, float posY);
        private:
            Label text;
            bool isHover;
            bool isClicked;
            Color outlineColorBtn;
            Color mainColorBtn;
            Rectangle rect;
        };
    }
}