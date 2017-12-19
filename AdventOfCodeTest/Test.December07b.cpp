#include "stdafx.h"
#include "CppUnitTest.h"
#include "../AdventOfCode/December07b.h"

namespace AdventOfCodeTest
{
    using namespace Microsoft::VisualStudio::CppUnitTestFramework;
    using namespace AdventOfCode::December07;

    TEST_CLASS(Test_December07b)
    {
    public:
        // ----------------------------------
        // ProgramTreeB: GetWeightForNode
        // ----------------------------------
        /*
        try to access non-existing node
        */
        TEST_METHOD(December07b_GetWeightForNode_nonExisting)
        {
            std::vector<ProgramData> list;
            ProgramTreeB test(list);

            Program undefined;
            Assert::AreEqual(undefined.GetWeight(), test.GetWeightForNode("hjklkahsjsdf"));
        }

        /*
        single node
        */
        TEST_METHOD(December07b_GetWeightForNode_single)
        {
            std::vector<ProgramData> list;
            list.push_back(ProgramData("qwertz", 20042, {}));

            ProgramTreeB test(list);
            Assert::AreEqual(20042, test.GetWeightForNode("qwertz"));
        }

        /*
        get weight for tree
        */
        TEST_METHOD(December07b_GetWeightForNode)
        {
            std::vector<ProgramData> list;
            list.push_back(ProgramData("test", 17, { "bla", "blubb" }));
            list.push_back(ProgramData("blubb", 1, {"testi"}));
            list.push_back(ProgramData("bla", 4, {}));
            list.push_back(ProgramData("testi", 56, {}));

            ProgramTreeB test(list);
            Assert::AreEqual(4, test.GetWeightForNode("bla"));
            Assert::AreEqual(57, test.GetWeightForNode("blubb"));
            Assert::AreEqual(78, test.GetWeightForNode("test"));
        }

        // ----------------------------------
        // GetUnbalancedNode
        // ----------------------------------
        /*
        empty tree
        */
        TEST_METHOD(December07b_GetUnbalancedNode_empty)
        {
            std::vector<ProgramData> list;
            ProgramTreeB test(list);

            std::shared_ptr<Program> node;
            // already balanced
            Assert::AreEqual(false, test.GetUnbalancedNode(node));
        }

        /*
        tree consisting of a single node
        */
        TEST_METHOD(December07b_GetUnbalancedNode_single)
        {
            std::vector<ProgramData> list;
            list.push_back(ProgramData("test", 256, {}));
            ProgramTreeB test(list);

            std::shared_ptr<Program> node;
            // already balanced
            Assert::AreEqual(false, test.GetUnbalancedNode(node));
        }

        /*
        single child -> always balanced
        */
        TEST_METHOD(December07_GetUnbalancedNode_oneChild)
        {
            std::vector<ProgramData> list;
            list.push_back(ProgramData("child", 16, {}));
            list.push_back(ProgramData("parent", 86, {"child"}));
            ProgramTreeB test(list);

            std::shared_ptr<Program> node;
            // already balanced
            Assert::AreEqual(false, test.GetUnbalancedNode(node));
        }

        /*
        two children with equal weight
        */
        TEST_METHOD(December07_GetUnbalancedNode_twoChildren_balanced)
        {
            std::vector<ProgramData> list;
            list.push_back(ProgramData("sgklh", 1, {}));
            list.push_back(ProgramData("izos", 2, { "sgklh", "ghajg" }));
            list.push_back(ProgramData("ghajg", 1, {}));
            ProgramTreeB test(list);

            std::shared_ptr<Program> node;
            // already balanced
            Assert::AreEqual(false, test.GetUnbalancedNode(node));
        }

        /*
        two children with different weight
        */
        TEST_METHOD(December07_GetUnbalancedNode_twoChildren_unbalanced)
        {
            std::vector<ProgramData> list;
            list.push_back(ProgramData("blue", 70, {}));
            list.push_back(ProgramData("red", 69, {}));
            list.push_back(ProgramData("green", 26, { "red", "blue" }));
            ProgramTreeB test(list);

            std::shared_ptr<Program> node;
            Assert::AreEqual(true, test.GetUnbalancedNode(node));
            Assert::AreEqual("green", node->GetName().c_str());
        }

        /*
        the tree is perfectly balanced
        */
        TEST_METHOD(December07b_GetUnbalancedNode_none)
        {
            std::vector<ProgramData> list;
            list.push_back(ProgramData("foo", 29, { "bla", "bar" }));
            list.push_back(ProgramData("bla", 8, {}));
            list.push_back(ProgramData("bar", 3, { "test" }));
            list.push_back(ProgramData("test", 5, {}));
            ProgramTreeB test(list);

            std::shared_ptr<Program> node;
            // already balanced
            Assert::AreEqual(false, test.GetUnbalancedNode(node));
        }

        /*
        root -> red / yellow / purple
        red : 15
        purple -> brown : 15
        yellow -> blue / green : 20
        */
        TEST_METHOD(December07b_GetUnbalancedNode_unbalanced)
        {
            std::vector<ProgramData> list;
            list.push_back(ProgramData("root", 29, { "red", "yellow" }));
            list.push_back(ProgramData("red", 15, {}));
            list.push_back(ProgramData("yellow", 2, { "blue", "green" }));
            list.push_back(ProgramData("blue", 7, {}));
            list.push_back(ProgramData("green", 6, {}));
            ProgramTreeB test(list);

            std::shared_ptr<Program> node;
            Assert::AreEqual(true, test.GetUnbalancedNode(node));
            Assert::AreEqual("yellow", node->GetName().c_str());
        }

        // ------------------------------
        // GetCorrectedWeightNode
        // -------------------------------
        /*
        single node -> already balanced
        */
        TEST_METHOD(December07b_GetCorrectedWeightNode_single)
        {
            std::vector<ProgramData> list;
            list.push_back(ProgramData("ghks", 15, {}));
            ProgramTreeB test(list);

            std::shared_ptr<Program> correctedNode;
            // already balanced
            Assert::AreEqual(false, test.GetCorrectedWeightNode(correctedNode));
        }

        /*
        balanced tree
        */
        TEST_METHOD(December07b_GetCorrectedWeightNode_balanced)
        {
            std::vector<ProgramData> list;
            list.push_back(ProgramData("ghks", 14, {}));
            list.push_back(ProgramData("shlsg", 27, {"zsg", "ghks"}));
            list.push_back(ProgramData("itr", 1, {}));
            list.push_back(ProgramData("zsg", 13, {"itr"}));
            ProgramTreeB test(list);

            std::shared_ptr<Program> correctedNode;
            // already balanced
            Assert::AreEqual(false, test.GetCorrectedWeightNode(correctedNode));
        }

        /*
        wildly unbalanced tree with more than 2 different sub-weights
        */
        TEST_METHOD(December07b_GetCorrectedWeightNode_incorrigible)
        {
            std::vector<ProgramData> list;
            list.push_back(ProgramData("a", 9, {}));
            list.push_back(ProgramData("b", 27, { "c", "a", "e" }));
            list.push_back(ProgramData("d", 2, {}));
            list.push_back(ProgramData("c", 23, { "d" }));
            list.push_back(ProgramData("e", 31, {}));
            ProgramTreeB test(list);

            std::shared_ptr<Program> correctedNode;
            // could not be corrected easily
            Assert::AreEqual(false, test.GetCorrectedWeightNode(correctedNode));
        }

        /*
        tree could only be balanced by assigning a negative weight
        */
        TEST_METHOD(December07b_GetCorrectedWeightNode_invalidCorrection)
        {
            std::vector<ProgramData> list;
            list.push_back(ProgramData("glorx", 194, {"bluut",  "flaz", "trisx" }));
            list.push_back(ProgramData("bluut", 10, {}));
            list.push_back(ProgramData("flaz", 3, { "sluit", "zkam" }));
            list.push_back(ProgramData("sluit", 7, {}));
            list.push_back(ProgramData("zkam", 7, {}));
            list.push_back(ProgramData("trisx", 10, {}));
            ProgramTreeB test(list);

            std::shared_ptr<Program> correctedNode;
            // could not be corrected easily
            Assert::AreEqual(false, test.GetCorrectedWeightNode(correctedNode));
            Assert::AreEqual(false, correctedNode->IsValid());
            Assert::AreEqual(-4, correctedNode->GetWeight());
        }

        /*
        root -> red / yellow / purple
        red : 15
        purple -> brown : 15
        yellow -> blue / green : 20 -> yellow needs to change to 3
        */
        TEST_METHOD(December07b_GetCorrectedWeightNode_unbalanced)
        {
            std::vector<ProgramData> list;
            list.push_back(ProgramData("root", 29, { "red", "yellow", "purple" }));
            list.push_back(ProgramData("red", 15, {}));
            list.push_back(ProgramData("purple", 5, { "brown" }));
            list.push_back(ProgramData("yellow", 8, { "blue", "green" }));
            list.push_back(ProgramData("blue", 6, {}));
            list.push_back(ProgramData("green", 6, {}));
            list.push_back(ProgramData("brown", 10, {}));
            ProgramTreeB test(list);

            std::shared_ptr<Program> correctedNode;
            Assert::AreEqual(true, test.GetCorrectedWeightNode(correctedNode));
            Assert::AreEqual("yellow", correctedNode->GetName().c_str());
            Assert::AreEqual(3, correctedNode->GetWeight());
        }

        // ---------------------------------------
        // Advent of code sample data
        // ---------------------------------------
        /*
        pbga (66)
        xhth (57)
        ebii (61)
        havc (66)
        ktlj (57)
        fwft (72) -> ktlj, cntj, xhth
        qoyq (66)
        padx (45) -> pbga, havc, qoyq
        tknk (41) -> ugml, padx, fwft
        jptl (61)
        ugml (68) -> gyxo, ebii, jptl
        gyxo (61)
        cntj (57)

        However, for tknk to be balanced, each of the programs standing on its disc and all programs above it must each match. This means that the following sums must all be the same:

        ugml + (gyxo + ebii + jptl) = 68 + (61 + 61 + 61) = 251
        padx + (pbga + havc + qoyq) = 45 + (66 + 66 + 66) = 243
        fwft + (ktlj + cntj + xhth) = 72 + (57 + 57 + 57) = 243
        */
        TEST_METHOD(December07b_AoC_GetWeightForNode)
        {
            std::vector<ProgramData> list;
            list.push_back(ProgramData("pbga", 66, {}));
            list.push_back(ProgramData("xhth", 57, {}));
            list.push_back(ProgramData("ebii", 61, {}));
            list.push_back(ProgramData("havc", 66, {}));
            list.push_back(ProgramData("ktlj", 57, {}));
            list.push_back(ProgramData("fwft", 72, { "ktlj", "cntj", "xhth" }));
            list.push_back(ProgramData("qoyq", 66, {}));
            list.push_back(ProgramData("padx", 45, { "pbga", "havc", "qoyq" }));
            list.push_back(ProgramData("tknk", 41, { "ugml", "padx", "fwft" }));
            list.push_back(ProgramData("jptl", 61, {}));
            list.push_back(ProgramData("ugml", 68, { "gyxo", "ebii", "jptl" }));
            list.push_back(ProgramData("gyxo", 61, {}));
            list.push_back(ProgramData("cntj", 57, {}));
            ProgramTreeB test(list);

            Assert::AreEqual(251, test.GetWeightForNode("ugml"));
            Assert::AreEqual(243, test.GetWeightForNode("padx"));
            Assert::AreEqual(243, test.GetWeightForNode("fwft"));
        }

        /*
        As you can see, tknk's disc is unbalanced: ugml's stack is heavier than the other two.
        */
        TEST_METHOD(December07b_AoC_GetUnbalancedNode)
        {
            std::vector<ProgramData> list;
            list.push_back(ProgramData("pbga", 66, {}));
            list.push_back(ProgramData("xhth", 57, {}));
            list.push_back(ProgramData("ebii", 61, {}));
            list.push_back(ProgramData("havc", 66, {}));
            list.push_back(ProgramData("ktlj", 57, {}));
            list.push_back(ProgramData("fwft", 72, { "ktlj", "cntj", "xhth" }));
            list.push_back(ProgramData("qoyq", 66, {}));
            list.push_back(ProgramData("padx", 45, { "pbga", "havc", "qoyq" }));
            list.push_back(ProgramData("tknk", 41, { "ugml", "padx", "fwft" }));
            list.push_back(ProgramData("jptl", 61, {}));
            list.push_back(ProgramData("ugml", 68, { "gyxo", "ebii", "jptl" }));
            list.push_back(ProgramData("gyxo", 61, {}));
            list.push_back(ProgramData("cntj", 57, {}));
            ProgramTreeB test(list);

            std::shared_ptr<Program> node;
            Assert::AreEqual(true, test.GetUnbalancedNode(node));
            Assert::AreEqual("tknk", node->GetName().c_str());
        }

        /*
        Even though the nodes above ugml are balanced, ugml itself is too heavy: it needs to be 8 units lighter for its stack to weigh 243 and keep the towers balanced. If this change were made, its weight would be 60.
        */
        TEST_METHOD(December07b_AoC_GetCorrectedWeightNode)
        {
            std::vector<ProgramData> list;
            list.push_back(ProgramData("pbga", 66, {}));
            list.push_back(ProgramData("xhth", 57, {}));
            list.push_back(ProgramData("ebii", 61, {}));
            list.push_back(ProgramData("havc", 66, {}));
            list.push_back(ProgramData("ktlj", 57, {}));
            list.push_back(ProgramData("fwft", 72, { "ktlj", "cntj", "xhth" }));
            list.push_back(ProgramData("qoyq", 66, {}));
            list.push_back(ProgramData("padx", 45, { "pbga", "havc", "qoyq" }));
            list.push_back(ProgramData("tknk", 41, { "ugml", "padx", "fwft" }));
            list.push_back(ProgramData("jptl", 61, {}));
            list.push_back(ProgramData("ugml", 68, { "gyxo", "ebii", "jptl" }));
            list.push_back(ProgramData("gyxo", 61, {}));
            list.push_back(ProgramData("cntj", 57, {}));
            ProgramTreeB test(list);

            std::shared_ptr<Program> correctedNode;
            Assert::AreEqual(true, test.GetCorrectedWeightNode(correctedNode));
            Assert::AreEqual("ugml", correctedNode->GetName().c_str());
            Assert::AreEqual(60, correctedNode->GetWeight());
        }
    };
}
