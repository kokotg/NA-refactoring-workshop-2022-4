//
// Created by Hubert Kulpaczyński on 15/07/2022.
//

#pragma once
#include <list>
#include <iterator>
#include "SnakeWorld.hpp"
#include "IPort.hpp"
#include "EventT.hpp"

namespace Snake {
    struct Segment
    {
        int x;
        int y;
    };
    class SnakeSegments {

        std::list<Segment> m_segments;
    public:
        void push_back(Segment);
        std::__list_const_iterator<Segment, void *> end() const;
        std::__list_const_iterator<Segment, std::__list_imp<Segment, std::allocator<Segment>>::__alloc_traits::void_pointer > cbegin() const noexcept;

        std::__list_const_iterator<Segment, std::__list_imp<Segment, std::allocator<Segment>>::__alloc_traits::void_pointer>
        cend() const noexcept;

        Segment front() const;
        Segment back() const;
        void pop_back();

        void push_front(const Segment &segment);

        bool isSegmentAtPosition(int x, int y) const;


        Segment calculateNewHead(const Snake::SnakeWorld &m_snakeWorld) const;

        void removeTailSegment(IPort& m_displayPort);
        void addHeadSegment(const Segment& newHead, IPort& m_displayPort);

        void removeTailSegmentIfNotScored(const Segment &newHead, const SnakeWorld &m_snakeWorld, IPort &m_foodPort,
                                          IPort &m_displayPort, IPort &m_scorePort);

        void updateSegmentsIfSuccessfullMove(const Segment& newHead, const SnakeWorld& m_snakeWorld, IPort& m_scorePort, IPort& m_displayPort, IPort& m_foodPort);


    };

} // Snake

