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



class SnakeWorld
{
    public:
    SnakeWorld (IPort& p_displayPort, IPort& p_foodPort, IPort& p_scorePort, std::string const& p_config);
    bool isPositionOutsideMap(int x, int y) const;
    void sendPlaceNewFood(int x, int y);
    void sendClearOldFood();

    IPort& m_displayPort;
    IPort& m_foodPort;
    IPort& m_scorePort;

    std::pair<int, int> m_mapDimension;
    std::pair<int, int> m_foodPosition;
};
}