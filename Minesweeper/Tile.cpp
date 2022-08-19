#include "Tile.h"

Tile::Tile(map<string, sf::Texture>& textures, int _xpos, int _ypos) {
	flag.setTexture(textures["flag"]);
	background.setTexture(textures["revealed"]);
	cover.setTexture(textures["hidden"]);
	bomb.setTexture(textures["mine"]);
	
	xpos = _xpos;
	ypos = _ypos;

	isflagged = false;
	isrevealed = false;
	isbomb = false;
}

void Tile::setBomb() {
	isbomb = true;
}

void Tile::draw(sf::RenderWindow& w, map<string, sf::Texture>& textures) {
	if (debug && isbomb) {
		if (!isflagged) {
			cover.setPosition(xpos, ypos);
			w.draw(cover);
			bomb.setPosition(xpos, ypos);
			w.draw(bomb);
		}
		else {
			cover.setPosition(xpos, ypos);
			w.draw(cover);
			flag.setPosition(xpos, ypos);
			w.draw(flag);
			bomb.setPosition(xpos, ypos);
			w.draw(bomb);
		}
	}
	else if (!isrevealed) {
		if (!isflagged) {
			cover.setPosition(xpos, ypos);
			w.draw(cover);
		}
		else {
			cover.setPosition(xpos, ypos);
			w.draw(cover);
			flag.setPosition(xpos, ypos);
			w.draw(flag);
		}
	}
	else if (isbomb) {
		if (isflagged) {
			background.setPosition(xpos, ypos);
			w.draw(background);
			flag.setPosition(xpos, ypos);
			w.draw(flag);
			bomb.setPosition(xpos, ypos);
			w.draw(bomb);
		}
		else {
			background.setPosition(xpos, ypos);
			w.draw(background);
			bomb.setPosition(xpos, ypos);
			w.draw(bomb);
		}
	}
	else {
		background.setPosition(xpos, ypos);
		w.draw(background);
		switch (neighborBombs) {
		case 1:
			num.setTexture(textures["one"]);
			num.setPosition(xpos, ypos);
			w.draw(num);
			break;
		case 2:
			num.setTexture(textures["two"]);
			num.setPosition(xpos, ypos);
			w.draw(num);
			break;
		case 3:
			num.setTexture(textures["three"]);
			num.setPosition(xpos, ypos);
			w.draw(num);
			break;
		case 4:
			num.setTexture(textures["four"]);
			num.setPosition(xpos, ypos);
			w.draw(num);
			break;
		case 5:
			num.setTexture(textures["five"]);
			num.setPosition(xpos, ypos);
			w.draw(num);
			break;
		case 6:
			num.setTexture(textures["six"]);
			num.setPosition(xpos, ypos);
			w.draw(num);
			break;
		case 7:
			num.setTexture(textures["seven"]);
			num.setPosition(xpos, ypos);
			w.draw(num);
			break;
		case 8:
			num.setTexture(textures["eight"]);
			num.setPosition(xpos, ypos);
			w.draw(num);
			break;
		}
	}
}

void Tile::determineNeighborAmt() {
	for (int i = 0; i < 8; i++) {
		if (neighbors[i] != nullptr) {
			numOfNeighbors++;
			if (neighbors[i]->isbomb) {
				neighborBombs++;
			}
		}
	}

}

void Tile::reveal(int& revealed) {
	revealed++;
	if (neighborBombs == 0 && !isbomb) {
		for (int i = 0; i < 8; i++) {
			if (neighbors[i] != nullptr && !neighbors[i]->isrevealed && !neighbors[i]->isflagged) {
				neighbors[i]->isrevealed = true;
				neighbors[i]->reveal(revealed);
			}
		}
	}
	else {
		return;
	}
}

void Tile::toggleDebug() {
	if (debug) {
		debug = false;
	}
	else {
		debug = true;
	}
}

bool Tile::getDebug() {
	return debug;
}