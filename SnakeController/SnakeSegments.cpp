#include "SnakeSegments.hpp"

#include <algorithm>
#include <sstream>

#include "EventT.hpp"
#include "IPort.hpp"

namespace Snake
{

SnakeSegments::SnakeSegments(std::string const& p_config):

    std::istringstream istr(p_config);
    char w, f, s, d;

        istr >> d;
        switch (d) {
            case 'U':
                m_currentDirection = Direction_UP;
                break;
            case 'D':
                m_currentDirection = Direction_DOWN;
                break;
            case 'L':
                m_currentDirection = Direction_LEFT;
                break;
            case 'R':
                m_currentDirection = Direction_RIGHT;
                break;
            default:
                throw ConfigurationError();
        }
        istr >> length;

        while (length--) {
            Segment seg;
            istr >> seg.x >> seg.y;
            m_segments.push_back(seg);
            score++;
        }
}
bool SnakeSegments::isSegmentAtPosition(int x, int y) const
{
    return m_segments.end() !=  std::find_if(m_segments.cbegin(), m_segments.cend(),
        [x, y](auto const& segment){ return segment.x == x and segment.y == y; });
}

Segment SnakeSegments::calculateNewHead() const
{
    Segment const& currentHead = m_segments.front();

    Segment newHead;
    newHead.x = currentHead.x + (isHorizontal(m_currentDirection) ? isPositive(m_currentDirection) ? 1 : -1 : 0);
    newHead.y = currentHead.y + (isVertical(m_currentDirection) ? isPositive(m_currentDirection) ? 1 : -1 : 0);

    return newHead;
}

void SnakeSegments::removeTailSegment()
{
    auto tail = m_segments.back();

    DisplayInd l_evt;
    l_evt.x = tail.x;
    l_evt.y = tail.y;
    l_evt.value = Cell_FREE;
    SnakeWorld::m_displayPort.send(std::make_unique<EventT<DisplayInd>>(l_evt));

    m_segments.pop_back();
}

void SnakeSegments::addHeadSegment(Segment const& newHead)
{
    m_segments.push_front(newHead);

    DisplayInd placeNewHead;
    placeNewHead.x = newHead.x;
    placeNewHead.y = newHead.y;
    placeNewHead.value = Cell_SNAKE;

    SnakeWorld::m_displayPort.send(std::make_unique<EventT<DisplayInd>>(placeNewHead));
}


void SnakeSegments::updateSegmentsIfSuccessfullMove(Segment const& newHead)
{
    if (isSegmentAtPosition(newHead.x, newHead.y) or isPositionOutsideMap(newHead.x, newHead.y)) {
        SnakeWorld::m_scorePort.send(std::make_unique<EventT<LooseInd>>());
    } else {
        addHeadSegment(newHead);
        removeTailSegmentIfNotScored(newHead);
    }
}


}

