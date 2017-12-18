#include "stdafx.h"
#include "CppUnitTest.h"
#include "../AdventOfCode/December08.h"

namespace AdventOfCodeTest
{
    using namespace Microsoft::VisualStudio::CppUnitTestFramework;
    using namespace AdventOfCode::December08;

    TEST_CLASS(Test_December08)
	{
	public:
		// ---------------------------------
		// Condition
		// ---------------------------------
		/*
		empty condition
		*/
		TEST_METHOD(December08_Condition_empty)
		{
			Condition condition;

			Assert::AreEqual("", condition.id.c_str());
			Assert::AreEqual(true, ComparisonType::CT_NONE == condition.comparisonType);
			Assert::AreEqual(0, condition.value);
			Assert::AreEqual(false, condition.IsValid());
		}

		/*
		valid condition
		*/
		TEST_METHOD(December08_Condition_valid)
		{
			Condition condition;
			condition.id = "x";
			condition.comparisonType = ComparisonType::CT_GREATER_THAN;
			condition.value = -8;

			Assert::AreEqual("x", condition.id.c_str());
			Assert::AreEqual(true, ComparisonType::CT_GREATER_THAN == condition.comparisonType);
			Assert::AreEqual(-8, condition.value);
			Assert::AreEqual(true, condition.IsValid());
			Assert::IsFalse(Condition() == condition);
		}

		// ---------------------------------
		// RegisterCommand
		// ---------------------------------
		/*
		empty command
		*/
		TEST_METHOD(December08_RegisterCommand_empty)
		{
			RegisterCommand command;

			Assert::IsFalse(command.IsValid());
			Assert::AreEqual("", command.GetId().c_str());
			Assert::AreEqual(0, command.GetBonus());
			Assert::AreEqual(false, command.HasCondition());
			Assert::AreEqual(true, Condition() == command.GetCondition());
		}

		/*
		command without condition
		*/
		TEST_METHOD(December08_RegisterCommand_noCondition)
		{
			Condition condition;
			RegisterCommand command("bla", 16, condition);

			Assert::AreEqual(true, command.IsValid());
			Assert::AreEqual("bla", command.GetId().c_str());
			Assert::AreEqual(16, command.GetBonus());
			Assert::AreEqual(false, command.HasCondition());
			Assert::AreEqual(true, Condition() == command.GetCondition());
		}

		/*
		command with condition
		*/
		TEST_METHOD(December08_RegisterCommand_hasCondition)
		{
			Condition condition;
			condition.comparisonType = ComparisonType::CT_NOT_EQUAL_TO;
			condition.id = "y";
			condition.value = 55;

			RegisterCommand command("q", -3, condition);

			Assert::AreEqual(true, command.IsValid());
			Assert::AreEqual("q", command.GetId().c_str());
			Assert::AreEqual(-3, command.GetBonus());
			Assert::AreEqual(true, command.HasCondition());
			Assert::IsFalse(Condition() == command.GetCondition());
		}

		/*
		empty command
		*/
		TEST_METHOD(December08_RegisterCommand_parseEmpty)
		{
			RegisterCommand expectedCommand;
			RegisterCommand parsedCommand("");

			Assert::IsFalse(parsedCommand.IsValid());
			Assert::AreEqual(true, parsedCommand == expectedCommand);
		}

		/*
		invalid command
		*/
		TEST_METHOD(December08_RegisterCommand_parseInvalidCommand)
		{
			RegisterCommand command("k set 16");

			Assert::IsFalse(RegisterCommand() == command);
			Assert::IsFalse(command.IsValid());
			Assert::IsFalse(command.HasCondition());
		}

		/*
		invalid command
		*/
		TEST_METHOD(December08_RegisterCommand_parseInvalidBonus)
		{
			RegisterCommand command("hljk inc nine");

			Assert::IsFalse(RegisterCommand() == command);
			Assert::IsFalse(command.IsValid());
			Assert::IsFalse(command.HasCondition());
		}

		/*
		simple command without condition
		*/
		TEST_METHOD(December08_RegisterCommand_parseNoCondition)
		{
			Condition condition;

			RegisterCommand expectedCommand("xyz", -7, condition);
			RegisterCommand parsedCommand("xyz dec 7");

			Assert::IsFalse(expectedCommand.HasCondition());
			Assert::IsFalse(expectedCommand.GetCondition().IsValid());
			Assert::AreEqual(true, parsedCommand == expectedCommand);
		}

		/*
		simple command with condition
		*/
		TEST_METHOD(December08_RegisterCommand_parseWithCondition)
		{
			Condition condition;
			condition.id = "a";
			condition.comparisonType = ComparisonType::CT_SMALLER_OR_EQUAL_TO;
			condition.value = 1367;

			RegisterCommand expectedCommand("t", 25, condition);
			RegisterCommand parsedCommand("t inc 25 if a <= 1367");

			Assert::AreEqual(true, parsedCommand.IsValid());
			Assert::AreEqual(true, expectedCommand.HasCondition());
			Assert::AreEqual(true, expectedCommand.GetCondition().IsValid());
			Assert::AreEqual(true, parsedCommand == expectedCommand);
		}

        /*
        condition compares against zero
        */
        TEST_METHOD(December08_RegisterCommand_zeroComparison)
        {
            Condition condition;
            condition.id = "uzt";
            condition.comparisonType = ComparisonType::CT_NOT_EQUAL_TO;
            condition.value = 0;

            RegisterCommand expectedCommand("testitest", -3, condition);
            RegisterCommand parsedCommand("testitest dec 3 if uzt != 0");

            Assert::AreEqual(true, parsedCommand.IsValid());
            Assert::AreEqual(true, expectedCommand.HasCondition());
            Assert::AreEqual(true, expectedCommand.GetCondition().IsValid());
            Assert::AreEqual(true, parsedCommand == expectedCommand);
        }

        // -------------------------------
		// RegisterHandler
		// -------------------------------
		/*
		try applying invalid commands
		*/
		TEST_METHOD(December08_RegisterHandler_invalidCommand)
		{
			RegisterHandler test;
			Assert::AreEqual(false, test.ApplyCommand("zzz set -9"));
			Assert::AreEqual(false, test.RegisterExists("zzz"));
		}

		TEST_METHOD(December08_RegisterHandler_tooFewParameters1)
		{
			RegisterHandler test;
			Assert::AreEqual(false, test.ApplyCommand("inc 8"));
		}

		TEST_METHOD(December08_RegisterHandler_tooFewParameters2)
		{
			RegisterHandler test;
			Assert::AreEqual(false, test.ApplyCommand("q dec"));
			Assert::AreEqual(false, test.RegisterExists("q"));
		}

		TEST_METHOD(December08_RegisterHandler_missingIf)
		{
			RegisterHandler test;
			Assert::AreEqual(false, test.ApplyCommand("b inc 9 q == 3"));
			Assert::AreEqual(false, test.RegisterExists("b"));
		}

		TEST_METHOD(December08_RegisterHandler_misSpeltIf)
		{
			RegisterHandler test;
			Assert::AreEqual(false, test.ApplyCommand("bbb inc 14 iff st != -2"));
			Assert::AreEqual(false, test.RegisterExists("bbb"));
		}

		TEST_METHOD(December08_RegisterHandler_missingSpace)
		{
			RegisterHandler test;
			Assert::AreEqual(false, test.ApplyCommand("tzz inc 4 if r>98"));
			Assert::AreEqual(false, test.RegisterExists("tzz"));
		}

		/*
		valid, without conditions
		*/
		TEST_METHOD(December08_RegisterHandler_validNoChange)
		{
			RegisterHandler test;
			Assert::AreEqual(true, test.ApplyCommand("q inc 0"));
			Assert::AreEqual(true, test.RegisterExists("q"));
			Assert::AreEqual(0, test.GetValue("q"));

			Assert::AreEqual(true, test.ApplyCommand("www dec 0"));
			Assert::AreEqual(true, test.RegisterExists("www"));
			Assert::AreEqual(0, test.GetValue("www"));
		}

		TEST_METHOD(December08_RegisterHandler_validIncPlusNoCondition)
		{
			RegisterHandler test;
			Assert::AreEqual(true, test.ApplyCommand("z inc 2"));
			Assert::AreEqual(true, test.RegisterExists("z"));
			Assert::AreEqual(2, test.GetValue("z"));
		}

		TEST_METHOD(December08_RegisterHandler_validDecMinusNoCondition)
		{
			RegisterHandler test;
			Assert::AreEqual(true, test.ApplyCommand("u dec -5"));
			Assert::AreEqual(true, test.RegisterExists("u"));
			Assert::AreEqual(5, test.GetValue("u"));
		}

		TEST_METHOD(December08_RegisterHandler_validDecPlusNoCondition)
		{
			RegisterHandler test;
			Assert::AreEqual(true, test.ApplyCommand("f dec 8"));
			Assert::AreEqual(true, test.RegisterExists("f"));
			Assert::AreEqual(-8, test.GetValue("f"));
		}

		TEST_METHOD(December08_RegisterHandler_validIncMinusNoCondition)
		{
			RegisterHandler test;
			Assert::AreEqual(true, test.ApplyCommand("g inc -23"));
			Assert::AreEqual(true, test.RegisterExists("g"));
			Assert::AreEqual(-23, test.GetValue("g"));
		}

		TEST_METHOD(December08_RegisterHandler_modifyExistingRegisterNoConditions)
		{
			RegisterHandler test;
			test.ApplyCommand("uvw dec -9");
			test.ApplyCommand("uvw inc -5");
			Assert::AreEqual(4, test.GetValue("uvw"));
		}

		/*
		valid, with condition
		*/
		TEST_METHOD(December08_RegisterHandler_conditionIsFalse)
		{
			RegisterHandler test;
			Assert::AreEqual(true, test.ApplyCommand("tt inc 13 if a > 2"));
			Assert::AreEqual(false, test.RegisterExists("tt"));
		}

		TEST_METHOD(December08_RegisterHandler_selfConditionIsTrue)
		{
			RegisterHandler test;
			test.ApplyCommand("bb inc 5");
			Assert::AreEqual(true, test.ApplyCommand("bb dec 2 if bb != 9"));
			Assert::AreEqual(true, test.RegisterExists("bb"));
			Assert::AreEqual(3, test.GetValue("bb"));
		}

		TEST_METHOD(December08_RegisterHandler_otherConditionIsTrue)
		{
			RegisterHandler test;
			test.ApplyCommand("q dec 98");
			Assert::AreEqual(true, test.ApplyCommand("w inc 12 if q <= -98"));
			Assert::AreEqual(true, test.RegisterExists("w"));
			Assert::AreEqual(12, test.GetValue("w"));
		}

		TEST_METHOD(December08_RegisterHandler_modifyExistingRegister_conditionFalse)
		{
			RegisterHandler test;
			test.ApplyCommand("xy inc 3");
			test.ApplyCommand("xy inc 5 if b != 0"); // no effect
			Assert::AreEqual(3, test.GetValue("xy"));
		}

        TEST_METHOD(December08_RegisterHandler_modifyExistingRegister_compareToNonExistingRegister)
        {
            RegisterHandler test;
            test.ApplyCommand("bla dec -2");
            test.ApplyCommand("bla inc 18 if qwrtz == 0"); // default value 0 -> true
            Assert::AreEqual(20, test.GetValue("bla"));
        }

        TEST_METHOD(December08_RegisterHandler_modifyExistingRegister_conditionTrue)
		{
			RegisterHandler test;
			test.ApplyCommand("abc inc 900");
			test.ApplyCommand("abc dec 50 if abc > -20");
			Assert::AreEqual(850, test.GetValue("abc"));
		}

		TEST_METHOD(December08_RegisterHandler_GetLargestRegisterEntry_emptyRegister)
		{
			RegisterHandler test;
			Assert::AreEqual(INT_MIN, test.GetLargestRegisterEntry());
		}

		TEST_METHOD(December08_RegisterHandler_GetLargestRegisterEntry)
		{
			RegisterHandler test;
			test.ApplyCommand("q inc 35");
			test.ApplyCommand("w dec -80 if q != 35"); // skipped
			Assert::AreEqual(false, test.RegisterExists("w"));
			Assert::AreEqual(35, test.GetLargestRegisterEntry());
		}

        /*
        ensure the commands are applied in the right order
        */
        TEST_METHOD(December08_RegisterHandler_OrderMatters)
        {
            RegisterHandler test;
            test.ApplyCommand("ffff inc 15 if zzz < 50"); // ffff becomes 15
            Assert::AreEqual(15, test.GetLargestRegisterEntry());
            test.ApplyCommand("zz inc 100 if aaa > -20"); // zz becomes 100
            Assert::AreEqual(100, test.GetLargestRegisterEntry());
            test.ApplyCommand("aaa dec 30"); // aaa becomes 30
            Assert::AreEqual(100, test.GetLargestRegisterEntry());
        }

        /*
		b inc 5 if a > 1
		a inc 1 if b < 5
		c dec -10 if a >= 1
		c inc -20 if c == 10

		These instructions would be processed as follows:

		Because a starts at 0, it is not greater than 1, and so b is not modified.
		a is increased by 1 (to 1) because b is less than 5 (it is 0).
		c is decreased by -10 (to 10) because a is now greater than or equal to 1 (it is 1).
		c is increased by -20 (to -10) because c is equal to 10.

		After this process, the largest value in any register is 1.
		*/
		TEST_METHOD(December08_AoC_test)
		{
			RegisterHandler test;
			Assert::AreEqual(true, test.ApplyCommand("b inc 5 if a > 1"));
			Assert::AreEqual(true, test.ApplyCommand("a inc 1 if b < 5"));
			Assert::AreEqual(true, test.ApplyCommand("c dec -10 if a >= 1"));
			Assert::AreEqual(true, test.ApplyCommand("c inc -20 if c == 10"));
			Assert::AreEqual(1, test.GetLargestRegisterEntry());
		}
	};
}
