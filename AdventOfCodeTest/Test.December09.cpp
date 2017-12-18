#include "stdafx.h"
#include "CppUnitTest.h"
#include "../AdventOfCode/December09.h"

namespace AdventOfCodeTest
{
    using namespace Microsoft::VisualStudio::CppUnitTestFramework;
    using namespace AdventOfCode::December09;

    TEST_CLASS(Test_December09)
	{
	public:
		//----------------------------------
		// StreamObject
		//----------------------------------
		/*
		single element
		*/
		TEST_METHOD(December09_StreamObject_GetScore_none)
		{
			StreamObject test(ObjectType::OT_ROOT, nullptr);
			Assert::AreEqual(0, test.GetScore());
		}

		TEST_METHOD(December09_StreamObject_GetScore_group)
		{
			StreamObject test(ObjectType::OT_GROUP, nullptr);
			Assert::AreEqual(1, test.GetScore());
		}

		TEST_METHOD(December09_StreamObject_GetScore_garbage)
		{
			StreamObject test(ObjectType::OT_GARBAGE, nullptr);
			Assert::AreEqual(0, test.GetScore());
		}

		/*
		nested groups element
		*/
		TEST_METHOD(December09_StreamObject_GetScore_groupInNone)
		{
			std::shared_ptr<StreamObject> root = std::make_shared<StreamObject>(ObjectType::OT_ROOT, nullptr);
			std::shared_ptr<StreamObject> group1 = std::make_shared<StreamObject>(ObjectType::OT_GROUP, root);
			std::shared_ptr<StreamObject> group2 = std::make_shared<StreamObject>(ObjectType::OT_GROUP, root);
			root->AddChild(group1);
			root->AddChild(group2);

			Assert::AreEqual(2, root->GetScore());
		}

		TEST_METHOD(December09_StreamObject_GetScore_groupInGroup)
		{
			std::shared_ptr<StreamObject> root = std::make_shared<StreamObject>(ObjectType::OT_GROUP, nullptr);
			std::shared_ptr<StreamObject> group1 = std::make_shared<StreamObject>(ObjectType::OT_GROUP, root);
			root->AddChild(group1);
			std::shared_ptr<StreamObject> group2 = std::make_shared<StreamObject>(ObjectType::OT_GROUP, group1);
			group1->AddChild(group2);

			Assert::AreEqual(6, root->GetScore());
		}

		TEST_METHOD(December09_StreamObject_GetScore_groupInGarbage)
		{
			std::shared_ptr<StreamObject> root = std::make_shared<StreamObject>(ObjectType::OT_GARBAGE, nullptr);
			std::shared_ptr<StreamObject> group1 = std::make_shared<StreamObject>(ObjectType::OT_GROUP, root);
			root->AddChild(group1);
			std::shared_ptr<StreamObject> group2 = std::make_shared<StreamObject>(ObjectType::OT_GROUP, group1);
			group1->AddChild(group2);

			Assert::AreEqual(0, root->GetScore());
		}

		//----------------------------------
		// StreamOfChars
		//----------------------------------
		TEST_METHOD(December09_GetGroupScore_empty)
		{
			StreamOfChars test(std::stringstream(""));
			Assert::AreEqual(0, test.GetGroupScore());
		}

		TEST_METHOD(December09_GetGroupScore_UnclosedGroup)
		{
			StreamOfChars test(std::stringstream("{abc<a>!}"));
			Assert::AreEqual(0, test.GetGroupScore());
		}


		TEST_METHOD(December09_GetGroupScore_UnopenedGroup)
		{
			StreamOfChars test(std::stringstream("}}}}"));
			Assert::AreEqual(0, test.GetGroupScore());
		}

		TEST_METHOD(December09_GetGroupScore_GarbageOnly)
		{
			StreamOfChars test(std::stringstream("<{ab}!>{{}{}{}>"));
			Assert::AreEqual(0, test.GetGroupScore());
		}

		//----------------------------------------
		// Advent of Code samples
		//----------------------------------------
		/*
		{}, score of 1.
		*/
		TEST_METHOD(December09_AoC_test1)
		{
			StreamOfChars test(std::stringstream("{}"));
			Assert::AreEqual(1, test.GetGroupScore());
		}

		/*
		{{{}}}, score of 1 + 2 + 3 = 6.
		*/
		TEST_METHOD(December09_AoC_test2)
		{
			StreamOfChars test(std::stringstream("{{{}}}"));
			Assert::AreEqual(6, test.GetGroupScore());
		}

		/*
		{{},{}}, score of 1 + 2 + 2 = 5.
		*/
		TEST_METHOD(December09_AoC_test3)
		{
			StreamOfChars test(std::stringstream("{{},{}}"));
			Assert::AreEqual(5, test.GetGroupScore());
		}

		/*
		{{{},{},{{}}}}, score of 1 + 2 + 3 + 3 + 3 + 4 = 16.
		*/
		TEST_METHOD(December09_AoC_test4)
		{
			StreamOfChars test(std::stringstream("{{{},{},{{}}}}"));
			Assert::AreEqual(16, test.GetGroupScore());
		}

		/*
		{<a>,<a>,<a>,<a>}, score of 1.
		*/
		TEST_METHOD(December09_AoC_test5)
		{
			StreamOfChars test(std::stringstream("{<a>,<a>,<a>,<a>}"));
			Assert::AreEqual(1, test.GetGroupScore());
		}

		/*
		{{<ab>},{<ab>},{<ab>},{<ab>}}, score of 1 + 2 + 2 + 2 + 2 = 9.
		*/
		TEST_METHOD(December09_AoC_test6)
		{
			StreamOfChars test(std::stringstream("{{<ab>},{<ab>},{<ab>},{<ab>}}"));
			Assert::AreEqual(9, test.GetGroupScore());
		}

		/*
		{{<!!>},{<!!>},{<!!>},{<!!>}}, score of 1 + 2 + 2 + 2 + 2 = 9.
		*/
		TEST_METHOD(December09_AoC_test7)
		{
			StreamOfChars test(std::stringstream("{{<!!>},{<!!>},{<!!>},{<!!>}}"));
			Assert::AreEqual(9, test.GetGroupScore());
		}

		/*
		{{<a!>},{<a!>},{<a!>},{<ab>}}, score of 1 + 2 = 3.
		*/
		TEST_METHOD(December09_AoC_test8)
		{
			StreamOfChars test(std::stringstream("{{<a!>},{<a!>},{<a!>},{<ab>}}"));
			Assert::AreEqual(3, test.GetGroupScore());
		}
	};
}
