#pragma once

#include "Preprocessor.hpp"

#include <string>

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
            Window() {}
            Window(int WindowWidth, int WindowHeight, const char *WindowTitle, bool windowResizeable) : 
            windowWidth(WindowWidth), windowHeight(WindowHeight), 
            windowTitle(const_cast<char*>(WindowTitle)),  canResizeable(windowResizeable) {}

            void SetWindowSize(int WindowWidth, int WindowHeight);
            void SetWindowTitle(const char *WindowTitle);
            void SetWindowResizeable(bool resizeable);
            void SetWindowFPS(int WindowFps);
            void SetWindowBackgroundColor(Color BackgroundColor);

            int GetWindowWidth() { return windowWidth; }
            int GetWindowHeight() { return windowHeight; }
            const char *GetWindowTitle() { return windowTitle; }

            // Register the window class to enable the GUI window.
            void Register();

            ~Window(){ if (IsWindowReady()) CloseWindow(); }

        private:
            int windowWidth;
            int windowHeight;
            char *windowTitle = nullptr;
            bool canResizeable = false;
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