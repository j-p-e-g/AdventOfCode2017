#include "stdafx.h"

#include <iostream>

#include "December09b.h"

using namespace AdventOfCode::December09;

StreamGarbageRemoval::StreamGarbageRemoval(const std::stringstream& stream)
{
    ProcessStream(stream);
}

StreamGarbageRemoval::StreamGarbageRemoval(const std::string& fileName)
{
    ReadFile(fileName);
}

void StreamGarbageRemoval::OutputResultToConsole() const
{
    std::cout << "December09.b: result = " << GetTotalGarbageSize() << std::endl;
}

void StreamGarbageRemoval::ProcessStream(const std::stringstream& stream)
{
    std::stringstream ss;
    ss << std::noskipws;
    ss << stream.str();

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
            continue;
            break;
        case '{':
            // open group (unless in garbage)
            if (!m_streamStack->GetIsGarbage())
            {
                std::shared_ptr<StreamObject> curr = std::make_shared<StreamObject>(ObjectType::OT_GROUP, m_streamStack);
                m_streamStack->AddChild(curr);
                m_streamStack = curr;
                continue;
            }
            break;
        case '}':
            // close group (if in group)
            if (m_streamStack->GetIsGroup())
            {
                m_streamStack = m_streamStack->GetParent();
                continue;
            }
            break;
        case '<':
            // open garbage (unless already in garbage)
            if (!m_streamStack->GetIsGarbage())
            {
                std::shared_ptr<StreamObject> curr = std::make_shared<StreamObject>(ObjectType::OT_GARBAGE, m_streamStack);
                m_streamStack->AddChild(curr);
                m_streamStack = curr;
                continue;
            }
            break;
        case '>':
            // close garbage (unless not currently in garbage)
            if (m_streamStack->GetIsGarbage())
            {
                m_streamStack = m_streamStack->GetParent();
                continue;
            }
            break;
        default:
            break;
        }

        m_streamStack->AddChar(buf);
    }

    // remove all unclosed elements
    while (m_streamStack && !m_streamStack->GetIsRoot())
    {
        std::shared_ptr<StreamObject> obj = m_streamStack;
        m_streamStack = obj->GetParent();
        m_streamStack->RemoveChild(obj);
    }
}

int StreamGarbageRemoval::GetTotalGarbageSize() const
{
    return m_streamStack->GetGarbageCount();
}
