#pragma once

#include <map>
#include <string>
#include <vector>

#include "AdventOfCodeBase.h"

/*
    https://adventofcode.com/2017/day/11

    Part 1:

    a program comes up to you, clearly in distress. "It's my child process," she says, "he's gotten lost in an infinite grid!"

    Fortunately for her, you have plenty of experience with infinite grids.

    Unfortunately for you, it's a hex grid.

    The hexagons ("hexes") in this grid are aligned such that adjacent hexes can be found to the north, northeast, southeast, south, southwest, and northwest:

          \ n  /
        nw +--+ ne
          /    \
        -+      +-
          \    /
        sw +--+ se
          / s  \

    You have the path the child process took. Starting where he started, you need to determine the fewest number of steps required to reach him. (A "step" means to move from the hex you are in to any adjacent hex.)

    For example:

        ne,ne,ne is 3 steps away.
        ne,ne,sw,sw is 0 steps away (back where you started).
        ne,ne,s,s is 2 steps away (se,se).
        se,sw,se,sw,sw is 3 steps away (s,s,sw).
*/

namespace AdventOfCode {
namespace December11 {

    struct Cell
	{
		Cell() = delete;
		Cell(int _x, int _y)
		{
			x = _x;
			y = _y;
		}

		bool operator ==(const Cell& other)
		{
			return x == other.x && y == other.y;
		}

		void operator +=(const Cell& other)
		{
			x += other.x;
			y += other.y;
		}

		int x = 0;
		int y = 0;
	};

	class InfiniteHexGrid
        : protected AdventOfCodeBase
	{
	public:
        InfiniteHexGrid();
        InfiniteHexGrid(const std::vector<std::string>& path);
        InfiniteHexGrid(const std::string& fileName);
        ~InfiniteHexGrid() = default;

    public:
        // AdventOfCodeBase
        virtual bool ParseLine(const std::string& inputLine) override;
        virtual void OutputResultToConsole() const override;
        // ~AdventOfCodeBase

    public:
		Cell GetTargetCell() const;
        int GetPathLength() const { return static_cast<int>(m_path.size()); }
        // for sanity checks
        std::vector<std::string> GetSimplifiedPath() const;
        static int GetTargetDistanceToOrigin(const Cell& target);

	protected:
		Cell GetDirection(std::string dirString) const;

    private:
		void SetupDirections();

	protected:
		std::vector<std::string> m_path;
		std::map<std::string, Cell> m_directions;

    private:
        Cell m_pathTarget = Cell(0, 0);
    };

}}
