#include "stdafx.h"
#include "December07.h"

using namespace December07;

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

ProgramTree::ProgramTree(std::vector<ProgramData> programData)
{
	m_root = std::make_shared<Program>("[root]", 0);

	for (const auto& data : programData)
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
		return std::make_shared<Program>("", -1);
	}
	else
	{
		return rootChildren[0];
	}
}
