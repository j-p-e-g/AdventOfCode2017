#pragma once

#include <map>
#include <string>
#include <vector>

/*
https://adventofcode.com/2017/day/11
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
namespace December11
{
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
	{
	public:
		InfiniteHexGrid(const std::vector<std::string>& path);
		~InfiniteHexGrid() = default;

	public:
		Cell GetTargetCell() const;
		int GetTargetDistanceToOrigin() const;

	private:
		Cell GetDirection(std::string dirString) const;
		void SetupDirections();

	private:
		std::vector<std::string> m_path;
		Cell m_pathTarget = Cell(0, 0);
		std::map<std::string, Cell> m_directions;
	};
}
