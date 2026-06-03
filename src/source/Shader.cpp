#include "../include/HLITE/Shader.hpp"
#include "../include/HLITE/File.hpp"

#include <raymath.h>

#include <string>

namespace HLITE
{
    namespace SHADERS
    {
        namespace GRAPHICS_2D
        {
            void Lighting::Init()
            {
                shader = LoadShader(
                    0,
                    HLITE::FILE::GetPathFile(
                        "src/HLITE/resources/shaders/core330/lighting.fs",
                        false
                    )
                );

                lightCountLoc = GetShaderLocation(shader, "lightCount");
                resolutionLoc = GetShaderLocation(shader, "resolution");

                for (int i = 0; i < MAX_LIGHTS; i++)
                {
                    std::string base =
                        "lights[" + std::to_string(i) + "].";
                
                    uniformCache[i].type =
                        GetShaderLocation(shader, (base + "type").c_str());
                
                    uniformCache[i].position =
                        GetShaderLocation(shader, (base + "position").c_str());
                
                    uniformCache[i].direction =
                        GetShaderLocation(shader, (base + "direction").c_str());
                
                    uniformCache[i].color =
                        GetShaderLocation(shader, (base + "color").c_str());
                
                    uniformCache[i].radius =
                        GetShaderLocation(shader, (base + "radius").c_str());
                
                    uniformCache[i].intensity =
                        GetShaderLocation(shader, (base + "intensity").c_str());
                
                    uniformCache[i].angle =
                        GetShaderLocation(shader, (base + "angle").c_str());
                }
            }

            void Lighting::AddLight(const LightData& light)
            {
                lights.push_back(light);
            }

            LightData Lighting::CreatePointLight(Vector2 pos, float radius, float intensity, Color color)
            {
                LightData light{};

                light.type = LIGHT_POINT;
                light.position = pos;
                light.direction = {0.0f, 0.0f};
                light.color = color;
                light.radius = radius;
                light.intensity = intensity;
                light.angle = 0.0f;

                return light;
            }

            LightData Lighting::CreateSpotLight(Vector2 pos, Vector2 dir, float radius, float intensity, float angle, Color color)
            {
                LightData light{};

                light.type = LIGHT_SPOT;
                light.position = pos;
                light.direction = dir;
                light.color = color;
                light.radius = radius;
                light.intensity = intensity;
                light.angle = angle;

                return light;
            }

            LightData Lighting::CreateDirectionalLight(Vector2 dir,float intensity, Color color)
            {
                LightData light{};
            
                light.type = LIGHT_DIRECTIONAL;
                light.position = {0.0f, 0.0f};
                light.direction = Vector2Normalize(dir);
                light.color = color;
                light.radius = 0.0f;
                light.intensity = intensity;
                light.angle = 0.0f;
            
                return light;
            }

            LightData Lighting::CreateAmbientLight(float intensity, Color color)
            {
                LightData light{};
            
                light.type = LIGHT_AMBIENT;
                light.position = {0.0f, 0.0f};
                light.direction = {0.0f, 0.0f};
                light.color = color;
                light.radius = 0.0f;
                light.intensity = intensity;
                light.angle = 0.0f;
            
                return light;
            }

            void Lighting::Update()
            {
                int count = std::min((int)lights.size(), MAX_LIGHTS);
            
                SetShaderValue(
                    shader,
                    lightCountLoc,
                    &count,
                    SHADER_UNIFORM_INT
                );
            
                Vector2 resolution =
                {
                    (float)GetScreenWidth(),
                    (float)GetScreenHeight()
                };
            
                SetShaderValue(
                    shader,
                    resolutionLoc,
                    &resolution,
                    SHADER_UNIFORM_VEC2
                );
            
                for (int i = 0; i < count; i++)
                {
                    const LightData& light = lights[i];
                
                    // type
                    SetShaderValue(
                        shader,
                        uniformCache[i].type,
                        &light.type,
                        SHADER_UNIFORM_INT
                    );
                
                    // position
                    SetShaderValue(
                        shader,
                        uniformCache[i].position,
                        &light.position,
                        SHADER_UNIFORM_VEC2
                    );
                
                    // direction
                    SetShaderValue(
                        shader,
                        uniformCache[i].direction,
                        &light.direction,
                        SHADER_UNIFORM_VEC2
                    );
                
                    // color
                    float color[3] =
                    {
                        light.color.r / 255.0f,
                        light.color.g / 255.0f,
                        light.color.b / 255.0f
                    };
                
                    SetShaderValue(
                        shader,
                        uniformCache[i].color,
                        color,
                        SHADER_UNIFORM_VEC3
                    );
                
                    // radius
                    SetShaderValue(
                        shader,
                        uniformCache[i].radius,
                        &light.radius,
                        SHADER_UNIFORM_FLOAT
                    );
                
                    // intensity
                    SetShaderValue(
                        shader,
                        uniformCache[i].intensity,
                        &light.intensity,
                        SHADER_UNIFORM_FLOAT
                    );
                
                    // angle
                    SetShaderValue(
                        shader,
                        uniformCache[i].angle,
                        &light.angle,
                        SHADER_UNIFORM_FLOAT
                    );
                }
            }

            void Lighting::Render(void(*Callback)())
            {
                BeginShaderMode(shader);

                Callback();

                EndShaderMode();
            }

            void Lighting::ClearLights()
            {
                lights.clear();
            }

            void Lighting::Close()
            {
                UnloadShader(shader);
            }
        }
    }
}