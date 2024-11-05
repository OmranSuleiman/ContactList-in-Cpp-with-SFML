# Standardmål för att bygga projektet
all: bin\main.exe

# Länka objektfiler och bibliotek för att skapa den körbara filen
bin\main.exe: main.o contact.o         
	g++ -o bin\main.exe main.o contact.o -Llib -lsfml-graphics -lsfml-window -lsfml-system -lopengl32

# Kompilera main.cpp till en objektfil
main.o: main.cpp
	g++ -c main.cpp -Iinclude

# Kompilera contact.cpp till en objektfil
contact.o: contact.cpp include\contact.h
	g++ -c contact.cpp -Iinclude

# Kör den körbara filen
run: bin\main.exe
	./bin/main.exe

# Rensa objektfiler och den körbara filen
clean:
	del /S *.o
	del /S bin\main.exe
