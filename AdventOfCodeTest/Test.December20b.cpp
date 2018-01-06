#include "stdafx.h"
#include "CppUnitTest.h"
#include "../AdventOfCode/December20b.h"

namespace AdventOfCodeTest
{
    using namespace Microsoft::VisualStudio::CppUnitTestFramework;
    using namespace AdventOfCode::December20;

    TEST_CLASS(Test_December20b)
    {
    public:
        /*
        single particle -> cannot be destroyed
        */
        TEST_METHOD(December20b_GetNumParticles_single)
        {
            ParticleManagerB test;
            test.ParseLine("p=<3,0,2>, v=<7,4,1>, a=<8,9,10>");
            test.ProcessParticles();

            Assert::AreEqual(1, test.GetNumParticles());
        }

        /*
        two particles that will collide and destroy each other
        */
        TEST_METHOD(December20b_GetNumParticles_2particles_collide)
        {
            ParticleManagerB test;
            // collide after 2 ticks at (2,2,2)
            test.ParseLine("p=<5,2,2>, v=<0,0,0>, a=<-1,0,0>");
            test.ParseLine("p=<0,6,8>, v=<1,-2,-3>, a=<0,0,0>");
            test.ProcessParticles();

            Assert::AreEqual(0, test.GetNumParticles());
        }

        /*
        two particles that will never collide
        */
        TEST_METHOD(December20b_GetNumParticles_2particles_neverCollide)
        {
            ParticleManagerB test;
            test.ParseLine("p=<1,2,3>, v=<0,1,1>, a=<1,0,0>");
            test.ParseLine("p=<5,4,3>, v=<1,0,8>, a=<0,0,0>");
            test.ProcessParticles();

            Assert::AreEqual(2, test.GetNumParticles());
        }

        /*
        particles with the same initial position collide immediately
        */
        TEST_METHOD(December20b_GetNumParticles_immediateCollision)
        {
            ParticleManagerB test;
            test.ParseLine("p=<3,4,-10>, v=<0,1,-2>, a=<1,0,-1>");
            test.ParseLine("p=<5,2,7>, v=<0,2,3>, a=<1,0,0>");
            test.ParseLine("p=<3,4,-10>, v=<10,10,0>, a=<1,1,0>");
            test.ProcessParticles();

            Assert::AreEqual(1, test.GetNumParticles());
        }

        /*
        Particle 3 would collide with particle 2, but by that time particle 1 and 2
        are already destroyed so particle 3 can continue unharmed.
        */
        TEST_METHOD(December20b_GetNumParticles_collisonPreventsCollision)
        {
            ParticleManagerB test;
            // collide after 1 tick at (5,0,-5)
            test.ParseLine("p=<4,0,-3>, v=<1,0,0>, a=<0,0,-2>");
            test.ParseLine("p=<2,0,-5>, v=<0,0,0>, a=<3,0,0>");
            // reaches (8,0,-5) after 2 ticks where it would collide with particle 2
            // if it wasn't already destroyed
            test.ParseLine("p=<4,0,-1>, v=<2,0,-2>, a=<0,0,0>");
            test.ProcessParticles();

            Assert::AreEqual(1, test.GetNumParticles());
        }

        /*
        p=<-6,0,0>, v=< 3,0,0>, a=< 0,0,0>
        p=<-4,0,0>, v=< 2,0,0>, a=< 0,0,0>    -6 -5 -4 -3 -2 -1  0  1  2  3
        p=<-2,0,0>, v=< 1,0,0>, a=< 0,0,0>    (0)   (1)   (2)            (3)
        p=< 3,0,0>, v=<-1,0,0>, a=< 0,0,0>

        In this example, particles 0, 1, and 2 are simultaneously destroyed [...]. On the next tick, particle 3 passes through unharmed.
        */
        TEST_METHOD(December20b_GetNumParticles_AoC_test)
        {
            ParticleManagerB test;
            test.ParseLine("p=<-6,0,0>, v=< 3,0,0>, a=< 0,0,0>");
            test.ParseLine("p=<-4,0,0>, v=< 2,0,0>, a=< 0,0,0>");
            test.ParseLine("p=<-2,0,0>, v=< 1,0,0>, a=< 0,0,0>");
            test.ParseLine("p=< 3,0,0>, v=<-1,0,0>, a=< 0,0,0>");
            test.ProcessParticles();

            // only 1 particle left
            Assert::AreEqual(1, test.GetNumParticles());
        }
    };
}
