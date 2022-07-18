#include <map>

class SnakeWorld
{
public:
	void ChooseCurrentDirection(char const& letter);
	void setMapDimension(int width, int height);
	bool isPositionOutsideMap(int x, int y) const;
private:
	std::map<char, char> mapDirection {{'U',0b00},{'D',0b10},{'L',0b01},{'R',0b11}};
	std::pair<int, int> m_mapDimension;
	char m_currentDirection;
}; 