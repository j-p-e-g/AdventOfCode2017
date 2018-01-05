#pragma once

#include <memory>
#include <vector>

#include "AdventOfCodeBase.h"

/*
    https://adventofcode.com/2017/day/20

    Part 1:

    Suddenly, the GPU contacts you, asking for help. Someone has asked it to simulate too many particles, and it won't be able to finish them all in time to render the next frame at this rate.

    It transmits to you a buffer (your puzzle input) listing each particle in order (starting with particle 0, then particle 1, particle 2, and so on). For each particle, it provides the X, Y, and Z coordinates for the particle's position (p), velocity (v), and acceleration (a), each in the format <X,Y,Z>.

    Each tick, all particles are updated simultaneously. A particle's properties are updated in the following order:

    Increase the X velocity by the X acceleration.
    Increase the Y velocity by the Y acceleration.
    Increase the Z velocity by the Z acceleration.
    Increase the X position by the X velocity.
    Increase the Y position by the Y velocity.
    Increase the Z position by the Z velocity.

    Because of seemingly tenuous rationale involving z-buffering, the GPU would like to know which particle will stay closest to position <0,0,0> in the long term. Measure this using the Manhattan distance, which in this situation is simply the sum of the absolute values of a particle's X, Y, and Z position.

        For example, suppose you are only given two particles, both of which stay entirely on the X-axis (for simplicity). Drawing the current states of particles 0 and 1 (in that order) with an adjacent a number line and diagram of current X positions (marked in parenthesis), the following would take place:

        p=< 3,0,0>, v=< 2,0,0>, a=<-1,0,0>    -4 -3 -2 -1  0  1  2  3  4
        p=< 4,0,0>, v=< 0,0,0>, a=<-2,0,0>                         (0)(1)

        p=< 4,0,0>, v=< 1,0,0>, a=<-1,0,0>    -4 -3 -2 -1  0  1  2  3  4
        p=< 2,0,0>, v=<-2,0,0>, a=<-2,0,0>                      (1)   (0)

        p=< 4,0,0>, v=< 0,0,0>, a=<-1,0,0>    -4 -3 -2 -1  0  1  2  3  4
        p=<-2,0,0>, v=<-4,0,0>, a=<-2,0,0>          (1)               (0)

        p=< 3,0,0>, v=<-1,0,0>, a=<-1,0,0>    -4 -3 -2 -1  0  1  2  3  4
        p=<-8,0,0>, v=<-6,0,0>, a=<-2,0,0>                         (0)

        At this point, particle 1 will never be closer to <0,0,0> than particle 0, and so, in the long run, particle 0 will stay closest.

    Which particle will stay closest to position <0,0,0> in the long term?
*/

namespace AdventOfCode {
namespace December20 {

    struct Vector3D
    {
        Vector3D(int _x, int _y, int _z)
            : x(_x)
            , y(_y)
            , z(_z)
        {
        }

        Vector3D()
            : Vector3D(0, 0, 0)
        {
        }

        void operator =(const Vector3D& other)
        {
            x = other.x;
            y = other.y;
            z = other.z;
        }

        void operator +=(const Vector3D& other)
        {
            x += other.x;
            y += other.y;
            z += other.z;
        }

        Vector3D operator - (const Vector3D& other) const
        {
            Vector3D temp;
            temp.x = x - other.x;
            temp.y = y - other.y;
            temp.z = z - other.z;
            return temp;
        }

        bool operator ==(const Vector3D& other) const
        {
            return x == other.x && y == other.y && z == other.z;
        }

        int GetDistanceSquared() const
        {
            return x*x + y*y + z*z;
        }

        int GetX() const { return x; }
        int GetY() const { return y; }
        int GetZ() const { return z; }

    private:
        int x;
        int y;
        int z;
    };

    class Particle
    {
    public:
        Particle() {};

    public:
        bool ParseProperties(const std::string& input);
        Vector3D GetPosition() const { return m_position; }
        Vector3D GetVelocity() const { return m_velocity; }
        Vector3D GetAcceleration() const { return m_acceleration; }
        void Tick();
        int GetDistanceSquared(const Vector3D& position) const;

    private:
        Vector3D m_position;
        Vector3D m_velocity;
        Vector3D m_acceleration;
    };

    class ParticleManager
        : protected AdventOfCodeBase
    {
    public:
        ParticleManager() {};
        ParticleManager(const std::string& fileName);
        ~ParticleManager() = default;

    public:
        // AdventOfCodeBase
        virtual bool ParseLine(const std::string& inputLine) override;
        virtual void OutputResultToConsole() const override;
        // ~AdventOfCodeBase

    public:
        void Tick();
        int GetNumParticles() const { return static_cast<int>(m_particles.size()); }
        int GetParticleIdLongtermClosestToOrigin() const;

    private:
        std::vector<std::shared_ptr<Particle>> m_particles;
    };

}}
