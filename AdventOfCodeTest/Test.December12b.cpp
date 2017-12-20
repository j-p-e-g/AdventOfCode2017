#include "stdafx.h"
#include "CppUnitTest.h"
#include "../AdventOfCode/December12b.h"

namespace AdventOfCodeTest
{
    using namespace Microsoft::VisualStudio::CppUnitTestFramework;
    using namespace AdventOfCode::December12;

    TEST_CLASS(Test_December12b)
    {
    public:
        /*
        empty connections list
        */
        TEST_METHOD(December12b_GetNumberOfGroups_empty)
        {
            ConnectionMap connections;

            ConnectionManagerB test(connections);
            Assert::AreEqual(0, test.GetNumberOfGroups());
        }

        /*
        single element
        */
        TEST_METHOD(December12b_GetNumberOfGroups_single)
        {
            ConnectionMap connections;
            connections.emplace(2, std::set<int>({ 2 }));

            ConnectionManagerB test(connections);
            Assert::AreEqual(1, test.GetNumberOfGroups());
        }

        /*
        single connected group
        */
        TEST_METHOD(December12b_GetNumberOfGroups_singleGroup)
        {
            ConnectionMap connections;
            connections.emplace(2, std::set<int>({ 2, 5, 7 }));
            connections.emplace(7, std::set<int>({ 3, 8 }));
            connections.emplace(9, std::set<int>({ 3 }));

            ConnectionManagerB test(connections);
            Assert::AreEqual(1, test.GetNumberOfGroups());
        }

        /*
        all elements are loners
        */
        TEST_METHOD(December12b_GetNumberOfGroups_allSeparate)
        {
            ConnectionMap connections;
            connections.emplace(2, std::set<int>({ 2 }));
            connections.emplace(5, std::set<int>({}));
            connections.emplace(24, std::set<int>({ 24 }));

            ConnectionManagerB test(connections);
            Assert::AreEqual(3, test.GetNumberOfGroups());
        }

        /*
        0 <-> 2
        1 <-> 1
        2 <-> 0, 3, 4
        3 <-> 2, 4
        4 <-> 2, 3, 6
        5 <-> 6
        6 <-> 4, 5

        In the example above, there were 2 groups: one consisting of programs 0,2,3,4,5,6, and the other consisting solely of program 1.
        */
        TEST_METHOD(December12b_GetNumberOfGroups_AoC_test)
        {
            ConnectionMap connections;
            connections.emplace(0, std::set<int>({ 2 }));
            connections.emplace(1, std::set<int>({ 1 }));
            connections.emplace(2, std::set<int>({ 0, 3, 4 }));
            connections.emplace(3, std::set<int>({ 2, 4 }));
            connections.emplace(5, std::set<int>({ 6 }));
            connections.emplace(6, std::set<int>({ 4, 5 }));

            ConnectionManagerB test(connections);
            Assert::AreEqual(2, test.GetNumberOfGroups());
        }
    };
}
