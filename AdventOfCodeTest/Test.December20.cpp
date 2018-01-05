#include "stdafx.h"
#include "CppUnitTest.h"
#include "../AdventOfCode/December20.h"

namespace AdventOfCodeTest
{
    using namespace Microsoft::VisualStudio::CppUnitTestFramework;
    using namespace AdventOfCode::December20;

    TEST_CLASS(Test_December20)
    {
    public:
        // ------------------------------
        // Particle::ParseProperties
        // ------------------------------
        TEST_METHOD(December20_Particle_default)
        {
            Particle test;
            Assert::AreEqual(true, Vector3D(0, 0, 0) == test.GetPosition());
            Assert::AreEqual(true, Vector3D(0, 0, 0) == test.GetVelocity());
            Assert::AreEqual(true, Vector3D(0, 0, 0) == test.GetAcceleration());
        }

        TEST_METHOD(December20_Particle_ParseProperties_missingOpeningBracket)
        {
            Particle test;
            Assert::AreEqual(false, test.ParseProperties("p=5,2,386>, v=<2,9,-35>, a=<1,2,33>"));
        }

        TEST_METHOD(December20_Particle_ParseProperties_missingClosingBracket)
        {
            Particle test;
            Assert::AreEqual(false, test.ParseProperties("p=<18,-3,29>, v=<-1,-3,5, a=<52,9,1>"));
        }

        TEST_METHOD(December20_Particle_ParseProperties_wrongBracketType)
        {
            Particle test;
            Assert::AreEqual(false, test.ParseProperties("p=(0,5,0), v=(52,1,11), a=(1,3,4)"));
        }

        TEST_METHOD(December20_Particle_ParseProperties_invalidPropertyTypes)
        {
            Particle test;
            Assert::AreEqual(false, test.ParseProperties("a=<4,-88,-16>, b=<8,3,-2>, c=<-9,3,1>"));
        }

        TEST_METHOD(December20_Particle_ParseProperties_redundantProperties)
        {
            Particle test;
            Assert::AreEqual(false, test.ParseProperties("p=<1,87,-3>, p=<1,87,-3>, p=<1,87,-3>"));
        }

        TEST_METHOD(December20_Particle_ParseProperties_missingPosition)
        {
            Particle test;
            Assert::AreEqual(false, test.ParseProperties("v=<18,2,98>, a=<8,2386,5>"));
        }

        TEST_METHOD(December20_Particle_ParseProperties_missingVelocity)
        {
            Particle test;
            Assert::AreEqual(false, test.ParseProperties("p=<-25,-2,25>, a=<68,2,-36>"));
        }

        TEST_METHOD(December20_Particle_ParseProperties_missingAcceleration)
        {
            Particle test;
            Assert::AreEqual(false, test.ParseProperties("p=<281,-627,22>, v=<7,-31,9726>"));
        }

        TEST_METHOD(December20_Particle_ParseProperties_allPositive)
        {
            Particle test;
            Assert::AreEqual(true, test.ParseProperties("p=<3,10021,5>, v=<47,99,6>, a=<1,13,9>"));
            Assert::AreEqual(true, Vector3D(3, 10021, 5) == test.GetPosition());
            Assert::AreEqual(true, Vector3D(47, 99, 6) == test.GetVelocity());
            Assert::AreEqual(true, Vector3D(1, 13, 9) == test.GetAcceleration());
        }

        TEST_METHOD(December20_Particle_ParseProperties_allNegative)
        {
            Particle test;
            Assert::AreEqual(true, test.ParseProperties("p=<-74,-2,-123>, v=<-8,-86,-9>, a=<-62,-923,-11>"));
            Assert::AreEqual(true, Vector3D(-74, -2, -123) == test.GetPosition());
            Assert::AreEqual(true, Vector3D(-8, -86, -9) == test.GetVelocity());
            Assert::AreEqual(true, Vector3D(-62, -923, -11) == test.GetAcceleration());
        }

        TEST_METHOD(December20_Particle_ParseProperties_addedSpaces)
        {
            Particle test;
            Assert::AreEqual(true, test.ParseProperties("p = <1, 23, 425>, v= < 82,-76, 25 >, a =< -26, -5, 269>"));

            Assert::AreEqual(true, Vector3D(1, 23, 425) == test.GetPosition());
            Assert::AreEqual(true, Vector3D(82, -76, 25) == test.GetVelocity());
            Assert::AreEqual(true, Vector3D(-26, -5, 269) == test.GetAcceleration());
        }

        TEST_METHOD(December20_Particle_ParseProperties_shuffledProperties)
        {
            Particle test;
            Assert::AreEqual(true, test.ParseProperties("a=<8,-2,2>, p=<962,27,-16>, v=<58,5,21>"));

            Assert::AreEqual(true, Vector3D(962, 27, -16) == test.GetPosition());
            Assert::AreEqual(true, Vector3D(58, 5, 21) == test.GetVelocity());
            Assert::AreEqual(true, Vector3D(8, -2, 2) == test.GetAcceleration());
        }

        TEST_METHOD(December20_Particle_ParseProperties_valid)
        {
            Particle test;
            Assert::AreEqual(true, test.ParseProperties("p=< 3,10021,5>, v=< 47,99,6>, a=<-1,-13,-9>"));
            Assert::AreEqual(true, Vector3D(3, 10021, 5) == test.GetPosition());
            Assert::AreEqual(true, Vector3D(47, 99, 6) == test.GetVelocity());
            Assert::AreEqual(true, Vector3D(-1, -13, -9) == test.GetAcceleration());
        }

        TEST_METHOD(December20_Particle_Tick)
        {
            Particle test;
            Assert::AreEqual(true, test.ParseProperties("p=<100, 200, -120>, v=<-14,99,5>, a=<3,-10,5>"));

            test.Tick();

            // acceleration should be unchanged
            Assert::AreEqual(true, Vector3D(3, -10, 5) == test.GetAcceleration());

            // acceleration was applied to velocity
            Assert::AreEqual(true, Vector3D(-11, 89, 10) == test.GetVelocity());

            // velocity was applied to position
            Assert::AreEqual(true, Vector3D(89, 289, -110) == test.GetPosition());
        }

        TEST_METHOD(December20_Particle_GetDistanceFromOrigin)
        {
            Particle test;
            Assert::AreEqual(true, test.ParseProperties("p=<10, 20, 30>, v=<-2,1,0>, a=<0,-1,0>"));

            Assert::AreEqual(1400, test.GetDistanceSquared(Vector3D(0,0,0)));
        }

        // ------------------------------
        // ParticleManager
        // ------------------------------

        TEST_METHOD(December20_ParticleManager)
        {
            ParticleManager test;
            Assert::AreEqual(0, test.GetNumParticles());
            Assert::AreEqual(-1, test.GetParticleIdLongtermClosestToOrigin());
        }

        TEST_METHOD(December20_ParticleManager_ParseLine)
        {
            ParticleManager test;
            Assert::AreEqual(true, test.ParseLine("p=<18,96,-3>, v=<-2,52,25>, a=<1,0,29>"));
            Assert::AreEqual(true, test.ParseLine("p=<0,0,0>, v=<1,1,1>, a=<2,2,2>"));
            Assert::AreEqual(2, test.GetNumParticles());
        }

        /*
        No matter the values, if there's only one particle, id 0 will be closest.
        */
        TEST_METHOD(December20_GetParticleIdLongtermClosestToOrigin_single)
        {
            ParticleManager test;
            test.ParseLine("p=<156,5836,22569>, v=<38,52,26>, a=<6,2,8>");

            Assert::AreEqual(0, test.GetParticleIdLongtermClosestToOrigin());
        }

        /*
        Particles only differ in their acceleration.
        */
        TEST_METHOD(December20_GetParticleIdLongtermClosestToOrigin_accelerationOnly)
        {
            ParticleManager test;
            test.ParseLine("p=<0,0,0>, v=<0,0,0>, a=<0,0,2>");
            test.ParseLine("p=<0,0,0>, v=<0,0,0>, a=<1,0,0>");
            test.ParseLine("p=<0,0,0>, v=<0,0,0>, a=<0,3,0>");

            Assert::AreEqual(1, test.GetParticleIdLongtermClosestToOrigin());
        }

        /*
        Particles only differ in their velocity.
        */
        TEST_METHOD(December20_GetParticleIdLongtermClosestToOrigin_velocityOnly)
        {
            ParticleManager test;
            test.ParseLine("p=<0,0,0>, v=<0,0,1>, a=<0,0,0>");
            test.ParseLine("p=<0,0,0>, v=<0,3,2>, a=<0,0,0>");
            test.ParseLine("p=<0,0,0>, v=<4,0,0>, a=<0,0,0>");

            Assert::AreEqual(0, test.GetParticleIdLongtermClosestToOrigin());
        }

        /*
        Particles only differ in their start position, but never move.
        */
        TEST_METHOD(December20_GetParticleIdLongtermClosestToOrigin_positionOnly)
        {
            ParticleManager test;
            test.ParseLine("p=<0,2,0>, v=<0,0,0>, a=<0,0,0>");
            test.ParseLine("p=<1,0,1>, v=<0,0,0>, a=<0,0,0>");
            test.ParseLine("p=<2,1,2>, v=<0,0,0>, a=<0,0,0>");

            Assert::AreEqual(1, test.GetParticleIdLongtermClosestToOrigin());
        }

        /*
        Particle 0 never moves, while particles 1 and 2 will keep moving until they're eventually farther away from the origin than particle 0.
        */
        TEST_METHOD(December20_GetParticleIdLongtermClosestToOrigin)
        {
            ParticleManager test;
            test.ParseLine("p=<0,0,0>, v=<10,10,10>, a=<0,0,0>");
            test.ParseLine("p=<0,0,0>, v=<0,0,0>, a=<1,0,0>");
            test.ParseLine("p=<90,52,108>, v=<0,0,0>, a=<0,0,0>");

            Assert::AreEqual(2, test.GetParticleIdLongtermClosestToOrigin());
        }

        /*
        Both particles have the same acceleration but the second one first has to overtake
        the origin while the first one starts moving away, meaning by the time the second
        one catches up, the first one (although it has a smaller initial velocity) will be 
        moving with a higher velocity, and keep that headstart.

        tick 1:
        p0: p=<1,0,0>, v=<1,0,0>
        p1: p=<1,0,0>, v=<1,0,0>

        tick 2:
        p0: p=<3,0,0>, v=<2,0,0>
        p1: p=<1,0,0>, v=<0,0,0>

        tick 3:
        p0: p=<6,0,0>, v=<3,0,0>
        p1: p=<0,0,0>, v=<-1,0,0>

        tick 4:
        p0: p=<10,0,0>, v=<4,0,0>
        p1: p=<-2,0,0>, v=<-2,0,0>
        */
        TEST_METHOD(December20_GetParticleIdLongtermClosestToOrigin_accelerationTie)
        {
            ParticleManager test;
            test.ParseLine("p=<0,0,0>, v=<0,0,0>, a=<1,0,0>");
            test.ParseLine("p=<0,0,0>, v=<2,0,0>, a=<-1,0,0>");

            // second one stays closer
            Assert::AreEqual(1, test.GetParticleIdLongtermClosestToOrigin());
        }

        /*
        As above, but both particles also have the same speed.

        tick 1:
        p0: p=<5,0,0>, v=<0,0,0>
        p1: p=<2,0,0>, v=<0,0,0>

        tick 2:
        p0: p=<6,0,0>, v=<1,0,0>
        p1: p=<1,0,0>, v=<-1,0,0>

        tick 3:
        p0: p=<8,0,0>, v=<2,0,0>
        p1: p=<-1,0,0>, v=<-2,0,0>
        */
        TEST_METHOD(December20_GetParticleIdLongtermClosestToOrigin_velocityTie)
        {
            ParticleManager test;
            test.ParseLine("p=<5,0,0>,v=<-1,0,0>,a=<1,0,0>");
            test.ParseLine("p=<2,0,0>,v=<1,0,0>,a=<-1,0,0>");

            // second one stays closer
            Assert::AreEqual(1, test.GetParticleIdLongtermClosestToOrigin());
        }

        /*
        p=< 3,0,0>, v=< 2,0,0>, a=<-1,0,0>
        p=< 4,0,0>, v=< 0,0,0>, a=<-2,0,0>

        [...] in the long run, particle 0 will stay closest.
        */
        TEST_METHOD(December20_GetParticleIdLongtermClosestToOrigin_AoC_test)
        {
            ParticleManager test;
            test.ParseLine("p=< 3,0,0>, v=< 2,0,0>, a=<-1,0,0>");
            test.ParseLine("p=< 4,0,0>, v=< 0,0,0>, a=<-2,0,0>");

            Assert::AreEqual(0, test.GetParticleIdLongtermClosestToOrigin());
        }
    };
}
