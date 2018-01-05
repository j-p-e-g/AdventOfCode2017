#include "stdafx.h"

#include <iostream>
#include <map>
#include <regex>
#include <set>

#include "CodeUtil.h"
#include "December20.h"

using namespace AdventOfCode::December20;

// ------------------------------
// Particle
// ------------------------------
bool Particle::ParseProperties(const std::string& input)
{
    std::string::const_iterator input_iter = input.cbegin();
    std::regex regex("(\\w)\\s*=\\s*<\\s*(-?\\d+)\\s*,\\s*(-?\\d+)\\s*,\\s*(-?\\d+)\\s*>");
    std::smatch match;

    std::set<char> types;
    while (std::regex_search(input_iter, input.end(), match, regex))
    {
        if (match.size() < 5)
        {
            return false;
        }

        // 0 is the entire match
        char id = match[1].str()[0];
        int x = atoi(match[2].str().c_str());
        int y = atoi(match[3].str().c_str());
        int z = atoi(match[4].str().c_str());

        switch (id)
        {
        case 'p':
            m_position = Vector3D(x, y, z);
            break;
        case 'v':
            m_velocity = Vector3D(x, y, z);
            break;
        case 'a':
            m_acceleration = Vector3D(x, y, z);
            break;
        default:
            return false;
        }

        types.emplace(id);
        input_iter = match[0].second;
    }

    // ensure that each type was set only once
    return (types.size() == 3);
}

void Particle::Tick()
{
    //Increase the X velocity by the X acceleration.
    //Increase the Y velocity by the Y acceleration.
    //Increase the Z velocity by the Z acceleration.
    m_velocity += m_acceleration;

    //Increase the X position by the X velocity.
    //Increase the Y position by the Y velocity.
    //Increase the Z position by the Z velocity.
    m_position += m_velocity;
}

int Particle::GetDistanceSquared(const Vector3D& position) const
{
    const Vector3D diff = m_position - position;
    return diff.GetDistanceSquared();
}

// ------------------------------
// ParticleManager
// ------------------------------
ParticleManager::ParticleManager(const std::string& fileName)
    : AdventOfCodeBase()
{
    ReadFile(fileName);
}

bool ParticleManager::ParseLine(const std::string& inputLine)
{
    std::shared_ptr<Particle> particle = std::make_shared<Particle>();
    if (!particle->ParseProperties(inputLine))
    {
        return false;
    }

    m_particles.push_back(particle);
    return true;
}

void ParticleManager::OutputResultToConsole() const
{
    std::cout << "December20: result = " << GetParticleIdLongtermClosestToOrigin() << std::endl;
}

void ParticleManager::Tick()
{
    for (auto& particle : m_particles)
    {
        particle->Tick();
    }
}

int ParticleManager::GetParticleIdLongtermClosestToOrigin() const
{
    if (m_particles.empty())
    {
        return -1;
    }

    // Since the velocity and position keep increasing (or decreasing over time), this means
    // that in the long run any particle that has non-zero velocity or non-zero acceleration
    // will move farther and farther away from the origin. 
    // (Even though it might first move closer, it will eventually move past and away.)

    // That, in turn, means that no matter the other values, the particle with the 
    // _lowest acceleration_ will in the long run (millions of ticks) remain closest to the origin.
    // In case of a tie, the particle with the smaller velocity will stay closest, and if
    // there's a tie in both acceleration and velocity, the particle with the lowest
    // distance to the origin.

    std::map<int, std::shared_ptr<Particle>> accelerationCandidates;
    accelerationCandidates.emplace(0, std::make_shared<Particle>(*m_particles[0]));

    for (int k = 1; k < m_particles.size(); k++)
    {
        int squaredAcceleration = m_particles[k]->GetAcceleration().GetDistanceSquared();
        int squaredMinAcceleration = accelerationCandidates.begin()->second->GetAcceleration().GetDistanceSquared();

        if (squaredAcceleration <= squaredMinAcceleration)
        {
            if (squaredAcceleration < squaredMinAcceleration)
            {
                accelerationCandidates.clear();
            }
            accelerationCandidates.emplace(k, std::make_shared<Particle>(*m_particles[k]));
        }
    }

    if (accelerationCandidates.size() == 1)
    {
        return accelerationCandidates.begin()->first;
    }

    // all have same acceleration

    // If the signs of velocity and acceleration don't match, a particle first has to 
    // move closer to the origin before moving away from it, meaning that its velocity
    // first has to decrease before it can increase again.
    // This in turn means that a particle with a smaller initial velocity can end up
    // a larger velocity by the time another particle (with the same acceleration) moves
    // past the origin and starts gathering speed.

    // Also, if two particles have the same velocity _and_ acceleration, the particle that
    // starts out closer to the origin will remain closer UNLESS another particle first has
    // to move closer to the origin before moving past it. This happens if the signs of 
    // their velocity and _position_ are different.

    // To handle these two cases, tick all candidate particles until all the signs match or are zero.

    while (true)
    {
        bool differentSigns = false;
        for (auto& c : accelerationCandidates)
        {
            c.second->Tick();

            if (differentSigns)
            {
                // tick only, no further comparison needed
                continue;
            }

            int vX = CodeUtils::CodeUtil::GetSign(c.second->GetVelocity().GetX());
            int aX = CodeUtils::CodeUtil::GetSign(c.second->GetAcceleration().GetX());
            int pX = CodeUtils::CodeUtil::GetSign(c.second->GetPosition().GetX());

            int vY = CodeUtils::CodeUtil::GetSign(c.second->GetVelocity().GetY());
            int aY = CodeUtils::CodeUtil::GetSign(c.second->GetAcceleration().GetY());
            int pY = CodeUtils::CodeUtil::GetSign(c.second->GetPosition().GetY());

            int vZ = CodeUtils::CodeUtil::GetSign(c.second->GetVelocity().GetZ());
            int aZ = CodeUtils::CodeUtil::GetSign(c.second->GetAcceleration().GetZ());
            int pZ = CodeUtils::CodeUtil::GetSign(c.second->GetPosition().GetZ());

            // p 1 v 1 a 1
            // p 1 v 1 a 0
            // p 1 v 1 a -1  -> p 1 v 0 a -1 -> p 0 v -1 a -1
            // p 1 v 0 a 1
            // p 1 v 0 a 0
            // p 1 v 0 a -1 -> p 0 v -1 a -1
            // p 1 v -1 a 1 -> p 1 v 0 a 1
            // p 1 v -1 a 0 -> p 0 v -1 a 0
            // p 1 v -1 a -1 -> p -1 v -2 a -1

            // p 0 v 1 a 1
            // p 0 v 1 a 0
            // p 0 v 1 a -1 -> p 0 v 0 a -1
            // p 0 v 0 a 1
            // p 0 v 0 a 0
            // p 0 v 0 a -1 -> p -1 v -1 a -1
            // p 0 v -1 a 1 -> p 0 v 0 a 1
            // p 0 v -1 a 0
            // p 0 v -1 a -1

            // p -1 v 1 a 1 -> p 1 v 2 a 1
            // p -1 v 1 a 0 -> p 0 v 1 a 0
            // p -1 v 1 a -1 -> p -1 v 0 a -1
            // p -1 v 0 a 1 -> p 0 v 1 a 1
            // p -1 v 0 a 0
            // p -1 v 0 a -1
            // p -1 v -1 a 1 -> p -1 v 0 a 1 -> p 0 v 1 a 1
            // p -1 v -1 a 0
            // p -1 v -1 a -1

            // correct if all signs are the same or zero
            if ((aX > 0 || vX > 0 || pX > 0) && (aX < 0 || vX < 0 || pX < 0)
                || (aY > 0 || vY > 0 || pY > 0) && (aY < 0 || vY < 0 || pY < 0)
                || (aZ > 0 || vZ > 0 || pZ > 0) && (aZ < 0 || vZ < 0 || pZ < 0))
            {
                differentSigns = true;
            }
        }

        if (!differentSigns)
        {
            break;
        }
    }

    // accelerations are still the same, so compare the velocities
    // in case of a tie, also compare distances directly

    int minId = accelerationCandidates.begin()->first;
    for (const auto& c : accelerationCandidates)
    {
        int squaredVelocity = c.second->GetVelocity().GetDistanceSquared();
        int squaredMinVelocity = accelerationCandidates[minId]->GetVelocity().GetDistanceSquared();

        if (squaredVelocity <= squaredMinVelocity)
        {
            if (squaredVelocity < squaredMinVelocity)
            {
                minId = c.first;
            }
            else if (squaredVelocity == squaredMinVelocity)
            {
                int squaredDistance = c.second->GetPosition().GetDistanceSquared();
                int squaredMinDistance = accelerationCandidates[minId]->GetPosition().GetDistanceSquared();

                if (squaredDistance < squaredMinDistance)
                {
                    minId = c.first;
                }
            }
        }
    }

    // if there's still a tie, returns the first one found
    return minId;
}
