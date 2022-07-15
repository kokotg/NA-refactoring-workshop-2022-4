//
// Created by Hubert Kulpaczyński on 15/07/2022.
//

#include "SnakeSegments.hpp"
#include "SnakeWorld.hpp"
#include "Relation.hpp"

namespace Snake {
    void SnakeSegments::push_back(Segment x) {
        m_segments.push_back(x);
    }

    std::__list_const_iterator<Segment, void *> SnakeSegments::end() const {
        {
            return m_segments.end();
        }
    }

    std::__list_const_iterator<Segment, std::__list_imp<Segment, std::allocator<Segment>>::__alloc_traits::void_pointer>
    SnakeSegments::cbegin() const noexcept {
            return m_segments.cbegin();

    }

    std::__list_const_iterator<Segment, std::__list_imp<Segment, std::allocator<Segment>>::__alloc_traits::void_pointer>
    SnakeSegments::cend() const noexcept {
        return m_segments.cend();
    }

    Segment SnakeSegments::front() const {
        return m_segments.front();
    }

    Segment SnakeSegments::back() const {
        return m_segments.back();
    }

    void SnakeSegments::pop_back() {
        m_segments.pop_back();
    }

    void SnakeSegments::push_front(const Segment &segment) {
        m_segments.push_front(segment);
    }

    bool SnakeSegments::isSegmentAtPosition(int x, int y) const {
        return m_segments.end() !=  std::find_if(m_segments.cbegin(), m_segments.cend(),
                             [x, y](auto const& segment){ return segment.x == x and segment.y == y; });
    }

    Segment SnakeSegments::calculateNewHead(const SnakeWorld& m_snakeWorld) const {
        Segment const& currentHead = m_segments.front();

        Segment newHead;
        newHead.x = currentHead.x + (Relation::isHorizontal(m_snakeWorld.getCurrentDirection()) ? Relation::isPositive(m_snakeWorld.getCurrentDirection()) ? 1 : -1 : 0);
        newHead.y = currentHead.y + (Relation::isVertical(m_snakeWorld.getCurrentDirection()) ? Relation::isPositive(m_snakeWorld.getCurrentDirection()) ? 1 : -1 : 0);

        return newHead;
    }

    void SnakeSegments::removeTailSegment(IPort &m_displayPort) {

        auto tail = m_segments.back();

        DisplayInd l_evt;
        l_evt.x = tail.x;
        l_evt.y = tail.y;
        l_evt.value = Cell_FREE;
        m_displayPort.send(std::make_unique<EventT<DisplayInd>>(l_evt));

        m_segments.pop_back();
    }

    void SnakeSegments::addHeadSegment(const Segment &newHead, IPort &m_displayPort) {
        m_segments.push_front(newHead);

        DisplayInd placeNewHead;
        placeNewHead.x = newHead.x;
        placeNewHead.y = newHead.y;
        placeNewHead.value = Cell_SNAKE;

        m_displayPort.send(std::make_unique<EventT<DisplayInd>>(placeNewHead));
    }

    void SnakeSegments::removeTailSegmentIfNotScored(const Segment& newHead, const SnakeWorld& m_snakeWorld, IPort& m_foodPort, IPort& m_displayPort, IPort& m_scorePort) {
        if (std::make_pair(newHead.x, newHead.y) == m_snakeWorld.getFoodPosition()) {
            m_scorePort.send(std::make_unique<EventT<ScoreInd>>());
            m_foodPort.send(std::make_unique<EventT<FoodReq>>());
        } else {
            removeTailSegment(m_displayPort);
        }
    }

    void SnakeSegments::updateSegmentsIfSuccessfullMove(const Segment &newHead, const SnakeWorld &m_snakeWorld,
                                                        IPort &m_scorePort, IPort &m_displayPort, IPort &m_foodPort) {
        if (isSegmentAtPosition(newHead.x, newHead.y) or m_snakeWorld.isPositionOutsideMap(newHead.x, newHead.y)) {
            m_scorePort.send(std::make_unique<EventT<LooseInd>>());
        } else {
            addHeadSegment(newHead, m_displayPort);
            removeTailSegmentIfNotScored(newHead,m_snakeWorld,m_foodPort,m_displayPort,m_scorePort);
        }

    }

} // Snake