#pragma once

#include <map>
#include <memory>
#include <string>
#include <vector>

/*
https://adventofcode.com/2017/day/7
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
namespace December07
{
	struct ProgramData
	{
		ProgramData(std::string _name, int _weight, std::vector<std::string> _subElem)
		{
			name = _name;
			weight = _weight;
			subProgramNames = _subElem;
		}

		std::string name;
		int weight;
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
	{
	public:
		ProgramTree(std::vector<ProgramData> programData);
		~ProgramTree() = default;

	public:
		void AddParentChildLink(std::shared_ptr<Program> parent, std::shared_ptr<Program> child);
		void CreateChildren(std::shared_ptr<Program> parent, std::vector<std::string> childNames);
		int GetSize() const { return m_programMap.size(); }
		std::shared_ptr<Program> GetRoot() const;
		bool IsValid() const;
		bool ContainsCircularDependency() const;

	private:
		std::shared_ptr<Program> m_root;
		std::map<std::string, std::shared_ptr<Program>> m_programMap;
	};
}
