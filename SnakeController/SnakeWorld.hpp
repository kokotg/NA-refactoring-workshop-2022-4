#pragma once
#include <stdexcept>
#include <functional>

#include "IEventHandler.hpp"
#include "SnakeInterface.hpp"

class Event;
class IPort;

namespace Snake
{

class SnakeWorld: public IEventHandler
{
public:
    SnakeWorld(IPort& p_displayPort, IPort& p_foodPort);

    SnakeWorld(SnakeWorld const& p_rhs) = delete;
    SnakeWorld& operator=(SnakeWorld const& p_rhs) = delete;

    void receive(std::unique_ptr<Event> e) override;

private:
    IPort& m_displayPort;
    IPort& m_foodPort;
    IPort& m_scorePort;

    std::pair<int, int> m_mapDimension;
    std::pair<int, int> m_foodPosition;

    void handleFoodInd(std::unique_ptr<Event>);
    void handleFoodResp(std::unique_ptr<Event>);
    void handlePauseInd(std::unique_ptr<Event>);

    void updateFoodPosition(int x, int y, std::function<void()> clearPolicy);
    void sendClearOldFood();
    void sendPlaceNewFood(int x, int y);
    bool SnakeWorld::isPositionOutsideMap(int x, int y) const;

    bool SnakeWorld::ReadCoonfig(std::istringstream& istr);
    bool m_paused;
};

} //namespace Snake