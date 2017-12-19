#include "stdafx.h"

#include <iostream>

#include "December07b.h"

using namespace AdventOfCode::December07;

ProgramTreeB::ProgramTreeB(const std::string& fileName)
    : ProgramTree(fileName)
{
}

void ProgramTreeB::OutputResultToConsole() const
{
    std::shared_ptr<Program> correctedNode;
    GetCorrectedWeightNode(correctedNode);

    std::cout << "December07.b: result = " << correctedNode->GetWeight() << std::endl;
}

ProgramTreeB::ProgramTreeB(std::vector<ProgramData> programData)
    : ProgramTree(programData)
{
}

int ProgramTreeB::GetWeightForNode(const std::string& id) const
{
    const auto& found = m_programMap.find(id);
    if (found == m_programMap.end())
    {
        return -1;
    }

    return found->second->GetTreeWeight();
}

bool ProgramTreeB::GetUnbalancedNode(std::shared_ptr<Program>& node) const
{
    return m_root->GetUnbalancedNode(node);
}

bool ProgramTreeB::GetCorrectedWeightNode(std::shared_ptr<Program>& node) const
{
    if (!GetUnbalancedNode(node))
    {
        return false;
    }

    std::map<int,  std::vector<std::shared_ptr<Program>> > weightMap;

    for (auto& child : node->GetChildren())
    {
        const int weight = child->GetTreeWeight();
        auto& found = weightMap.find(weight);
        if (found == weightMap.end())
        {
            weightMap.emplace(weight, std::vector<std::shared_ptr<Program>>( {child} ));
        }
        else
        {
            found->second.push_back(child);
        }
    }

    if (static_cast<int>(weightMap.size()) != 2)
    {
        // either already balanced (size 1) or there are more than 2 different weights (size 3+)
        return false;
    }

    int balancedWeight = -1;
    bool foundIncorrectNode = false;
    for (const auto& elem : weightMap)
    {
        if (!foundIncorrectNode && elem.second.size() == 1)
        {
            node = elem.second[0];
            foundIncorrectNode = true;
        }
        else
        {
            balancedWeight = elem.first;
        }
    }

    if (!foundIncorrectNode || balancedWeight == -1)
    {
        // no single node found whose weight differs from the others
        return false;
    }

    const int difference = balancedWeight - node->GetTreeWeight();

    if (difference == 0)
    {
        // already balanced, after all
        return false;
    }

    node->SetWeight(node->GetWeight() + difference);

    if (!node->IsValid())
    {
        // changing the weight invalidated the node
        return false;
    }

    // returns true iff the tree is now balanced
    return m_root->IsBalancedSubTree();
}
