#include "stdafx.h"
#include "December11.h"

#include <math.h>

using namespace December11;

InfiniteHexGrid::InfiniteHexGrid(const std::vector<std::string>& path)
	: m_path(path)
{
	SetupDirections();
	m_pathTarget = GetTargetCell();
}

Cell InfiniteHexGrid::GetDirection(std::string dirString) const
{
	const auto found = m_directions.find(dirString);

	if (found == m_directions.end())
	{
		return Cell(0, 0);
	}

	return found->second;
}

void InfiniteHexGrid::SetupDirections()
{
	//      \ n  /              \ (0, -1) /
	//    nw +--+ ne     (-1, 0) +-------+ (1, -1)
	//      /    \              /         \
	//    -+      +-        ---+  (0, 0)   +---
	//      \    /              \         /
	//    sw +--+ se     (-1, 1) +-------+ (1, 0)
	//      / s  \              / (0, 1)  \

	m_directions.emplace("n", Cell(0, -1));
	m_directions.emplace("ne", Cell(1, -1));
	m_directions.emplace("se", Cell(1, 0));
	m_directions.emplace("s", Cell(0, 1));
	m_directions.emplace("sw", Cell(-1, 1));
	m_directions.emplace("nw", Cell(-1, 0));
}

Cell InfiniteHexGrid::GetTargetCell() const
{
	Cell curr = Cell(0, 0);

	for (const auto& dir : m_path)
	{
		curr += GetDirection(dir);
	}

	return curr;
}

int InfiniteHexGrid::GetTargetDistanceToOrigin() const
{
	return static_cast<int>(std::fmax(std::abs(m_pathTarget.x), std::abs(m_pathTarget.y)));
}

