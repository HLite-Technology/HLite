#include <vector>
#include <string_view>
#include <HLITE/Core.hpp>
#include <HLITE/File.hpp>
#include <HLITE/UserInterface.hpp>

using namespace HLITE;

typedef struct
{
    std::string_view id;
    Vector2 pos;
    float scale;
    Rectangle src, dst;
    Vector2 ori;
    float rotate;
    std::vector<unsigned char> meta;
    Texture texture;
} Planet;

constinit CORE::Window wc({800, 600}, "HLITE - HBrick Sample", BLACK, false, 60);

UI::VMessageBox bikFailMsg("BIK Failed", "", {300, 200}, UI::VMSBoxMod::MB_OK, UI::VMSBoxMod::MB_ICONERROR);

HLITE::FILE::HBrick bik;

bool isSuccessLoad = true;
Texture backStars;
std::vector<unsigned char> bfrBackStars;
Planet planets[3] = {{"mercury.png"}, {"venus.png"}, {"earth.png"}};

void HLITEMain::Init()
{
    wc.Register();

    planets[0].pos = {100.0f, 300.0f};
    planets[0].scale = 35.0f;

    planets[1].pos = {350.0f, 300.0f};
    planets[1].scale = 150.0f;

    planets[2].pos = {650.0f, 300.0f};
    planets[2].scale = 200.0f;

    bik.Open(HLITE::FILE::GetPathFile("example/Graphics2D/HBrickSample/gfx/planets.bik",
            false));

    if (bik.IsOpen())
    {
        if (!bik.GetData(bfrBackStars, "stars_background.png")) isSuccessLoad = false;

        for (auto& i : planets)
        {
            if (!bik.GetData(i.meta, i.id.data())) isSuccessLoad = false;
        }
    }
    else
    {
        bikFailMsg.SetDescribe("Failed to load binary pack file!");
        bikFailMsg.Appear();
    }

    if (isSuccessLoad)
    {
        Image tmpBkg = LoadImageFromMemory(".png", bfrBackStars.data(), bfrBackStars.size());
        backStars = LoadTextureFromImage(tmpBkg);
        UnloadImage(tmpBkg);

        for (auto& i : planets)
        {
            Image tmp = LoadImageFromMemory(".png", i.meta.data(), i.meta.size());
            i.texture = LoadTextureFromImage(tmp);
            i.src = {0.0f, 0.0f, 128.0f, 128.0f};
            i.dst = {i.pos.x, i.pos.y, i.scale, i.scale};
            i.ori = {i.scale / 2.0f, i.scale / 2.0f};
            UnloadImage(tmp);
        }
    }
    else
    {
        bikFailMsg.SetDescribe("Metadata is not found in the binary pack!");
        bikFailMsg.Appear();
    }
}

void HLITEMain::Update()
{
    if (bikFailMsg.Update() == MB_BTN_OK)
        wc.Dispatch();

    if (bikFailMsg.IsMBXApear()) return;

    Vector2 mousePos = GetMousePosition();

    if (CheckCollisionPointRec(mousePos, planets[0].dst))
    {
        DrawText("Mercury",
                 planets[0].dst.x - planets[0].dst.width - 25.0f,
                 planets[0].dst.y - planets[0].dst.height - 25.0f,
                 25, WHITE);
    }

    if (CheckCollisionPointRec(mousePos, planets[1].dst))
    {
        DrawText("Venus",
                 planets[1].dst.x - planets[1].dst.width + 100.0f,
                 planets[1].dst.y - planets[1].dst.height + 35.0f,
                 25, WHITE);
    }

    if (CheckCollisionPointRec(mousePos, planets[2].dst))
    {
        DrawText("Earth",
                 planets[2].dst.x - planets[2].dst.width + 155.0f,
                 planets[2].dst.y - planets[2].dst.height + 35.0f,
                 25, WHITE);
    }
}

void HLITEMain::Render()
{
    bikFailMsg.Draw();

    if (bikFailMsg.IsMBXApear()) return;

    DrawTexture(backStars, 0, 0, Fade(WHITE, 0.3f));

    for (const auto& i : planets)
        DrawTexturePro(i.texture, i.src, i.dst, i.ori, i.rotate, WHITE);
}

void HLITEMain::Unload()
{ 
    if (backStars.id > 0) UnloadTexture(backStars);

    for (auto& i : planets)
    {
        if (i.texture.id > 0) UnloadTexture(i.texture);
    }
}