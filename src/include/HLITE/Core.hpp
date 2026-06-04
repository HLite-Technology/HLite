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
            Window(int WindowWidth, int WindowHeight, const char *WindowTitle) : 
            windowWidth(WindowWidth), windowHeight(WindowHeight), 
            windowTitle(const_cast<char*>(WindowTitle)) {}

            void SetWindowSize(int WindowWidth, int WindowHeight);
            void SetWindowTitle(const char *WindowTitle);
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

        // Key combine support (Todo...).
        namespace Key
        {
            // Combination of 2 keys that are pressed (Todo...).
            bool isCombine_2Key(bool key1, bool key2, float maxDelay);
            // Combination of 3 keys that are pressed (Todo....).
            bool isCombine_3Key(bool key1, bool key2, bool key3, float maxDelay);
        }

        // Countdown timer support.
        class Countdown
        {
        public:
            Countdown() {}
            Countdown(int Minutes, int Seconds, float Delay) : 
            minutes(Minutes), seconds(Seconds), setterDelay(Delay) {}

            void SetMinutes(int Minutes) { minutes = Minutes; }
            void SetSeconds(int Seconds) { seconds = Seconds; }
            void SetDelay(float Delay) { setterDelay = Delay; }

            int GetMinutes() { return minutes; }
            int GetSeconds() { return seconds; }

            // Update the timer that will be decreased (true if active, false if the time is up).
            bool Update();
            // Getting the text form from the timer.
            std::string Str(); 
        private:
            int minutes;
            int seconds;
            float setterDelay;
            float countDelay;
        };
    }
}