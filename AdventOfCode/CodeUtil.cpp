#include "stdafx.h"
#include "CodeUtil.h"
#include <sstream>

using namespace CodeUtils;

std::vector<std::string> CodeUtil::SplitStringBySpace(std::string input)
{
	std::vector<std::string> elements;

	// read input into stream
	std::stringstream ss(input);

	// read stream into buffer
	std::string buf;
	while (ss >> buf)
	{
		elements.push_back(buf);
	}

	return elements;
}
