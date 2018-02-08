#include "stdafx.h"
#include "CppUnitTest.h"
#include "../AdventOfCode/December24.h"

namespace AdventOfCodeTest
{
    using namespace Microsoft::VisualStudio::CppUnitTestFramework;
    using namespace AdventOfCode::December24;

    TEST_CLASS(Test_December24)
    {
    public:
        /*
        ParseLine
        */
        TEST_METHOD(December24_ParseLine_invalid_empty)
        {
            PortConnection test;
            Assert::AreEqual(false, test.ParseLine(""));
        }

        TEST_METHOD(December24_ParseLine_invalid_wrongSeparator)
        {
            PortConnection test;
            Assert::AreEqual(false, test.ParseLine("5-9"));
        }

        TEST_METHOD(December24_ParseLine_invalid_missingStartNumber)
        {
            PortConnection test;
            Assert::AreEqual(false, test.ParseLine("/7"));
        }

        TEST_METHOD(December24_ParseLine_invalid_missingEndNumber)
        {
            PortConnection test;
            Assert::AreEqual(false, test.ParseLine("3/"));
        }

        TEST_METHOD(December24_ParseLine_invalid_missingSeparator)
        {
            PortConnection test;
            Assert::AreEqual(false, test.ParseLine("04"));
        }

        TEST_METHOD(December24_ParseLine_invalid_tooManyElements)
        {
            PortConnection test;
            Assert::AreEqual(false, test.ParseLine("2/8/5"));
        }

        TEST_METHOD(December24_ParseLine_invalid_nonNumber)
        {
            PortConnection test;
            Assert::AreEqual(false, test.ParseLine("g/3"));
        }

        TEST_METHOD(December24_ParseLine_invalid_negativeNumber)
        {
            PortConnection test;
            Assert::AreEqual(false, test.ParseLine("9/-7"));
        }

        TEST_METHOD(December24_ParseLine_valid_different)
        {
            PortConnection test;
            Assert::AreEqual(true, test.ParseLine("14/6"));
        }

        TEST_METHOD(December24_ParseLine_valid_same)
        {
            PortConnection test;
            Assert::AreEqual(true, test.ParseLine("0/0"));
        }

        /*
        AddConnection
        */
        TEST_METHOD(December24_AddConnection_params)
        {
            PortConnection test;
            test.AddConnection("54", "14", 4);
            Assert::AreEqual(1, test.GetNumberOfConnections());

            Assert::AreEqual(4, test.GetWeight("54", "14"));
            Assert::AreEqual(4, test.GetWeight("14", "54"));
            Assert::AreEqual(-1, test.GetWeight("14", "14"));
            Assert::AreEqual(-1, test.GetWeight("54", "54"));
        }

        TEST_METHOD(December24_AddConnection_struct)
        {
            const Connection connect("3", "7", 5);

            PortConnection test;
            test.AddConnection(connect);
            Assert::AreEqual(1, test.GetNumberOfConnections());

            Assert::AreEqual(5, test.GetWeight("7", "3"));
            Assert::AreEqual(-1, test.GetWeight("3", "3"));
            Assert::AreEqual(-1, test.GetWeight("7", "7"));
            Assert::AreEqual(5, test.GetWeight("3", "7"));
        }

        /*
        AddPossiblePath
        */
        TEST_METHOD(December24_AddPossiblePath_single)
        {
            PortConnection test;
            test.AddConnection("1", "2", 3);

            std::set<std::vector<Connection>> allPaths;
            test.AddPossiblePath(allPaths, "1", std::vector<Connection>());
            Assert::AreEqual(1, static_cast<int>(allPaths.size()));
        }

        /*
        simple graph starting at 3:
        3/5
        3/5 - 5/2
        3/9
        */
        TEST_METHOD(December24_AddPossiblePath_multi)
        {
            PortConnection test;
            test.AddConnection("3", "5", 8);
            test.AddConnection("3", "9", 12);
            test.AddConnection("2", "5", 7);

            std::set<std::vector<Connection>> allPaths;
            test.AddPossiblePath(allPaths, "3", std::vector<Connection>());
            Assert::AreEqual(3, static_cast<int>(allPaths.size()));
        }

        /*
        starting at 5: contains a loop, so there are two possible directions
        5/7
        5/7 - 7/8
        5/7 - 7/8 - 8/5
        5/8
        5/8 - 8/7
        5/8 - 8/7 - 7/5
        */
        TEST_METHOD(December24_AddPossiblePath_circle)
        {
            PortConnection test;
            test.AddConnection("8", "5", 5);
            test.AddConnection("7", "5", 18);
            test.AddConnection("7", "8", 7);

            std::set<std::vector<Connection>> allPaths;
            test.AddPossiblePath(allPaths, "5", std::vector<Connection>());
            Assert::AreEqual(6, static_cast<int>(allPaths.size()));
        }

        /*
        starting at 2: contains self-referential connections
        2/8
        2/8 - 8/8
        2/8 - 8/8 - 8/3
        2/8 - 8/8 - 8/3 - 3/3
        2/8 - 8/8 - 8/3 - 3/4
        2/8 - 8/8 - 8/3 - 3/3 - 3/4
        2/8 - 8/3
        2/8 - 8/3 - 3/3
        2/8 - 8/3 - 3/4
        2/8 - 8/3 - 3/3 - 3/4
        */
        TEST_METHOD(December24_AddPossiblePath_recursion)
        {
            PortConnection test;
            test.AddConnection("2", "8", 10);
            test.AddConnection("8", "8", 16);
            test.AddConnection("3", "3", 6);
            test.AddConnection("8", "3", 11);
            test.AddConnection("4", "3", 7);

            std::set<std::vector<Connection>> allPaths;
            test.AddPossiblePath(allPaths, "2", std::vector<Connection>());
            Assert::AreEqual(10, static_cast<int>(allPaths.size()));
        }

        /*
        With them, you could make the following valid bridges:

        0/1
        0/1--10/1
        0/1--10/1--9/10
        0/2
        0/2--2/3
        0/2--2/3--3/4
        0/2--2/3--3/5
        0/2--2/2
        0/2--2/2--2/3
        0/2--2/2--2/3--3/4
        0/2--2/2--2/3--3/5
        */
        TEST_METHOD(December24_AddPossiblePath_AoC_test)
        {
            PortConnection test;
            test.AddConnection("0", "2", 2);
            test.AddConnection("2", "2", 4);
            test.AddConnection("2", "3", 5);
            test.AddConnection("3", "4", 7);
            test.AddConnection("3", "5", 8);
            test.AddConnection("0", "1", 1);
            test.AddConnection("10", "1", 11);
            test.AddConnection("9", "10", 19);

            std::set<std::vector<Connection>> allPaths;
            test.AddPossiblePath(allPaths, "0", std::vector<Connection>());

            Assert::AreEqual(11, static_cast<int>(allPaths.size()));
        }

        /*
        Given the above examples, here are the paths that cannot be extended by another connection at the end.

        0/1--10/1--9/10
        0/2--2/3--3/4
        0/2--2/3--3/5
        0/2--2/2--2/3--3/4
        0/2--2/2--2/3--3/5
        */
        TEST_METHOD(December24_AddPossibleLongPath_AoC_test)
        {
            PortConnection test;
            test.AddConnection("0", "2", 2);
            test.AddConnection("2", "2", 4);
            test.AddConnection("2", "3", 5);
            test.AddConnection("3", "4", 7);
            test.AddConnection("3", "5", 8);
            test.AddConnection("0", "1", 1);
            test.AddConnection("10", "1", 11);
            test.AddConnection("9", "10", 19);

            std::set<std::vector<Connection>> allPaths;
            test.AddPossibleLongPath(allPaths, "0", std::vector<Connection>());

            Assert::AreEqual(5, static_cast<int>(allPaths.size()));
        }

        /*
        CalculateBestPath
        */
        /*
        8/2 - 2/3 - 3/1 : weight 19 ==> connectE - connectC - connectA
        8/2 - 2/5 : weight 17
        8/4 : weight 12
        */
        TEST_METHOD(December24_CalculateBestPath)
        {
            Connection connectA("1", "3", 4);
            Connection connectB("8", "4", 12);
            Connection connectC("2", "3", 5);
            Connection connectD("2", "5", 7);
            Connection connectE("2", "8", 10);

            PortConnection test;
            test.AddConnection(connectA);
            test.AddConnection(connectB);
            test.AddConnection(connectC);
            test.AddConnection(connectD);
            test.AddConnection(connectE);

            std::vector<Connection> bestPath;
            test.CalculateBestPath("8", bestPath);

            Assert::AreEqual(3, static_cast<int>(bestPath.size()));
            Assert::AreEqual(true, bestPath[0] == connectE);
            Assert::AreEqual(true, bestPath[1] == connectC);
            Assert::AreEqual(true, bestPath[2] == connectA);

            Assert::AreEqual(19, test.GetWeight(bestPath));
        }

        /*
         GetStrongestBridgeWeight
         */
        TEST_METHOD(December24_GetStrongestBridgeWeight_single)
        {
            PortConnection test;
            test.AddConnection("8", "0", 5);

            Assert::AreEqual(5, test.CalculateStrongestBridgeWeight());
        }

        /*
        0/7 : weight 7
        0/3 - 3/4 : weight 10
        */
        TEST_METHOD(December24_GetStrongestBridgeWeight_simple)
        {
            PortConnection test;
            test.AddConnection("4", "3", 7);
            test.AddConnection("3", "0", 3);
            test.AddConnection("0", "7", 7);

            Assert::AreEqual(10, test.CalculateStrongestBridgeWeight());
        }

        /*
        Of these bridges, the strongest one is 0/1--10/1--9/10; it has a strength of 0+1 + 1+10 + 10+9 = 31.
        */
        TEST_METHOD(December24_GetStrongestBridgeWeight_AoC_test)
        {
            PortConnection test;
            test.AddConnection("0", "2", 2);
            test.AddConnection("2", "2", 4);
            test.AddConnection("2", "3", 5);
            test.AddConnection("3", "4", 7);
            test.AddConnection("3", "5", 8);
            test.AddConnection("0", "1", 1);
            test.AddConnection("10", "1", 11);
            test.AddConnection("9", "10", 19);

            Assert::AreEqual(31, test.CalculateStrongestBridgeWeight());
        }
    };
}
