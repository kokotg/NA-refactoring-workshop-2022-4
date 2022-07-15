#include "SnakeController.hpp"

#include <algorithm>
#include <sstream>

#include "EventT.hpp"
#include "IPort.hpp"
#include "Relation.hpp"

namespace Snake
{
ConfigurationError::ConfigurationError()
    : std::logic_error("Bad configuration of Snake::Controller.")
{}

UnexpectedEventException::UnexpectedEventException()
    : std::runtime_error("Unexpected event received!")
{}

Controller::Controller(IPort& p_displayPort, IPort& p_foodPort, IPort& p_scorePort, std::string const& p_config)
    : m_displayPort(p_displayPort),
      m_foodPort(p_foodPort),
      m_scorePort(p_scorePort),
      m_paused(false)
{
    std::istringstream istr(p_config);
    char w, f, s, d;

    int width, height, length;
    int foodX, foodY;
    istr >> w >> width >> height >> f >> foodX >> foodY >> s;

    if (w == 'W' and f == 'F' and s == 'S') {
        m_snakeWorld.setMapDimensions({width,height});
        m_snakeWorld.setFoodPosition({foodX,foodY});
        istr >> d;
        switch (d) {
            case 'U':
                m_snakeWorld.setCurrentDirection(Direction_UP);
                break;
            case 'D':
                m_snakeWorld.setCurrentDirection( Direction_DOWN);
                break;
            case 'L':
                m_snakeWorld.setCurrentDirection(Direction_LEFT);
                break;
            case 'R':
                m_snakeWorld.setCurrentDirection(Direction_RIGHT);
                break;
            default:
                throw ConfigurationError();
        }
        istr >> length;

        while (length--) {
            Segment seg {};
            istr >> seg.x >> seg.y;
            m_segments.push_back(seg);
        }
    } else {
        throw ConfigurationError();
    }
}

void Controller::sendPlaceNewFood(int x, int y)
{
    m_snakeWorld.setFoodPosition({x,y});

    DisplayInd placeNewFood;
    placeNewFood.x = x;
    placeNewFood.y = y;
    placeNewFood.value = Cell_FOOD;

    m_displayPort.send(std::make_unique<EventT<DisplayInd>>(placeNewFood));
}

void Controller::sendClearOldFood()
{
    DisplayInd clearOldFood;
    clearOldFood.x = m_snakeWorld.getFoodPosition().first;
    clearOldFood.y = m_snakeWorld.getFoodPosition().second;
    clearOldFood.value = Cell_FREE;

    m_displayPort.send(std::make_unique<EventT<DisplayInd>>(clearOldFood));
}


void Controller::handleTimeoutInd()
{
    m_segments.updateSegmentsIfSuccessfullMove(m_segments.calculateNewHead(m_snakeWorld),m_snakeWorld,m_scorePort,m_displayPort,m_foodPort);
}

void Controller::handleDirectionInd(std::unique_ptr<Event> e)
{
    auto direction = payload<DirectionInd>(*e).direction;

    if (Relation::perpendicular(m_snakeWorld.getCurrentDirection(), direction)) {
        m_snakeWorld.setCurrentDirection(direction);
    }
}

void Controller::updateFoodPosition(int x, int y, std::function<void()> clearPolicy)
{
    if (m_segments.isSegmentAtPosition(x, y) || m_snakeWorld.isPositionOutsideMap(x, y)) {
        m_foodPort.send(std::make_unique<EventT<FoodReq>>());
        return;
    }

    clearPolicy();
    sendPlaceNewFood(x, y);
}

void Controller::handleFoodInd(std::unique_ptr<Event> e)
{
    auto receivedFood = payload<FoodInd>(*e);

    updateFoodPosition(receivedFood.x, receivedFood.y, std::bind(&Controller::sendClearOldFood, this));
}

void Controller::handleFoodResp(std::unique_ptr<Event> e)
{
    auto requestedFood = payload<FoodResp>(*e);

    updateFoodPosition(requestedFood.x, requestedFood.y, []{});
}

void Controller::handlePauseInd(std::unique_ptr<Event> e)
{
    m_paused = not m_paused;
}

void Controller::receive(std::unique_ptr<Event> e)
{
    switch (e->getMessageId()) {
        case TimeoutInd::MESSAGE_ID:
            if (!m_paused) {
                return handleTimeoutInd();
            }
            return;
        case DirectionInd::MESSAGE_ID:
            if (!m_paused) {
                return handleDirectionInd(std::move(e));
            }
            return;
        case FoodInd::MESSAGE_ID:
            return handleFoodInd(std::move(e));
        case FoodResp::MESSAGE_ID:
            return handleFoodResp(std::move(e));
        case PauseInd::MESSAGE_ID:
            return handlePauseInd(std::move(e));
        default:
            throw UnexpectedEventException();
    }
}

} // namespace Snake
