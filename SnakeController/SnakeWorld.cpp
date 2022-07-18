#include "SnakeWorld.hpp"

void SnakeWorld::ChooseCurrentDirection(char const& letter) {
	m_currentDirection = mapDirection[letter];
}

void SnakeWorld::setMapDimension(int width, int height) {
	m_mapDimension = {width, height};
}

bool SnakeWorld::isPositionOutsideMap(int x, int y) const
{
    return x < 0 or y < 0 or x >= m_mapDimension.first or y >= m_mapDimension.second;
} 