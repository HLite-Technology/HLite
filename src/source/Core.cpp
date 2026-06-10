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
        void Window::SetWindowResizeable(bool resizeable) { canResizeable = resizeable; }
        void Window::SetWindowFPS(int WindowFps) { windowFps = WindowFps; }
        void Window::SetWindowBackgroundColor(Color BackgroundColor) { windowBkgCol = BackgroundColor; }
        void Window::Register()
        {
            if (windowWidth != 0 && windowHeight != 0 && windowTitle != nullptr)
            {
                std::printf("[HLITE] GUI window active!\n");
                if (canResizeable) SetConfigFlags(FLAG_WINDOW_RESIZABLE);
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
    }
}