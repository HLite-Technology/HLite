#include "../include/HLITE/Core.hpp"

#include <cstdio>

Color windowBkgCol = RAYWHITE;

namespace HLITE
{
    namespace CORE
    {
        // ===========================
        // WINDOW CORE
        // ===========================
    
        void Window::SetWindowSize(Vector2& windowSize)
        {
            windowWidth = windowSize.x;
            windowHeight = windowSize.y;
        }
        void Window::SetWindowTitle(const char *windowTitle) { this->windowTitle = windowTitle; }
        void Window::SetWindowResizeable(bool resizeable) { canResizeable = resizeable; }
        void Window::SetWindowFPS(int windowFps) { fps = windowFps; }
        void Window::SetWindowBackgroundColor(Color& backgroundColor) { windowBkgCol = backgroundColor; }
        int Window::GetWindowWidth() const { return windowWidth; }
        int Window::GetWindowHeight() const { return windowHeight; }
        const char *Window::GetWindowTitle() const { return windowTitle; }
        void Window::Register() const
        {
            if (windowWidth != 0 && windowHeight != 0 && windowTitle != nullptr)
            {
                std::printf("[HLITE] GUI window active!\n");
                if (canResizeable) SetConfigFlags(FLAG_WINDOW_RESIZABLE);
                InitWindow(windowWidth, windowHeight, windowTitle);
                windowBkgCol = backgroundColor;
                SetTargetFPS(fps);
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

            if (!IsWindowReady())
            {
                std::printf("Press any key to exit...\n");
                std::getchar();
            }
            
            if (IsWindowReady())
            {
                while (!WindowShouldClose())
                {
                    WindowUpdate();
                    BeginDrawing();
                    ClearBackground(windowBkgCol);
                    WindowRender();
                    EndDrawing();
                }
                WindowUnload();
                CloseWindow();
            }
        }
    }
}