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

	class Program : std::enable_shared_from_this<Program>
	{
	public:
        Program()
            : Program("", -1)
        {
        }

		Program(std::string name, int weight);
		~Program() = default;

	public:
		std::string GetName() const { return m_name; }
		void SetWeight(int weight) { m_weight = weight; }
        int GetWeight() const { return m_weight; }
		std::shared_ptr<Program> GetParent() const { return m_parent; }
		std::vector<std::shared_ptr<Program>> GetChildren() const { return m_children; }

        bool IsValid() const;
        bool HasCircularDependency(std::vector<std::string>& visitedNodeNames) const;
        void SetParent(std::shared_ptr<Program> parent);
        void AddChild(std::shared_ptr<Program> child);
        void RemoveChild(std::shared_ptr<Program> child);
        int GetTreeWeight() const;
        bool IsBalancedSubTree() const;
        /// returns false if the tree is already balanced
        bool GetUnbalancedNode(std::shared_ptr<Program>& node) const;

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
        virtual bool ParseLine(const std::string& inputLine) override;;
        virtual void OutputResultToConsole() const override;
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

	protected:
		std::shared_ptr<Program> m_root;
		std::map<std::string, std::shared_ptr<Program>> m_programMap;
	};

}}