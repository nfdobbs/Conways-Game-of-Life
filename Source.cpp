#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include "Cell.h"
using namespace std;

const int WINDOW_WIDTH = 2000;
const int WINDOW_HEIGHT = 1500;
const int CELL_SIZE = 25;
const int X = WINDOW_WIDTH / CELL_SIZE;
const int Y = WINDOW_HEIGHT / CELL_SIZE;
const int UPDATE = 40000;

void update(bool buffer[][X], std::vector<std::vector<Cell>> grid);
int mod(int a, int b);
void swapDraw(const bool buffer[][X], std::vector<std::vector<Cell>> &grid, sf::RenderWindow &window);

int main()
{
	//Creating Render Winow//
	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Conway's Game of Life (Enter to Start)", sf::Style::Default);

	//Settings//
	
	
	
	
	
	//Local Declarations//
	std::vector<std::vector<Cell>> grid(Y, std::vector<Cell>(X));
	bool buffer[Y][X] = { 0 }; //Initializing the whole buffer to 0
	int frame = 0;
	bool start = false;
	int mousePosX;
	int mousePosY;
	int squareX;
	int squareY;

	//Start up Draw//
	window.clear(sf::Color::Black);
	for (int j = 0; j < Y; j++)
		for (int i = 0; i < X; i++)
		{
			grid[j][i].setSize(CELL_SIZE);
			grid[j][i].setPosition(i * CELL_SIZE, j * CELL_SIZE);
			window.draw(grid[j][i].getCell());
		}

	window.display();

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

			if (event.type == sf::Event::MouseButtonPressed && start == false)
			{
				mousePosX = event.mouseButton.x;
				mousePosY = event.mouseButton.y;
				squareX = mousePosX / CELL_SIZE;
				squareY = mousePosY / CELL_SIZE;

				grid[squareY][squareX].setState(!grid[squareY][squareX].getState()); //Swaps state of cell
				window.draw(grid[squareY][squareX].getCell());
				window.display();
			}

			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Escape)
				{
					window.close();
				}

				if (event.key.code == sf::Keyboard::Enter)
				{
					start = true;
					window.setTitle("Conway's Game of Life");
				}

				if (event.key.code == sf::Keyboard::R)
				{
					for (int j = 0; j < Y; j++)
						for (int i = 0; i < X; i++)
						{
							grid[j][i].setState(DEAD);
							buffer[j][i] = DEAD;
							window.draw(grid[j][i].getCell());
						}
					window.display();
					start = false;
					window.setTitle("Conway's Game of Life (Enter to Start)");
				}
			}
		}
		
		if (frame % UPDATE == 0 && start == true)
		{
			update(buffer, grid);
			swapDraw(buffer, grid, window);
			window.display();
		}
		
		if (!start)
		{
			for (int j = 0; j < Y; j++)
				for (int i = 0; i < X; i++)
					window.draw(grid[j][i].getCell());
		}		
		
		frame++;
	}
	
	return 0;
}

void update(bool buffer[][X], std::vector<std::vector<Cell>> grid)
{
	int count = 0;
	int north, south, east, west;

	for(int j = 0; j < Y; j++)
		for (int i = 0; i < X; i++)
		{
			north = mod((j - 1),Y);
			south = mod((j + 1), Y);
			west = mod((i - 1), X);
			east = mod((i + 1), X);
			
			//Check North
			if (grid[north][i].getState() == ALIVE)
				count++;
			//Check Northwest
			if (grid[north][west].getState() == ALIVE)
				count++;
			//Check West
			if (grid[j][west].getState() == ALIVE)
				count++;
			//Check Southwest
			if (grid[south][west].getState() == ALIVE)
				count++;
			//Check South
			if (grid[south][i].getState() == ALIVE)
				count++;
			//Check Southeast
			if (grid[south][east].getState() == ALIVE)
				count++;
			//Check East
			if (grid[j][east].getState() == ALIVE)
				count++;
			//Check Northeast
			if (grid[north][east].getState() == ALIVE)
				count++;

			//Implemeting Rules of Game of Life
			if (grid[j][i].getState() == ALIVE)
			{
				if (count < 2)
					buffer[j][i] = DEAD;
				else if (count < 4)
					buffer[j][i] = ALIVE;
				else
					buffer[j][i] = DEAD;
			}
			else if (count == 3)
				buffer[j][i] = ALIVE;

			count = 0;
		}
}

void swapDraw(const bool buffer[][X], std::vector<std::vector<Cell>> &grid, sf::RenderWindow &window)
{
	for (int j = 0; j < Y; j++)
		for (int i = 0; i < X; i++)
		{
			if (buffer[j][i] != grid[j][i].getState())
				grid[j][i].setState(buffer[j][i]);
			
			window.draw(grid[j][i].getCell());
		}
}

int mod(int a, int b)
{
	int c;
	c = a % b;
	if (c < 0)
		c = c + b;
	return c;
}