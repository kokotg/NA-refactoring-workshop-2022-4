#include "SnakeInterface.hpp"
#include <stdexcept>

namespace Snake
{
class SnakeWorld
{
    public:
    std::pair<int, int> m_mapDimension;
    std::pair<int, int> m_foodPosition;
};
}