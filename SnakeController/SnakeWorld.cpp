#include "sstream"
#include "EventT.hpp"
#include "IPort.hpp"
#include "SnakeInterface.hpp"
#include "SnakeWorld.hpp"

namespace Snake
{
SnakeWorld::SnakeWorld(IPort& p_displayPort, IPort& p_foodPort): 
                        m_displayPort(p_displayPort), 
                        m_foodPort(p_foodPort)
{}
bool SnakeWorld::ReadCoonfig(std::istringstream& istr)
{
    char w,f, s;
    int width, height, length;
    int foodX, foodY;
    istr >> w >> width >> height >> f >> foodX >> foodY >> s;
    if (w == 'W' and f == 'F' and s == 'S') {
        m_mapDimension = std::make_pair(width, height);
        m_foodPosition = std::make_pair(foodX, foodY);
        return true;
    }
    return false;
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




}