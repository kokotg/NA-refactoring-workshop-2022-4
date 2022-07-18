#include <list>
#include <algorithm>

class SnakeSegments {
public:
    struct Segment
    {
        int x;
        int y;
    };

	void addSegment(int x, int y);
	bool isSegmentAtPosition(int x, int y) const;
	Segment getHead();
	Segment getTail();
	void removeTail();
	void addHead(Segment head);

private:
    std::list<Segment> m_segments;
}; 