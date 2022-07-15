#include "IEventHandler.hpp"
#include "SnakeInterface.hpp"

#include "EventT.hpp"
#include "IPort.hpp"

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
}
