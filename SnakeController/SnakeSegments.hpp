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

struct ConfigurationError : std::logic_error
{
    ConfigurationError();
};

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

    bool isSegmentAtPosition(int x, int y) const;

};

}