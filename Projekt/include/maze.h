/**
 * Filnamn: main.cpp
 * @author: ommo2200
 * Kurs: Programmeringsmetodik
 * Lärare: Martin Kjellqvist
 * @version: 1.0
 * @date: 2024-10-11
 * @details: Programmet genererar, löser och visualiserar en labyrint med hjälp av DSF and external bibliotek SFML/grafphic.hpp
*/


#ifndef MAZE_H
#define MAZE_H

#include <iostream>
#include <vector>
#include <ctime>
#include <stack>
#include <algorithm>
#include <chrono>
#include <map>
#include <random>
 
//using namespace std;

struct Node {
    int x, y;
    bool visited = false;
    Node* neighbors[4] = {nullptr, nullptr, nullptr, nullptr};
    char displayChar = ' ';
};

class Maze {
public:
    // Konstruktor för att skapa en labyrint med angiven bredd och höjd.
    Maze(int width, int height);

    // Generera labyrinten.
    void generateMaze();

    // Visa den genererade labyrinten.
    void visualizeGeneratedMaze();

    // Konvertera den interna representationen av labyrinten till en extern representation i en 2D-vektor.
    void convertMaze(std::vector < std::vector<char>>& Maze);

    // Visa den lösta labyrinten.
    void visualizeSolvedMaze(const std::vector < std::vector<char>>& Maze);

    // Visa lösningen för labyrinten.
    void visualizeSolution(const std::vector < std::vector<char>>& Maze);

    // Ange start- och slutnoden för labyrinten.
    void setStartAndEnd();

    // Lös labyrinten och uppdatera den med lösningen.
    void solveMaze(std::vector < std::vector<char>>& Maze);

    // Getter-funktioner för bredd, höjd, startnod och slutnod.
    int getWidth() const;
    int getHeight() const;
    Node* getStartNode() const;
    Node* getEndNode() const;
    const std::vector<std::vector<Node>>& getMaze() const;

private:
    int width_;
    int height_;
    std::vector <std::vector<Node>> maze_;
    Node* startNode_;
    Node* endNode_;
};




#endif //MAZE_H
