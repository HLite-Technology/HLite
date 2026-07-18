#include "../include/HLITE/Graphics2D.hpp"

#include <array>
#include <cmath>

namespace HLITE
{
    namespace GRAPHICS_2D
    {
        // ==================
        // PRIMITIVE PARTICLE
        // ==================
        
        void Particle::Emit(Vector2 Position, Vector2 Velocity, float Radius, float LifeTime, Color ColorParticles)
        {
            for (auto &p : particles)
            {
                if (!p.IsAlive())
                {
                    p.Init(Position, Velocity, Radius, LifeTime, ColorParticles);
                    break;
                }
            }
        }

        void Particle::Update(float DeltaTime)
        {
            for (auto &p : particles) p.Update(DeltaTime);
        }

        void Particle::Draw()
        {
            for (auto &p : particles) p.Draw();
        }

        void Particle::ParticleSystem::Init(Vector2 Position, Vector2 Velocity, float Radius, float LifeTime, Color ParticleCol)
        {
            position = Position;
            velocity = Velocity;
            radius = Radius;
            color = ParticleCol;
            lifeTime = LifeTime;
            alive = true;
        }

        void Particle::ParticleSystem::Update(float DeltaTime)
        {
            if (!alive) return;
            
            position.x += velocity.x * DeltaTime;
            position.y += velocity.y * DeltaTime;
        
            lifeTime -= DeltaTime;
            if (lifeTime <= 0.0f) alive = false;
        }

        void Particle::ParticleSystem::Draw()
        {
            if (alive) DrawCircleV(position, radius, color);
        }

        // ===============
        // MODERN PARTICLE
        // ===============

        void ParticleEx::Emit(Vector2 Position, Vector2 Velocity, float Radius, float LifeTime, float GravityParticle, Color ColorParticles, ParticleType Type)
        {
            for (auto &p : particles)
            {
                if (!p.IsAlive())
                {
                    p.Init(Position, Velocity, Radius, LifeTime, GravityParticle, ColorParticles, Type);
                    break;
                }
            }
        }

        void ParticleEx::Update(float DeltaTime)
        {
            for (auto &p : particles) p.Update(DeltaTime);
        }

        void ParticleEx::Draw()
        {
            for (auto &p : particles) p.Draw();
        }

        void ParticleEx::ParticleExSystem::Init(Vector2 Position, Vector2 Velocity, float Radius, float LifeTime, float GravityParticle, Color ParticleCol, ParticleType Type)
        {
            position = Position;
            velocity = Velocity;
            radius = Radius;
            lifeTime = LifeTime;
            gravity = GravityParticle;
            color = ParticleCol;
            alive = true;
            t = Type;
        }

        void ParticleEx::ParticleExSystem::Update(float DeltaTime)
        {
            if (!alive) return;
            lifeTime -= DeltaTime;
            if (lifeTime <= 0.0f) alive = false;

            switch (t) {
            case ParticleType::WATER:
                position.x += velocity.x * DeltaTime;
                if (gravity == 0.0f) velocity.y += 0.2f; // gravity
                else velocity.y += gravity;
                position.y += velocity.y * DeltaTime;
                break;
            case ParticleType::SMOKE:
                position.x += velocity.x * DeltaTime;
                velocity.y -= 0.05f;
                position.y += velocity.y * DeltaTime;
                radius += 0.5f * DeltaTime;
                color.a = (color.a > 4) ? color.a - 4 : 0;
                if (color.a <= 4) alive = false;
                break;
            case ParticleType::FIRE:
                position.x += velocity.x * DeltaTime + std::cosf(lifeTime*215.0f);
                velocity.y -= 0.05f;
                position.y += velocity.y * DeltaTime;
                radius -= 0.15f * DeltaTime;
                if (color.g > 3) color.g -= 3;
                if (radius <= 0.02f) alive = false;
                break;
            }
        }

        void ParticleEx::ParticleExSystem::Draw()
        {
            if (alive) DrawCircleV(position, radius, color);
        }
    }
}