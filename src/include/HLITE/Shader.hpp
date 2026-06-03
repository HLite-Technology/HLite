#pragma once

#include "Preprocessor.hpp"

#include <array>
#include <vector>

constexpr int MAX_LIGHTS = 32;

namespace HLITE
{
    namespace SHADERS
    {
        namespace GRAPHICS_2D
        {
            enum LightType
            {
                LIGHT_POINT = 0,
                LIGHT_SPOT = 1,
                LIGHT_DIRECTIONAL = 2,
                LIGHT_AMBIENT = 3
            };

            struct LightData
            {
                int type;
                Vector2 position;
                Vector2 direction;
                Color color;
                float radius;
                float intensity;
                float angle;
            };

            struct LightUniform
            {
                int type;
                int position;
                int direction;
                int color;
                int radius;
                int intensity;
                int angle;
            };

            class Lighting
            {
            public:
                void Init();

                void AddLight(const LightData& light);

                LightData CreatePointLight(Vector2 pos, float radius, float intensity, Color color);
                LightData CreateSpotLight(Vector2 pos,Vector2 dir, float radius, float intensity, float angle, Color color);
                LightData CreateDirectionalLight(Vector2 dir, float intensity, Color color);
                LightData CreateAmbientLight( float intensity, Color color);

                void Update();
                void Render(void(*Callback)());
                void ClearLights();
                void Close();

            private:
                Shader shader;
                int lightCountLoc;
                int resolutionLoc;
                std::vector<LightData> lights;
                std::array<LightUniform, MAX_LIGHTS> uniformCache;
            };
        }
    }
}