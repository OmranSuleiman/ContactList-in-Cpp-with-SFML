/**
 * Filnamn: main.cpp
 * @author: ommo2200
 * Kurs: Programmeringsmetodik
 * Lärare: Martin Kjellqvist
 * @version: 1.0
 * @date: 2024-10-11
 * @details: Programmet genererar, löser och visualiserar en labyrint med hjälp av DSF and external bibliotek SFML/grafphic.hpp
*/

#include <maze.h>

// Returnerar labyrintens bredd
int Maze::getWidth() const {
    return width_;
}

// Returnerar labyrintens höjd
int Maze::getHeight() const {
    return height_;
}

// Returnerar en pekare till labyrintens startpunkt
Node* Maze::getStartNode() const {
    return startNode_;
}

// Returnerar en pekare till labyrintens slutpunkt
Node* Maze::getEndNode() const {
    return endNode_;
}
const std::vector<std::vector<Node>>& Maze::getMaze() const{
    return maze_;
}
// Konstruktorn initialiserar labyrinten med angiva höjg och bredd
Maze::Maze(int width, int height) {
    width_ = width;
    height_ = height; 

    // Ändra storleken på maze till höjd rader, varje rad har bredd kolomn av typen Node.
    maze_.resize(height_, std::vector<Node>(width_));

    // Initialisera Node med x och y i kordinatorn
    for (int i = 0; i < height_; ++i) {
        for (int j = 0; j < width_; ++j) {
            maze_[i][j].y = i;
            maze_[i][j].x = j;
        }
    }
    // Slumptalsgeneratorn
    srand(time(0));
}

/**
 * @details Func använder DSF
 * Labyrinten skapas som 2D-vec av noder där varje cell representerar en cell i labyrinten.
 * Varje node har införmation om sina grannar om den har besökt tidigare eller inte
*/
void Maze::generateMaze() {
    // Initialesera alla noder och markera de som obesökt, en ny obj av vec skapas då markeras alla som obesökta
    maze_.assign(height_, std::vector<Node>(width_));

    // Loopa genom alla noder som finns i Maze och initialisera deras x och y kordinaterna
    for (int i = 0; i < height_; ++i) {
        for (int j = 0; j < width_; ++j) {
            maze_[i][j].y = i;
            maze_[i][j].x = j;
        }
    }

    // Initialisera DFS stack och start från slumpmässigt node
    std::stack<Node*> dfsStack;
    Node* startNode = &maze_[rand() % height_][rand() % width_];
    dfsStack.push(startNode);
    startNode->visited = true;

                
    // så länge dfsSatcken inte tom utför blocket
    while (!dfsStack.empty()) {
        Node* current = dfsStack.top();
        dfsStack.pop();

        // En aray för riktning (höger, ner, vänster, up)
        int dx[] = {1, 0, -1, 0};
        int dy[] = {0, 1, 0, -1};

        // Listan över alla riktingarna
        std::vector<int> directions = {0, 1, 2, 3};

        // Slå ihop riktningarna med hjälp av shuffel. 
        random_shuffle(directions.begin(), directions.end());

        // Utforska varje riktning 
        for (int dir : directions) {
            int newX = current->x + dx[dir];
            int newY = current->y + dy[dir];

            // Kontrollera om den nya position ligger inom labyrintens gräns och att noden på den här position inte besökt än
            if (newX >= 0 && newX < width_ && newY >= 0 && newY < height_ && !maze_[newY][newX].visited) {
                // Koppla den nuvarande noden med den nya noden
                current->neighbors[dir] = &maze_[newY][newX];
                maze_[newY][newX].visited = true;// Markera den noden som besökt
                dfsStack.push(&maze_[newY][newX]); // Lägg till den nya noden i stacken 
            }
        }
    }

      
       
}

/**
 * @details Func visualiserar den genererade labyrint.
 * Den tar den interna labyrinten som 2D-vec av noder och omvandlar den till 2D-vec av tecken och skriver ut den på skärmen
 *  Den visar noderna och passager som finns mellan de
*/
void Maze::visualizeGeneratedMaze() {

    int Width = width_ * 2 + 1;
    int Height = height_ * 2 + 1;
    // Skapa en 2D-vec ich initialisera med # som representerar en vägg
    std::vector<std::vector<char>> maze(Height, std::vector<char>(Width, '#'));

    // Loopa genom den ursprungliga labyrinten strukturen
    for (int i = 0; i < height_; ++i) {
        for (int j = 0; j < width_; ++j) {
            Node& node = maze_[i][j];
            maze[i*2+1][j*2+1] = node.displayChar;
            // Om noden har en granne till höger, skapa en passage
            if (node.neighbors[0]) maze[i*2+1][j*2+2] = ' ';
            // Om noden har en granne till nedåt, skapa en passage
            if (node.neighbors[1]) maze[i*2+2][j*2+1] = ' ';
            // Om noden har en granne till vänster, skapa en passage
        if (node.neighbors[2] && j > 0) maze[i*2+1][j*2] = ' ';          
        // Om noden har en granne uppåt, skapa en passage
        if (node.neighbors[3] && i > 0) maze[i*2][j*2+1] = ' ';  
        
    
            
        }
    }

    // skriv ut labyrinten till konsolen
    for (int i = 0; i < Height; ++i) {
        for (int j = 0; j < Width; ++j) {
            std::cout << maze[i][j] << ' ';
        }
        std::cout << std::endl;
    }
}

/**
 * @details omvandlas 2D-vec av noder till 2D.vec av tecken ' ' för att skapa passage
 * @param maze en referens till en 2D-vec som ska innehålla den omvandlade labyrint
*/
void Maze::convertMaze(std::vector<std::vector<char>>& Maze) {
    Maze.resize(height_ * 2 + 1, std::vector<char>(width_ * 2 + 1, '#'));

    // Loppa genom den ursprungliga labyrinten
    for (int i = 0; i < height_; ++i) {
        for (int j = 0; j < width_; ++j) {
            Node& node = maze_[i][j];
            Maze[i * 2 + 1][j * 2 + 1] = node.displayChar;
            // Om noden har en granne till höger, skapa en passage
            if (node.neighbors[0]) Maze[i * 2 + 1][j * 2 + 2] = ' ';
            // Om noden har en granne till nedåt, skapa en passage
            if (node.neighbors[1]) Maze[i * 2 + 2][j * 2 + 1] = ' ';
            // Om noden har en granne till vänster, skapa en passage
            if (node.neighbors[2] && j > 0) Maze[i * 2 + 1][j * 2] = ' ';
            // Om noden har en granne ovanför, skapa en passage
            if (node.neighbors[3] && i > 0) Maze[i * 2][j * 2 + 1] = ' ';
        }
    }
}

/**
 * @details func ritar den lösta labyrinten på skärmen.
 * Den går genom varje cell i den visualiserade labyrinten och skriver ut den
*/
void Maze::visualizeSolvedMaze(const std::vector<std::vector<char>>& Maze) {
    // Loopa genom hela labyrinten
    for (const auto& row : Maze) {
        for (char ch : row) {
            std::cout << ch << ' '; // skriv ut varje tecken med mellanslag
        }
        std::cout << std::endl; // Ny rad
    }
}


/**
 * @details func löser labyrinten genom att använda DFS.
 * Den går från start till E och om väg nåddes
 *  Väggen märks med med punkter för att tydliggöra
*/
void Maze::solveMaze(std::vector<std::vector<char>>& Maze) {
    // Start och slut koordinaterna i den visualiserade kabyrinten
    int startX = startNode_->x * 2 + 1;
    int startY = startNode_->y * 2 + 1;
    int endX = endNode_->x * 2 + 1;
    int endY = endNode_->y * 2 + 1;

    // En 2D-vec för att hålla koll på vilka noder som är besökt
    std::vector<std::vector<bool>> visited(Maze.size(), std::vector<bool>(Maze[0].size(), false));
    std::stack<std::pair<int, int>> dfsStack;
    // För att hålla koll på den föregående position för varje besökt position
    std::map<std::pair<int, int>, std::pair<int, int>> previous;

    // starta från startpositionen
    dfsStack.push(std::make_pair(startX, startY));
    visited[startY][startX] = true;

    //Riktning
    int dx[] = {1, 0, -1, 0};
    int dy[] = {0, 1, 0, -1};


    while (!dfsStack.empty()) {
        std::pair<int, int> current = dfsStack.top();
        int currentX = current.first;
        int currentY = current.second;
        dfsStack.pop();

        // Om vi har nått slutpunkten avsluta loopen
        if (currentX == endX && currentY == endY) {
            break;
        }

        // Loopa genom alla fyra positionerna från nuvarandra position
        for (int dir = 0; dir < 4; ++dir) {
            int newX = currentX + dx[dir];
            int newY = currentY + dy[dir];

            // Kontrollera att den nya positionen liggen inom gränsen, att den inte besökt, inte mellanslag eller slutpunkten E
            if (newX >= 0 && newX < Maze[0].size() && newY >= 0 && newY < Maze.size() && !visited[newY][newX] && (Maze[newY][newX] == ' ' || Maze[newY][newX] == 'E')) {
                visited[newY][newX] = true;
                dfsStack.push(std::make_pair(newX, newY));
                // Lagra den nuvarandra positionen som den föregående positien för den nya position
                previous[std::make_pair(newX, newY)] = std::make_pair(currentX, currentY);
            }
        }
    }

    // Hitta tillbaka från E till S med hjälp av 'pervious' och markera den valda vägen med '.'
    std::pair<int, int> current = std::make_pair(endX, endY);
    while (previous.find(current) != previous.end()) {
        if (Maze[current.second][current.first] != 'E') {
            Maze[current.second][current.first] = '.';
        }
        current = previous[current]; // Gå till den föregående position
    }
    Maze[startY][startX] = 'S'; // Markera startposition med S
}

/**
 * @details Func sätter s och E slumpmässigt i 4 oilka sidor
*/
void Maze::setStartAndEnd() {
    int side = rand() % 4; 
    
    switch (side) {
        case 0: // Översta väggen
            startNode_ = &maze_[0][rand() % width_];
            endNode_ = &maze_[height_-1][rand() % width_];
            break;
        case 1: // Nedre väggen
            startNode_ = &maze_[height_-1][rand() % width_];
            endNode_ = &maze_[0][rand() % width_];
            break;
        case 2: // Vänstra väggen
            startNode_ = &maze_[rand() % height_][0];
            endNode_ = &maze_[rand() % height_][width_-1];
            break;
        case 3: // Högra väägen
            startNode_ = &maze_[rand() % height_][width_-1];
            endNode_ = &maze_[rand() % height_][0];
            break;
    }

    // Start och slutpunkterna markeras mee S och E
    startNode_->displayChar = 'S';
    endNode_->displayChar = 'E';
}


/**
 * @details func visualisearar den lösta labyrint genom att anropa en anna func
 * visualizeSolvedMaze(Maze);
*/
void Maze::visualizeSolution(const std::vector<std::vector<char>>& Maze) {
    visualizeSolvedMaze(Maze);
}

