//
// Created by Hubert Kulpaczyński on 15/07/2022.
//

#pragma once
#include "SnakeInterface.hpp"

namespace Snake {

    class Relation {
    public:
        static bool isHorizontal(Direction direction);


        static bool isVertical(Direction direction);


        static bool isPositive(Direction direction);


        static bool perpendicular(Direction dir1, Direction dir2);

    };

} // Snake

