#include "stdafx.h"
#include "CppUnitTest.h"
#include "../AdventOfCode/December07.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

using namespace December07;

namespace AdventOfCodeTest
{
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
