#include "stdafx.h"
#include "CppUnitTest.h"
#include "../AdventOfCode/December07.h"

namespace AdventOfCodeTest
{
    using namespace Microsoft::VisualStudio::CppUnitTestFramework;
    using namespace AdventOfCode::December07;

	TEST_CLASS(Test_December07)
	{
	public:
		// -----------------------------------------
		// Program
		// -----------------------------------------
		/*
		create a program without parent or children
		*/
		TEST_METHOD(December07_CreateProgram_empty)
		{
			Program test = Program("test", 5);
			Assert::AreEqual(false, test.IsValid());

			std::vector<std::string> temp;
			Assert::AreEqual(false, test.HasCircularDependency(temp));
		}

		/*
		create valid program
		*/
		TEST_METHOD(December07_CreateProgram_validLeaf)
		{
			std::shared_ptr<Program> parent = std::make_shared<Program>("parent", 333);
			std::shared_ptr<Program> child = std::make_shared<Program>("child", 2);
			child->SetParent(parent);

			Assert::AreEqual(true, child->IsValid());
			std::vector<std::string> temp;
			Assert::AreEqual(false, parent->HasCircularDependency(temp));
		}

		/*
		create valid program
		*/
		TEST_METHOD(December07_CreateProgram_validNode)
		{
			std::shared_ptr<Program> parent = std::make_shared<Program>("ppp", 4);
			std::shared_ptr<Program> test = std::make_shared<Program>("test", 4);
			std::shared_ptr<Program> child1 = std::make_shared<Program>("cc1", 4);
			std::shared_ptr<Program> child2 = std::make_shared<Program>("cc2", 4);
			test->SetParent(parent);
			test->AddChild(child1);
			test->AddChild(child2);

			Assert::AreEqual(true, test->IsValid());
			std::vector<std::string> temp;
			Assert::AreEqual(false, parent->HasCircularDependency(temp));
		}

		/*
		create a program that has itself as its parent
		*/
		TEST_METHOD(December07_CreateProgram_selfAsParent)
		{
			std::shared_ptr<Program> test = std::make_shared<Program>("blubb", 95);
			test->SetParent(test);

			Assert::AreEqual(false, test->IsValid());
		}

		/*
		create a program that has itself as one of its children
		*/
		TEST_METHOD(December07_CreateProgram_selfAsChild)
		{
			std::shared_ptr<Program> test1 = std::make_shared<Program>("xyz", 67432);
			std::shared_ptr<Program> test2 = std::make_shared<Program>("xyz", 67432);
			test2->SetParent(test1);
			test1->AddChild(test2);
			test1->AddChild(test1);

			Assert::AreEqual(false, test2->IsValid());
			std::vector<std::string> temp;
			Assert::AreEqual(true, test1->HasCircularDependency(temp));
		}

        // -----------------------------------------
        // Program::GetTreeWeight
        // -----------------------------------------
        /*
        tree consisting of a single node
        */
        TEST_METHOD(December07_GetTreeWeight_single)
        {
            Program test = Program("test", 17);
            Assert::AreEqual(17, test.GetTreeWeight());
        }

        /*
        small tree with a single child
        */
        TEST_METHOD(December07_GetTreeWeight_oneChild)
        {
            std::shared_ptr<Program> parent = std::make_shared<Program>("parent", 53);
            std::shared_ptr<Program> child = std::make_shared<Program>("child", 3236);
            child->SetParent(parent);
            parent->AddChild(child);

            Assert::AreEqual(3236, child->GetTreeWeight());
            Assert::AreEqual(3289, parent->GetTreeWeight());
        }

        /*
        tree with several children
        */
        TEST_METHOD(December07_GetTreeWeight_multipleChildren)
        {
            std::shared_ptr<Program> parent = std::make_shared<Program>("bla", 0);
            std::shared_ptr<Program> child1 = std::make_shared<Program>("foo", 86);
            std::shared_ptr<Program> child2 = std::make_shared<Program>("bar", 3);
            std::shared_ptr<Program> child3 = std::make_shared<Program>("baz", 98);
            child1->SetParent(parent);
            child2->SetParent(parent);
            child3->SetParent(parent);
            parent->AddChild(child1);
            parent->AddChild(child2);
            parent->AddChild(child3);

            Assert::AreEqual(187, parent->GetTreeWeight());
        }

        /*
        recursive tree weight
        */
        TEST_METHOD(December07_GetTreeWeight_recursive)
        {
            std::shared_ptr<Program> parent = std::make_shared<Program>("abc", 7);
            std::shared_ptr<Program> child = std::make_shared<Program>("def", 6);
            std::shared_ptr<Program> grandchild = std::make_shared<Program>("ghi", 13);
            std::shared_ptr<Program> greatgrandchild = std::make_shared<Program>("jkl", 5);
            child->SetParent(parent);
            parent->AddChild(child);
            grandchild->SetParent(child);
            child->AddChild(grandchild);
            greatgrandchild->SetParent(grandchild);
            grandchild->AddChild(greatgrandchild);

            Assert::AreEqual(31, parent->GetTreeWeight());
        }

        // -----------------------------------------
        // IsBalancedSubTree
        // -----------------------------------------
        /*
        tree consisting of a single node
        */
        TEST_METHOD(December07_IsBalancedSubTree_single)
        {
            Program test = Program("guaz", 6);
            Assert::AreEqual(true, test.IsBalancedSubTree());
        }

        /*
        single child -> always balanced
        */
        TEST_METHOD(December07_IsBalancedSubTree_oneChild)
        {
            std::shared_ptr<Program> parent = std::make_shared<Program>("ztlksg", 62);
            std::shared_ptr<Program> child = std::make_shared<Program>("lafk", 18);
            child->SetParent(parent);
            parent->AddChild(child);

            Assert::AreEqual(true, parent->IsBalancedSubTree());
        }

        /*
        two children with equal weight
        */
        TEST_METHOD(December07_IsBalancedSubTree_twoChildren_balanced)
        {
            std::shared_ptr<Program> parent = std::make_shared<Program>("blue", 5);
            std::shared_ptr<Program> child1 = std::make_shared<Program>("red", 99);
            std::shared_ptr<Program> child2 = std::make_shared<Program>("green", 99);
            child1->SetParent(parent);
            parent->AddChild(child1);
            child2->SetParent(parent);
            parent->AddChild(child2);

            Assert::AreEqual(true, parent->IsBalancedSubTree());
        }

        /*
        two children with different weight
        */
        TEST_METHOD(December07_IsBalancedSubTree_twoChildren_unbalanced)
        {
            std::shared_ptr<Program> parent = std::make_shared<Program>("test", 17);
            std::shared_ptr<Program> child1 = std::make_shared<Program>("testa", 8);
            std::shared_ptr<Program> child2 = std::make_shared<Program>("testb", 9);
            child1->SetParent(parent);
            parent->AddChild(child1);
            child2->SetParent(parent);
            parent->AddChild(child2);

            Assert::AreEqual(false, parent->IsBalancedSubTree());
        }

        /*
        balanced subtree
        */
        TEST_METHOD(December07_IsBalancedSubTree_balancedSubTree)
        {
            std::shared_ptr<Program> parent = std::make_shared<Program>("abc", 1);
            std::shared_ptr<Program> child1 = std::make_shared<Program>("de", 36);
            std::shared_ptr<Program> child2 = std::make_shared<Program>("fg", 5);
            std::shared_ptr<Program> grandchild = std::make_shared<Program>("h", 31);
            child1->SetParent(parent);
            parent->AddChild(child1);
            child2->SetParent(parent);
            parent->AddChild(child2);
            grandchild->SetParent(child2);
            child2->AddChild(grandchild);

            Assert::AreEqual(true, parent->IsBalancedSubTree());
        }

        /*
        unbalanced subtree
        */
        TEST_METHOD(December07_IsBalancedSubTree_unbalancedSubTree)
        {
            std::shared_ptr<Program> parent = std::make_shared<Program>("abc", 54);
            std::shared_ptr<Program> child1 = std::make_shared<Program>("de", 21);
            std::shared_ptr<Program> child2 = std::make_shared<Program>("fg", 21);
            std::shared_ptr<Program> grandchild = std::make_shared<Program>("h", 2);
            child1->SetParent(parent);
            parent->AddChild(child1);
            child2->SetParent(parent);
            parent->AddChild(child2);
            grandchild->SetParent(child2);
            child2->AddChild(grandchild);

            Assert::AreEqual(false, parent->IsBalancedSubTree());
        }

        // -----------------------------------------
        // GetUnbalancedNode
        // -----------------------------------------
        /*
        tree consisting of a single node
        */
        TEST_METHOD(December07_GetUnbalancedNode_single)
        {
            Program test = Program("hgal", 879);
            std::shared_ptr<Program> node;
            // already balanced
            Assert::AreEqual(false, test.GetUnbalancedNode(node));
        }

        /*
        single child -> always balanced
        */
        TEST_METHOD(December07_GetUnbalancedNode_oneChild)
        {
            std::shared_ptr<Program> parent = std::make_shared<Program>("test", 2);
            std::shared_ptr<Program> child = std::make_shared<Program>("testi", 33);
            child->SetParent(parent);
            parent->AddChild(child);

            std::shared_ptr<Program> node;
            // already balanced
            Assert::AreEqual(false, parent->GetUnbalancedNode(node));
        }

        /*
        two children with equal weight
        */
        TEST_METHOD(December07_GetUnbalancedNode_twoChildren_balanced)
        {
            std::shared_ptr<Program> parent = std::make_shared<Program>("bla", 96);
            std::shared_ptr<Program> child1 = std::make_shared<Program>("blubb", 4);
            std::shared_ptr<Program> child2 = std::make_shared<Program>("blargh", 4);
            child1->SetParent(parent);
            parent->AddChild(child1);
            child2->SetParent(parent);
            parent->AddChild(child2);

            std::shared_ptr<Program> node;
            // already balanced
            Assert::AreEqual(false, parent->GetUnbalancedNode(node));
        }

        /*
        two children with different weight
        */
        TEST_METHOD(December07_GetUnbalancedNode_twoChildren_unbalanced)
        {
            std::shared_ptr<Program> parent = std::make_shared<Program>("ghkj", 5);
            std::shared_ptr<Program> child1 = std::make_shared<Program>("ajkh", 13);
            std::shared_ptr<Program> child2 = std::make_shared<Program>("gzts", 21);
            child1->SetParent(parent);
            parent->AddChild(child1);
            child2->SetParent(parent);
            parent->AddChild(child2);

            std::shared_ptr<Program> node;
            Assert::AreEqual(true, parent->GetUnbalancedNode(node));
            Assert::AreEqual("ghkj", node->GetName().c_str());
        }

        /*
        balanced subtree
        */
        TEST_METHOD(December07_GetUnbalancedNode_balancedSubTree)
        {
            std::shared_ptr<Program> parent = std::make_shared<Program>("abc", 1000);
            std::shared_ptr<Program> child1 = std::make_shared<Program>("de", 16);
            std::shared_ptr<Program> child2 = std::make_shared<Program>("fg", 9);
            std::shared_ptr<Program> grandchild = std::make_shared<Program>("h", 7);
            child1->SetParent(parent);
            parent->AddChild(child1);
            child2->SetParent(parent);
            parent->AddChild(child2);
            grandchild->SetParent(child2);
            child2->AddChild(grandchild);

            std::shared_ptr<Program> node;
            // already balanced
            Assert::AreEqual(false, parent->GetUnbalancedNode(node));
        }

        /*
        unbalanced subtree
        */
        TEST_METHOD(December07_GetUnbalancedNode_unbalancedSubTree)
        {
            std::shared_ptr<Program> parent = std::make_shared<Program>("lgh", 54);
            std::shared_ptr<Program> child1 = std::make_shared<Program>("uz", 21);
            std::shared_ptr<Program> child2 = std::make_shared<Program>("agag", 21);
            std::shared_ptr<Program> grandchild = std::make_shared<Program>("ghs", 2);
            child1->SetParent(parent);
            parent->AddChild(child1);
            child2->SetParent(parent);
            parent->AddChild(child2);
            grandchild->SetParent(child2);
            child2->AddChild(grandchild);

            std::shared_ptr<Program> node;
            Assert::AreEqual(true, parent->GetUnbalancedNode(node));
            Assert::AreEqual("lgh", node->GetName().c_str());
        }

        // -----------------------------------------
        // ParseDataFromLine
        // -----------------------------------------
        /*
        try to parse an empty line
        */
        TEST_METHOD(December07_ParseDataFromLine_empty)
        {
            ProgramData test;
            bool result = ProgramTree::ParseDataFromLine("", test);

            Assert::AreEqual(false, result);
            Assert::AreEqual(ProgramData().name, test.name);
            Assert::AreEqual(ProgramData().weight, test.weight);
            Assert::AreEqual(true, test.subProgramNames.empty());
        }

        /*
        invalid string (missing the key)
        */
        TEST_METHOD(December07_ParseDataFromLine_missingKey)
        {
            ProgramData test;
            bool result = ProgramTree::ParseDataFromLine("    (23) -> x, y, xyzzy", test);

            Assert::AreEqual(false, result);
            Assert::AreEqual(ProgramData().name, test.name);
            Assert::AreEqual(ProgramData().weight, test.weight);
            Assert::AreEqual(true, test.subProgramNames.empty());
        }

        /*
        invalid string (missing the weight)
        */
        TEST_METHOD(December07_ParseDataFromLine_missingWeight)
        {
            ProgramData test;
            bool result = ProgramTree::ParseDataFromLine("abc -> def", test);

            Assert::AreEqual(false, result);
            Assert::AreEqual(ProgramData().name, test.name);
            Assert::AreEqual(ProgramData().weight, test.weight);
            Assert::AreEqual(true, test.subProgramNames.empty());
        }

        /*
        invalid string (missing the brackets around the weight)
        */
        TEST_METHOD(December07_ParseDataFromLine_missingWeightBrackets)
        {
            ProgramData test;
            bool result = ProgramTree::ParseDataFromLine("hfhjhg 44 -> rzu", test);

            Assert::AreEqual(false, result);
            Assert::AreEqual(ProgramData().name, test.name);
            Assert::AreEqual(ProgramData().weight, test.weight);
            Assert::AreEqual(true, test.subProgramNames.empty());
        }

        /*
        invalid string (missing the suffix after the -> signal)
        */
        TEST_METHOD(December07_ParseDataFromLine_missingSuffix)
        {
            ProgramData test;
            bool result = ProgramTree::ParseDataFromLine("test (81) ->  ", test);

            Assert::AreEqual(false, result);
            Assert::AreEqual(ProgramData().name, test.name);
            Assert::AreEqual(ProgramData().weight, test.weight);
            Assert::AreEqual(true, test.subProgramNames.empty());
        }

        /*
        invalid string (suffix contains empty strings)
        */
        TEST_METHOD(December07_ParseDataFromLine_emptySuffixElements)
        {
            ProgramData test;
            bool result = ProgramTree::ParseDataFromLine("bla (474) -> abc, , , , qwrtz ", test);

            Assert::AreEqual(false, result);
            Assert::AreEqual(ProgramData().name, test.name);
            Assert::AreEqual(ProgramData().weight, test.weight);
            Assert::AreEqual(true, test.subProgramNames.empty());
        }

        /*
        parse valid format (without specifying children)
        */
        TEST_METHOD(December07_ParseDataFromLine_noChildren)
        {
            ProgramData test;
            bool result = ProgramTree::ParseDataFromLine("blubb (5795)", test);

            Assert::AreEqual(true, result);
            Assert::AreEqual("blubb", test.name.c_str());
            Assert::AreEqual(5795, test.weight);
            Assert::AreEqual(true, test.subProgramNames.empty());
        }

        /*
        parse valid format (with specified children)
        */
        TEST_METHOD(December07_ParseDataFromLine_withChildren)
        {
            ProgramData test;
            bool result = ProgramTree::ParseDataFromLine("foo (9) -> bar, baz, foobar", test);

            Assert::AreEqual(true, result);
            Assert::AreEqual("foo", test.name.c_str());
            Assert::AreEqual(9, test.weight);
            Assert::AreEqual(3, (int)test.subProgramNames.size());

            Assert::AreEqual("bar", test.subProgramNames[0].c_str());
            Assert::AreEqual("baz", test.subProgramNames[1].c_str());
            Assert::AreEqual("foobar", test.subProgramNames[2].c_str());
        }

        // -----------------------------------------
		// ProgramTree
		// -----------------------------------------
		/*
		create the tree with empty data
		*/
		TEST_METHOD(December07_CreateProgramTree_empty)
		{
			std::vector<ProgramData> list;

			ProgramTree test(list);
			Assert::AreEqual(true, test.IsValid());
			Assert::AreEqual(0, test.GetSize());
			Assert::AreEqual(false, test.ContainsCircularDependency());
		}

		/*
		create a "tree" with a single element
		*/
		TEST_METHOD(December07_CreateProgramTree_single)
		{
			std::vector<ProgramData> list;
			list.push_back(ProgramData("xyzzy", 66, {}));

			ProgramTree test(list);
			Assert::AreEqual(true, test.IsValid());
			Assert::AreEqual(1, test.GetSize());
			Assert::AreEqual(false, test.ContainsCircularDependency());
		}

		/*
		create a "tree" with a single invalid element
		*/
		TEST_METHOD(December07_CreateProgramTree_singleInvalid)
		{
			std::vector<ProgramData> list;
			list.push_back(ProgramData("", 700, {}));

			ProgramTree test(list);
			Assert::AreEqual(false, test.IsValid());
			Assert::AreEqual(false, test.ContainsCircularDependency());
		}

		/*
		create a "tree" with invalid elements
		*/
		TEST_METHOD(December07_CreateProgramTree_invalidElement)
		{
			std::vector<ProgramData> list;
			list.push_back(ProgramData("hjkl", 3, {"yubn"}));
			list.push_back(ProgramData("yubn", -1, {}));

			ProgramTree test(list);
			Assert::AreEqual(false, test.IsValid());
			Assert::AreEqual(false, test.ContainsCircularDependency());
		}

		/*
		create a "tree" with two non-connected branches
		*/
		TEST_METHOD(December07_CreateProgramTree_multiRoot)
		{
			std::vector<ProgramData> list;
			list.push_back(ProgramData("one", 11, {}));
			list.push_back(ProgramData("two", 4, {}));

			ProgramTree test(list);
			Assert::AreEqual(false, test.IsValid());
			Assert::AreEqual(2, test.GetSize());
			Assert::AreEqual(false, test.ContainsCircularDependency());
		}

		/*
		create a "tree" with circular dependency
		*/
		TEST_METHOD(December07_CreateProgramTree_circular)
		{
			std::vector<ProgramData> list;
			list.push_back(ProgramData("red", 1, {"green"}));
			list.push_back(ProgramData("blue", 99, {"red"}));
			list.push_back(ProgramData("green", 15, { "red" }));

			ProgramTree test(list);
			Assert::AreEqual(false, test.IsValid());
			Assert::AreEqual(true, test.ContainsCircularDependency());
		}

		/*
		create a small tree
		*/
		TEST_METHOD(December07_CreateProgramTree_smallTree)
		{
			std::vector<ProgramData> list;
			list.push_back(ProgramData("test", 19, {}));
			list.push_back(ProgramData("bla", 24, {"test"}));
			list.push_back(ProgramData("foo", 8, { "bla", "baz" }));
			list.push_back(ProgramData("baz", 19, {}));

			ProgramTree test(list);
			Assert::AreEqual(true, test.IsValid());
			Assert::AreEqual(4, test.GetSize());
			Assert::AreEqual("foo", test.GetRoot()->GetName().c_str());
		}

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

		In this example, tknk is at the bottom of the tower (the bottom program), and is holding up ugml, padx, and fwft. 
		*/
		TEST_METHOD(December07_AoC_test)
		{
			std::vector<ProgramData> list;
			list.push_back(ProgramData("pbga", 66, {}));
			list.push_back(ProgramData("xhth", 57, {}));
			list.push_back(ProgramData("ebii", 61, {}));
			list.push_back(ProgramData("havc", 66, {}));
			list.push_back(ProgramData("ktlj", 57, {}));
			list.push_back(ProgramData("fwft", 72, {"ktlj", "cntj", "xhth"}));
			list.push_back(ProgramData("qoyq", 66, {}));
			list.push_back(ProgramData("padx", 45, {"pbga", "havc", "qoyq"}));
			list.push_back(ProgramData("tknk", 41, { "ugml", "padx", "fwft" }));
			list.push_back(ProgramData("jptl", 61, {}));
			list.push_back(ProgramData("ugml", 68, {"gyxo", "ebii", "jptl"}));
			list.push_back(ProgramData("gyxo", 61, {}));
			list.push_back(ProgramData("cntj", 57, {}));

			ProgramTree test(list);
			Assert::AreEqual(true, test.IsValid());
			Assert::AreEqual("tknk", test.GetRoot()->GetName().c_str());
		}
	};
}
