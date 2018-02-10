#include "stdafx.h"
#include "CppUnitTest.h"
#include "../AdventOfCode/December25.h"

namespace AdventOfCodeTest
{
    using namespace Microsoft::VisualStudio::CppUnitTestFramework;
    using namespace AdventOfCode::December25;

    TEST_CLASS(Test_December25)
    {
    public:
        /*
        ParseLine: read various invalid lines
        */
        TEST_METHOD(December25_ParseLine_invalid_missingBeginState)
        {
            TMBlueprints test;
            Assert::AreEqual(false, test.ParseLine("Begin in state."));
        }

        TEST_METHOD(December25_ParseLine_invalid_wrongSyntax)
        {
            TMBlueprints test;
            Assert::AreEqual(false, test.ParseLine("Perform a checksum after 19 steps"));
        }

        TEST_METHOD(December25_ParseLine_invalid_missingState)
        {
            TMBlueprints test;
            Assert::AreEqual(false, test.ParseLine("In state:"));
        }

        TEST_METHOD(December25_ParseLine_invalid_wrongValue)
        {
            TMBlueprints test;
            Assert::AreEqual(false, test.ParseLine("If the current value is 3:"));
        }

        TEST_METHOD(December25_ParseLine_invalid_missingWriteValue)
        {
            TMBlueprints test;
            Assert::AreEqual(false, test.ParseLine("- Write the value"));
        }

        TEST_METHOD(December25_ParseLine_invalid_wrongDirection)
        {
            TMBlueprints test;
            Assert::AreEqual(false, test.ParseLine("- Move one slot to the ."));
        }

        TEST_METHOD(December25_ParseLine_invalid_missingContinueState)
        {
            TMBlueprints test;
            Assert::AreEqual(false, test.ParseLine("- Continue with state."));
        }

        /*
        ParseLine: empty line is valid
        */
        TEST_METHOD(December25_ParseLine_emptyLine)
        {
            TMBlueprints test;
            Assert::AreEqual(true, test.ParseLine(""));
            Assert::AreEqual(true, test.ParseLine("          "));
            Assert::AreEqual(true, test.ParseLine(" "));
        }

        /*
        ParseLine: read valid blueprint intro, assuming no initial spaces (or tabs)
        */
        TEST_METHOD(December25_ParseLine_intro_noSpaces)
        {
            TMBlueprints test;
            Assert::AreEqual(true, test.ParseLine("Begin in state C."));
            Assert::AreEqual(true, test.ParseLine("Perform a diagnostic checksum after 19 steps."));
        }

        /*
        ParseLine: read valid blueprint intro, with different kinds of initial spacing
        */
        TEST_METHOD(December25_ParseLine_intro_withSpaces)
        {
            TMBlueprints test;
            Assert::AreEqual(true, test.ParseLine(" Begin in state A.   "));
            Assert::AreEqual(true, test.ParseLine("        Perform a diagnostic checksum after 26862526636 steps.   "));
        }

        /*
        check uninitialized Blueprint step validity
        */
        TEST_METHOD(December25_nonInitializedBlueprintStep)
        {
            TMBlueprints test;
            BlueprintStep bpStep = test.GetNewBlueprint();
            Assert::AreEqual(false, bpStep.IsValid());

            std::vector<BlueprintStep> definedSteps = test.GetBlueprintSteps();
            Assert::AreEqual(true, definedSteps.empty());
        }

        /*
        check uninitialized Blueprint step validity
        */
        TEST_METHOD(December25_initializedBlueprintStep)
        {
            BlueprintStep bpStep;
            bpStep.stateCondition = 'C';
            bpStep.valueCondition = 1;
            bpStep.newState = 'A';
            bpStep.newValue = 0;
            bpStep.newDirection = -1;
            Assert::AreEqual(true, bpStep.IsValid());
        }

        /*
        ParseLine: read valid blueprint step, assuming no initial spaces (or tabs)
        */
        TEST_METHOD(December25_ParseLine_step_noInitialSpaces)
        {
            TMBlueprints test;
            Assert::AreEqual(true, test.ParseLine("In state C:"));
            Assert::AreEqual(true, test.ParseLine("If the current value is 0:"));
            Assert::AreEqual(true, test.ParseLine("- Write the value 1."));
            Assert::AreEqual(true, test.ParseLine("- Move one slot to the left."));
            Assert::AreEqual(true, test.ParseLine("- Continue with state A."));

            BlueprintStep bpStep = test.GetNewBlueprint();
            Assert::AreEqual(true, bpStep.IsValid());

            Assert::AreEqual('C', bpStep.stateCondition);
            Assert::AreEqual(0, bpStep.valueCondition);
            Assert::AreEqual(1, bpStep.newValue);
            Assert::AreEqual(-1, bpStep.newDirection);
            Assert::AreEqual('A', bpStep.newState);
        }

        /*
        ParseLine: read valid blueprint, with different kinds of initial spacing
        */
        TEST_METHOD(December25_ParseLine_step_withSpaces)
        {
            TMBlueprints test;
            Assert::AreEqual(true, test.ParseLine("In state B:  "));
            Assert::AreEqual(true, test.ParseLine("  If the current value is 1:"));
            Assert::AreEqual(true, test.ParseLine(" - Write the value 0.      "));
            Assert::AreEqual(true, test.ParseLine("    - Move one slot to the right."));
            Assert::AreEqual(true, test.ParseLine("     - Continue with state F. "));

            BlueprintStep bpStep = test.GetNewBlueprint();
            Assert::AreEqual(true, bpStep.IsValid());

            Assert::AreEqual('B', bpStep.stateCondition);
            Assert::AreEqual(1, bpStep.valueCondition);
            Assert::AreEqual(0, bpStep.newValue);
            Assert::AreEqual(1, bpStep.newDirection);
            Assert::AreEqual('F', bpStep.newState);
        }

        /*
        ParseLine: a newly defined blueprint step needs to be added to the list of steps
        */
        TEST_METHOD(December25_GetBlueprintSteps_single)
        {
            TMBlueprints test;
            Assert::AreEqual(true, test.ParseLine("In state A:"));
            Assert::AreEqual(true, test.ParseLine("If the current value is 1:"));
            Assert::AreEqual(true, test.ParseLine("- Write the value 1."));
            Assert::AreEqual(true, test.ParseLine("- Move one slot to the right."));
            Assert::AreEqual(true, test.ParseLine("- Continue with state B."));

            BlueprintStep bpStep = test.GetNewBlueprint();
            Assert::AreEqual(true, bpStep.IsValid());

            std::vector<BlueprintStep> definedSteps = test.GetBlueprintSteps();
            Assert::AreEqual(true, definedSteps.empty());

            // after an empty line, the step should be added to the list of steps
            Assert::AreEqual(true, test.ParseLine(""));

            // the previous step is added to the list
            definedSteps = test.GetBlueprintSteps();
            Assert::AreEqual(1, static_cast<int>(definedSteps.size()));
            Assert::AreEqual(true, definedSteps[0] == bpStep);

            // ... but the new one is invalid
            bpStep = test.GetNewBlueprint();
            Assert::AreEqual(false, bpStep.IsValid());
        }

        /*
        ParseLine: a newly defined blueprint step needs to be added to the list of steps
        */
        TEST_METHOD(December25_GetBlueprintSteps_complete)
        {
            TMBlueprints test;
            Assert::AreEqual(true, test.ParseLine("In state D:"));
            Assert::AreEqual(true, test.ParseLine("If the current value is 0:"));
            Assert::AreEqual(true, test.ParseLine("- Write the value 1."));
            Assert::AreEqual(true, test.ParseLine("- Move one slot to the left."));
            Assert::AreEqual(true, test.ParseLine("- Continue with state A."));
            Assert::AreEqual(true, test.ParseLine("If the current value is 1:"));
            Assert::AreEqual(true, test.ParseLine("- Write the value 0."));
            Assert::AreEqual(true, test.ParseLine("- Move one slot to the left."));
            Assert::AreEqual(true, test.ParseLine("- Continue with state B."));
            Assert::AreEqual(true, test.ParseLine(""));

            std::vector<BlueprintStep> definedSteps = test.GetBlueprintSteps();
            Assert::AreEqual(2, static_cast<int>(definedSteps.size()));

            Assert::AreEqual('D', definedSteps[0].stateCondition);
            Assert::AreEqual(0, definedSteps[0].valueCondition);
            Assert::AreEqual(1, definedSteps[0].newValue);
            Assert::AreEqual(-1, definedSteps[0].newDirection);
            Assert::AreEqual('A', definedSteps[0].newState);

            Assert::AreEqual('D', definedSteps[1].stateCondition);
            Assert::AreEqual(1, definedSteps[1].valueCondition);
            Assert::AreEqual(0, definedSteps[1].newValue);
            Assert::AreEqual(-1, definedSteps[1].newDirection);
            Assert::AreEqual('B', definedSteps[1].newState);
        }

        /*
        undefined entry always returns 0
        */
        TEST_METHOD(December25_GetCurrentValue)
        {
            TMBlueprints test;
            test.SetCurrentIndex(1057);
            Assert::AreEqual(0, test.GetCurrentValue());
        }

        /*
        set uninitialized value or override existing value
        */
        TEST_METHOD(December25_SetCurrentValue)
        {
            TMBlueprints test;
            test.SetCurrentIndex(25);
            test.SetCurrentValue(5);
            Assert::AreEqual(5, test.GetCurrentValue());

            test.SetCurrentValue(712);
            Assert::AreEqual(712, test.GetCurrentValue());
        }

        /*
        GetChecksum
        */
        TEST_METHOD(December25_GetChecksum_empty)
        {
            TMBlueprints test;
            Assert::AreEqual(0, test.GetCheckSum());
        }

        TEST_METHOD(December25_GetChecksum_count)
        {
            TMBlueprints test;
            test.SetCurrentValue(10);

            test.SetCurrentIndex(3);
            test.SetCurrentValue(5);

            test.SetCurrentIndex(-97);
            test.SetCurrentValue(8);

            Assert::AreEqual(23, test.GetCheckSum());
        }

        TEST_METHOD(December25_GetChecksum_override)
        {
            TMBlueprints test;
            test.SetCurrentIndex(5);
            test.SetCurrentValue(7);
            // override
            test.SetCurrentValue(2);

            Assert::AreEqual(2, test.GetCheckSum());
        }

        /*
        no steps registered happens, should still be 0
        */
        TEST_METHOD(December25_ExecuteSteps_noStepsRegistered)
        {
            TMBlueprints test;
            test.SetNumSteps(15);
            test.ExecuteSteps();

            Assert::AreEqual(0, test.GetCheckSum());
        }

        /*
        Begin in state A.
        Perform a diagnostic checksum after 6 steps.

        In state A:
        If the current value is 0:
        - Write the value 1.
        - Move one slot to the right.
        - Continue with state B.
        If the current value is 1:
        - Write the value 0.
        - Move one slot to the left.
        - Continue with state B.

        In state B:
        If the current value is 0:
        - Write the value 1.
        - Move one slot to the left.
        - Continue with state A.
        If the current value is 1:
        - Write the value 1.
        - Move one slot to the right.
        - Continue with state A.

        In the above example, the diagnostic checksum is 3.
        */
        TEST_METHOD(December25_ExecuteSteps_AoC_test)
        {
            TMBlueprints test;
            test.SetCurrentState('A');
            test.SetNumSteps(6);

            BlueprintStep step1;
            step1.stateCondition = 'A';
            step1.valueCondition = 0;
            step1.newValue = 1;
            step1.newDirection = 1;
            step1.newState = 'B';

            BlueprintStep step2;
            step2.stateCondition = 'A';
            step2.valueCondition = 1;
            step2.newValue = 0;
            step2.newDirection = -1;
            step2.newState = 'B';

            BlueprintStep step3;
            step3.stateCondition = 'B';
            step3.valueCondition = 0;
            step3.newValue = 1;
            step3.newDirection = -1;
            step3.newState = 'A';

            BlueprintStep step4;
            step4.stateCondition = 'B';
            step4.valueCondition = 1;
            step4.newValue = 1;
            step4.newDirection = 1;
            step4.newState = 'A';

            test.AddBlueprintStep(step1);
            test.AddBlueprintStep(step2);
            test.AddBlueprintStep(step3);
            test.AddBlueprintStep(step4);
            test.ExecuteSteps();

            Assert::AreEqual(3, test.GetCheckSum());
        }
    };
}
