#include "../include/HLITE/Core.hpp"
#include "../include/HLITE/Metadata.hpp"

#include <cstdio>

typedef struct
{
    Texture icon;
    Rectangle src;
    Rectangle dest;
    Vector2 ori;
    float rotate;
    unsigned char opacity;
    Color color;
    bool isApear;
    Rectangle dstbkg;
    float scaleBacklight;
    Color backLightCol;
    float downPosBkg;
} HliteIcon;

HliteIcon hliteIcon;
Color backLightCols[3] = {RED, GREEN, BLUE};
Color windowBkgCol = RAYWHITE;
bool isWindowRunning = false;
bool isSetAudio = true;

void updateHliteIcon(HliteIcon& hlite, float scale)
{   
    if (hlite.downPosBkg <= 405)
        hlite.downPosBkg += 155.0f * GetFrameTime();
    else
    {
        if (hlite.scaleBacklight <= 800.0f)
        {
            if (hlite.opacity >= 0) hlite.opacity -= 1;
            hlite.scaleBacklight += 255.0f * GetFrameTime();
        }
        else
        {
            hlite.opacity = 255.0f;
            hlite.downPosBkg = 0.0f;
            hlite.scaleBacklight = 0.0f;
            hlite.isApear = false;
        }
    }

    hlite.dest = {GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f,
                  scale, scale - 50};
    hlite.ori = {hlite.dest.width / 2.0f, hlite.dest.height / 2.0f};
    hlite.dstbkg = {GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f + hliteIcon.downPosBkg,
                    scale, scale - 50};
}

void drawhLiteIcon(HliteIcon& hlite)
{
    if (hlite.isApear)
    {
        Rectangle bkgCol = {0.0f, 0.0f,
                            static_cast<float>(GetScreenWidth()),
                            static_cast<float>(GetScreenHeight())};
        DrawRectangleRec(bkgCol, BLACK);
        DrawCircle(hlite.dest.x, hlite.dest.y, hlite.scaleBacklight, hlite.backLightCol);
        DrawTexturePro(hlite.icon, hlite.src, hlite.dest, hlite.ori, 0.0f, (Color){
                                                                                    .r = hlite.color.r,
                                                                                    .g = hlite.color.g,
                                                                                    .b = hlite.color.b,
                                                                                    .a = hlite.opacity});
        DrawRectanglePro(hlite.dstbkg, {hlite.dest.width / 2.0f, hlite.dest.height / 2.0f}, 0.0f, BLACK);

        // DrawText(TextFormat("Pos : %.2f", hlite.downPosBkg), 25, 25, 25, BLUE);
    }
}

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
        void Window::SetHLITEIntro(bool status) { showIcon = status; }
        void Window::SetAudio(const bool status) { isSetAudio = status; }
        void Window::Dispatch() { isWindowActive = false; isWindowRunning = false; }
        int Window::GetWindowWidth() const { return windowWidth; }
        int Window::GetWindowHeight() const { return windowHeight; }
        const char *Window::GetWindowTitle() const { return windowTitle; }
        void Window::Register() const
        {
            if (windowWidth != 0 && windowHeight != 0 && windowTitle != nullptr)
            {
                isWindowRunning = this->isWindowActive;
                isSetAudio = this->isAudio;

                std::printf("[HLITE] GUI window active!\n");
                if (canResizeable) SetConfigFlags(FLAG_WINDOW_RESIZABLE);
                InitWindow(windowWidth, windowHeight, windowTitle);
                if (isSetAudio)
                    InitAudioDevice();
                
                if (showIcon)
                {
                    hliteIcon.isApear = showIcon;

                    Image tmpHliteIcon = LoadImageFromMemory(".png",
                                                             hlite_icon_bin_png,
                                                             sizeof(hlite_icon_bin_png) / sizeof(hlite_icon_bin_png[0]));

                    hliteIcon.icon = LoadTextureFromImage(tmpHliteIcon);

                    UnloadImage(tmpHliteIcon);

                    hliteIcon.src = {0.0f, 0.0f,
                                     static_cast<float>(hliteIcon.icon.width),
                                     static_cast<float>(hliteIcon.icon.height)};
                    hliteIcon.rotate = 0.0f;
                    hliteIcon.color = WHITE;
                    hliteIcon.opacity = 255;

                    hliteIcon.scaleBacklight = 0.0f;
                    hliteIcon.downPosBkg = 0.0f;
                    hliteIcon.backLightCol = backLightCols[GetRandomValue(0, 2)];
                }
                else hliteIcon.isApear = showIcon;

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
                while (isWindowRunning && !WindowShouldClose())
                {
                    updateHliteIcon(hliteIcon, 255.0f);

                    if (!hliteIcon.isApear)
                        WindowUpdate();
                    BeginDrawing();
                    ClearBackground(windowBkgCol);

                    drawhLiteIcon(hliteIcon);

                    if (!hliteIcon.isApear)
                        WindowRender();
                    EndDrawing();
                }
                
                if (hliteIcon.isApear)
                    UnloadTexture(hliteIcon.icon);
                WindowUnload();
                if (isSetAudio)
                    CloseAudioDevice();
                CloseWindow();
            }
        }
    }
}