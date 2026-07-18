#pragma once

#include "Preprocessor.hpp"

// HLite callback framework.
namespace HLITEMain
{
    // Window assets initialization or for cli game (For one-time asset initialization).
    void Init();
    // Window update (For window update only not for render).
    void Update();
    // Window Render (For render any object in screen).
    void Render();
    // Window unload all assets (Always unload assets that you no longer use when window is closed).
    void Unload();
}

namespace HLITE
{
    // HLGE core support.
    namespace CORE
    {
        // Window class attribute settings.
        class Window
        {
        public:
            explicit constexpr Window() {}
            explicit constexpr Window(const Vector2 sizeWindow, const char *windowTitle, const Color backgroundColor, const bool windowResizeable) : 
            windowWidth(static_cast<int>(sizeWindow.x)), windowHeight(static_cast<int>(sizeWindow.y)), 
            windowTitle(windowTitle), backgroundColor(backgroundColor),  canResizeable(windowResizeable) {}
            explicit constexpr Window(const Vector2 sizeWindow, const char *windowTitle, const Color backgroundColor, const bool windowResizeable, const int fps)
            : windowWidth(static_cast<int>(sizeWindow.x)), windowHeight(static_cast<int>(sizeWindow.y)),
            windowTitle(windowTitle), backgroundColor(backgroundColor),  canResizeable(windowResizeable), fps(fps) {}

            void SetWindowSize(Vector2& windowSize);
            void SetWindowTitle(const char *windowTitle);
            void SetWindowResizeable(bool resizeable);
            void SetWindowFPS(int windowFps);
            void SetWindowBackgroundColor(Color& backgroundColor);

            int GetWindowWidth() const;
            int GetWindowHeight() const;
            const char *GetWindowTitle() const;

            // Register the window class to enable the GUI window.
            void Register() const;

        private:
            int windowWidth;
            int windowHeight;
            const char *windowTitle = nullptr;
            Color backgroundColor = WHITE;
            bool canResizeable = false;
            int fps;
        };

        // App running class.
        namespace APP
        {
            // Running window (Dont use it, if you using HLite Framework!).
            void Run(
                void (*WindowInit)(), 
                void (*WindowUpdate)(), 
                void (*WindowRender)(),
                void (*WindowUnload)()
            );
        }
    }
}