#include "Board.h"

Board::Board(int _columns, int _rows, int _bombs) {
	columns = _columns;
	rows = _rows;
	originalBombs = _bombs;
	numOfFlags = originalBombs;

	lost = false;
	won = false;

	srand(time(NULL));
	loadTextures();
	loadTestBoards();
	createTiles();
}

void Board::loadTextures() {
	sf::Texture temp;
	temp.loadFromFile("images/tile_hidden.png");
	textures.emplace("hidden", temp);
	temp.loadFromFile("images/tile_revealed.png");
	textures.emplace("revealed", temp);
	temp.loadFromFile("images/tile_revealed.png");
	textures.emplace("revealed", temp);
	temp.loadFromFile("images/flag.png");
	textures.emplace("flag", temp);
	temp.loadFromFile("images/mine.png");
	textures.emplace("mine", temp);
	temp.loadFromFile("images/number_1.png");
	textures.emplace("one", temp);
	temp.loadFromFile("images/number_2.png");
	textures.emplace("two", temp);
	temp.loadFromFile("images/number_3.png");
	textures.emplace("three", temp);
	temp.loadFromFile("images/number_4.png");
	textures.emplace("four", temp);
	temp.loadFromFile("images/number_5.png");
	textures.emplace("five", temp);
	temp.loadFromFile("images/number_6.png");
	textures.emplace("six", temp);
	temp.loadFromFile("images/number_7.png");
	textures.emplace("seven", temp);
	temp.loadFromFile("images/number_8.png");
	textures.emplace("eight", temp);
	temp.loadFromFile("images/test_1.png");
	textures.emplace("test1", temp);
	temp.loadFromFile("images/test_2.png");
	textures.emplace("test2", temp);
	temp.loadFromFile("images/test_3.png");
	textures.emplace("test3", temp);
	temp.loadFromFile("images/face_happy.png");
	textures.emplace("happy", temp);
	temp.loadFromFile("images/face_lose.png");
	textures.emplace("lost", temp);
	temp.loadFromFile("images/face_win.png");
	textures.emplace("won", temp);
	temp.loadFromFile("images/debug.png");
	textures.emplace("debug", temp);
	temp.loadFromFile("images/digits.png");
	textures.emplace("digits", temp);

	resetButton.setPosition((columns * 16) - 32, rows * 32);
	debug.setPosition((columns * 16) + 96, rows * 32);
	debug.setTexture(textures["debug"]);
	test1.setPosition((columns * 16) + 160, rows * 32);
	test1.setTexture(textures["test1"]);
	test2.setPosition((columns * 16) + 224, rows * 32);
	test2.setTexture(textures["test2"]);
	test3.setPosition((columns * 16) + 288, rows * 32);
	test3.setTexture(textures["test3"]);

	negative.setTexture(textures["digits"]);
	firstDigit.setTexture(textures["digits"]);
	secondDigit.setTexture(textures["digits"]);
	thirdDigit.setTexture(textures["digits"]);
	negative.setTextureRect(sf::Rect<int>(210, 0, 21, 32));
	negative.setPosition(0, rows * 32);
	firstDigit.setPosition(21, rows * 32);
	secondDigit.setPosition(42, rows * 32);
	thirdDigit.setPosition(63, rows * 32);
}

void Board::createTiles() {
	tiles.clear();
	int x = 0;
	int y = 0;
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++)
		{
			Tile t = Tile(textures, x, y);
			tiles.push_back(t);
			x += 32;
		}
		x = 0;
		y += 32;
	}
	GenerateRandomBombs();
	setBombs(bombSet);
	setNeighbors();
}

void Board::GenerateRandomBombs(){
	bombSet.clear();
	for (int i = 0; i < rows * columns; i++) {
		bombSet.push_back(0);
	}
	int limit = 0;
	while (limit < originalBombs) {
		int random = rand() % (rows * columns);
		if (bombSet[random] == 0)
		{
			limit++;
			bombSet[random] = 1;
		}
	}
}

void Board::setBombs(vector<int>& bombVec) {
	bombs = 0;
	for (int i = 0; i < rows * columns; i++) {
		if (bombVec[i] == 1) {
			tiles[i].setBomb();
			bombs++;
		}
	}
}

void Board::draw(sf::RenderWindow& w) {
	for (int i = 0; i < rows * columns; i++) {
		tiles[i].draw(w, textures);
	}

	if (won) {
		resetButton.setTexture(textures["won"]);
	}
	else if (lost) {
		resetButton.setTexture(textures["lost"]);
	}
	else {
		resetButton.setTexture(textures["happy"]);
	}

	w.draw(resetButton);
	w.draw(debug);
	w.draw(test1);
	w.draw(test2);
	w.draw(test3);

	int temp;
	if (numOfFlags < 0) {
		w.draw(negative);
		temp = -1 * numOfFlags;
	}
	else {
		temp = numOfFlags;
	}

	int third = temp % 10;
	temp /= 10;
	int second = temp % 10;
	int first = temp / 10;
	firstDigit.setTextureRect(sf::Rect<int>(21 * first, 0, 21, 32));
	secondDigit.setTextureRect(sf::Rect<int>(21 * second, 0, 21, 32));
	thirdDigit.setTextureRect(sf::Rect<int>(21 * third, 0, 21, 32));

	w.draw(firstDigit);
	w.draw(secondDigit);
	w.draw(thirdDigit);
}

void Board::setNeighbors() {
	for (int i = 0; i < rows * columns; i++) {
		tiles[i].neighbors.clear();
		for (int j = 0; j < 8; j++)
		{
			tiles[i].neighbors.push_back(nullptr);
		}
		if (i == 0) {
			tiles[i].neighbors[2] = &(tiles[i + 1]);
			tiles[i].neighbors[3] = &(tiles[i + columns + 1]);
			tiles[i].neighbors[4] = &(tiles[i + columns]);
		}
		else if (i == (columns - 1)) {
			tiles[i].neighbors[4] = &(tiles[i + columns]);
			tiles[i].neighbors[5] = &(tiles[i + columns - 1]);
			tiles[i].neighbors[6] = &(tiles[i - 1]);
		}
		else if (i < columns){
			tiles[i].neighbors[2] = &(tiles[i + 1]);
			tiles[i].neighbors[3] = &(tiles[i + columns + 1]);
			tiles[i].neighbors[4] = &(tiles[i + columns]);
			tiles[i].neighbors[5] = &(tiles[i + columns - 1]);
			tiles[i].neighbors[6] = &(tiles[i - 1]);
		}
		else if (i == ((rows * columns) - columns)) {
			tiles[i].neighbors[0] = &(tiles[i - columns]);
			tiles[i].neighbors[1] = &(tiles[i - columns + 1]);
			tiles[i].neighbors[2] = &(tiles[i + 1]);
		}
		else if (i == ((columns * rows) - 1)) {
			tiles[i].neighbors[0] = &(tiles[i - columns]);
			tiles[i].neighbors[6] = &(tiles[i - 1]);
			tiles[i].neighbors[7] = &(tiles[i - columns - 1]);
		}
		else if (i > ((rows * columns) - columns)) {
			tiles[i].neighbors[0] = &(tiles[i - columns]);
			tiles[i].neighbors[1] = &(tiles[i - columns + 1]);
			tiles[i].neighbors[2] = &(tiles[i + 1]);
			tiles[i].neighbors[6] = &(tiles[i - 1]);
			tiles[i].neighbors[7] = &(tiles[i - columns - 1]);
		}
		else if (i % columns == 0) {
			tiles[i].neighbors[0] = &(tiles[i - columns]);
			tiles[i].neighbors[1] = &(tiles[i - columns + 1]);
			tiles[i].neighbors[2] = &(tiles[i + 1]);
			tiles[i].neighbors[3] = &(tiles[i + columns + 1]);
			tiles[i].neighbors[4] = &(tiles[i + columns]);
		}
		else if ((i + 1 - columns) % columns == 0) {
			tiles[i].neighbors[0] = &(tiles[i - columns]);
			tiles[i].neighbors[4] = &(tiles[i + columns]);
			tiles[i].neighbors[5] = &(tiles[i + columns - 1]);
			tiles[i].neighbors[6] = &(tiles[i - 1]);
			tiles[i].neighbors[7] = &(tiles[i - columns - 1]);
		}
		else {
			tiles[i].neighbors[0] = &(tiles[i - columns]);
			tiles[i].neighbors[1] = &(tiles[i - columns + 1]);
			tiles[i].neighbors[2] = &(tiles[i + 1]);
			tiles[i].neighbors[3] = &(tiles[i + columns + 1]);
			tiles[i].neighbors[4] = &(tiles[i + columns]);
			tiles[i].neighbors[5] = &(tiles[i + columns - 1]);
			tiles[i].neighbors[6] = &(tiles[i - 1]);
			tiles[i].neighbors[7] = &(tiles[i - columns - 1]);
		}
		tiles[i].determineNeighborAmt();
	}
}

void Board::click(int x, int y, bool leftClick) {
	if (leftClick) {
		if (y < (rows * 32)) {
			int xpos = x / 32;
			int ypos = y / 32;

			int tilePos = (ypos * columns) + xpos;
			if (!tiles[tilePos].isrevealed && !tiles[tilePos].isflagged && !won && !lost) {
				tiles[tilePos].isrevealed = true;
				tiles[tilePos].reveal(tilesRevealed);
				checkStatus(tiles[tilePos]);
			}
			else {
				return;
			}
		}
		else if (y > (rows * 32)) {
			if (x > (columns * 16) - 32 && x < (columns * 16) + 32) {
				reset();
			}
			else if (x > (columns * 16) + 96 && x < (columns * 16) + 160 && !won && !lost) {
				for (int i = 0; i < tiles.size(); i++) {
					tiles[i].toggleDebug();
				}
			}
			else if (x > (columns * 16) + 160 && x < (columns * 16) + 224) {
				bool temp = tiles[0].getDebug();
				loadTestOne();
				tilesRevealed = 0;
				won = false;
				lost = false;
				if (temp) {
					for (int i = 0; i < tiles.size(); i++) {
						tiles[i].toggleDebug();
					}
				}
			}
			else if (x > (columns * 16) + 224 && x < (columns * 16) + 288) {
				bool temp = tiles[0].getDebug();
				loadTestTwo();
				tilesRevealed = 0;
				won = false;
				lost = false;
				if (temp) {
					for (int i = 0; i < tiles.size(); i++) {
						tiles[i].toggleDebug();
					}
				}
			}
			else if (x > (columns * 16) + 288 && x < (columns * 16) + 352) {
				bool temp = tiles[0].getDebug();
				loadTestThree();
				tilesRevealed = 0;
				won = false;
				lost = false;
				if (temp) {
					for (int i = 0; i < tiles.size(); i++) {
						tiles[i].toggleDebug();
					}
				}
			}
		}
	}
	if (!leftClick) {
		if (y < (rows * 32)) {
			int xpos = x / 32;
			int ypos = y / 32;

			int tilePos = (ypos * columns) + xpos;
			if (!tiles[tilePos].isrevealed && !tiles[tilePos].isflagged && !won && !lost) {
				tiles[tilePos].isflagged = true;
				numOfFlags--;
			}
			else if(!tiles[tilePos].isrevealed && tiles[tilePos].isflagged && !won && !lost) {
				tiles[tilePos].isflagged = false;
				numOfFlags++;
			}
		}
	}
}

void Board::checkStatus(Tile tile) {
	if ((rows * columns) - tilesRevealed == bombs) {
		won = true;
		end();
	}
	if (tile.isbomb) {
		lost = true;
		end();
	}
}

void Board::end() {
	if (won) {
		for (int i = 0; i < tiles.size(); i++) {
			if (tiles[i].isbomb && !tiles[i].isflagged) {
				tiles[i].isflagged = true;
			}
		}
		numOfFlags = 0;
	}
	else if (lost) {
		for (int i = 0; i < tiles.size(); i++) {
			if (tiles[i].isbomb) {
				tiles[i].isrevealed = true;
			}
		}
	}
}

void Board::reset() {
	bool temp = tiles[0].getDebug();
	createTiles();
	tilesRevealed = 0;
	numOfFlags = originalBombs;
	lost = false;
	won = false;
	if (temp) {
		for (int i = 0; i < tiles.size(); i++) {
			tiles[i].toggleDebug();
		}
	}
}

void Board::loadTestBoards() {
	fstream file;
	file.open("boards/testboard1.brd");
	string line;
	while (getline(file, line)) {
		for (int i = 0; i < line.size(); i++) {
			testOneBombs.push_back((line[i] - 48));
		}
	}
	file.close();

	file.open("boards/testboard2.brd");
	while (getline(file, line)) {
		for (int i = 0; i < line.size(); i++) {
			testTwoBombs.push_back((line[i] - 48));
		}
	}
	file.close();

	file.open("boards/testboard3.brd");
	while (getline(file, line)) {
		for (int i = 0; i < line.size(); i++) {
			testThreeBombs.push_back((line[i] - 48));
		}
	}
	file.close();
}

void Board::loadTestOne() {
	tiles.clear();
	int x = 0;
	int y = 0;
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++)
		{
			Tile t = Tile(textures, x, y);
			tiles.push_back(t);
			x += 32;
		}
		x = 0;
		y += 32;
	}
	setBombs(testOneBombs);
	numOfFlags = bombs;
	setNeighbors();
}

void Board::loadTestTwo() {
	tiles.clear();
	int x = 0;
	int y = 0;
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++)
		{
			Tile t = Tile(textures, x, y);
			tiles.push_back(t);
			x += 32;
		}
		x = 0;
		y += 32;
	}
	setBombs(testTwoBombs);
	numOfFlags = bombs;
	setNeighbors();
}

void Board::loadTestThree() {
	tiles.clear();
	int x = 0;
	int y = 0;
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++)
		{
			Tile t = Tile(textures, x, y);
			tiles.push_back(t);
			x += 32;
		}
		x = 0;
		y += 32;
	}
	setBombs(testThreeBombs);
	numOfFlags = bombs;
	setNeighbors();
}