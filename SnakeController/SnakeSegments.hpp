#pragma once

#include <list>
#include "SnakeInterface.hpp"

namespace Snake
{
class SnakeSegments
{
    public:
    struct Segment
    {
        int x;
        int y;
    };
    std::list<Segment> m_segments;
    Direction m_currentDirection;
};
} // namespace Snake