#pragma once

#include <list>
#include <memory>
#include <stdexcept>
#include <functional>

#include "IEventHandler.hpp"
#include "SnakeInterface.hpp"

class Event;
class IPort;

namespace Snake
{
struct ConfigurationError : std::logic_error
{
    ConfigurationError();
};

struct UnexpectedEventException : std::runtime_error
{
    UnexpectedEventException();
};

class SnakeSegments
{
public:
    struct Segment
    {
        int x;
        int y;
    };
    SnakeSegments(IPort& p_displayPort, IPort& p_foodPort, IPort& p_scorePort, std::string const& p_config);
    bool isSegmentAtPosition(int x, int y) const;
    Segment calculateNewHead() const;
    void updateSegmentsIfSuccessfullMove(Segment const& newHead);
    void addHeadSegment(Segment const& newHead);
    void removeTailSegmentIfNotScored(Segment const& newHead);
    void removeTailSegment();

    int scoreIndication() { return m_segments.size(); }

private:
    std::list<Segment> m_segments;
    bool isSegmentAtPosition(int x, int y) const;
};

class SnakeWorld
{
public:
    SnakeWorld(IPort& p_displayPort, IPort& p_foodPort);
    bool isPositionOutsideMap(int x, int y) const;
    void sendPlaceNewFood(int x, int y);
    bool WorldLoad(std::istringstream istr)
    {
        char w, f, s, d;

        int width, height, length;
        int foodX, foodY;
        istr >> w >> width >> height >> f >> foodX >> foodY >> s;
        if (w == 'W' and f == 'F' and s == 'S') {
            m_mapDimension = std::make_pair(width, height);
            m_foodPosition = std::make_pair(foodX, foodY);
            return true;    
        }
        else return true;

    }

private:
    std::pair<int, int> m_mapDimension;
    std::pair<int, int> m_foodPosition;
};

class Controller : public IEventHandler
{
public:
    Controller(IPort& p_displayPort, IPort& p_foodPort, IPort& p_scorePort, std::string const& p_config);
    //todo Task 5: Torus World, T in p_config string instead of W indicates this feature enabled 

    Controller(Controller const& p_rhs) = delete;
    Controller& operator=(Controller const& p_rhs) = delete;

    void receive(std::unique_ptr<Event> e) override;
    // int scoreIndication() { return m_segments.size(); } //now to SnakeSegment
   bool m_paused;

private:
    IPort& m_displayPort;
    IPort& m_foodPort;
    IPort& m_scorePort;

    SnakeSegments segments;
    SnakeWorld world;

    // std::pair<int, int> m_mapDimension;
    // std::pair<int, int> m_foodPosition;

    // struct Segment
    // {
    //     int x;
    //     int y;
    // };

    // std::list<Segment> m_segments; //to SnakeSegments
    Direction m_currentDirection;

    void handleTimeoutInd();
    void handleDirectionInd(std::unique_ptr<Event>);
    void handleFoodInd(std::unique_ptr<Event>);
    void handleFoodResp(std::unique_ptr<Event>);
    void handlePauseInd(std::unique_ptr<Event>);

    // bool isSegmentAtPosition(int x, int y) const;
    // Segment calculateNewHead() const;
    // void updateSegmentsIfSuccessfullMove(Segment const& newHead);
    // void addHeadSegment(Segment const& newHead);
    // void removeTailSegmentIfNotScored(Segment const& newHead);
    // void removeTailSegment();

    // bool isPositionOutsideMap(int x, int y) const;

    void updateFoodPosition(int x, int y, std::function<void()> clearPolicy);
    void sendClearOldFood();
    // void sendPlaceNewFood(int x, int y);

 
};

} // namespace Snake
