#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <map>
using namespace std;

class Tile
{
	sf::Sprite background;
	sf::Sprite cover;
	sf::Sprite num;
	sf::Sprite flag;
	sf::Sprite bomb;

	bool debug = false;

	int xpos;
	int ypos;
	int numOfNeighbors = 0;
	int neighborBombs = 0;
public:
	bool isflagged;
	bool isrevealed;
	bool isbomb;
	
	vector<Tile*> neighbors;

	Tile(map<string, sf::Texture>& textures, int _xpos, int _ypos);
	void setBomb();
	void toggleDebug();
	void reveal(int& revealed);
	void draw(sf::RenderWindow& w, map<string, sf::Texture>& textures);
	void determineNeighborAmt();
	bool getDebug();
};
