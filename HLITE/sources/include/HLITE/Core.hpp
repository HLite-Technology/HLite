#pragma once

#include "Preprocessor.hpp"

// HLite callback framework.
namespace HLITEMain
{
    /// @brief Initializes window assets or one-time command-line game assets.
    void Init();
    /// @brief Updates application state without rendering.
    void Update();
    /// @brief Renders application objects to the window.
    void Render();
    /// @brief Unloads application assets when the window closes.
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
            /// @brief Creates an empty window configuration.
            explicit constexpr Window() {}
            /// @brief Creates a window configuration with the specified display settings.
            /// @param sizeWindow The initial window dimensions.
            /// @param windowTitle The title displayed in the window title bar.
            /// @param backgroundColor The initial window background color.
            /// @param windowResizeable Whether the window can be resized.
            explicit constexpr Window(const Vector2 sizeWindow, const char *windowTitle, const Color backgroundColor, const bool windowResizeable) : 
            windowWidth(static_cast<int>(sizeWindow.x)), windowHeight(static_cast<int>(sizeWindow.y)), 
            windowTitle(windowTitle), backgroundColor(backgroundColor),  canResizeable(windowResizeable) {}
            /// @brief Creates a window configuration with the specified display settings and frame rate.
            /// @param sizeWindow The initial window dimensions.
            /// @param windowTitle The title displayed in the window title bar.
            /// @param backgroundColor The initial window background color.
            /// @param windowResizeable Whether the window can be resized.
            /// @param fps The target window frame rate.
            explicit constexpr Window(const Vector2 sizeWindow, const char *windowTitle, const Color backgroundColor, const bool windowResizeable, const int fps)
            : windowWidth(static_cast<int>(sizeWindow.x)), windowHeight(static_cast<int>(sizeWindow.y)),
            windowTitle(windowTitle), backgroundColor(backgroundColor),  canResizeable(windowResizeable), fps(fps) {}

            /// @brief Sets the window dimensions.
            /// @param windowSize The new window dimensions.
            void SetWindowSize(Vector2& windowSize);
            /// @brief Sets the window title.
            /// @param windowTitle The new window title.
            void SetWindowTitle(const char *windowTitle);
            /// @brief Enables or disables window resizing.
            /// @param resizeable Whether the window can be resized.
            void SetWindowResizeable(bool resizeable);
            /// @brief Sets the target window frame rate.
            /// @param windowFps The new target frame rate.
            void SetWindowFPS(int windowFps);
            /// @brief Sets the window background color.
            /// @param backgroundColor The new background color.
            void SetWindowBackgroundColor(Color& backgroundColor);

            /// @brief Returns the configured window width.
            /// @return The window width in pixels.
            int GetWindowWidth() const;
            /// @brief Returns the configured window height.
            /// @return The window height in pixels.
            int GetWindowHeight() const;
            /// @brief Returns the configured window title.
            /// @return The configured window title.
            const char *GetWindowTitle() const;

            /// @brief Registers the configured window and enables the GUI window.
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
            /// @brief Runs the application using the supplied lifecycle callbacks.
            /// @param WindowInit The callback invoked during initialization.
            /// @param WindowUpdate The callback invoked during each update cycle.
            /// @param WindowRender The callback invoked during each render cycle.
            /// @param WindowUnload The callback invoked during shutdown.
            void Run(
                void (*WindowInit)(), 
                void (*WindowUpdate)(), 
                void (*WindowRender)(),
                void (*WindowUnload)()
            );
        }
    }
}