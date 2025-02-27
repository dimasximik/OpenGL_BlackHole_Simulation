#pragma once
#include <vector>

struct Particle {
    float x, y;
    float vx, vy;
    float life;
    float maxLife;
};

class ParticleSystem {
public:
    ParticleSystem(int numParticles);
    void initialize();
    void update(float dt);
    const std::vector<Particle>& getParticles() const;

private:
    void respawn(Particle& p);

    int m_numParticles;
    std::vector<Particle> m_particles;

    float m_swirlForce;
    float m_radialForce;
    float m_gravity;
    float m_minRadius;
    float m_spawnMinR;
    float m_spawnMaxR;
};
