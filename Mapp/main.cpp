// main.cpp

#include "contact.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <memory> // För std::shared_ptr

/** \mainpage 
 <h1>Kontakt lista i C++ med GUI</h1>
 <p>En kontakt lista med gui baserat på SFML</p>
*/

int main()
{
    // backgroundColor tilldelar green färg 
    sf::Color backgroundColor = sf::Color::Green; 

    // rita fönstret i 1300 pixlar bredd och 500 pixlar höjd och sätt title till "Welcome to the Contact Book!"
    sf::RenderWindow window(sf::VideoMode(1300, 500), "Welcome to the Contact Book!");
    sf::Font font;
    if (!font.loadFromFile(DEFAULT_FONT))
    {
        std::cerr << "Kunde inte ladda fonten!" << std::endl;
        return -1; //avsluta programmet
    }

    // Knappar
    float buttonWidth = 250.0f; // bestämma bredden
    float buttonHeight = 60.0f; // bestämma höjden
    float buttonSpacing = 20.0f; // bestämma avståndet mellan knapparna

    // här skapar ett knapobj med etiketten "Add Contact"
    // Vector2f stätter knappen storlek
    // 30 tecken storlek för knappens text
    // setPosition(sf::Vector2f(60, 200)): Sätter knappens position i fönstret (x = 60, y = 200).
    //setFont(font): Sätter fonten för knappens text.
    Button addButton("Add Contact", sf::Vector2f(buttonWidth, buttonHeight), 30, sf::Color::Blue, sf::Color::White);
    addButton.setPosition(sf::Vector2f(60, 200));
    addButton.setFont(font);

    // hur detta placeras 100 + (buttonWidth + buttonSpacing)
    // x-position = 100 + (buttonWidth + buttonSpacing)
    //            = 100 + 250 + 20
    //            = 100 + 270
    //            = 370
    // Show Contacts-knappen placeras vid x-position 370 pixlar.
    Button showButton("Show Contacts", sf::Vector2f(buttonWidth, buttonHeight), 30, sf::Color::Blue, sf::Color::White);
    showButton.setPosition(sf::Vector2f(100 + (buttonWidth + buttonSpacing), 200));
    showButton.setFont(font);

    Button deleteButton("Delete Contact", sf::Vector2f(buttonWidth, buttonHeight), 30, sf::Color::Blue, sf::Color::White);
    deleteButton.setPosition(sf::Vector2f(140 + 2 * (buttonWidth + buttonSpacing), 200));
    deleteButton.setFont(font);

    Button editButton("Edit Contact", sf::Vector2f(buttonWidth, buttonHeight), 30, sf::Color::Blue, sf::Color::White);
    editButton.setPosition(sf::Vector2f(180 + 3 * (buttonWidth + buttonSpacing), 200));
    editButton.setFont(font);

    // skapa en Vektor av smarta pekare till kontakter
    // shared_ptr innehar en refersnräknare som har koll på alla obj 
    // när referensräknare blir noll frigörs minnet automatisk
    std::vector<std::shared_ptr<contact>> contacts;

    // den här kör en loop så länge fönstret öppet
    while (window.isOpen())
    {
        // detta lysnnar på användarinteration
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            // addButton.isMouseOver(window): Kontrollerar om muspekaren är över "Add Contact"-knappen.
            //isMouseOver(sf::RenderWindow &window): En metod i Button-klassen som jämför muspekarens position med knappens position och storlek.
            //event.type == sf::Event::MouseButtonPressed: Kontrollerar om en musknapp har tryckts ned (vänster, höger eller mittknapp).
            if(event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left){
                if(addButton.isMouseOver(window) ) addContact(window, contacts);
                if(showButton.isMouseOver(window) ) showAllContacts(window, contacts);
                if(deleteButton.isMouseOver(window)) deleteContact(window, contacts);
                if(editButton.isMouseOver(window)) editContact(window, contacts);
            }
        }

        // rensa fönstret för att rita nästa under
        window.clear(backgroundColor);

        std::vector<Button> buttons = {addButton, showButton, deleteButton, editButton};
        for (auto &button : buttons)
        {
            window.draw(button.buttonShape); // knapparnas bg och färg
            window.draw(button.buttonText); // knapparnas text
        }

        window.display(); // visa allt på fönstret
    }

    return 0;
}
