#include "SnakeWorld.hpp"

#include <algorithm>
#include <sstream>

#include "EventT.hpp"
#include "IPort.hpp"

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