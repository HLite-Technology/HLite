#ifndef SHADER_HPP
#define SHADER_HPP

#include "Preprocessor.hpp"

#include <array>
#include <vector>

constexpr int MAX_LIGHTS = 32;

namespace HLITE
{
    // Shader support.
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
                /// @brief Initializes the lighting shader and its uniform locations.
                void Init();

                /// @brief Adds a light to the active lighting collection.
                /// @param light The light description to add.
                void AddLight(const LightData& light);

                /// @brief Creates a point light description.
                /// @param pos The point light position.
                /// @param radius The point light radius.
                /// @param intensity The point light intensity.
                /// @param color The point light color.
                /// @return A configured point light description.
                LightData CreatePointLight(Vector2 pos, float radius, float intensity, Color color);
                /// @brief Creates a spot light description.
                /// @param pos The spot light position.
                /// @param dir The spot light direction.
                /// @param radius The spot light radius.
                /// @param intensity The spot light intensity.
                /// @param angle The spot light cone angle.
                /// @param color The spot light color.
                /// @return A configured spot light description.
                LightData CreateSpotLight(Vector2 pos,Vector2 dir, float radius, float intensity, float angle, Color color);
                /// @brief Creates a directional light description.
                /// @param dir The directional light direction.
                /// @param intensity The directional light intensity.
                /// @param color The directional light color.
                /// @return A configured directional light description.
                LightData CreateDirectionalLight(Vector2 dir, float intensity, Color color);
                /// @brief Creates an ambient light description.
                /// @param intensity The ambient light intensity.
                /// @param color The ambient light color.
                /// @return A configured ambient light description.
                LightData CreateAmbientLight( float intensity, Color color);

                /// @brief Updates shader data for all active lights.
                void Update();
                /// @brief Renders the scene through the lighting shader.
                /// @param Callback The callback used to render the scene.
                void Render(void(*Callback)());
                /// @brief Removes all active lights.
                void ClearLights();
                /// @brief Releases lighting resources.
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

#endif