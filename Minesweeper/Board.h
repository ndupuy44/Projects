#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <random>
#include "Tile.h"

using namespace std;

class Board
{
	bool lost, won;

	map<string, sf::Texture> textures;

	int columns, rows, bombs, originalBombs, numOfFlags;
	int tilesRevealed = 0;

	vector<Tile> tiles;
	vector<int> bombSet;
	vector<int> testOneBombs;
	vector<int> testTwoBombs;
	vector<int> testThreeBombs;
	
	sf::Sprite resetButton;
	sf::Sprite debug;
	sf::Sprite test1;
	sf::Sprite test2;
	sf::Sprite test3;

	sf::Sprite negative;
	sf::Sprite firstDigit;
	sf::Sprite secondDigit;
	sf::Sprite thirdDigit;
public:
	Board(int _columns, int _rows, int _bombs);
	void createTiles();
	void loadTextures();
	void GenerateRandomBombs();
	void setBombs(vector<int>& bombVec);
	void draw(sf::RenderWindow& w);
	void setNeighbors();
	void click(int x, int y, bool leftClick);
	void checkStatus(Tile tile);
	void end();
	void reset();
	void loadTestBoards();
	void loadTestOne();
	void loadTestTwo();
	void loadTestThree();
};
