//
// Created by Hubert Kulpaczyński on 15/07/2022.
//
#pragma once
#include <utility>
#include "SnakeInterface.hpp"
namespace Snake {
    class SnakeWorld {
        std::pair<int, int> m_mapDimension;
        std::pair<int, int> m_foodPosition;

        Direction m_currentDirection;
    public:
        void setMapDimensions(const std::pair<int,int> pos);
        void setFoodPosition(const std::pair<int,int> pos);
        void setCurrentDirection(const Direction dir);
        std::pair<int,int> getMapDimensions() const;
        std::pair<int,int> getFoodPosition() const;
        Direction getCurrentDirection() const;

        bool isPositionOutsideMap(int x, int y) const;
    };

} // Snake

