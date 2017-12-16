#include "stdafx.h"
#include "CppUnitTest.h"
#include "../AdventOfCode/December12.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

using namespace December12;

namespace AdventOfCodeTest
{
	TEST_CLASS(Test_December12)
	{
	public:

        /*
        empty map
        */
        TEST_METHOD(December12_GetConnectedNodes_empty)
        {
            ConnectionMap connections;
            ConnectionManager test(connections);

            std::set<int> connectedNodes;
            test.GetConnectedNodes(5, connectedNodes);
            Assert::AreEqual(true, connectedNodes.empty());
        }

        /*
        non-empty but element doesn't exist
        */
        TEST_METHOD(December12_GetConnectedNodes_nonExistingElement)
        {
            ConnectionMap connections;
            connections.emplace(3, std::set<int>({ 4, 7 }));
            ConnectionManager test(connections);

            std::set<int> connectedNodes;
            test.GetConnectedNodes(2, connectedNodes);
            Assert::AreEqual(true, connectedNodes.empty());
        }

        /*
        single element
        */
        TEST_METHOD(December12_GetConnectedNodes_single)
        {
            ConnectionMap connections;
            connections.emplace(8, std::set<int>({}));
            ConnectionManager test(connections);

            std::set<int> connectedNodes;
            test.GetConnectedNodes(8, connectedNodes);

            Assert::AreEqual(1, static_cast<int>(connectedNodes.size()));
            Assert::AreEqual(false, connectedNodes.end() == connectedNodes.find(8));
        }

        /*
        non-connected element
        */
        TEST_METHOD(December12_GetConnectedNodes_notConnected)
        {
            ConnectionMap connections;
            connections.emplace(4, std::set<int>({}));
            connections.emplace(2, std::set<int>({7, -3}));
            ConnectionManager test(connections);

            std::set<int> connectedNodes;
            test.GetConnectedNodes(4, connectedNodes);

            Assert::AreEqual(1, static_cast<int>(connectedNodes.size()));
            Assert::AreEqual(false, connectedNodes.end() == connectedNodes.find(4));
            // other group
            Assert::AreEqual(true, connectedNodes.end() == connectedNodes.find(-3));
            Assert::AreEqual(true, connectedNodes.end() == connectedNodes.find(2));
            Assert::AreEqual(true, connectedNodes.end() == connectedNodes.find(7));
        }

        /*
        element is map key
        */
        TEST_METHOD(December12_GetConnectedNodes_mapKey)
        {
            ConnectionMap connections;
            connections.emplace(2, std::set<int>({ 5, 4, -4 }));
            ConnectionManager test(connections);

            std::set<int> connectedNodes;
            test.GetConnectedNodes(2, connectedNodes);

            Assert::AreEqual(4, static_cast<int>(connectedNodes.size()));
            Assert::AreEqual(false, connectedNodes.end() == connectedNodes.find(-4));
            Assert::AreEqual(false, connectedNodes.end() == connectedNodes.find(2));
            Assert::AreEqual(false, connectedNodes.end() == connectedNodes.find(4));
            Assert::AreEqual(false, connectedNodes.end() == connectedNodes.find(5));
        }

        /*
        element is map value
        */
        TEST_METHOD(December12_GetConnectedNodes_mapValue)
        {
            ConnectionMap connections;
            connections.emplace(3, std::set<int>({ 9, 2 }));
            ConnectionManager test(connections);

            std::set<int> connectedNodes;
            test.GetConnectedNodes(9, connectedNodes);

            Assert::AreEqual(3, static_cast<int>(connectedNodes.size()));
            Assert::AreEqual(false, connectedNodes.end() == connectedNodes.find(2));
            Assert::AreEqual(false, connectedNodes.end() == connectedNodes.find(3));
            Assert::AreEqual(false, connectedNodes.end() == connectedNodes.find(9));
        }

        /*
        element is linked recursively
        */
        TEST_METHOD(December12_GetConnectedNodes_recursive)
        {
            ConnectionMap connections;
            connections.emplace(1, std::set<int>({ 4 }));
            connections.emplace(4, std::set<int>({ 3 }));
            connections.emplace(3, std::set<int>({ 5 }));
            ConnectionManager test(connections);

            std::set<int> connectedNodes;
            test.GetConnectedNodes(4, connectedNodes);

            Assert::AreEqual(4, static_cast<int>(connectedNodes.size()));
            Assert::AreEqual(false, connectedNodes.end() == connectedNodes.find(1));
            Assert::AreEqual(false, connectedNodes.end() == connectedNodes.find(3));
            Assert::AreEqual(false, connectedNodes.end() == connectedNodes.find(4));
            Assert::AreEqual(false, connectedNodes.end() == connectedNodes.find(5));
        }

        // -------------------------------------
        // GetGroupSize
        // -------------------------------------

        /*
        empty map
        */
        TEST_METHOD(December12_GetGroupSize_empty)
        {
            ConnectionMap connections;
            ConnectionManager test(connections);

            Assert::AreEqual(0, test.GetGroupSize(5));
        }

        /*
        non-empty map but element does not exist
        */
        TEST_METHOD(December12_GetGroupSize_nonExistingElement)
        {
            ConnectionMap connections;
            connections.emplace(7, std::set<int>({ 3, 8 }));
            connections.emplace(8, std::set<int>({ 2, 5 }));
            ConnectionManager test(connections);

            //std::set<int> connectedNodes;
            //test.GetConnectedNodes(8, connectedNodes);
            //Assert::AreEqual(false, connectedNodes.end() == connectedNodes.find(2));
            //Assert::AreEqual(false, connectedNodes.end() == connectedNodes.find(3));
            //Assert::AreEqual(false, connectedNodes.end() == connectedNodes.find(5));
            //Assert::AreEqual(false, connectedNodes.end() == connectedNodes.find(7));
            //Assert::AreEqual(false, connectedNodes.end() == connectedNodes.find(8));
            Assert::AreEqual(0, test.GetGroupSize(4));
        }

        /*
        element is not connected to anything else
        */
        TEST_METHOD(December12_GetGroupSize_single)
        {
            ConnectionMap connections;
            connections.emplace(3, std::set<int>({}));
            connections.emplace(6, std::set<int>({ 4, 7, 6, 2 }));

            ConnectionManager test(connections);
            Assert::AreEqual(1, test.GetGroupSize(3));
        }

        /*
        element is map key
        */
        TEST_METHOD(December12_GetGroupSize_mapKey)
        {
            ConnectionMap connections;
            connections.emplace(1, std::set<int>({-2, -3, 49543, 5}));

            ConnectionManager test(connections);
            Assert::AreEqual(5, test.GetGroupSize(1));
        }

        /*
        element is map value
        */
        TEST_METHOD(December12_GetGroupSize_mapValue)
        {
            ConnectionMap connections;
            connections.emplace(-7, std::set<int>({ 5, 9, -11 }));

            ConnectionManager test(connections);
            Assert::AreEqual(4, test.GetGroupSize(9));
        }

        /*
        recursively connected elements
        */
        TEST_METHOD(December12_GetGroupSize_recursive)
        {
            ConnectionMap connections;
            connections.emplace(1, std::set<int>({2}));
            connections.emplace(2, std::set<int>({3, 8}));
            connections.emplace(4, std::set<int>({3, 5}));
            connections.emplace(6, std::set<int>({5}));

            ConnectionManager test(connections);
            Assert::AreEqual(7, test.GetGroupSize(3));
        }

        /*
        0 <-> 2
        1 <-> 1
        2 <-> 0, 3, 4
        3 <-> 2, 4
        4 <-> 2, 3, 6
        5 <-> 6
        6 <-> 4, 5

        In this example, the following programs are in the group that contains program ID 0:

        Program 0 by definition.
        Program 2, directly connected to program 0.
        Program 3 via program 2.
        Program 4 via program 2.
        Program 5 via programs 6, then 4, then 2.
        Program 6 via programs 4, then 2.

        Therefore, a total of 6 programs are in this group; all but program 1, which has a pipe that connects it to itself.
        */
		TEST_METHOD(December12_AoC_test)
		{
            ConnectionMap connections;
            connections.emplace(0, std::set<int>({ 2 }));
            connections.emplace(1, std::set<int>({ 1 }));
            connections.emplace(2, std::set<int>({ 0, 3, 4 }));
            connections.emplace(3, std::set<int>({ 2, 4 }));
            connections.emplace(5, std::set<int>({ 6 }));
            connections.emplace(6, std::set<int>({ 4, 5 }));

			ConnectionManager test(connections);
			Assert::AreEqual(6, test.GetGroupSize(0));
		}
	};
}
