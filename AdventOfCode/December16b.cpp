#include "stdafx.h"

#include <iostream>
#include <regex>

#include "CodeUtil.h"
#include "December16b.h"

using namespace AdventOfCode::December16;

ProgramDancingMasterB::ProgramDancingMasterB(int size, long long numRepeats)
    : ProgramDancingMaster(size)
    , m_numRepetitions(numRepeats)
{
}

ProgramDancingMasterB::ProgramDancingMasterB(const std::string& fileName, int size, long long numRepeats)
    : ProgramDancingMasterB(size, numRepeats)
{
    ReadFile(fileName);
}

bool ProgramDancingMasterB::ParseLine(const std::string& inputLine)
{
    if (inputLine.empty())
    {
        return true;
    }

    std::vector<std::string> moveCommands;
    std::regex commaRegex("([\\w/]+),\\s*");
    if (!CodeUtils::CodeUtil::SplitStringByRegex(inputLine, moveCommands, commaRegex))
    {
        return false;
    }

    std::vector<std::shared_ptr<DancingMove>> moves;
    if (!CreateMoves(moveCommands, moves))
    {
        return false;
    }

    if (!SimplifyMoves(moves))
    {
        return false;
    }

    return HandleDance(moves);
}

bool ProgramDancingMasterB::CreateMoves(std::vector<std::string>& commands, std::vector<std::shared_ptr<DancingMove>>& moves)
{
    for (const auto& moveCommand : commands)
    {
        std::shared_ptr<DancingMove> move;
        if (!ParseDancingMove(moveCommand, move))
        {
            return false;
        }
        else
        {
            moves.push_back(move);
        }
    }

    return true;
}

bool ProgramDancingMasterB::SimplifyMoves(std::vector<std::shared_ptr<DancingMove>>& moves)
{
    const int formationLength = static_cast<int>(m_dancingFormation.length());

    std::vector<std::shared_ptr<DancingMove>> partnerMoves;
    std::vector<std::shared_ptr<DancingMove>> exchangeMoves;
    std::vector<std::shared_ptr<DancingMove>> spinMoves;

    // first extract all partner moves (independent from the other two)
    for (int k = 0; k < moves.size();)
    {
        if (moves[k]->GetType() == "Partner")
        {
            // move into separate list
            partnerMoves.push_back(moves[k]);

            // remove from this one
            auto found = std::find(moves.begin(), moves.end(), moves[k]);
            moves.erase(found);
            continue;
        }

        k++;
    }

    // combine all spin moves
    // extract all exchange moves (requires id modification to take into account all spins)
    for (const auto& m : moves)
    {
        if (m->GetType() == "Spin")
        {
            if (spinMoves.empty())
            {
                // add to separate list
                spinMoves.push_back(m);
            }
            else
            {
                // combine consecutive spins
                const int combinedSpin = (spinMoves[0]->GetSize() + m->GetSize()) % formationLength;

                if (combinedSpin == 0)
                {
                    spinMoves.clear();
                }
                else
                {
                    // replace with combined move
                    spinMoves[0] = std::make_shared<Spin>(Spin(combinedSpin));
                }
            }
        }
        else if (m->GetType() == "Exchange")
        {
            if (spinMoves.empty())
            {
                // move into separate list
                exchangeMoves.push_back(m);
            }
            else
            {
                const int spinSize = spinMoves[0]->GetSize();

                // update ids and move into separate list
                int newId1 = (formationLength + m->GetId1() - spinSize) % formationLength;
                int newId2 = (formationLength + m->GetId2() - spinSize) % formationLength;
                exchangeMoves.push_back(std::make_shared<Exchange>(Exchange(newId1, newId2)));
            }
        }
    }

    moves.clear();

    RemoveCanceledElements(partnerMoves);
    RemoveCanceledElements(exchangeMoves);

    // add exchanges
    for (const auto& m : exchangeMoves)
    {
        moves.push_back(m);
    }
    // add spins
    for (const auto& m : spinMoves)
    {
        moves.push_back(m);
    }
    // add partner swaps
    for (const auto& m : partnerMoves)
    {
        moves.push_back(m);
    }

    return true;
}

void ProgramDancingMasterB::RemoveCanceledElements(std::vector<std::shared_ptr<DancingMove>>& moves)
{
    for (int k = 0; k < static_cast<int>(moves.size() - 1); )
    {
        bool isCancelled = false;
        for (int m = k + 1; m < moves.size(); m++)
        {
            if (moves[k]->CanUndo(moves[m]))
            {
                const auto& found1 = std::find(moves.begin(), moves.end(), moves[k]);
                const auto& found2 = std::find(moves.begin(), moves.end(), moves[m]);
                moves.erase(found2);
                moves.erase(found1);

                isCancelled = true;
                break;
            }
            else if (moves[k]->AffectsSameTarget(moves[m]))
            {
                // interferes with any potential cancelation
                break;
            }
        }

        if (!isCancelled)
        {
            k++;
        }
    }
}

bool ProgramDancingMasterB::HandleDance(const std::vector<std::shared_ptr<DancingMove>>& moves)
{
    m_formations.emplace(GetFinalFormation(), 0);

    for (int k = 0; k < m_numRepetitions; k++)
    {
        for (const auto& move : moves)
        {
            if (!ApplyDancingMove(move))
            {
                return false;
            }
        }

        const std::string current = GetFinalFormation();
        const auto& found = m_formations.find(current);
        if (found == m_formations.end())
        {
            m_formations.emplace(current, k + 1);
        }
        else
        {
            const int cycleTime = k + 1 - found->second;
            std::cout << "\t" << current << " last seen " << cycleTime << " runs ago (at time " << found->second << ")" << std::endl;

            // run again (with same value that started the first cycle)
            // but only with a limited number of repetitions
            m_numRepetitions = m_numRepetitions % cycleTime;
            m_formations.clear();
            HandleDance(moves);
            break;
        }
    }

    return true;
}

void ProgramDancingMasterB::OutputResultToConsole() const
{
    std::cout << "December16.b: result = " << GetFinalFormation() << std::endl;
}
