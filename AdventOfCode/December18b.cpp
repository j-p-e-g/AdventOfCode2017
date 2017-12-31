#include "stdafx.h"

#include <iostream>

#include "December18b.h"

using namespace AdventOfCode::December18;

// ---------------------------------
// RegisterCommand(s) overrides
// ---------------------------------

// send value
bool RegisterSndB::Apply(RegisterSolo& rd)
{
    const long long value = param.isChar ? rd.GetRegisterValue(param.id) : param.value;
    rd.Send(value);
    RegisterCommand::Apply(rd);

    return true;
}

// receive value
bool RegisterRcvB::Apply(RegisterSolo& rd)
{
    if (rd.SetQueuedValue(param.id))
    {
        // only increase index if we're not stalled
        RegisterCommand::Apply(rd);
    }

    return true;
}

// ---------------------------------
// RegisterSoloB
// ---------------------------------
RegisterSoloB::RegisterSoloB(int id, const std::shared_ptr<RegisterDuet>& duet)
    : m_id(id)
    , m_duet(duet)
{
    m_registers.emplace('p', m_id);
    m_currentIndex = 0;
}

bool RegisterSoloB::ParseCommand(const std::string& command, const CharOrNumber& param1, const CharOrNumber& param2)
{
    if (command == "snd")
    {
        if (!param1.isValid || param2.isValid)
        {
            return false;
        }

        m_commands.push_back(std::make_shared<RegisterSndB>(param1));
    }
    else if (command == "rcv")
    {
        if (!param1.isValid || param2.isValid || !param1.isChar)
        {
            return false;
        }

        m_commands.push_back(std::make_shared<RegisterRcvB>(param1));
    }
    else
    {
        return RegisterSolo::ParseCommand(command, param1, param2);
    }

    return true;
}

bool RegisterSoloB::ExecuteNextCommand()
{
    if (m_currentIndex < 0 || m_currentIndex >= m_commands.size())
    {
        m_state = S_FINISHED;
        return true;
    }

    m_state = S_RUNNING;
    if (!RegisterSolo::ExecuteNextCommand())
    {
        return false;
    }

    return true;
}

void RegisterSoloB::Send(long long value)
{
    m_duet->Send(m_id, value);
    m_sendCount++;
}

void RegisterSoloB::AddToQueue(long long val)
{
    m_queue.push_back(val);
}

bool RegisterSoloB::SetQueuedValue(char id)
{
    if (m_queue.empty())
    {
        m_state = S_WAITING;
        return false;
    }

    SetRegisterValue(id, m_queue.front());
    m_queue.erase(std::find(m_queue.begin(), m_queue.end(), m_queue.front()));
    m_state = S_RUNNING;
    return true;
}

int RegisterSoloB::GetSendCount() const
{
    return m_sendCount;
}

// ---------------------------------
// RegisterDuet
// ---------------------------------
void RegisterDuet::ReadFile(const std::string& fileName)
{
    AdventOfCodeBase::ReadFile(fileName);
}

void RegisterDuet::OutputResultToConsole() const
{
    if (m_programs.size() < 2)
    {
        std::cerr << "December18.b FAILED (too few sub-programs)" << std::endl;
        return;
    }
    
    std::cout << "December18.b: result = " << m_programs[1]->GetSendCount() << std::endl;
}

void RegisterDuet::RegisterProgram(std::shared_ptr<RegisterSoloB>& program)
{
    m_programs.push_back(program);
}

bool RegisterDuet::ParseCommand(const std::string& command, const CharOrNumber& param1, const CharOrNumber& param2)
{
    for (auto& elem : m_programs)
    {
        if (!elem->ParseCommand(command, param1, param2))
        {
            return false;
        }
    }

    return true;
}

bool RegisterDuet::ExecuteCommands()
{
    int countFinished = 0;
    int countStalled = 0;

    while (countFinished + countStalled < m_programs.size())
    {
        countFinished = 0;
        countStalled = 0;

        for (auto& program : m_programs)
        {
            if (program->IsFinished())
            {
                countFinished++;
            }
            else
            {
                if (!program->ExecuteNextCommand())
                {
                    return false;
                }

                if (program->IsFinished())
                {
                    countFinished++;
                }
                else if (program->IsStalled())
                {
                    countStalled++;
                }
            }
        }
    }

    // true if all programs have finished, else false
    return countFinished == m_programs.size();
}

void RegisterDuet::Send(int id, long long value)
{
    // send to all _other_ programs
    if (id >= 0 && id < m_programs.size())
    {
        for (int k = 0; k < static_cast<int>(m_programs.size()); k++)
        {
            if (k != id)
            {
                m_programs[k]->AddToQueue(value);
            }
        }
    }
}
