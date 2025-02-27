#include "ParticleSystem.h"
#include <random>
#include <cmath>

ParticleSystem::ParticleSystem(int numParticles)
    : m_numParticles(numParticles),
      m_particles(numParticles),
      m_swirlForce(10.0f),
      m_radialForce(-16.0f),
      m_gravity(0.0f),
      m_minRadius(20.0f),
      m_spawnMinR(120.0f),
      m_spawnMaxR(130.0f)
{
}

void ParticleSystem::initialize() {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_real_distribution<float> distAngle(0.0f, 2.0f * 3.14159f);
    std::uniform_real_distribution<float> distR(0.0f, 1.0f);
    std::uniform_real_distribution<float> distLife(3.0f, 5.0f);

    for (auto& p : m_particles) {
        float angle = distAngle(gen);
        float baseR = m_spawnMinR + (m_spawnMaxR - m_spawnMinR) * distR(gen);
        p.x = baseR * std::cos(angle);
        p.y = baseR * std::sin(angle);
        p.vx = 0.0f;
        p.vy = 0.0f;
        p.life = distLife(gen);
        p.maxLife = p.life;
    }
}

void ParticleSystem::update(float dt) {
    for (auto& p : m_particles) {
        p.life -= dt;
        if (p.life <= 0.0f) {
            respawn(p);
            continue;
        }
        float dx = p.x;
        float dy = p.y;
        float r  = std::sqrt(dx * dx + dy * dy);

        if (r < m_minRadius) {
            respawn(p);
            continue;
        }
        if (r > 0.0001f) {
            float invR = 1.0f / r;
            float nx = dx * invR;
            float ny = dy * invR;
            float tx = -ny;
            float ty = nx;

            p.vx += m_swirlForce * tx * dt;
            p.vy += m_swirlForce * ty * dt;
            p.vx += m_radialForce * nx * dt;
            p.vy += m_radialForce * ny * dt;
        }
        p.vy -= m_gravity * dt;
        p.x += p.vx * dt;
        p.y += p.vy * dt;
    }
}

const std::vector<Particle>& ParticleSystem::getParticles() const {
    return m_particles;
}

void ParticleSystem::respawn(Particle& p) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_real_distribution<float> distAngle(0.0f, 2.0f * 3.14159f);
    std::uniform_real_distribution<float> distR(0.0f, 1.0f);
    std::uniform_real_distribution<float> distLife(3.0f, 5.0f);

    float angle = distAngle(gen);
    float baseR = m_spawnMinR + (m_spawnMaxR - m_spawnMinR) * distR(gen);
    p.x = baseR * std::cos(angle);
    p.y = baseR * std::sin(angle);
    p.vx = 0.0f;
    p.vy = 0.0f;
    p.life = distLife(gen);
    p.maxLife = p.life;
}
