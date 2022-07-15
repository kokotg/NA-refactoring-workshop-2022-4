//
// Created by Hubert Kulpaczyński on 15/07/2022.
//

#include "Relation.hpp"

namespace Snake {
    bool Relation::isHorizontal(Direction direction) {
        {
            return Direction_LEFT == direction or Direction_RIGHT == direction;
        }
    }

    bool Relation::isVertical(Direction direction)
    {
        return Direction_UP == direction or Direction_DOWN == direction;
    }

    bool Relation::isPositive(Direction direction)
    {
        return (isVertical(direction) and Direction_DOWN == direction)
               or (isHorizontal(direction) and Direction_RIGHT == direction);
    }

    bool Relation::perpendicular(Direction dir1, Direction dir2) {
        return isHorizontal(dir1) == isVertical(dir2);
    }


} // Snake