#pragma once

#include <list>
#include <memory>
#include <stdexcept>
#include <functional>

#include "IEventHandler.hpp"
#include "SnakeInterface.hpp"

class IPort;

class SnakeWorld
{
    public:
    SnakeWorld (IPort& p_displayPort, IPort& p_foodPort, IPort& p_scorePort, std::string const& p_config);
    IPort& m_displayPort;
    IPort& m_foodPort;
    IPort& m_scorePort;

    std::pair<int, int> m_mapDimension;
    std::pair<int, int> m_foodPosition;
};