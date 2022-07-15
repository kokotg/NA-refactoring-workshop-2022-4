#pragma once

#include <list>
#include <memory>
#include <stdexcept>
#include <functional>

#include "IEventHandler.hpp"
#include "SnakeInterface.hpp"
#include "SnakeWorld.hpp"

class Event;
class IPort;

namespace Snake
{

class SnakeSegments
{
public:
    SnakeSegments (std::string const& p_config);

struct Segment
    {
        int x;
        int y;
    };

    std::list<Segment> m_segments;
    Direction m_currentDirection;
    int score = 0;

    bool isSegmentAtPosition(int x, int y) const;
    Segment calculateNewHead() const;
    void updateSegmentsIfSuccessfullMove(Segment const& newHead);
    void addHeadSegment(Segment const& newHead);
    
    void removeTailSegment();
};

}