#include <algorithm>

#include "SnakeSegments.hpp"


namespace Snake
{

     SnakeSegment::SnakeSegment(/* args */)
     {
     }

    SnakeSegment::~SnakeSegment()
    {
    }

    void SnakeSegment::addSnakeSegment(int x, int y)
    {
        Segment seg;
        seg.x = x;
        seg.y = y;
        m_snakeSegmentList.push_back(seg);
    }

    bool SnakeSegment::checkIfSnakeHaveSegmentAtPosition(int x, int y) const
    {
        return m_snakeSegmentList.end() != std::find_if(m_snakeSegmentList.cbegin(), m_snakeSegmentList.cend(),
                                                        [x, y](auto const &segment)
                                                        { return segment.x == x and segment.y == y; });
    }

    DisplayInd SnakeSegment::returnLastSegmentCordinates()
    {
        DisplayInd dispInd;
        auto tail = m_snakeSegmentList.back();
        dispInd.x = tail.x;
        dispInd.y = tail.y;
        dispInd.value = Cell_FREE;
        m_snakeSegmentList.pop_back();
        return dispInd;
    }

    DisplayInd SnakeSegment::addNewHedAndReturnDispCordinates(std::pair<int, int> newHead)
    {
        DisplayInd dispInd;
        Segment newSegment;
        newSegment.x = newHead.first;
        newSegment.y = newHead.second;
        m_snakeSegmentList.push_front(newSegment);
        dispInd.x = newHead.first;
        dispInd.y = newHead.second;
        dispInd.value = Cell_SNAKE;
        return dispInd;
    }
    std::pair<int, int> SnakeSegment::returnCurrentHeadCords()
    {
        auto currentHead = m_snakeSegmentList.front();
        return std::make_pair(currentHead.x, currentHead.y);
    }
}