#pragma once

#include <map>
#include <memory>
#include <string>
#include <vector>

#include "AdventOfCodeBase.h"

/*
    https://adventofcode.com/2017/day/7

    Part 1:

    Wandering further through the circuits of the computer, you come upon a tower of programs that have gotten themselves into a bit of trouble. A recursive algorithm has gotten out of hand, and now they're balanced precariously in a large tower.

    One program at the bottom supports the entire tower. It's holding a large disc, and on the disc are balanced several more sub-towers. At the bottom of these sub-towers, standing on the bottom disc, are other programs, each holding their own disc, and so on. At the very tops of these sub-sub-sub-...-towers, many programs stand simply keeping the disc below them balanced but with no disc of their own.

    You offer to help, but first you need to understand the structure of these towers. You ask each program to yell out their name, their weight, and (if they're holding a disc) the names of the programs immediately above them balancing on that disc. You write this information down (your puzzle input). Unfortunately, in their panic, they don't do this in an orderly fashion; by the time you're done, you're not sure which program gave which information.

    For example, if your list is the following:

        pbga (66)
        xhth (57)
        ebii (61)
        havc (66)
        ktlj (57)
        fwft (72) -> ktlj, cntj, xhth
        qoyq (66)
        padx (45) -> pbga, havc, qoyq
        tknk (41) -> ugml, padx, fwft
        jptl (61)
        ugml (68) -> gyxo, ebii, jptl
        gyxo (61)
        cntj (57)

    ...then you would be able to recreate the structure of the towers that looks like this:

                       gyxo
                     /
                ugml - ebii
              /      \
             |         jptl
             |
             |         pbga
            /        /
        tknk --- padx - havc
            \        \
             |         qoyq
             |
             |         ktlj
              \      /
                fwft - cntj
                     \
                       xhth

        In this example, tknk is at the bottom of the tower (the bottom program), and is holding up ugml, padx, and fwft. Those programs are, in turn, holding up other programs; in this example, none of those programs are holding up any other programs, and are all the tops of their own towers. (The actual tower balancing in front of you is much larger.)

    Before you're ready to help them, you need to make sure your information is correct. What is the name of the bottom program?
*/
/*
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

	struct ProgramData
	{
        ProgramData() {}

		ProgramData(std::string _name, int _weight, std::vector<std::string> _subElem)
            : name(_name)
            , weight(_weight)
            , subProgramNames(_subElem)
		{
		}

		std::string name;
		int weight = 0;
		std::vector<std::string> subProgramNames;
	};

	class Program
	{
	public:
		Program(std::string name, int weight);
		~Program() = default;

	public:
		bool IsValid() const;
		bool HasCircularDependency(std::vector<std::string>& visitedNodeNames) const;

		std::string GetName() const { return m_name; }
		void SetWeight(int weight) { m_weight = weight; }

		std::shared_ptr<Program> GetParent() const { return m_parent; }
		void SetParent(std::shared_ptr<Program> parent)
		{
			// maybe assert that this doesn't overwrite a valid parent
			m_parent = parent;
		}

		std::vector<std::shared_ptr<Program>> GetChildren() const { return m_children; }

		void AddChild(std::shared_ptr<Program> child)
		{
			m_children.push_back(child);
		}

		void RemoveChild(std::shared_ptr<Program> child)
		{
			auto found = std::find(m_children.begin(), m_children.end(), child);
			if (found != m_children.end())
			{
				m_children.erase(found);
			}
		}

	private:
		std::string m_name;
		int m_weight;
		std::shared_ptr<Program> m_parent;
		std::vector<std::shared_ptr<Program>> m_children;
	};

	class ProgramTree
        : protected AdventOfCodeBase
	{
	public:
        ProgramTree(const std::string& fileName);
        ProgramTree(std::vector<ProgramData> programData);
		~ProgramTree() = default;

	public:
        // AdventOfCodeBase
        bool ParseLine(const std::string& inputLine) override;;
        void OutputResultToConsole() const override;
        // ~AdventOfCodeBase

    public:
        static bool ParseDataFromLine(const std::string& inputLine, ProgramData& data);
        void AddData(ProgramData data);
		void AddParentChildLink(std::shared_ptr<Program> parent, std::shared_ptr<Program> child);
		void CreateChildren(std::shared_ptr<Program> parent, std::vector<std::string> childNames);
		int GetSize() const { return static_cast<int>(m_programMap.size()); }
		std::shared_ptr<Program> GetRoot() const;
		bool IsValid() const;
		bool ContainsCircularDependency() const;

	private:
		std::shared_ptr<Program> m_root;
		std::map<std::string, std::shared_ptr<Program>> m_programMap;
	};

}}