#pragma once

#include <list>
#include <utility>

#include "SnakeInterface.hpp"

namespace Snake
{

    class SnakeSegment
    {
        
    private:
        struct Segment
        {
            int x;
            int y;
        };
        std::list<Segment> m_snakeSegmentList;

    public:
        SnakeSegment(/* args */);
        ~SnakeSegment();
        void addSnakeSegment(int x, int y);
        bool checkIfSnakeHaveSegmentAtPosition(int x, int y) const;
        DisplayInd returnLastSegmentCordinates();
        DisplayInd addNewHedAndReturnDispCordinates(std::pair<int, int> newHead);
        std::pair<int, int> returnCurrentHeadCords();
    };

}
