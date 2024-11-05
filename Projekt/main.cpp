/**
 * Filnamn: main.cpp
 * @author: ommo2200
 * Kurs: Programmeringsmetodik
 * Lärare Martin Kjellqvist
 * @version: 1.0
 * skapad: 2024-10-11
 * @details: Programmet genererar, löser och visualiserar en labyrint med hjälp av DSF and external bibliotek SFML/grafphic.hpp
*/

#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include <maze.h>

#define MAZE_WIDTH 11
#define MAZE_HEIGHT 11

int main() {
    int width, height;
    bool genNew = true;
    sf::RenderWindow window(sf::VideoMode(625, 625), "Maze");

    // Ladda font för textvisning
    sf::Font font;
    if (!font.loadFromFile("C:/Users/omran/OneDrive/Skrivbord/Laboration_PMetodik/Projekt/arial.ttf")) {
        std::cout << "Kunde inte ladda font" << std::endl;
        return -1;
    }

    // Skapa textobjekt
    sf::Text infoText;
    infoText.setFont(font);
    infoText.setString("Press 'G' to generate a new Maze");
    infoText.setCharacterSize(24); // Teckenstorlek
    infoText.setFillColor(sf::Color::Cyan); // Textfärg

    // Beräkna fönstrets bredd och centrera texten horisontellt
    sf::FloatRect textRect = infoText.getLocalBounds();
    infoText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
    infoText.setPosition(window.getSize().x / 2.0f, 20); // Y = 20 för att hålla det lite under toppen

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            // Hantera stängningshändelse
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Generera ny labyrint om 'G' trycks
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::G)) {
            genNew = true;
        }

        // Om ny labyrint ska genereras
        if (genNew) {
            window.clear();
            Maze dflLavyrint(MAZE_WIDTH, MAZE_HEIGHT);
            dflLavyrint.generateMaze();
            dflLavyrint.setStartAndEnd();

            sf::Vector2f nodeSize(25, 25);
            sf::RectangleShape cell(nodeSize);
            sf::RectangleShape borderX(sf::Vector2f(600, 50));
            sf::RectangleShape borderY(sf::Vector2f(50, 600));
            borderX.setFillColor(sf::Color::Red);
            borderY.setFillColor(sf::Color::Red);

            borderX.setPosition(25, 0);
            borderY.setPosition(0, 0);
            window.draw(borderX);
            window.draw(borderY);
            borderX.setPosition(0, 575);
            borderY.setPosition(575, 25);
            window.draw(borderX);
            window.draw(borderY);

            std::vector<std::vector<Node>> ourMaze = dflLavyrint.getMaze();

            for (int y = 0; y < MAZE_HEIGHT; y++) {
                for (int x = 0; x < MAZE_WIDTH; x++) {
                    Node& node = ourMaze[y][x];
                    x++;
                    y++;
                    cell.setPosition(x * 2 * 25, y * 2 * 25);
                    window.draw(cell);
                    cell.setFillColor(sf::Color::White);
                    if (node.neighbors[0]) {
                        cell.setPosition((x * 2 + 1) * 25, y * 2 * 25);
                        window.draw(cell);
                    }
                    if (node.neighbors[1]) {
                        cell.setPosition(x * 2 * 25, (y * 2 + 1) * 25);
                        window.draw(cell);
                    }
                    if (node.neighbors[2]) {
                        cell.setPosition((x * 2 - 1) * 25, y * 2 * 25);
                        window.draw(cell);
                    }
                    if (node.neighbors[3]) {
                        cell.setPosition(x * 2 * 25, (y * 2 - 1) * 25);
                        window.draw(cell);
                    }
                    x--;
                    y--;
                }
            }

            // Rita start- och slutpunkter
            cell.setFillColor(sf::Color::Green);
            cell.setPosition((dflLavyrint.getStartNode()->x + 1) * 50, (dflLavyrint.getStartNode()->y + 1) * 50);
            window.draw(cell);
            cell.setFillColor(sf::Color::Blue);
            cell.setPosition((dflLavyrint.getEndNode()->x + 1) * 50, (dflLavyrint.getEndNode()->y + 1) * 50);
            window.draw(cell);

            // Rita texten
            window.draw(infoText); // Rita texten på skärmen
            window.display();

            genNew = false;
        }
    }

    return 0;
}
