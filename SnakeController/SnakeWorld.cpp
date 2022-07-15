//
// Created by Hubert Kulpaczyński on 15/07/2022.
//

#include "SnakeWorld.hpp"
#include "SnakeInterface.hpp"

namespace Snake {
    void SnakeWorld::setMapDimensions(const std::pair<int, int> pos) {
        m_mapDimension = pos;
    }

    void SnakeWorld::setFoodPosition(const std::pair<int, int> pos) {
        m_foodPosition = pos;
    }

    void SnakeWorld::setCurrentDirection(const Direction dir) {
        m_currentDirection = dir;

    }

    std::pair<int, int> SnakeWorld::getMapDimensions()const {
        return m_mapDimension;
    }

    std::pair<int, int> SnakeWorld::getFoodPosition()  const {
        return m_foodPosition;
    }

    Direction SnakeWorld::getCurrentDirection() const {
        return m_currentDirection;
    }

    bool SnakeWorld::isPositionOutsideMap(const int x, const int y) const {
        return x < 0 or y < 0 or x >= m_mapDimension.first or y >= m_mapDimension.second;
    }
} // Snake