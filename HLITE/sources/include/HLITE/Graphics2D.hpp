#ifndef GRAPHICS2D_HPP
#define GRAPHICS2D_HPP

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
            /// @brief Emits a particle with the specified initial state.
            /// @param Position The initial particle position.
            /// @param Velocity The initial particle velocity.
            /// @param Radius The particle radius.
            /// @param LifeTime The particle lifetime in seconds.
            /// @param ColorParticles The particle color.
            void Emit(
                Vector2 Position,
                Vector2 Velocity,
                float Radius,
                float LifeTime,
                Color ColorParticles
            );
            /// @brief Advances all active particles by the elapsed time.
            /// @param DeltaTime The elapsed time in seconds.
            void Update(float DeltaTime);
            /// @brief Draws all active particles.
            virtual void Draw();
        private:
            // Protected system particle system support.
            class ParticleSystem
            {
            public:
                /// @brief Initializes a particle system entry.
                /// @param Position The initial particle position.
                /// @param Velocity The initial particle velocity.
                /// @param Radius The particle radius.
                /// @param LifeTime The particle lifetime in seconds.
                /// @param ParticleCol The particle color.
                void Init(
                    Vector2 Position, 
                    Vector2 Velocity, 
                    float Radius,  
                    float LifeTime,
                    Color ParticleCol
                );
                /// @brief Advances the particle by the elapsed time.
                /// @param deltaTime The elapsed time in seconds.
                void Update(float deltaTime);
                /// @brief Returns whether the particle is still active.
                /// @return `true` while the particle is active; otherwise, `false`.
                bool IsAlive() { return alive; }
                /// @brief Draws the particle.
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
            /// @brief Emits an extended particle with gravity and a particle type.
            /// @param Position The initial particle position.
            /// @param Velocity The initial particle velocity.
            /// @param Radius The particle radius.
            /// @param LifeTime The particle lifetime in seconds.
            /// @param GravityParticle The gravity applied to the particle.
            /// @param ColorParticles The particle color.
            /// @param Type The type of particle to emit.
            void Emit(
                Vector2 Position,
                Vector2 Velocity,
                float Radius,
                float LifeTime,
                float GravityParticle,
                Color ColorParticles,
                ParticleType Type
            );
            /// @brief Advances all extended particles by the elapsed time.
            /// @param DeltaTime The elapsed time in seconds.
            void Update(float DeltaTime);
            /// @brief Draws all active extended particles.
            void Draw() override;
        private:
            class ParticleExSystem
            {
            public:
                /// @brief Initializes an extended particle system entry.
                /// @param Position The initial particle position.
                /// @param Velocity The initial particle velocity.
                /// @param Radius The particle radius.
                /// @param LifeTime The particle lifetime in seconds.
                /// @param GravityParticle The gravity applied to the particle.
                /// @param ColorParticles The particle color.
                /// @param Type The type of particle to initialize.
                void Init(
                    Vector2 Position,
                    Vector2 Velocity,
                    float Radius,
                    float LifeTime,
                    float GravityParticle,
                    Color ColorParticles,
                    ParticleType Type
                );
                /// @brief Advances the extended particle by the elapsed time.
                /// @param DeltaTime The elapsed time in seconds.
                void Update(float DeltaTime);
                /// @brief Returns whether the extended particle is still active.
                /// @return `true` while the particle is active; otherwise, `false`.
                bool IsAlive() { return alive; }
                /// @brief Draws the extended particle.
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

#endif