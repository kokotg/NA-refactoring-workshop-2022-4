#pragma once

#include <utility>
namespace Snake
{
class SnakeWorld
{
    public:
    std::pair<int, int> m_mapDimension;
    std::pair<int, int> m_foodPosition;
};
} // namespace Snake
        