#pragma once

#include <memory>

#include "AdventOfCodeBase.h"

/*
    https://adventofcode.com/2017/day/16

    Part 1:

    You come upon a very unusual sight; a group of programs here appear to be dancing.

    There are sixteen programs in total, named a through p. They start by standing in a line: a stands in position 0, b stands in position 1, and so on until p, which stands in position 15.

    The programs' dance consists of a sequence of dance moves:

    Spin, written sX, makes X programs move from the end to the front, but maintain their order otherwise. (For example, s3 on abcde produces cdeab).
    Exchange, written xA/B, makes the programs at positions A and B swap places.
    Partner, written pA/B, makes the programs named A and B swap places.

        For example, with only five programs standing in a line (abcde), they could do the following dance:

        s1, a spin of size 1: eabcd.
        x3/4, swapping the last two programs: eabdc.
        pe/b, swapping programs e and b: baedc.

        After finishing their dance, the programs end up in order baedc.

    You watch the dance for a while and record their dance moves (your puzzle input). In what order are the programs standing after their dance?
*/

namespace AdventOfCode {
namespace December16 {

    class DancingMove
    {
    public:
        virtual bool IsValid() const;
        virtual bool ApplyMove(std::string& formation) const;
        virtual std::string GetCommand() const;
        virtual bool CanUndo(std::shared_ptr<DancingMove> other) const;
        virtual bool AffectsSameTarget(std::shared_ptr<DancingMove> other) const { return false; };
        std::string GetType() const { return m_type; }
        virtual int GetSize() const { return -1; }
        virtual int GetId1() const { return -1; }
        virtual int GetId2() const { return -1; }
        virtual char GetChar1() const { return '-'; }
        virtual char GetChar2() const { return '-'; }

    protected:
        std::string m_type = "";
    };

    class Spin 
        : public DancingMove
    {
    public:
        Spin(int _size)
        {
            m_size = _size;
            m_type = "Spin";
        }

        bool IsValid() const override;
        bool ApplyMove(std::string& formation) const override;
        std::string GetCommand() const override;
        virtual int GetSize() const override { return m_size; }

    private:
        int m_size;
    };

    class Exchange 
        : public DancingMove
    {
    public:
        Exchange(int _id1, int _id2)
        {
            m_id1 = _id1;
            m_id2 = _id2;
            m_type = "Exchange";
        }

        bool IsValid() const override;
        bool ApplyMove(std::string& formation) const override;
        std::string GetCommand() const override;
        bool CanUndo(std::shared_ptr<DancingMove> other) const override;
        bool AffectsSameTarget(std::shared_ptr<DancingMove> other) const override;
        int GetId1() const override { return m_id1; }
        int GetId2() const override { return m_id2; }

    private:
        int m_id1;
        int m_id2;
    };

    class Partner 
        : public DancingMove
    {
    public:
        Partner(int _char1, int _char2)
        {
            m_char1 = _char1;
            m_char2 = _char2;
            m_type = "Partner";
        }

        bool IsValid() const override;
        bool ApplyMove(std::string& formation) const override;
        std::string GetCommand() const override;
        bool CanUndo(std::shared_ptr<DancingMove> other) const override;
        bool AffectsSameTarget(std::shared_ptr<DancingMove> other) const override;
        char GetChar1() const override { return m_char1; }
        char GetChar2() const override { return m_char2; }

    private:
        int m_char1;
        int m_char2;
    };

    class ProgramDancingMaster
        : protected AdventOfCodeBase
    {
    public:
        ProgramDancingMaster(int size = 16);
        ProgramDancingMaster(const std::string& fileName, int size = 16);
        ~ProgramDancingMaster() = default;

    public:
        // AdventOfCodeBase
        virtual bool ParseLine(const std::string& inputLine) override;
        virtual void OutputResultToConsole() const override;
        // ~AdventOfCodeBase

    public:
        bool ParseDancingMove(const std::string& input, std::shared_ptr<DancingMove>& move);
        bool ApplyDancingMove(const std::shared_ptr<DancingMove>& move);
        std::string GetFinalFormation() const;

    protected:
        std::string m_dancingFormation;
    };

}}
