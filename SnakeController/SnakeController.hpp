#pragma once

#include <list>
#include <memory>
#include <stdexcept>
#include <functional>
#include <algorithm>
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

 struct Segment
{
        int x;
        int y;
};

class SnakeSegments
{
private:
   

    std::list<Segment> m_segments;
    int numberOfSegments; 


public:
    
    
    void addSegment(Segment seg){
        m_segments.push_back(seg);
    }
    
    Segment getHeadOfSnake() const{
        return m_segments.front();
    }

    
    Segment getTailOfSnake() const{
        return m_segments.back();
    }

    void removeTailOfSnake() {
        m_segments.pop_back();
    }

    void addHeadToSnake(Segment newHead) {
        m_segments.push_front(newHead);
    }

    std::list<Segment> getSegments() const {
        return m_segments;
    }
    bool checkPosition(int x,int y) const {
        return m_segments.end() !=  std::find_if(m_segments.cbegin(), m_segments.cend(),
        [x, y](auto const& segment){ return segment.x == x and segment.y == y; });
    }
};




class SnakeWorld
{
private:
    std::pair<int, int> m_mapDimension;
    std::pair<int, int> m_foodPosition;
public:  
    
    void setMapDimension(int x, int y){
        m_mapDimension.first = x;
        m_mapDimension.second = y; 
    }

    std::pair<int,int> getMapDimension() const {
        return m_mapDimension; 
    }

    void setFoodPosition(int x, int y){
        m_foodPosition.first = x;
        m_foodPosition.second = y;
    }

    std::pair<int,int> getFoodPosition(){
        return m_foodPosition; 
    }
};



class Controller : public IEventHandler
{
public:
    Controller(IPort& p_displayPort, IPort& p_foodPort, IPort& p_scorePort, std::string const& p_config);

    Controller(Controller const& p_rhs) = delete;
    Controller& operator=(Controller const& p_rhs) = delete;

    void receive(std::unique_ptr<Event> e) override;

private:
    IPort& m_displayPort;
    IPort& m_foodPort;
    IPort& m_scorePort;

    
    Direction m_currentDirection;

    void handleTimeoutInd();
    void handleDirectionInd(std::unique_ptr<Event>);
    void handleFoodInd(std::unique_ptr<Event>);
    void handleFoodResp(std::unique_ptr<Event>);
    void handlePauseInd(std::unique_ptr<Event>);

    Segment calculateNewHead() const;
    void removeTailSegment();
    void addHeadSegment(Segment const& newHead);
    void removeTailSegmentIfNotScored(Segment const& newHead);
    bool isSegmentAtPosition(int x, int y) const;
    void updateSegmentsIfSuccessfullMove(Segment const& newHead);

    void sendPlaceNewFood(int x, int y);
    void sendClearOldFood();
    void updateFoodPosition(int x, int y, std::function<void()> clearPolicy);
    bool isPositionOutsideMap(int x, int y) const;


    bool m_paused;

    SnakeSegments snakeSegments; 
    SnakeWorld snakeWorld; 
};

} // namespace Snake


