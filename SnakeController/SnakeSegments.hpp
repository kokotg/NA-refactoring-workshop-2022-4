#pragma once
#include <list>
#include "SnakeInterface.hpp"
#include "IEventHandler.hpp"

class SnakeSegments

{
    public:
     struct Segment
    {
        int x;
        int y;
    };

    std::list<Segment> m_segments;
    Snake::Direction m_currentDirection;

    bool isSegmentAtPosition(int x, int y) const;




};