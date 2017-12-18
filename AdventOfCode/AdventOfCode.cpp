// AdventOfCode.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "December01b.h"
#include "December02b.h"
#include "December03b.h"
#include "December04.h"
#include "December05.h"
#include "December06.h"
#include "December07.h"
#include "December08.h"
#include "December09.h"
#include "December10.h"
#include "December11.h"
#include "December12.h"

int main()
{
    {
        AdventOfCode::December01::CheckSum testa("InputFiles/input01.txt");
        testa.OutputResultToConsole();
        AdventOfCode::December01::CircularCheckSum testb("InputFiles/input01.txt");
        testb.OutputResultToConsole();
    }
    {
        AdventOfCode::December02::MatrixCheckSum testa("InputFiles/input02.txt");
        testa.OutputResultToConsole();
        AdventOfCode::December02::MatrixCheckSumMultiple testb("InputFiles/input02.txt");
        testb.OutputResultToConsole();
    }
    {
        AdventOfCode::December03::SpiralMemory testa("InputFiles/input03.txt");
        testa.OutputResultToConsole();
        AdventOfCode::December03::SumSpiralMemory testb("InputFiles/input03.txt");
        testb.OutputResultToConsole();
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
    {
        AdventOfCode::December08::RegisterHandler test("InputFiles/input08.txt");
        test.OutputResultToConsole();
    }
    {
        AdventOfCode::December09::StreamOfChars test("InputFiles/input09.txt");
        test.OutputResultToConsole();
    }

    // December10

    {
        AdventOfCode::December11::InfiniteHexGrid test("InputFiles/input11.txt");
        test.OutputResultToConsole();
    }
    {
        AdventOfCode::December12::ConnectionManager test("InputFiles/input12.txt");
        test.OutputResultToConsole();
    }

    return 0;
}

