#pragma once
#include <list>


#include "EventT.hpp"
#include "IPort.hpp"

namespace Snake
{

struct Segment
{
    int x;
    int y;
};

class SnakeBody
{
public:

SnakeBody(IPort& displayPort, IPort& scorePort);

void addHeadSegment(Segment const& newHead);
void removeTailSegment();
void removeTailSegmentIfNotScored(Segment const& newHead, std::pair<int, int> position);
void updateSegmentsIfSuccessfullMove(std::pair<int, int> position);

Segment calculateNewHead() const;

std::list<Segment> m_segments; //to encapsulate later

private:

IPort& m_displayPort;
IPort& m_scorePort;

};

} //namespace Snake