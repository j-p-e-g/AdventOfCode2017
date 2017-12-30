// AdventOfCode.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <memory>

#include "December01b.h"
#include "December02b.h"
#include "December03b.h"
#include "December04b.h"
#include "December05b.h"
#include "December06b.h"
#include "December07b.h"
#include "December08b.h"
#include "December09b.h"
#include "December10b.h"
#include "December11b.h"
#include "December12b.h"
#include "December13b.h"
#include "December14b.h"
#include "December15b.h"
#include "December16b.h"
#include "December17.h"
#include "December17b.h"
#include "December18.h"

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
        AdventOfCode::December04::PassPhraseCheck testa("InputFiles/input04.txt");
        testa.OutputResultToConsole();
        AdventOfCode::December04::AnagramPassPhraseCheck testb("InputFiles/input04.txt");
        testb.OutputResultToConsole();
    }
    {
        AdventOfCode::December05::InstructionMaze testa("InputFiles/input05.txt");
        testa.OutputResultToConsole();
        AdventOfCode::December05::InstructionMazeB testb("InputFiles/input05.txt");
        testb.OutputResultToConsole();
    }
    {
        AdventOfCode::December06::MemoryReallocator testa("InputFiles/input06.txt");
        testa.OutputResultToConsole();
        AdventOfCode::December06::MemoryReallocatorCycleCount testb("InputFiles/input06.txt");
        testb.OutputResultToConsole();
    }
    {
        AdventOfCode::December07::ProgramTree testa("InputFiles/input07.txt");
        testa.OutputResultToConsole();
        AdventOfCode::December07::ProgramTreeB testb("InputFiles/input07.txt");
        testb.OutputResultToConsole();
    }
    {
        AdventOfCode::December08::RegisterHandler testa("InputFiles/input08.txt");
        testa.OutputResultToConsole();
        AdventOfCode::December08::RegisterHandlerB testb("InputFiles/input08.txt");
        testb.OutputResultToConsole();
    }
    {
        AdventOfCode::December09::StreamOfChars testa("InputFiles/input09.txt");
        testa.OutputResultToConsole();
        AdventOfCode::December09::StreamGarbageRemoval testb("InputFiles/input09.txt");
        testb.OutputResultToConsole();
    }
    {
        AdventOfCode::December10::SimpleKnotHash testa("InputFiles/input10.txt");
        testa.OutputResultToConsole();
        AdventOfCode::December10::ComplexKnotHash testb("InputFiles/input10.txt");
        testb.OutputResultToConsole();
    }
    {
        AdventOfCode::December11::InfiniteHexGrid testa("InputFiles/input11.txt");
        testa.OutputResultToConsole();
        AdventOfCode::December11::InfiniteHexGridB testb("InputFiles/input11.txt");
        testb.OutputResultToConsole();
    }
    {
        AdventOfCode::December12::ConnectionManager testa("InputFiles/input12.txt");
        testa.OutputResultToConsole();
        AdventOfCode::December12::ConnectionManagerB testb("InputFiles/input12.txt");
        testb.OutputResultToConsole();
    }
    {
        AdventOfCode::December13::Firewall testa("InputFiles/input13.txt");
        testa.OutputResultToConsole();
        AdventOfCode::December13::FirewallB testb("InputFiles/input13.txt");
        testb.OutputResultToConsole();
    }
    {
        AdventOfCode::December14::DiskDefragmenter testa("InputFiles/input14.txt");
        testa.OutputResultToConsole();
        AdventOfCode::December14::DiskDefragmenterB testb("InputFiles/input14.txt");
        testb.OutputResultToConsole();
    }
    {
        using namespace AdventOfCode::December15;

        // no point in reading from input file
        DuelingGeneratorJudge testa;
        testa.AddGenerator(std::make_shared<Generator>(722, 16807, 2147483647));
        testa.AddGenerator(std::make_shared<Generator>(354, 48271, 2147483647));
        testa.OutputResultToConsole();

        DuelingGeneratorJudgeB testb;
        testb.AddGenerator(std::shared_ptr<Generator>(new GeneratorB(722, 16807, 2147483647, 4)));
        testb.AddGenerator(std::shared_ptr<Generator>(new GeneratorB(354, 48271, 2147483647, 8)));
        testb.OutputResultToConsole();
    }
    {
        AdventOfCode::December16::ProgramDancingMaster testa("InputFiles/input16.txt");
        testa.OutputResultToConsole();
        AdventOfCode::December16::ProgramDancingMasterB testb("InputFiles/input16.txt", 16, 100);
        testb.OutputResultToConsole();
    }
    {
        AdventOfCode::December17::Spinlock testa("InputFiles/input17.txt");
        testa.OutputResultToConsole();
        AdventOfCode::December17::SpinlockB testb("InputFiles/input17.txt");
        testb.OutputResultToConsole();
    }
    {
        AdventOfCode::December18::RegisterDuet test("InputFiles/input18.txt");
        test.OutputResultToConsole();
    }

    return 0;
}

