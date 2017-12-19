#pragma once

#include <memory>
#include <sstream>
#include <vector>

#include "AdventOfCodeBase.h"

/*
    https://adventofcode.com/2017/day/9

    Part 1:

    you discover that it's a stream of characters.

    You sit for a while and record part of the stream (your puzzle input). The characters represent groups - sequences that begin with { and end with }. Within a group, there are zero or more other things, separated by commas: either another group or garbage. Since groups can contain other groups, a } only closes the most-recently-opened unclosed group - that is, they are nestable. Your puzzle input represents a single, large group which itself contains many smaller ones.

    Sometimes, instead of a group, you will find garbage. Garbage begins with < and ends with >. Between those angle brackets, almost any character can appear, including { and }. Within garbage, < has no special meaning.

    In a futile attempt to clean up the garbage, some program has canceled some of the characters within it using !: inside garbage, any character that comes after ! should be ignored, including <, >, and even another !.

    You don't see any characters that deviate from these rules. Outside garbage, you only find well-formed groups, and garbage always terminates according to the rules above.

    Here are some self-contained pieces of garbage:

        <>, empty garbage.
        <random characters>, garbage containing random characters.
        <<<<>, because the extra < are ignored.
        <{!>}>, because the first > is canceled.
        <!!>, because the second ! is canceled, allowing the > to terminate the garbage.
        <!!!>>, because the second ! and the first > are canceled.
        <{o"i!a,<{i<a>, which ends at the first >.

    Here are some examples of whole streams and the number of groups they contain:

        {}, 1 group.
        {{{}}}, 3 groups.
        {{},{}}, also 3 groups.
        {{{},{},{{}}}}, 6 groups.
        {<{},{},{{}}>}, 1 group (which itself contains garbage).
        {<a>,<a>,<a>,<a>}, 1 group.
        {{<a>},{<a>},{<a>},{<a>}}, 5 groups.
        {{<!>},{<!>},{<!>},{<a>}}, 2 groups (since all but the last > are canceled).

    Your goal is to find the total score for all groups in your input. Each group is assigned a score which is one more than the score of the group that immediately contains it. (The outermost group gets a score of 1.)

        {}, score of 1.
        {{{}}}, score of 1 + 2 + 3 = 6.
        {{},{}}, score of 1 + 2 + 2 = 5.
        {{{},{},{{}}}}, score of 1 + 2 + 3 + 3 + 3 + 4 = 16.
        {<a>,<a>,<a>,<a>}, score of 1.
        {{<ab>},{<ab>},{<ab>},{<ab>}}, score of 1 + 2 + 2 + 2 + 2 = 9.
        {{<!!>},{<!!>},{<!!>},{<!!>}}, score of 1 + 2 + 2 + 2 + 2 = 9.
        {{<a!>},{<a!>},{<a!>},{<ab>}}, score of 1 + 2 = 3.

    What is the total score for all groups in your input?
*/

namespace AdventOfCode {
namespace December09 {

	enum ObjectType
	{
		OT_ROOT,
		OT_GROUP,
		OT_GARBAGE
	};

	class StreamObject
	{
	public:
		StreamObject(ObjectType type, std::shared_ptr<StreamObject> parent);
        ~StreamObject() = default;

	public:
		std::shared_ptr<StreamObject> GetParent() const { return m_parent; }
		bool GetIsRoot() const { return m_objectType == OT_ROOT; }
		bool GetIsGroup() const { return m_objectType == OT_GROUP; }
		bool GetIsGarbage() const { return m_objectType == OT_GARBAGE; }
        int GetContentSize() const { return static_cast<int>(m_content.length()); }
        
        int GetScore(int parentScore = 0) const;
        int GetGarbageCount() const;

		void AddChild(std::shared_ptr<StreamObject>);
		void RemoveChild(std::shared_ptr<StreamObject>);
        void AddChar(char c);

	private:
		ObjectType m_objectType = OT_ROOT;
		std::vector<std::shared_ptr<StreamObject>> m_children;
		std::shared_ptr<StreamObject> m_parent;
        std::string m_content;
	};

	class StreamOfChars
        : protected AdventOfCodeBase
	{
	public:
        StreamOfChars() {};
		StreamOfChars(const std::stringstream& stream);
        StreamOfChars(const std::string& fileName);
        ~StreamOfChars() = default;

    public:
        // AdventOfCodeBase
        virtual bool ParseLine(const std::string& inputLine) override;
        virtual void OutputResultToConsole() const override;
        // ~AdventOfCodeBase

	public:
		virtual void ProcessStream(const std::stringstream& stream);
		int GetGroupScore() const;

	protected:
		std::shared_ptr<StreamObject> m_streamStack;
	};

}}
