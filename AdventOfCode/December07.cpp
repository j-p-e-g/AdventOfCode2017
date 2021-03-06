#include "stdafx.h"

#include <iostream>
#include <regex>

#include "CodeUtil.h"
#include "December07.h"

using namespace AdventOfCode::December07;

Program::Program(std::string name, int weight)
	: m_name(name)
	, m_weight(weight)
{
}

bool Program::IsValid() const
{
	if (m_name == "" || m_weight < 0)
	{
		return false;
	}

	if (m_parent == nullptr || m_parent->GetName() == this->GetName())
	{
		return false;
	}

	for (const auto& child : m_children)
	{
		if (child->GetName() == this->GetName() || child->GetName() == m_parent->GetName())
		{
			return false;
		}
	}

	return true;
}

bool Program::HasCircularDependency(std::vector<std::string>& visitedNodeNames) const
{
	const auto& found = std::find(visitedNodeNames.begin(), visitedNodeNames.end(), GetName());
	if (found != visitedNodeNames.end())
	{
		return true;
	}

	visitedNodeNames.push_back(GetName());

	for (const auto& child : m_children)
	{
		if (child->HasCircularDependency(visitedNodeNames))
		{
			return true;
		}
	}

	return false;
}

void Program::SetParent(std::shared_ptr<Program> parent)
{
    // maybe assert that this doesn't overwrite a valid parent
    m_parent = parent;
}

void Program::AddChild(std::shared_ptr<Program> child)
{
    m_children.push_back(child);
}

void Program::RemoveChild(std::shared_ptr<Program> child)
{
    auto found = std::find(m_children.begin(), m_children.end(), child);
    if (found != m_children.end())
    {
        m_children.erase(found);
    }
}

int Program::GetTreeWeight() const
{
    int treeWeight = m_weight;

    for (const auto& child : m_children)
    {
        treeWeight += child->GetTreeWeight();
    }

    return treeWeight;
}

bool Program::IsBalancedSubTree() const
{
    if (m_children.empty())
    {
        return true;
    }

    int balancedWeight = -1;
    for (const auto& child : m_children)
    {
        const int weight = child->GetTreeWeight();
        if (balancedWeight == -1)
        {
            balancedWeight = weight;
        }
        else if (weight != balancedWeight)
        {
            return false;
        }
    }

    return true;
}

bool Program::GetUnbalancedNode(std::shared_ptr<Program>& node) const
{
    // always balanced
    if (m_children.empty())
    {
        return false;
    }

    for (const auto& child : m_children)
    {
        // recursively try to reach unbalanced child node
        if (child->GetUnbalancedNode(node))
        {
            return true;
        }
    }

    // if each child is balanced but the tree is not, _this_ is the first unbalanced node
    if (!IsBalancedSubTree())
    {
        node = std::make_shared<Program>(*this);
        return true;
    }

    // the subtree is balanced
    return false;
}

/*
 *  ProgramTree
 */
ProgramTree::ProgramTree(const std::string& fileName)
    : AdventOfCodeBase()
{
    m_root = std::make_shared<Program>("[root]", 0);

    ReadFile(fileName);
}

bool ProgramTree::ParseLine(const std::string& inputLine)
{
    ProgramData data;
    if (!ParseDataFromLine(inputLine, data))
    {
        return false;
    }

    AddData(data);
    return true;
}

void ProgramTree::OutputResultToConsole() const
{
    std::cout << "December07.a: result = " << GetRoot()->GetName() << std::endl;
}

bool ProgramTree::ParseDataFromLine(const std::string& inputLine, ProgramData& data)
{
    // input format:
    //   nwtkz (304) -> eykks, rxivjye

    //    ^(\w+) \((\d+)\)$
    // or 
    //    ^(\w+) \((\d+)\) -> ([\w\s,])$
    std::regex regex("(\\w+)\\s+\\((\\d+)\\)(\\s*->\\s*([\\w\\s,]+))?");
    std::smatch match;

    std::string key;
    int weight = 0;
    std::vector<std::string> children;

    if (!std::regex_match(inputLine, match, regex))
    {
        return false;
    }

    // 0: entire line
    // 1: first word
    // 2: number in brackets
    // 3: entire string after the closing brackets (optional)
    // 4: entire string after the -> symbol (if 3)
    for (int index = 0; index < match.size(); index++)
    {
        const auto m = match[index];
        switch (index)
        {
        case 1:
            if (!m.matched)
            {
                return false;
            }
            key = m.str();
            break;
        case 2:
            if (!m.matched)
            {
                return false;
            }
            weight = std::atoi(m.str().c_str());
            break;
        case 4:
        {
            if (!m.matched) // optional
            {
                break;
            }

            // fail if the base match is valid but the suffix is empty
            std::string suffix = m.str();
            std::regex suffixRegex("\\s*");
            if (std::regex_match(suffix, suffixRegex))
            {
                return false;
            }

            // parse sub elements into children
            std::regex commaRegex("(\\w+),\\s*");
            if (!CodeUtils::CodeUtil::SplitStringByRegex(suffix, children, commaRegex))
            {
                return false;
            }

            // should not contain any other commas
            commaRegex = ",";
            if (std::regex_search(children[children.size() - 1], commaRegex))
            {
                return false;
            }
        }
        }
    }

    data = ProgramData(key, weight, children);

    return true;
}

ProgramTree::ProgramTree(std::vector<ProgramData> programData)
    : AdventOfCodeBase()
{
	m_root = std::make_shared<Program>("[root]", 0);

	for (const auto& data : programData)
	{
        AddData(data);
	}
}

void ProgramTree::AddData(ProgramData data)
{
    auto found = m_programMap.find(data.name);
    if (found == m_programMap.end())
    {
        auto temp = std::make_shared<Program>(data.name, data.weight);
        AddParentChildLink(m_root, temp);
        m_programMap.emplace(data.name, temp);

        CreateChildren(temp, data.subProgramNames);
    }
    else
    {
        found->second->SetWeight(data.weight);
        CreateChildren(found->second, data.subProgramNames);
    }
}

void ProgramTree::AddParentChildLink(std::shared_ptr<Program> parent, std::shared_ptr<Program> child)
{
	parent->AddChild(child);

	auto prevParent = child->GetParent();
	if (prevParent)
	{
		prevParent->RemoveChild(child);
	}

	child->SetParent(parent);
}

void ProgramTree::CreateChildren(std::shared_ptr<Program> parent, std::vector<std::string> childNames)
{
	for (const auto& childName : childNames)
	{
		auto foundChild = m_programMap.find(childName);
		if (foundChild == m_programMap.end())
		{
			auto tempChild = std::make_shared<Program>(childName, -1);
			AddParentChildLink(parent, tempChild);
			m_programMap.emplace(childName, tempChild);
		}
		else
		{
			AddParentChildLink(parent, foundChild->second);
		}
	}
}

bool ProgramTree::IsValid() const
{
	if (!m_root)
	{
		return false;
	}

	auto rootChildren = m_root->GetChildren();
	if (rootChildren.size() == 0 && GetSize() == 0)
	{
		return true;
	}

	if (rootChildren.size() != 1 || GetSize() < 1)
	{
		return false;
	}

	for (const auto& elem : m_programMap)
	{
		if (!elem.second->IsValid())
		{
			return false;
		}

	}

	if (ContainsCircularDependency())
	{
		return false;
	}

	return true;
}

bool ProgramTree::ContainsCircularDependency() const
{
	std::vector<std::string> visitedNodeNames;
	if (m_root->HasCircularDependency(visitedNodeNames))
	{
		return true;
	}

	// visited nodes include m_root
	return visitedNodeNames.size() != GetSize() + 1;
}

std::shared_ptr<Program> ProgramTree::GetRoot() const
{
	auto rootChildren = m_root->GetChildren();
	if (rootChildren.empty())
	{
		return std::make_shared<Program>();
	}
	else
	{
		return rootChildren[0];
	}
}
