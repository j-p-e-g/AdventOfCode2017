#pragma once

#include <map>
#include <vector>

#include "AdventOfCodeBase.h"

/*
http://adventofcode.com/2017/day/25

Part 1:

You find the Turing machine blueprints (your puzzle input) on a tablet in a nearby pile of debris. Looking back up at the broken Turing machine above, you can start to identify its parts:

A tape which contains 0 repeated infinitely to the left and right.
A cursor, which can move left or right along the tape and read or write values at its current position.
A set of states, each containing rules about what to do based on the current value under the cursor.
Each slot on the tape has two possible values: 0 (the starting value for all slots) and 1. Based on whether the cursor is pointing at a 0 or a 1, the current state says what value to write at the current position of the cursor, whether to move the cursor left or right one slot, and which state to use next.

For example, suppose you found the following blueprint:

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

Running it until the number of steps required to take the listed diagnostic checksum would result in the following tape configurations (with the cursor marked in square brackets):

    ... 0  0  0 [0] 0  0 ... (before any steps; about to run state A)
    ... 0  0  0  1 [0] 0 ... (after 1 step;     about to run state B)
    ... 0  0  0 [1] 1  0 ... (after 2 steps;    about to run state A)
    ... 0  0 [0] 0  1  0 ... (after 3 steps;    about to run state B)
    ... 0 [0] 1  0  1  0 ... (after 4 steps;    about to run state A)
    ... 0  1 [1] 0  1  0 ... (after 5 steps;    about to run state B)
    ... 0  1  1 [0] 1  0 ... (after 6 steps;    about to run state A)

The CPU can confirm that the Turing machine is working by taking a diagnostic checksum after a specific number of steps (given in the blueprint). Once the specified number of steps have been executed, the Turing machine should pause; once it does, count the number of times 1 appears on the tape. In the above example, the diagnostic checksum is 3.

Recreate the Turing machine and save the computer! What is the diagnostic checksum it produces once it's working again?
*/

namespace AdventOfCode {
    namespace December25 {

        struct BlueprintStep
        {
            bool IsValid() const
            {
                return stateCondition >= 'A' && stateCondition <= 'Z'
                    && valueCondition >= 0 && valueCondition <= 1
                    && newValue >= 0 && newValue <= 1
                    && (newDirection == -1 || newDirection == 1)
                    && newState >= 'A' && newState <= 'Z';
            }

            bool operator== (const BlueprintStep& other)
            {
                return stateCondition == other.stateCondition
                    && valueCondition == other.valueCondition
                    && newValue == other.newValue
                    && newDirection == other.newDirection
                    && newState == other.newState;
            }

            char stateCondition = ' ';
            int valueCondition = -1;

            int newValue = -1;
            int newDirection = 0;
            char newState = ' ';
        };

        class TMBlueprints
            : public AdventOfCodeBase
        {
        public:
            TMBlueprints() {};
            TMBlueprints(const std::string& fileName);
            ~TMBlueprints() = default;

        public:
            // AdventOfCodeBase
            virtual bool ParseLine(const std::string& inputLine) override;
            virtual void OutputResultToConsole() const override;
            // ~AdventOfCodeBase

        public:
            BlueprintStep GetNewBlueprint() const { return m_newStep; }
            std::vector<BlueprintStep> GetBlueprintSteps() const { return m_blueprintSteps; }
            void AddBlueprintStep(const BlueprintStep& step) { m_blueprintSteps.push_back(step); }

        public:
            void ExecuteSteps();
            void SetNumSteps(int num) { m_numSteps = num; }
            void SetCurrentIndex(int index) { m_currentIndex = index; }
            void ShiftIndex(int offset) { m_currentIndex += offset; }
            int GetCurrentValue() const;
            void SetCurrentValue(int value);
            void SetCurrentState(char state) { m_currentState = state; }
            int GetCheckSum() const;

        private:
            int m_numSteps = 0;

            // index, value
            std::map<int, int> m_tapeValues;
            int m_currentIndex = 0;
            char m_currentState = 'A';

            BlueprintStep m_newStep;
            std::vector<BlueprintStep> m_blueprintSteps;
        };
    }
}
