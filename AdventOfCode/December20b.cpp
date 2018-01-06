#include "stdafx.h"

#include <iostream>
#include <map>

#include "December20b.h"

using namespace AdventOfCode::December20;

ParticleManagerB::ParticleManagerB(const std::string& fileName)
    : ParticleManager()
{
    ReadFile(fileName);
    ProcessParticles();
}

void ParticleManagerB::OutputResultToConsole() const
{
    std::cout << "December20.b: result = " << GetNumParticles() << std::endl;
}

void ParticleManagerB::ProcessParticles()
{
    std::map<Vector3D, std::vector<std::shared_ptr<Particle>>> collidingParticles;

    // tick until all particles are destroyed or all particles have matching signs
    // for position, velocity and acceleration AND there haven't been any collisions
    // in a while
    bool allParticlesHaveMatchingSigns = false;
    int timeSinceLastCollision = 0;

    const int ABORT_AT_TIME_SINCE_LAST_COLLISION = 20;

    while (!m_particles.empty())
    {
        collidingParticles.clear();
        bool differentSigns = false;
        bool didCollide = false;

        for (const auto& p : m_particles)
        {
            auto& found = collidingParticles.find(p->GetPosition());
            if (found == collidingParticles.end())
            {
                collidingParticles.emplace(p->GetPosition(), std::vector<std::shared_ptr<Particle>>({ p }));
            }
            else
            {
                didCollide = true;
                found->second.push_back(p);
            }

            // update the particle's velocity and position
            p->Tick();

            if (allParticlesHaveMatchingSigns || differentSigns)
            {
                // tick only, no further comparison needed
                continue;
            }

            if (p->CheckHasDifferentSigns())
            {
                differentSigns = true;
            }
        }

        // destroy all particles that collided this tick
        for (const auto& c : collidingParticles)
        {
            if (c.second.size() > 1)
            {
                for (auto& p : c.second)
                {
                    const auto& found = std::find(m_particles.begin(), m_particles.end(), p);
                    m_particles.erase(found);
                }
            }
        }

        if (didCollide)
        {
            timeSinceLastCollision = 0;
        }
        else
        {
            timeSinceLastCollision++;
        }

        // all particles have matching signs
        if (!differentSigns)
        {
            allParticlesHaveMatchingSigns = true;
        }

        if (allParticlesHaveMatchingSigns && timeSinceLastCollision > ABORT_AT_TIME_SINCE_LAST_COLLISION)
        {
            break;
        }
    }
}
