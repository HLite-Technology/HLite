#pragma once

#include <array>

#include "Preprocessor.hpp"

namespace HLITE
{
    // Graphics 2D support.
    namespace GRAPHICS_2D
    {
        // Particle type support (Selection) (Todo...).
        typedef enum { WATER, SMOKE, FIRE } ParticleType;

        // Primitive particle.
        class Particle
        {
        public:
            void Emit(
                Vector2 Position,
                Vector2 Velocity,
                float Radius,
                float LifeTime,
                Color ColorParticles
            );
            void Update(float DeltaTime);
            virtual void Draw();
        private:
            // Protected system particle system support.
            class ParticleSystem
            {
            public:
                void Init(
                    Vector2 Position, 
                    Vector2 Velocity, 
                    float Radius,  
                    float LifeTime,
                    Color ParticleCol
                );
                void Update(float deltaTime);
                bool IsAlive() { return alive; }
                void Draw();
            
            private:
                Vector2 position;
                Vector2 velocity;
                float radius;
                Color color;
                float lifeTime;
                bool alive;
            };

            std::array<ParticleSystem, MAX_PARTICLES> particles;
        };

        // Modern particle.
        class ParticleEx : public Particle
        {
        public:
            void Emit(
                Vector2 Position,
                Vector2 Velocity,
                float Radius,
                float LifeTime,
                float GravityParticle,
                Color ColorParticles,
                ParticleType Type
            );
            void Update(float DeltaTime);
            void Draw() override;
        private:
            class ParticleExSystem
            {
            public:
                void Init(
                    Vector2 Position,
                    Vector2 Velocity,
                    float Radius,
                    float LifeTime,
                    float GravityParticle,
                    Color ColorParticles,
                    ParticleType Type
                );
                void Update(float DeltaTime);
                bool IsAlive() { return alive; }
                void Draw();
            private:
                Vector2 position;
                Vector2 velocity;
                float radius;
                Color color;
                float lifeTime;
                float gravity;
                bool alive;
                ParticleType t;
            };
            std::array<ParticleExSystem, MAX_PARTICLES> particles;
        };
    }
}