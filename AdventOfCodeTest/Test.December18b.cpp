#include "stdafx.h"
#include "CppUnitTest.h"
#include "../AdventOfCode/December18b.h"

namespace AdventOfCodeTest
{
    using namespace Microsoft::VisualStudio::CppUnitTestFramework;
    using namespace AdventOfCode::December18;

    TEST_CLASS(Test_December18b)
    {
    public:
        // ------------------------------------------
        // RegisterSoloB
        // ------------------------------------------
        TEST_METHOD(December18b_RegisterSoloB_noCommands)
        {
            std::shared_ptr<RegisterDuet> duet = std::make_shared<RegisterDuet>();
            std::shared_ptr<RegisterSoloB> solo = std::make_shared<RegisterSoloB>(18, duet);
            duet->RegisterProgram(solo);

            // finished cleanly
            Assert::AreEqual(true, duet->ExecuteCommands());

            Assert::AreEqual(18, static_cast<int>(solo->GetRegisterValue('p')));
            Assert::AreEqual(true, solo->IsFinished());
            Assert::AreEqual(0, solo->GetSendCount());
        }

        // ------------------------------------------
        // Apply commands: RegisterSndB
        // ------------------------------------------
        TEST_METHOD(December18b_RegisterSndB_Apply)
        {
            std::shared_ptr<RegisterDuet> duet = std::make_shared<RegisterDuet>();
            std::shared_ptr<RegisterSoloB> solo1 = std::make_shared<RegisterSoloB>(0, duet);
            std::shared_ptr<RegisterSoloB> solo2 = std::make_shared<RegisterSoloB>(1, duet);
            duet->RegisterProgram(solo1);
            duet->RegisterProgram(solo2);

            duet->ParseLine("snd 53");

            // finished cleanly
            Assert::AreEqual(true, duet->ExecuteCommands());

            Assert::AreEqual(true, solo1->IsFinished());
            Assert::AreEqual(true, solo2->IsFinished());
            Assert::AreEqual(1, solo1->GetSendCount());
            Assert::AreEqual(1, solo2->GetSendCount());
        }

        // ------------------------------------------
        // Apply commands: RegisterRcvB
        // ------------------------------------------
        TEST_METHOD(December18b_RegisterRcvB_SendValue)
        {
            std::shared_ptr<RegisterDuet> duet = std::make_shared<RegisterDuet>();
            std::shared_ptr<RegisterSoloB> solo1 = std::make_shared<RegisterSoloB>(0, duet);
            std::shared_ptr<RegisterSoloB> solo2 = std::make_shared<RegisterSoloB>(1, duet);
            duet->RegisterProgram(solo1);
            duet->RegisterProgram(solo2);

            duet->ParseLine("snd -9");
            duet->ParseLine("rcv q");

            // finished cleanly
            Assert::AreEqual(true, duet->ExecuteCommands());

            Assert::AreEqual(true, solo1->IsFinished());
            Assert::AreEqual(true, solo2->IsFinished());
            Assert::AreEqual(-9, static_cast<int>(solo1->GetRegisterValue('q')));
            Assert::AreEqual(-9, static_cast<int>(solo2->GetRegisterValue('q')));
        }

        TEST_METHOD(December18b_RegisterRcvB_SendId)
        {
            std::shared_ptr<RegisterDuet> duet = std::make_shared<RegisterDuet>();
            std::shared_ptr<RegisterSoloB> solo1 = std::make_shared<RegisterSoloB>(0, duet);
            std::shared_ptr<RegisterSoloB> solo2 = std::make_shared<RegisterSoloB>(1, duet);
            duet->RegisterProgram(solo1);
            duet->RegisterProgram(solo2);

            duet->ParseLine("snd p");
            duet->ParseLine("rcv b");

            // finished cleanly
            Assert::AreEqual(true, duet->ExecuteCommands());

            Assert::AreEqual(true, solo1->IsFinished());
            Assert::AreEqual(true, solo2->IsFinished());
            // program 0 receives 1, program 1 receives 0
            Assert::AreEqual(1, static_cast<int>(solo1->GetRegisterValue('b')));
            Assert::AreEqual(0, static_cast<int>(solo2->GetRegisterValue('b')));
        }

        TEST_METHOD(December18b_RegisterRcv_Apply_stalled)
        {
            std::shared_ptr<RegisterDuet> duet = std::make_shared<RegisterDuet>();
            std::shared_ptr<RegisterSoloB> solo = std::make_shared<RegisterSoloB>(0, duet);
            duet->RegisterProgram(solo);

            RegisterRcvB rcv(CharOrNumber("f"));
            rcv.Apply(*solo);

            Assert::AreEqual(true, solo->IsStalled());
            Assert::AreEqual(0, static_cast<int>(solo->GetRegisterValue('f')));
        }

        TEST_METHOD(December18b_RegisterRcv_oneProgramStalled)
        {
            std::shared_ptr<RegisterDuet> duet = std::make_shared<RegisterDuet>();
            std::shared_ptr<RegisterSoloB> solo1 = std::make_shared<RegisterSoloB>(0, duet);
            std::shared_ptr<RegisterSoloB> solo2 = std::make_shared<RegisterSoloB>(1, duet);
            duet->RegisterProgram(solo1);
            duet->RegisterProgram(solo2);
            duet->ParseLine("jgz p 2"); // skipped for solo1 (p == 0)
            duet->ParseLine("snd 89"); // solo1 sends 89 -> solo2; skipped by solo2
            duet->ParseLine("rcv a"); // solo2 receives 89; solo1 stalls (empty queue)

            // one program is stalled
            Assert::AreEqual(false, duet->ExecuteCommands());

            // solo1 (program 0), never received anything
            Assert::AreEqual(0, static_cast<int>(solo1->GetRegisterValue('a')));
            Assert::AreEqual(true, solo1->IsStalled());
            Assert::AreEqual(1, solo1->GetSendCount());

            // solo2 (program 1), never sent anything
            Assert::AreEqual(89, static_cast<int>(solo2->GetRegisterValue('a')));
            Assert::AreEqual(true, solo2->IsFinished());
            Assert::AreEqual(0, solo2->GetSendCount());
        }

        TEST_METHOD(December18b_RegisterRcv_stalledProgramCatchesUp)
        {
            std::shared_ptr<RegisterDuet> duet = std::make_shared<RegisterDuet>();
            std::shared_ptr<RegisterSoloB> solo1 = std::make_shared<RegisterSoloB>(0, duet);
            std::shared_ptr<RegisterSoloB> solo2 = std::make_shared<RegisterSoloB>(1, duet);
            duet->RegisterProgram(solo1);
            duet->RegisterProgram(solo2);
            duet->ParseLine("jgz p 2"); // skipped for solo1 (p == 0)
            duet->ParseLine("snd -34"); // solo1 sends -34 -> solo2; skipped by solo2
            duet->ParseLine("rcv w"); // solo2 receives -34; solo1 stalls (empty queue), later receives 181
            duet->ParseLine("mul p -2"); // solo1: p = 0; solo2: p = -2
            duet->ParseLine("add p 1"); // solo1: p = 1; solo2: p = -1
            duet->ParseLine("jgz p 2"); // skipped for solo2 (p == -1)
            duet->ParseLine("snd 181"); // solo2 sends 181 -> solo1; skipped by solo1

            // finished cleanly
            Assert::AreEqual(true, duet->ExecuteCommands());

            // solo1 (program 0), sent -34, receives 181
            Assert::AreEqual(1, static_cast<int>(solo1->GetRegisterValue('p')));
            Assert::AreEqual(181, static_cast<int>(solo1->GetRegisterValue('w')));
            Assert::AreEqual(1, solo1->GetSendCount());
            Assert::AreEqual(true, solo1->IsFinished());

            // solo1 (program 0), receives -34, sent 181
            Assert::AreEqual(-1, static_cast<int>(solo2->GetRegisterValue('p')));
            Assert::AreEqual(-34, static_cast<int>(solo2->GetRegisterValue('w')));
            Assert::AreEqual(1, solo2->GetSendCount());
            Assert::AreEqual(true, solo2->IsFinished());
        }

        TEST_METHOD(December18b_RegisterRcv_complex)
        {
            std::shared_ptr<RegisterDuet> duet = std::make_shared<RegisterDuet>();
            std::shared_ptr<RegisterSoloB> solo1 = std::make_shared<RegisterSoloB>(0, duet);
            std::shared_ptr<RegisterSoloB> solo2 = std::make_shared<RegisterSoloB>(1, duet);
            duet->RegisterProgram(solo1);
            duet->RegisterProgram(solo2);
            duet->ParseLine("jgz p 2"); // skipped for solo1 (p == 0)
            duet->ParseLine("snd 532"); // solo1 sends 532 -> solo2; skipped by solo2
            duet->ParseLine("snd -7"); // solo1 sends -7 -> solo2; solo2 sends -7 -> solo1
            duet->ParseLine("rcv k"); // solo1 receives -7; solo2 receives 532
            duet->ParseLine("rcv t"); // solo1 stalls (empty queue), then receives 15; solo2 receives -7
            duet->ParseLine("snd 15"); // solo1 sends 15 -> solo1; solo2 sends 15 -> solo1
            duet->ParseLine("rcv f"); // solo1 stalls (empty queue); solo2 receives 15

            // one program is stalled
            Assert::AreEqual(false, duet->ExecuteCommands());

            // solo1 (program 0) skipped the jump command and executed all other commands
            // stalled on rcv f
            Assert::AreEqual(-7, static_cast<int>(solo1->GetRegisterValue('k')));
            Assert::AreEqual(15, static_cast<int>(solo1->GetRegisterValue('t')));
            Assert::AreEqual(0, static_cast<int>(solo1->GetRegisterValue('f')));
            Assert::AreEqual(true, solo1->IsStalled());
            Assert::AreEqual(3, solo1->GetSendCount());

            // solo2 (program 1) executed the jump command and thus skipped snd 532
            Assert::AreEqual(532, static_cast<int>(solo2->GetRegisterValue('k')));
            Assert::AreEqual(-7, static_cast<int>(solo2->GetRegisterValue('t')));
            Assert::AreEqual(15, static_cast<int>(solo2->GetRegisterValue('f')));
            Assert::AreEqual(true, solo2->IsFinished());
            Assert::AreEqual(2, solo2->GetSendCount());
        }

        /*
        snd 1
        snd 2
        snd p
        rcv a
        rcv b
        rcv c
        rcv d

        Both programs begin by sending three values to the other. Program 0 sends 1, 2, 0; program 1 sends 1, 2, 1. Then, each program receives a value (both 1) and stores it in a, receives another value (both 2) and stores it in b, and then each receives the program ID of the other program (program 0 receives 1; program 1 receives 0) and stores it in c. Each program now sees a different value in its own copy of register c.

        Finally, both programs try to rcv a fourth time, but no data is waiting for either of them, and they reach a deadlock. When this happens, both programs terminate.
        */
        TEST_METHOD(December18b_GetSendCount_AoC_test)
        {
            std::shared_ptr<RegisterDuet> duet = std::make_shared<RegisterDuet>();
            std::shared_ptr<RegisterSoloB> solo1 = std::make_shared<RegisterSoloB>(0, duet);
            std::shared_ptr<RegisterSoloB> solo2 = std::make_shared<RegisterSoloB>(1, duet);
            duet->RegisterProgram(solo1);
            duet->RegisterProgram(solo2);

            duet->ParseLine("snd 1");
            duet->ParseLine("snd 2");
            duet->ParseLine("snd p");
            duet->ParseLine("rcv a");
            duet->ParseLine("rcv b");
            duet->ParseLine("rcv c");
            duet->ParseLine("rcv d");

            // both programs are stalled
            Assert::AreEqual(false, duet->ExecuteCommands());

            // both programs sent and received 3 values
            Assert::AreEqual(3, solo1->GetSendCount());
            Assert::AreEqual(3, solo2->GetSendCount());

            // both programs are stalled
            Assert::AreEqual(true, solo1->IsStalled());
            Assert::AreEqual(true, solo2->IsStalled());

            // a and b are the same for both programs
            Assert::AreEqual(1, static_cast<int>(solo1->GetRegisterValue('a')));
            Assert::AreEqual(1, static_cast<int>(solo2->GetRegisterValue('a')));
            Assert::AreEqual(2, static_cast<int>(solo1->GetRegisterValue('b')));
            Assert::AreEqual(2, static_cast<int>(solo2->GetRegisterValue('b')));

            // c is the other program's id
            Assert::AreEqual(1, static_cast<int>(solo1->GetRegisterValue('c')));
            Assert::AreEqual(0, static_cast<int>(solo2->GetRegisterValue('c')));
        }
    };
}
