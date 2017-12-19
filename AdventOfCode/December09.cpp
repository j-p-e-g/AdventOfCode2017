#include "stdafx.h"

#include <iostream>

#include "December09.h"

using namespace AdventOfCode::December09;

StreamObject::StreamObject(ObjectType type, std::shared_ptr<StreamObject> parent)
	: m_objectType(type)
	, m_parent(parent)
{
}

void StreamObject::AddChild(std::shared_ptr<StreamObject> child)
{
	m_children.push_back(child);
}

void StreamObject::RemoveChild(std::shared_ptr<StreamObject> child)
{
	auto found = std::find(m_children.begin(), m_children.end(), child);

	if (found != m_children.end())
	{
		m_children.erase(found);
	}
}

void StreamObject::AddChar(char c)
{
    m_content += c;
}

int StreamObject::GetScore(int parentScore) const
{
	int score = 0;

	switch (m_objectType)
	{
	case ObjectType::OT_GROUP:
		score = parentScore + 1;
		break;
	case ObjectType::OT_ROOT:
		break;
	case ObjectType::OT_GARBAGE:
	default:
		return 0;
	}

	int totalScore = score;
	for (const auto& child : m_children)
	{
		totalScore += child->GetScore(score);
	}

	return totalScore;
}


int StreamObject::GetGarbageCount() const
{
    if (m_objectType == OT_GARBAGE)
    {
        return GetContentSize();
    }

    int sum = 0;
    for (const auto& child : m_children)
    {
        sum += child->GetGarbageCount();
    }

    return sum;
}

// -----------------------------------
// StreamOfChars
// -----------------------------------

StreamOfChars::StreamOfChars(const std::string& fileName)
    : AdventOfCodeBase()
{
    ReadFile(fileName);
}

bool StreamOfChars::ParseLine(const std::string& inputLine)
{
    std::stringstream stream(inputLine);
    ProcessStream(stream);
    return true;
}

void StreamOfChars::OutputResultToConsole() const
{
    std::cout << "December09.a: result = " << GetGroupScore() << std::endl;
}

StreamOfChars::StreamOfChars(const std::stringstream& stream)
{
	ProcessStream(stream);
}

void StreamOfChars::ProcessStream(const std::stringstream& stream)
{
	std::stringstream ss(stream.str());

	m_streamStack = std::make_shared<StreamObject>(ObjectType::OT_ROOT, nullptr);

	char buf;
	bool skipNext = false;
	while (ss >> buf)
	{
		if (skipNext)
		{
			skipNext = false;
			continue;
		}

		switch (buf)
		{
		case '!':
			skipNext = true;
			break;
		case '{':
			// open group (unless in garbage)
			if (!m_streamStack->GetIsGarbage())
			{
				std::shared_ptr<StreamObject> curr = std::make_shared<StreamObject>(ObjectType::OT_GROUP, m_streamStack);
				m_streamStack->AddChild(curr);
				m_streamStack = curr;
			}
			break;
		case '}':
			// close group (if in group)
			if (m_streamStack->GetIsGroup())
			{
				m_streamStack = m_streamStack->GetParent();
			}
			break;
		case '<':
			// open garbage (unless already in garbage)
			if (!m_streamStack->GetIsGarbage())
			{
				std::shared_ptr<StreamObject> curr = std::make_shared<StreamObject>(ObjectType::OT_GARBAGE, m_streamStack);
				m_streamStack->AddChild(curr);
				m_streamStack = curr;
			}
			break;
		case '>':
			// close garbage (unless not currently in garbage)
			if (m_streamStack->GetIsGarbage())
			{
				m_streamStack = m_streamStack->GetParent();
			}
			break;
		default:
			break;
		}
	}

	// remove all unclosed elements
	while (m_streamStack && !m_streamStack->GetIsRoot())
	{
		std::shared_ptr<StreamObject> obj = m_streamStack;
		m_streamStack = obj->GetParent();
		m_streamStack->RemoveChild(obj);
	}
}

int StreamOfChars::GetGroupScore() const
{
	return m_streamStack->GetScore();
}
