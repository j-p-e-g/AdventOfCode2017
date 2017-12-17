// AdventOfCode.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "December01.h"
#include "December02.h"
#include "December03.h"
#include "December04.h"
#include "December05.h"
#include "December06.h"
#include "December07.h"
#include "December08.h"
#include "December09.h"

int main()
{
    {
        AdventOfCode::December01::CheckSum test("InputFiles/input01.txt");
        test.OutputResultToConsole();
    }
    {
        AdventOfCode::December02::MatrixCheckSum test("InputFiles/input02.txt");
        test.OutputResultToConsole();
    }
    {
        AdventOfCode::December03::SpiralMemory test("InputFiles/input03.txt");
        test.OutputResultToConsole();
    }
    {
        AdventOfCode::December04::PassPhraseCheck test("InputFiles/input04.txt");
        test.OutputResultToConsole();
    }
    {
        AdventOfCode::December05::InstructionMaze test("InputFiles/input05.txt");
        test.OutputResultToConsole();
    }
    {
        AdventOfCode::December06::MemoryReallocator test("InputFiles/input06.txt");
        test.OutputResultToConsole();
    }
    {
        AdventOfCode::December07::ProgramTree test("InputFiles/input07.txt");
        test.OutputResultToConsole();
    }

    return 0;
}

