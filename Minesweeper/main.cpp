#include <SFML/Graphics.hpp>
#include <fstream>
#include <iostream>
#include "Board.h"
using namespace std;

void getBoardSize(int& columns, int& rows, int& bombs) {
    fstream file("boards/config.cfg");
    string temp;
    if (file.is_open()) {
        getline(file, temp);
        columns = stoi(temp);
        getline(file, temp);
        rows = stoi(temp);
        getline(file, temp);
        bombs = stoi(temp);
    }
    else {
        cout << "failed" << endl;
    }
}

int main()
{
    int columns, rows, bombs;
    getBoardSize(columns, rows, bombs);
    sf::RenderWindow window(sf::VideoMode(columns * 32, (rows * 32) + 88), "Minesweeper");
    Board board(columns, rows, bombs);

    while (window.isOpen())
    {
        sf::Event event;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::MouseButtonPressed)
            {
                bool leftClick = (event.mouseButton.button == sf::Mouse::Left);
                board.click(event.mouseButton.x, event.mouseButton.y, leftClick);
            }
        }

        window.clear(sf::Color(255, 255, 255, 255));
        board.draw(window);
        window.display();
    }

    return 0;
}