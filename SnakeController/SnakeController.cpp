#include "SnakeController.hpp"
#include "SnakeWorld.hpp"
#include "SnakeSegments.hpp"

#include <algorithm>
#include <sstream>

#include "EventT.hpp"
#include "IPort.hpp"

namespace Snake
{
ConfigurationError::ConfigurationError()
    : std::logic_error("Bad configuration of Snake::Controller.")
{}

UnexpectedEventException::UnexpectedEventException()
    : std::runtime_error("Unexpected event received!")
{}

Controller::Controller (IPort& p_displayPort, IPort& p_foodPort, IPort& p_scorePort, std::string const& p_config)
{
    SnakeWorld world(IPort& p_displayPort, IPort& p_foodPort, IPort& p_scorePort, std::string const& p_config);
    SnakeSegments segments(std::string const& p_config);
    m_paused = false;

}

void Controller::removeTailSegmentIfNotScored(SnakeSegments::Segment const& newHead)
{
    if (std::make_pair(newHead.x, newHead.y) == world.m_foodPosition) {
        world.m_scorePort.send(std::make_unique<EventT<ScoreInd>>());
        world.m_foodPort.send(std::make_unique<EventT<FoodReq>>());
    } else {
        removeTailSegment();
    }
}

void Controller::updateFoodPosition(int x, int y, std::function<void()> clearPolicy)
{
    if (segments.isSegmentAtPosition(x, y) || world.isPositionOutsideMap(x,y)) {
        world.m_foodPort.send(std::make_unique<EventT<FoodReq>>());
        return;
    }

    clearPolicy();
    world.sendPlaceNewFood(x, y);
}

SnakeSegments::Segment Controller::calculateNewHead() const
{
    SnakeSegments::Segment const& currentHead = segments.m_segments.front();

    SnakeSegments::Segment newHead;
    newHead.x = currentHead.x + (isHorizontal(segments.m_currentDirection) ? isPositive(segments.m_currentDirection) ? 1 : -1 : 0);
    newHead.y = currentHead.y + (isVertical(segments.m_currentDirection) ? isPositive(segments.m_currentDirection) ? 1 : -1 : 0);

    return newHead;
}

void Controller::removeTailSegment()
{
    auto tail = segments.m_segments.back();

    DisplayInd l_evt;
    l_evt.x = tail.x;
    l_evt.y = tail.y;
    l_evt.value = Cell_FREE;
    world.m_displayPort.send(std::make_unique<EventT<DisplayInd>>(l_evt));

    segments.m_segments.pop_back();
}

void Controller::addHeadSegment(SnakeSegments::Segment const& newHead)
{
    segments.m_segments.push_front(newHead);

    DisplayInd placeNewHead;
    placeNewHead.x = newHead.x;
    placeNewHead.y = newHead.y;
    placeNewHead.value = Cell_SNAKE;
    world.m_displayPort.send(std::make_unique<EventT<DisplayInd>>(placeNewHead));
    score++;
}


void Controller::updateSegmentsIfSuccessfullMove(SnakeSegments::Segment const& newHead)
{
    if (segments.isSegmentAtPosition(newHead.x, newHead.y) or world.isPositionOutsideMap(newHead.x, newHead.y)) {
        world.m_scorePort.send(std::make_unique<EventT<LooseInd>>());
    } else {
        addHeadSegment(newHead);
        removeTailSegmentIfNotScored(newHead);
    }
}


namespace
{
bool isHorizontal(Direction direction)
{
    return Direction_LEFT == direction or Direction_RIGHT == direction;
}

bool isVertical(Direction direction)
{
    return Direction_UP == direction or Direction_DOWN == direction;
}

bool isPositive(Direction direction)
{
    return (isVertical(direction) and Direction_DOWN == direction)
        or (isHorizontal(direction) and Direction_RIGHT == direction);
}

bool perpendicular(Direction dir1, Direction dir2)
{
    return isHorizontal(dir1) == isVertical(dir2);
}
} // namespace



void Controller::handleTimeoutInd()
{
    updateSegmentsIfSuccessfullMove(calculateNewHead());
}

void Controller::handleDirectionInd(std::unique_ptr<Event> e)
{
    auto direction = payload<DirectionInd>(*e).direction;

    if (perpendicular(segments.m_currentDirection, direction)) {
        segments.m_currentDirection = direction;
    }
}


void Controller::handleFoodInd(std::unique_ptr<Event> e)
{
    auto receivedFood = payload<FoodInd>(*e);

    updateFoodPosition(receivedFood.x, receivedFood.y, std::bind(&SnakeWorld::sendClearOldFood, this));
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
