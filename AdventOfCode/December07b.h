#pragma once

#include "December07.h"

/*
    https://adventofcode.com/2017/day/7

    Part 2:

    Apparently, one program has the wrong weight, [...]

    For any program holding a disc, each program standing on that disc forms a sub-tower. Each of those sub-towers are supposed to be the same weight, or the disc itself isn't balanced. The weight of a tower is the sum of the weights of the programs in that tower.

    In the example above, this means that for ugml's disc to be balanced, gyxo, ebii, and jptl must all have the same weight, and they do: 61.

    However, for tknk to be balanced, each of the programs standing on its disc and all programs above it must each match. This means that the following sums must all be the same:

        ugml + (gyxo + ebii + jptl) = 68 + (61 + 61 + 61) = 251
        padx + (pbga + havc + qoyq) = 45 + (66 + 66 + 66) = 243
        fwft + (ktlj + cntj + xhth) = 72 + (57 + 57 + 57) = 243

        As you can see, tknk's disc is unbalanced: ugml's stack is heavier than the other two. Even though the nodes above ugml are balanced, ugml itself is too heavy: it needs to be 8 units lighter for its stack to weigh 243 and keep the towers balanced. If this change were made, its weight would be 60.

    Given that exactly one program is the wrong weight, what would its weight need to be to balance the entire tower?
*/

namespace AdventOfCode {
namespace December07 {

    class ProgramTreeB
        : public ProgramTree
    {
    public:
        ProgramTreeB(const std::string& fileName);
        ProgramTreeB(std::vector<ProgramData> programData);
        ~ProgramTreeB() = default;

    public:
        // AdventOfCodeBase
        virtual void OutputResultToConsole() const override;
        // ~AdventOfCodeBase

    public:
        int GetWeightForNode(const std::string& id) const;
        /// returns false if the tree is already balanced
        bool ProgramTreeB::GetUnbalancedNode(std::shared_ptr<Program>& node) const;
        /// returns false if the tree could not be corrected
        bool GetCorrectedWeightNode(std::shared_ptr<Program>& node) const;
    };

}}
