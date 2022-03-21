#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;

const bool DEAD = 0;
const bool ALIVE = 1;

class Cell
{
private:
	bool state;
	int size;
	sf::Vector2f position;
	void setColor();

public:
	Cell();
	bool getState();
	void setState(const bool &state);
	void setPosition(const int x, const int y);
	void setSize(int cellSize);
	sf::RectangleShape& getCell();

protected:
	sf::RectangleShape cell;
};

Cell::Cell()
{
	setSize(5);
	setState(DEAD);
	setPosition(0,0);
	cell.setOutlineColor(sf::Color(211,211,211));
	cell.setOutlineThickness(-4);
}

bool Cell::getState()
{
	return state;
}

void Cell::setState(const bool &cellState)
{
	state = cellState;
	setColor();
}

void Cell::setPosition(const int x, const int y)
{
	position = sf::Vector2f(x, y);
	cell.setPosition(position);
}

void Cell::setSize(int cellSize)
{
	size = cellSize;
	cell.setSize(sf::Vector2f(size, size));
	cell.setOutlineThickness(size*.08*-1);
}

void Cell::setColor()
{
	if (state == ALIVE)
		cell.setFillColor(sf::Color::Black);

	else
		cell.setFillColor(sf::Color::White);
}

sf::RectangleShape & Cell::getCell()
{
	return cell;
}

