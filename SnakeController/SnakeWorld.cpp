#include "SnakeWorld.hpp"

#include <algorithm>
#include <sstream>

#include "EventT.hpp"
#include "IPort.hpp"

namespace Snake
{

SnakeWorld::SnakeWorld (IPort& p_displayPort, IPort& p_foodPort, IPort& p_scorePort, std::string const& p_config):
    m_displayPort(p_displayPort),
    m_foodPort(p_foodPort),
    m_scorePort(p_scorePort)
{
    std::istringstream istr(p_config);
    char w, f, s, d;

    int width, height, length;
    int foodX, foodY;
    istr >> w >> width >> height >> f >> foodX >> foodY >> s;

    if (w == 'W' and f == 'F' and s == 'S') {
        m_mapDimension = std::make_pair(width, height);
        m_foodPosition = std::make_pair(foodX, foodY);
}
}

bool SnakeWorld::isPositionOutsideMap(int x, int y) const
{
    return x < 0 or y < 0 or x >= m_mapDimension.first or y >= m_mapDimension.second;
}

void SnakeWorld::sendPlaceNewFood(int x, int y)
{
    m_foodPosition = std::make_pair(x, y);

    DisplayInd placeNewFood;
    placeNewFood.x = x;
    placeNewFood.y = y;
    placeNewFood.value = Cell_FOOD;

    m_displayPort.send(std::make_unique<EventT<DisplayInd>>(placeNewFood));
}

void SnakeWorld::sendClearOldFood()
{
    DisplayInd clearOldFood;
    clearOldFood.x = m_foodPosition.first;
    clearOldFood.y = m_foodPosition.second;
    clearOldFood.value = Cell_FREE;

    m_displayPort.send(std::make_unique<EventT<DisplayInd>>(clearOldFood));
}

void SnakeWorld::removeTailSegmentIfNotScored(SnakeSegments::Segment const& newHead)
{
    if (std::make_pair(newHead.x, newHead.y) == m_foodPosition) {
        m_scorePort.send(std::make_unique<EventT<ScoreInd>>());
        m_foodPort.send(std::make_unique<EventT<FoodReq>>());
    } else {
        removeTailSegment();
    }
}

void SnakeWorld::updateFoodPosition(int x, int y, std::function<void()> clearPolicy)
{
    if (isSegmentAtPosition(x, y) || isPositionOutsideMap(x,y)) {
        m_foodPort.send(std::make_unique<EventT<FoodReq>>());
        return;
    }

    clearPolicy();
    sendPlaceNewFood(x, y);
}

}
//         istr >> d;
//         switch (d) {
//             case 'U':
//                 segments.m_currentDirection = Direction_UP;
//                 break;
//             case 'D':
//                 segments.m_currentDirection = Direction_DOWN;
//                 break;
//             case 'L':
//                 segments.m_currentDirection = Direction_LEFT;
//                 break;
//             case 'R':
//                 segments.m_currentDirection = Direction_RIGHT;
//                 break;
//             default:
//                 throw ConfigurationError();
//         }
//         istr >> length;

//         while (length--) {
//             SnakeSegments::Segment seg;
//             istr >> seg.x >> seg.y;
//             segments.m_segments.push_back(seg);
//             segments.score++;
//         }
//     } else {
//         throw ConfigurationError();
//     }