#pragma once

#include <list>
#include <memory>
#include <stdexcept>
#include <functional>

#include "IEventHandler.hpp"
#include "SnakeInterface.hpp"
#include "SnakeBody.hpp"



class Event;
class IPort;

namespace Snake
{
struct ConfigurationError : std::logic_error
{
    ConfigurationError();
};

struct UnexpectedEventException : std::runtime_error
{
    UnexpectedEventException();
};

class Controller : public IEventHandler
{
public:
    Controller(IPort& p_displayPort, IPort& p_foodPort, IPort& p_scorePort, std::string const& p_config);

    Controller(Controller const& p_rhs) = delete;
    Controller& operator=(Controller const& p_rhs) = delete;

    void receive(std::unique_ptr<Event> e) override;

private:
    IPort& m_displayPort;
    IPort& m_foodPort;
    IPort& m_scorePort;

    Direction m_currentDirection;

    std::pair<int, int> m_mapDimension;
    std::pair<int, int> m_foodPosition;

    void handleTimeoutInd();
    void handleDirectionInd(std::unique_ptr<Event>);
    void handleFoodInd(std::unique_ptr<Event>);
    void handleFoodResp(std::unique_ptr<Event>);
    void handlePauseInd(std::unique_ptr<Event>);

    bool isSegmentAtPosition(int x, int y) const;

    bool isPositionOutsideMap(int x, int y) const;

    void updateFoodPosition(int x, int y, std::function<void()> clearPolicy);
    void sendClearOldFood();
    void sendPlaceNewFood(int x, int y);

    bool m_paused;

    std::unique_ptr<SnakeBody> m_snakeBody;
};

} // namespace Snake
