all: main

main: main.o maze.o game.o
	g++ -o bin/main main.o maze.o game.o -Llib -lsfml-graphics -lsfml-window -lsfml-system -lopengl32 -lsfml-audio

main.o: main.cpp
	g++ -c main.cpp -Iinclude

maze.o: maze.cpp
	g++ -c maze.cpp -Iinclude

game.o: game.cpp
	g++ -c game.cpp -Iinclude

run: main
	./bin/main
	
clean:
	del /S *.o
	del /S bin\main.exe

