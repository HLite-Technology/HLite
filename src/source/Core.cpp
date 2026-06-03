#include "../include/HLITE/Core.hpp"

#include <cstdio>

int windowFps = 60;
Color windowBkgCol = RAYWHITE;

namespace HLITE
{
    namespace CORE
    {
        // ===========================
        // WINDOW CORE
        // ===========================

        void Window::SetWindowSize(int WindowWidth, int WindowHeight)
        {
            windowWidth = WindowWidth;
            windowHeight = WindowHeight;
        }
        void Window::SetWindowTitle(const char *WindowTitle) { windowTitle = const_cast<char*>(WindowTitle); }
        void Window::SetWindowFPS(int WindowFps) { windowFps = WindowFps; }
        void Window::SetWindowBackgroundColor(Color BackgroundColor) { windowBkgCol = BackgroundColor; }
        void Window::Register()
        {
            if (windowWidth != 0 && windowHeight != 0 && windowTitle != nullptr)
            {
                std::printf("[HLITE] GUI window active!\n");
                InitWindow(windowWidth, windowHeight, windowTitle);
            }
            else 
            {
                std::fprintf(stderr, "[HLITE] Failed register window! Window Width, Window Height, Window Title must not be empty.\n");
            }
        }

        // ============
        // HLGE RUNNING (Window Core)
        // ============

        void HLITE::CORE::APP::Run(void (*WindowInit)(), void (*WindowUpdate)(), void (*WindowRender)(), void (*WindowUnload)())
        {
            WindowInit();

            if (IsWindowReady())
            {
                SetTargetFPS(windowFps);
                while (!WindowShouldClose())
                {
                    WindowUpdate();
                    BeginDrawing();
                    ClearBackground(windowBkgCol);
                    WindowRender();
                    EndDrawing();
                }
                WindowUnload();
            }

            if (!IsWindowReady())
            {
                std::printf("Press any key to exit...\n");
                std::getchar();
            }
        }

        // ===================
        // KEY COMBINE SUPPORT
        // ===================

        namespace Key
        {
            bool isCombine_2Key(bool key1, bool key2, float maxDelay)
            {
                bool combine2KeyHnd = false;
                double key1Time = 0.0;
                double currentTime = GetTime();
            
                if (key1) 
                {
                    combine2KeyHnd = true;
                    key1Time = currentTime;
                }
                if (combine2KeyHnd && key2 && (currentTime - key1Time <= maxDelay)) 
                {
                    combine2KeyHnd = false;
                    return true; 
                }
                if (combine2KeyHnd && (currentTime - key1Time > maxDelay)) combine2KeyHnd = false;
                return false;
            }

            bool isCombine_3Key(bool key1, bool key2, bool key3, float maxDelay)
            {
                int comboStage = 0;    
                double lastKeyTime = 0.0;
                double currentTime = GetTime();

                if (comboStage == 0 && key1) 
                {
                    comboStage = 1;
                    lastKeyTime = currentTime;
                    return false;
                }
                if (comboStage == 1) 
                {
                    if (currentTime - lastKeyTime > maxDelay) 
                    {
                        comboStage = 0; 
                        return false;
                    }
                    if (key2) 
                    {
                        comboStage = 2;
                        lastKeyTime = currentTime;
                        return false;
                    }
                }
                if (comboStage == 2) 
                {
                    if (currentTime - lastKeyTime > maxDelay) 
                    {
                        comboStage = 0;
                        return false;
                    }
                    if (key3) 
                    {
                        comboStage = 0; 
                        return true;    
                    }
                }
                return false;
            }
        }

        // =======================
        // COUNTDOWN SUPPORT CLASS
        // =======================

        bool Countdown::Update()
        {
            if (!IsWindowReady())
            {
                if (seconds != 0) seconds -= 1;
                else if (seconds > 60) seconds = 60;
                else if (seconds == 0)
                {
                    if (minutes != 0)
                    {
                        minutes -= 1;
                        seconds = 60;
                    }
                    else if (minutes > 60) minutes = 60;
                    else return false;
                }
            }
        
            if (IsWindowReady())
            {
                countDelay += GetFrameTime();
            
                if (countDelay >= setterDelay)
                {
                    countDelay = 0.0f;
                
                    if (seconds > 0) seconds -= 1;
                    else
                    {
                        if (minutes > 0)
                        {
                            minutes -= 1;
                            seconds = 59;
                        }
                        else return false; // waktu habis
                    }
                }
            }
            return true;
        }

        std::string Countdown::Str()
        {
            return std::to_string(minutes) + ":" + std::to_string(seconds);
        }
    }
}