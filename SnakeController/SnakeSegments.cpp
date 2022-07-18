#include "SnakeSegments.hpp"

void SnakeSegments::addSegment(int x, int y){
    m_segments.push_back(Segment{x, y});
}

bool SnakeSegments::isSegmentAtPosition(int x, int y) const
{
    return m_segments.end() != std::find_if(m_segments.cbegin(), m_segments.cend(),
        [x, y](auto const& segment){ return segment.x == x and segment.y == y; });
}

SnakeSegments::Segment SnakeSegments::getHead(){
    return m_segments.front();
}

SnakeSegments::Segment SnakeSegments::getTail(){
    return m_segments.back();
}

void SnakeSegments::addHead(SnakeSegments::Segment head){
    m_segments.push_front(head);
}

void SnakeSegments::removeTail(){
    m_segments.pop_back();
}
