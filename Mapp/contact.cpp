// contact.cpp

#include "contact.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <regex>
#include <cctype>
#include <memory> // För std::shared_ptr

// Implementering av kontaktklassen

/**
 * @brief Standardkonstruktor för kontaktklassen.
 *
 * Initierar alla medlemmar med tomma strängar.
 * detta minskar risk för odefinerade värde
 */
contact::contact()
{
    fName = "";
    lName = "";
    phone = "";
    birthday = "";
    address = "";
    zip = "";
    email = "";
}

/**
 * @brief Konstruktor med parametrar för kontaktklassen.
 *
 * @param fName Förnamn.
 * @param lName Efternamn.
 * @param phone Telefonnummer.
 * @param birthday Födelsedag.
 * @param address Adress.
 * @param zip Postnummer.
 * @param email E-postadress.
 */
contact::contact(std::string fName, std::string lName, std::string phone, std::string birthday,
                 std::string address, std::string zip, std::string email)
{
    this->fName = fName;
    this->lName = lName;
    this->phone = phone;
    this->birthday = birthday;
    this->address = address;
    this->zip = zip;
    this->email = email;
}

// Getter-metoder

/**
 * @brief Hämtar förnamnet.
 * @return Förnamn.
 */
std::string contact::getfName() const { return fName; }

/**
 * @brief Hämtar efternamnet.
 * @return Efternamn.
 */
std::string contact::getlName() const { return lName; }

/**
 * @brief Hämtar telefonnumret.
 * @return Telefonnummer.
 */
std::string contact::getphoneNumber() const { return phone; }

/**
 * @brief Hämtar födelsedagen.
 * @return Födelsedag.
 */
std::string contact::getBirthday() const { return birthday; }

/**
 * @brief Hämtar adressen.
 * @return Adress.
 */
std::string contact::getAddress() const { return address; }

/**
 * @brief Hämtar postnumret.
 * @return Postnummer.
 */
std::string contact::getZipNumber() const { return zip; }

/**
 * @brief Hämtar e-postadressen.
 * @return E-postadress.
 */
std::string contact::getEmail() const { return email; }

// Setter-metoder

/**
 * @brief Sätter förnamnet.
 * @param fName Förnamn.
 */
void contact::setfName(const std::string &fName) { this->fName = fName; }

/**
 * @brief Sätter efternamnet.
 * @param lName Efternamn.
 */
void contact::setlName(const std::string &lName) { this->lName = lName; }

/**
 * @brief Sätter telefonnumret.
 * @param phone Telefonnummer.
 */
void contact::setPhoneNumber(const std::string &phone) { this->phone = phone; }

/**
 * @brief Sätter födelsedagen.
 * @param birthday Födelsedag.
 */
void contact::setBirthday(const std::string &birthday) { this->birthday = birthday; }

/**
 * @brief Sätter adressen.
 * @param address Adress.
 */
void contact::setAddress(const std::string &address) { this->address = address; }

/**
 * @brief Sätter postnumret.
 * @param zip Postnummer.
 */
void contact::setZipNumber(const std::string &zip) { this->zip = zip; }

/**
 * @brief Sätter e-postadressen.
 * @param email E-postadress.
 */
void contact::setEmail(const std::string &email) { this->email = email; }

// Implementering av Button-klassen

/**
 * @brief Konstruktor för klassen Button.
 *
 * @param text Texten som visas på knappen.
 * @param size Knappens storlek.
 * @param textSize Textens storlek.
 * @param bgColor Knappens bakgrundsfärg.
 * @param textColor Textens färg.
 */
Button::Button(std::string text, sf::Vector2f size, int textSize, sf::Color bgColor, sf::Color textColor)
{
    buttonShape.setSize(size);
    buttonShape.setFillColor(bgColor);
    buttonText.setString(text);
    buttonText.setCharacterSize(textSize);
    buttonText.setFillColor(textColor);
}

/**
 * @brief Sätter fonten för knappens text.
 *
 * @param font Fonten som ska användas.
 */
void Button::setFont(sf::Font &font)
{
    buttonText.setFont(font);
}

/**
 * @brief Sätter positionen för knappen.
 *
 * @param position Positionen som ska sättas.
 */
void Button::setPosition(sf::Vector2f position)
{
    buttonShape.setPosition(position);
    buttonText.setPosition(position.x + 20, position.y + 10);
}

/**
 * @brief Kontrollerar om musen är över knappen.
 *
 * @param window SFML-fönstret.
 * @return true Om musen är över knappen.
 * @return false Om musen inte är över knappen.
 */
bool Button::isMouseOver(sf::RenderWindow &window)
{
    // Denna funktion hämtar muspekarens aktuella position i förhållande till det angivna fönstret (window).
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    // Denna funktion returnerar en sf::FloatRect som representerar knappens globala gränser.
    // sf::FloatRect innehåller knappens position (x, y), bredd och höjd.
    // contains() på sf::FloatRect kontrollerar om en given punkt (sf::Vector2f) är inom rektangeln.
    // Eftersom mousePos är av typen sf::Vector2i (heltal), behöver vi konvertera den till
    // sf::Vector2f (flyttal) för att matcha typen som contains() förväntar sig.
    // Detta görs med static_cast<sf::Vector2f>(mousePos).
    return buttonShape.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos));
}

/********************************************************** Read from file **********************************************************  */

/**
 * @brief Läser in alla kontakter från filen "Book.txt".
 *
 * Denna funktion öppnar filen "Book.txt" och läser in varje kontakt.
 * Varje kontakt förväntas vara på en egen rad med fält separerade av '|'.
 * Kontakterna lagras i vektorn som smarta pekare till `contact`-objekt.
 * @param contacts Vektor av smarta pekare till kontaktobjekt.
 */
void readAllContacts(std::vector<std::shared_ptr<contact>> &contacts)
{
    std::ifstream file("Book.txt");
    if (!file.is_open())
    {
        std::cerr << "Kunde inte öppna filen 'Book.txt'!" << std::endl;
        return;
    }

    std::string line;
    while (std::getline(file, line))
    {
        if (line.size() < 5)
            continue;

        std::stringstream ss(line);
        std::string fName, lName, phone, birthday, address, zip, email;
        std::getline(ss, fName, '|');
        std::getline(ss, lName, '|');
        std::getline(ss, phone, '|');
        std::getline(ss, birthday, '|');
        std::getline(ss, address, '|');
        std::getline(ss, zip, '|');
        std::getline(ss, email, '|');

        // Skapa en smart pekare till en ny kontakt
        // make_shared används för att skapa nya obj och lagra de i vec med shared_ptr detta säkerställer att obj frigörs när de inte längre används
        auto c = std::make_shared<contact>(fName, lName, phone, birthday, address, zip, email);
        contacts.push_back(c);
    }

    file.close();
}

/********************************************************** write to file **********************************************************  */

/**
 * @brief Skriver alla kontakter till filen "Book.txt".
 *
 * Denna funktion öppnar filen "Book.txt" och skriver alla kontakter från den givna vektorn.
 * Varje kontakt skrivs på en egen rad med fält separerade av '|'.
 *
 * @param contacts Vektor av smarta pekare till kontaktobjekt.
 */
void writeAllContacts(const std::vector<std::shared_ptr<contact>> &contacts)
{
    std::ofstream file("Book.txt", std::ios::trunc); // Skriver över filen
    if (!file.is_open())
    {
        std::cerr << "Kunde inte öppna filen 'Book.txt' för skrivning!" << std::endl;
        return;
    }

    for (const auto &c : contacts)
    {
        file << c->getfName() << "|"
             << c->getlName() << "|"
             << c->getphoneNumber() << "|"
             << c->getBirthday() << "|"
             << c->getAddress() << "|"
             << c->getZipNumber() << "|"
             << c->getEmail() << std::endl;
    }

    file.close();
}

/********************************************************** Add contact to file **********************************************************  */

/**
 * @brief Lägger till en ny kontakt.
 *
 * Denna funktion hanterar användarinmatning för att skapa en ny kontakt. Den validerar varje inmatningsfält
 * och vid lyckad validering läggs kontakten till i vektorn och sparas till filen.
 *
 * @param window Referens till SFML-fönstret.
 * @param contacts Vektor av smarta pekare till kontaktobjekt.
 */
void addContact(sf::RenderWindow &window, std::vector<std::shared_ptr<contact>> &contacts)
{
    auto c = std::make_shared<contact>(); // skapa en nytt obj av contact
    std::string input;                    // ta emot inmatning från användaren
    bool validInput = false;              // kontrollerar om inmatningen är korrekt

    // Valideringsfunktioner
    auto isValidName = [](const std::string &str)
    {
        for (char ch : str)
        {
            if (!std::isalpha(ch) && ch != ' ')
            {
                return false;
            }
        }
        return !str.empty();
    };

    // här används -> bool för att ange explicit retur typ som är false eller true
    // auto används för att kompliatorn deducera [] lambda-func
    auto isValidBirthday = [](const std::string &str) -> bool
    {
        if (str.size() != 10)
            return false;
        if (str[4] != '-' || str[7] != '-')
            return false;
        for (size_t i = 0; i < str.size(); ++i)
        {
            if (i == 4 || i == 7)
                continue;
            if (!std::isdigit(static_cast<unsigned char>(str[i])))
                return false;
        }
        return true;
    };

    auto isValidZip = [](const std::string &str) -> bool
    {
        if (str.size() != 6)
            return false;
        if (str[3] != ' ')
            return false;

        // Kontrollera att de första tre tecknen är siffror
        for (size_t i = 0; i < 3; ++i)
        {
            if (!std::isdigit(static_cast<unsigned char>(str[i])))
                return false;
        }

        // Kontrollera att de sista två tecknen är siffror
        for (size_t i = 4; i < 6; ++i)
        {
            if (!std::isdigit(static_cast<unsigned char>(str[i])))
                return false;
        }

        return true;
    };

    auto isValidPhone = [](const std::string &str)
    {
         if (str.size() != 11)
            return false;
        if (str[3] != '-' )
            return false;
        for (size_t i = 0; i < str.size(); ++i)
        {
            if (i == 3)
                continue;
            if (!std::isdigit(static_cast<unsigned char>(str[i])))
                return false;
        }
        return true;
    };

    auto isValidEmail = [](const std::string &email)
    {
        const std::regex pattern(R"((\w+)(\.?)(\w*)@(\w+)\.(\w+))");
        //std::regex_match: En funktion som kontrollerar om hela strängen email matchar regex-mönstret pattern.
        return std::regex_match(email, pattern);
    };

    auto isValidAddress = [](const std::string &str)
    {
        for (char ch : str)
        {
            if (!std::isalnum(ch) && ch != ' ')
            {
                return false;
            }
        }
        return !str.empty();
    };

    // Font- och textinställningar
    sf::Font font;
    if (!font.loadFromFile(DEFAULT_FONT))
    {
        std::cerr << "Kunde inte ladda fonten!" << std::endl;
        return;
    }

    sf::Text textInputLabel, textInputField, errorMessage, backButtonText, thankYouMessage;
    textInputLabel.setFont(font);
    textInputField.setFont(font);
    errorMessage.setFont(font);
    errorMessage.setCharacterSize(18);

    textInputLabel.setPosition(20, 20);
    errorMessage.setPosition(20, 60);

    // Skapa 'Back'-knapp
    sf::RectangleShape backButton(sf::Vector2f(1200, 50));
    backButton.setFillColor(sf::Color::Blue);
    backButton.setPosition(50, window.getSize().y - 80);

    backButtonText.setFont(font);
    backButtonText.setString("Back");
    backButtonText.setCharacterSize(24);
    backButtonText.setFillColor(sf::Color::White);
    backButtonText.setPosition(backButton.getPosition().x + 550, backButton.getPosition().y + 10);
    
    // Funktion för att hantera inmatning
    // std::string &lable visar etiketten i fönstret för användaren
    //const std::function<bool(const std::string &)> &validationFunc tar emot string och retunerar bool för att kontrollerar inmatningen
    //const std::function<void(const std::string &)> &setContactFunc: funktion som tar en string och uppdaterar motsvarande fält i kontaktinformationen.
    // const std::string &errorMsg: Ett felmeddelande som visas om inmatningen är ogiltig.
    auto handleTextInput = [&](const std::string &label, const std::function<bool(const std::string &)> &validationFunc,
                               const std::function<void(const std::string &)> &setContactFunc, const std::string &errorMsg)
    {
        input = ""; // nollställ inmatningssträngen
        textInputLabel.setString(label); // uppdatera etiketten som visa
        textInputField.setPosition(20 + textInputLabel.getGlobalBounds().width, 20); // textinmatningsfältet breddvid etiketten 
        
        do
        {
            sf::Event ev;
            while (window.pollEvent(ev))
            {
                if (ev.type == sf::Event::Closed)
                {
                    window.close();
                    return false;
                }

                if (ev.type == sf::Event::TextEntered)
                {
                    if (ev.text.unicode == 13) // Carriage Return (CR) kallas 13 ASCII värde motsvarar Enter-tangenten
                    {
                        if (validationFunc(input))
                        {
                            setContactFunc(input);
                            input = "";
                            errorMessage.setString("");
                            validInput = true;
                        }
                        else
                        {
                            errorMessage.setString(errorMsg);
                            input = "";
                        }
                    }
                    else if (ev.text.unicode == 8 && !input.empty()) // // 8 ASCII värde motsvarar Backspace
                    {
                        input.erase(input.end() - 1); // tar bort den sista tecken om det finns inmatning
                    }
                    // 32 och 126 tecken i ASCII-värde motsvarar alla utskrivtbara(menas nåt man kan se på skärmen) 
                    else if (ev.text.unicode >= 32 && ev.text.unicode <= 126)
                    {
                        // exe när user matar in A blir det 65 ASCII-värdet och sedan explict konverterar till char
                        // med hjälp av static_cast till sträng
                        input += static_cast<char>(ev.text.unicode);
                    }

                    textInputField.setString(input);
                }

                // Kontrollera om back-knappen klickades
                if (ev.type == sf::Event::MouseButtonPressed)
                {
                    if (ev.mouseButton.button == sf::Mouse::Left)
                    {
                        sf::Vector2f mousePos(ev.mouseButton.x, ev.mouseButton.y);
                        if (backButton.getGlobalBounds().contains(mousePos))
                        {
                            return false;
                        }
                    }
                }

                window.clear();
                window.draw(textInputLabel);
                window.draw(textInputField);
                window.draw(errorMessage);
                window.draw(backButton);
                window.draw(backButtonText);
                window.display();
            }

        } while (!validInput); // kör loopen till validInput blir true
        validInput = false; // återställer validInput till nästa
        return true;
    };

    // Hantera varje fält
    if (!handleTextInput("Enter First Name: ", isValidName, [&](const std::string &value)
                         { c->setfName(value); }, "Invalid input! First name should contain only letters and spaces."))
        return;
    if (!handleTextInput("Enter Last Name: ", isValidName, [&](const std::string &value)
                         { c->setlName(value); }, "Invalid input! Last name should contain only letters and spaces."))
        return;
    if (!handleTextInput("Enter Phone Number (000-0000000): ", isValidPhone, [&](const std::string &value)
                         { c->setPhoneNumber(value); }, "Invalid input! Phone number should contain only digits."))
        return;
    if (!handleTextInput("Enter Birthday (YYYY-MM-DD): ", isValidBirthday, [&](const std::string &value)
                         { c->setBirthday(value); }, "Invalid input! Birthday should be in the format YYYY-MM-DD."))
        return;
    if (!handleTextInput("Enter ZIP Code (123 45): ", isValidZip, [&](const std::string &value)
                         { c->setZipNumber(value); }, "Invalid input! ZIP code should be in the format 123 45."))
        return;
    if (!handleTextInput("Enter Address: ", isValidAddress, [&](const std::string &value)
                         { c->setAddress(value); }, "Invalid input! Address should contain only letters, numbers, and spaces."))
        return;
    if (!handleTextInput("Enter Email: ", isValidEmail, [&](const std::string &value)
                         { c->setEmail(value); }, "Invalid input! Please enter a valid email address (e.g., example@domain.com)."))
        return;

    // Lägg till kontakten till vektorn
    contacts.push_back(c);

    // Skriv kontakter till filen
    writeAllContacts(contacts);

    // Visa tackmeddelande
    thankYouMessage.setFont(font);
    thankYouMessage.setString("Thank you! Contact saved.");
    thankYouMessage.setCharacterSize(35);
    thankYouMessage.setFillColor(sf::Color::Green);
    thankYouMessage.setPosition(400, 200);

    bool buttonClicked = false;

    while (!buttonClicked)
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
                return;
            }
            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);
                    if (backButton.getGlobalBounds().contains(mousePos))
                    {
                        buttonClicked = true;
                    }
                }
            }
        }

        window.clear();
        window.draw(backButton);
        window.draw(backButtonText);
        window.draw(thankYouMessage);
        window.display();
    }
}

/********************************************************** show all contact from file **********************************************************  */

/**
 * @brief Visar alla kontakter i fönstret.
 *
 * Denna funktion läser in alla kontakter från filen, visar dem i fönstret
 * och hanterar användarinteraktion för scrollning och återgång till huvudmenyn.
 *
 * @param window Referens till SFML-fönstret.
 * @param contacts Vektor av smarta pekare till kontaktobjekt.
 */
void showAllContacts(sf::RenderWindow &window, std::vector<std::shared_ptr<contact>> &contacts)
{
    // Läs in kontakter från fil
    contacts.clear();
    readAllContacts(contacts);

    // Ladda font
    sf::Font font;
    if (!font.loadFromFile(DEFAULT_FONT))
    {
        std::cerr << "Kunde inte ladda fonten!" << std::endl;
        return;
    }

    // Skapa textobjekt för varje kontakt
    std::vector<sf::Text> contactTexts;
    float yOffset = 20.0f;

    if (contacts.empty())
    {
        sf::Text noContactsText;
        noContactsText.setFont(font);
        noContactsText.setString("No contacts found in the file!");
        noContactsText.setCharacterSize(24);
        noContactsText.setFillColor(sf::Color::White);
        noContactsText.setPosition(500, yOffset); // placering av texten
        contactTexts.push_back(noContactsText);
    }
    else
    {
        for (const auto &c : contacts)
        {
            std::string contactInfo = "Name: " + c->getfName() + " " + c->getlName() + '\n' +
                                      "Phone Number: " + c->getphoneNumber() + '\n' +
                                      "Birthday: " + c->getBirthday() + '\n' +
                                      "Address: " + c->getAddress() + '\n' +
                                      "ZIP Code: " + c->getZipNumber() + '\n' +
                                      "Email: " + c->getEmail() + "\n\n";

            sf::Text contactText;
            contactText.setFont(font);
            contactText.setString(contactInfo);
            contactText.setCharacterSize(24);
            contactText.setFillColor(sf::Color::White);
            contactText.setPosition(500, yOffset);

            yOffset += contactText.getGlobalBounds().height + 10.0f; // placera nästa contactt under den första på 10 pixlar 

            contactTexts.push_back(contactText);
        }
    }

    // Scrollvariabel som börjar from 0 så länge användaren inte scrolla
    float textOffsetY = 0.0f;

    // 'Back'-knapp inställning
    sf::RectangleShape backButton(sf::Vector2f(1200, 50));
    backButton.setPosition(50, window.getSize().y - 80);
    backButton.setFillColor(sf::Color::Blue);

    sf::Text backButtonText;
    backButtonText.setFont(font);
    backButtonText.setString("Back");
    backButtonText.setCharacterSize(24);
    backButtonText.setFillColor(sf::Color::White);
    backButtonText.setPosition(600, window.getSize().y - 70);

    // Huvudloop
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed)
            {
                sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);
                if (backButton.getGlobalBounds().contains(mousePos))
                {
                    return;
                }
            }

            if (event.type == sf::Event::MouseWheelScrolled)
            {
                if (event.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel)
                {
                    // event.mouseWheelScroll.delta ger positionen upp(positiv) och ner(negativ)
                    // multiplicerar med -10 för att ha koll hur mycket det har flyttat i pixlar
                    //exe scrollning 1 * -10-0f = -10.0f minskar med -10.0f neråt
                    //exe scrollning -1 * -10-0f = -10.0f ökar med -10.0f uppåt
                    textOffsetY += event.mouseWheelScroll.delta * -10.0f;
                    for (auto &text : contactTexts)
                    {
                        //move flyttar text beroende på (x,y)
                        // två parameter 0-x och y kommer från delta beroende på users scrollning
                        text.move(0, event.mouseWheelScroll.delta * -10.0f);
                    }
                }
            }
        }

        window.clear();
        for (const auto &text : contactTexts)
        {
            window.draw(text);
        }
        window.draw(backButton);
        window.draw(backButtonText);
        window.display();
    }
}

/********************************************************** Get contact from file and delete **********************************************************  */

/**
 * @brief Tar bort en kontakt från kontaktlistan.
 *
 * Denna funktion visar alla kontakter och låter användaren välja en kontakt att ta bort.
 * När en kontakt tas bort, uppdateras kontaktlistan och ändringarna sparas till filen.
 *
 * @param window Referens till SFML-fönstret.
 * @param contacts Vektor av smarta pekare till kontaktobjekt.
 */
void deleteContact(sf::RenderWindow &window, std::vector<std::shared_ptr<contact>> &contacts)
{
    // Läs in kontakter från fil
    contacts.clear();
    readAllContacts(contacts);

    // Font- och textinställningar
    sf::Font font;
    if (!font.loadFromFile(DEFAULT_FONT))
    {
        std::cerr << "Kunde inte ladda fonten!" << std::endl;
        return;
    }

    float yOffset = 20.0f;
    std::vector<sf::Text> contactTexts;

    if (contacts.empty())
    {
        sf::Text noContactsText;
        noContactsText.setFont(font);
        noContactsText.setString("No contacts found in the file!");
        noContactsText.setCharacterSize(24);
        noContactsText.setFillColor(sf::Color::White);
        noContactsText.setPosition(500.0f, yOffset);

        contactTexts.push_back(noContactsText);
    }
    else
    {
        // Skapa textobjekt för varje kontakt
        for (size_t i = 0; i < contacts.size(); ++i)
        {
            sf::Text contactText;
            contactText.setFont(font);
            contactText.setString(contacts[i]->getfName() + " " + contacts[i]->getlName());
            contactText.setCharacterSize(20);
            contactText.setFillColor(sf::Color::White);
            contactText.setPosition(500.0f, yOffset);
            yOffset += 30.0f; // ökar 30 pixlar för vaje ny pixlar
            contactTexts.push_back(contactText);
        }
    }

    // 'Delete'-knapp inställning
    sf::RectangleShape deleteButton(sf::Vector2f(1200, 50));
    deleteButton.setFillColor(sf::Color::Red);
    deleteButton.setPosition(50, window.getSize().y - 150);

    sf::Text deleteButtonText;
    deleteButtonText.setFont(font);
    deleteButtonText.setString("Delete");
    deleteButtonText.setCharacterSize(24);
    deleteButtonText.setFillColor(sf::Color::White);
    deleteButtonText.setPosition(deleteButton.getPosition().x + 550, deleteButton.getPosition().y + 10);

    // 'Back'-knapp inställning
    sf::RectangleShape backButton(sf::Vector2f(1200, 50));
    backButton.setFillColor(sf::Color::Blue);
    backButton.setPosition(50, window.getSize().y - 80);

    sf::Text backButtonText;
    backButtonText.setFont(font);
    backButtonText.setString("Back");
    backButtonText.setCharacterSize(24);
    backButtonText.setFillColor(sf::Color::White);
    backButtonText.setPosition(backButton.getPosition().x + 550, backButton.getPosition().y + 10);

    int selectedIndex = -1;

    // Huvudloop
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    sf::Vector2i mousePos = sf::Mouse::getPosition(window);

                    // Kontrollera om en kontakt klickades
                    for (size_t i = 0; i < contactTexts.size(); ++i)
                    {
                        if (contactTexts[i].getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos)))
                        {
                            selectedIndex = i; // Sparar indexet för den valda kontakten
                            for (auto &text : contactTexts)
                            {
                                text.setFillColor(sf::Color::White); // Återställer färgen för alla texter
                            }
                            contactTexts[i].setFillColor(sf::Color::Red); // Markerar den valda kontakten med röd färg
                            break;
                        }
                    }

                    // Kontrollera om 'Delete'-knappen klickades
                    // getGlobalBounds hämtar rektanglär område och contains checkar om detta rektanglär område är klickad och då spara den i selectedIndex = i
                    if (deleteButton.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos)))
                    {
                        if (selectedIndex != -1 && !contacts.empty())
                        {
                            contacts.erase(contacts.begin() + selectedIndex); // den tar bar från filen den aktuella obje
                            contactTexts.erase(contactTexts.begin() + selectedIndex); //den tar bort från fönstret som visas på skärmen

                            // Uppdatera positioner
                            yOffset = 20.0f;
                            for (auto &text : contactTexts)
                            {
                                text.setPosition(500.0f, yOffset);
                                yOffset += 30.0f;
                            }
                            selectedIndex = -1;

                            // Skriv uppdaterade kontakter till fil
                            writeAllContacts(contacts);
                        }
                    }

                    // Kontrollera om 'Back'-knappen klickades
                    if (backButton.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos)))
                    {
                        return;
                    }
                }
            }
        }

        window.clear();
        for (const auto &text : contactTexts)
        {
            window.draw(text);
        }
        window.draw(deleteButton);
        window.draw(deleteButtonText);
        window.draw(backButton);
        window.draw(backButtonText);
        window.display();
    }
}

/********************************************************** This func let the user to handle the edition after chossing the contact ***********************************************************/

/**
 * @brief Redigerar en vald kontakt.
 * @param window Referens till SFML-fönstret.
 * @param contacts Vektor av smarta pekare till kontaktobjekt.
 * @param index Index för den valda kontakten i vektorn.
 */
// void editSelectedContact(sf::RenderWindow &window, std::vector<std::shared_ptr<contact>> &contacts, int index);

void editSelectedContact(sf::RenderWindow &window, std::vector<std::shared_ptr<contact>> &contacts, int index)
{
    auto &c = contacts[index];

    std::string input;
    bool validInput = false;

     // Valideringsfunktioner
    auto isValidName = [](const std::string &str)
    {
        for (char ch : str)
        {
            if (!std::isalpha(ch) && ch != ' ')
            {
                return false;
            }
        }
        return !str.empty();
    };

    // här används -> bool för att ange explicit retur typ som är false eller true
    // auto används för att kompliatorn deducera [] lambda-func
    auto isValidBirthday = [](const std::string &str) -> bool
    {
        if (str.size() != 10)
            return false;
        if (str[4] != '-' || str[7] != '-')
            return false;
        for (size_t i = 0; i < str.size(); ++i)
        {
            if (i == 4 || i == 7)
                continue;
            if (!std::isdigit(static_cast<unsigned char>(str[i])))
                return false;
        }
        return true;
    };

    auto isValidZip = [](const std::string &str) -> bool
    {
        if (str.size() != 6)
            return false;
        if (str[3] != ' ')
            return false;

        // Kontrollera att de första tre tecknen är siffror
        for (size_t i = 0; i < 3; ++i)
        {
            if (!std::isdigit(static_cast<unsigned char>(str[i])))
                return false;
        }

        // Kontrollera att de sista två tecknen är siffror
        for (size_t i = 4; i < 6; ++i)
        {
            if (!std::isdigit(static_cast<unsigned char>(str[i])))
                return false;
        }

        return true;
    };

    auto isValidPhone = [](const std::string &str)
    {
         if (str.size() != 11)
            return false;
        if (str[3] != '-' )
            return false;
        for (size_t i = 0; i < str.size(); ++i)
        {
            if (i == 3)
                continue;
            if (!std::isdigit(static_cast<unsigned char>(str[i])))
                return false;
        }
        return true;
    };

    auto isValidEmail = [](const std::string &email)
    {
        const std::regex pattern(R"((\w+)(\.?)(\w*)@(\w+)\.(\w+))");
        //std::regex_match: En funktion som kontrollerar om hela strängen email matchar regex-mönstret pattern.
        return std::regex_match(email, pattern);
    };

    auto isValidAddress = [](const std::string &str)
    {
        for (char ch : str)
        {
            if (!std::isalnum(ch) && ch != ' ')
            {
                return false;
            }
        }
        return !str.empty();
    };

    // Font- och textinställningar
    sf::Font font;
    if (!font.loadFromFile(DEFAULT_FONT))
    {
        std::cerr << "Kunde inte ladda fonten!" << std::endl;
        return;
    }

    sf::Text textInputLabel, textInputField, errorMessage, backButtonText;
    textInputLabel.setFont(font);
    textInputField.setFont(font);
    errorMessage.setFont(font);
    errorMessage.setCharacterSize(18);

    textInputLabel.setPosition(20, 20);
    errorMessage.setPosition(20, 60);

    // 'Back'-knapp
    sf::RectangleShape backButton(sf::Vector2f(1200, 50));
    backButton.setFillColor(sf::Color::Blue);
    backButton.setPosition(50, window.getSize().y - 80);

    backButtonText.setFont(font);
    backButtonText.setString("Back");
    backButtonText.setCharacterSize(24);
    backButtonText.setFillColor(sf::Color::White);
    backButtonText.setPosition(backButton.getPosition().x + 550, backButton.getPosition().y + 10);

    // Funktion för att hantera inmatning
    auto handleTextInput = [&](const std::string &label, const std::string &initialValue,
                               const std::function<bool(const std::string &)> &validationFunc,
                               const std::function<void(const std::string &)> &setContactFunc,
                               const std::string &errorMsg)
    {
        input = initialValue;
        textInputLabel.setString(label);
        textInputField.setPosition(20 + textInputLabel.getGlobalBounds().width, 20);

        do
        {
            sf::Event ev;
            while (window.pollEvent(ev))
            {
                if (ev.type == sf::Event::Closed)
                {
                    window.close();
                    return false;
                }

                if (ev.type == sf::Event::TextEntered)
                {
                    if (ev.text.unicode == 13) // Enter-tangenten
                    {
                        if (validationFunc(input))
                        {
                            setContactFunc(input);
                            input = "";
                            errorMessage.setString("");
                            validInput = true;
                        }
                        else
                        {
                            errorMessage.setString(errorMsg);
                            input = "";
                        }
                    }
                    else if (ev.text.unicode == 8 && !input.empty()) // Backspace
                    {
                        input.erase(input.end() - 1);
                    }
                    else if (ev.text.unicode >= 32 && ev.text.unicode <= 126)
                    {
                        input += static_cast<char>(ev.text.unicode);
                    }

                    textInputField.setString(input);
                }

                // Kontrollera om back-knappen klickades
                if (ev.type == sf::Event::MouseButtonPressed)
                {
                    if (ev.mouseButton.button == sf::Mouse::Left)
                    {
                        sf::Vector2f mousePos(ev.mouseButton.x, ev.mouseButton.y);
                        if (backButton.getGlobalBounds().contains(mousePos))
                        {
                            return false;
                        }
                    }
                }

                window.clear();
                window.draw(textInputLabel);
                window.draw(textInputField);
                window.draw(errorMessage);
                window.draw(backButton);
                window.draw(backButtonText);
                window.display();
            }

        } while (!validInput);
        validInput = false;
        return true;
    };

    // Hantera varje fält
    if (!handleTextInput("Edit First Name: ", c->getfName(), isValidName, [&](const std::string &value)
                         { c->setfName(value); }, "Invalid input! First name should contain only letters and spaces."))
        return;
    if (!handleTextInput("Edit Last Name: ", c->getlName(), isValidName, [&](const std::string &value)
                         { c->setlName(value); }, "Invalid input! Last name should contain only letters and spaces."))
        return;
    if (!handleTextInput("Edit Phone Number: ", c->getphoneNumber(), isValidPhone, [&](const std::string &value)
                         { c->setPhoneNumber(value); }, "Invalid input! Phone number should contain only digits."))
        return;
    if (!handleTextInput("Edit Birthday (YYYY-MM-DD): ", c->getBirthday(), isValidBirthday, [&](const std::string &value)
                         { c->setBirthday(value); }, "Invalid input! Birthday should be in the format YYYY-MM-DD."))
        return;
    if (!handleTextInput("Edit ZIP Code (123 45): ", c->getZipNumber(), isValidZip, [&](const std::string &value)
                         { c->setZipNumber(value); }, "Invalid input! ZIP code should be in the format 123 45."))
        return;
    if (!handleTextInput("Edit Address: ", c->getAddress(), isValidAddress, [&](const std::string &value)
                         { c->setAddress(value); }, "Invalid input! Address should contain only letters, numbers, and spaces."))
        return;
    if (!handleTextInput("Edit Email: ", c->getEmail(), isValidEmail, [&](const std::string &value)
                         { c->setEmail(value); }, "Invalid input! Please enter a valid email address (e.g., example@domain.com)."))
        return;

    // Skriv uppdaterade kontakter till fil
    writeAllContacts(contacts);
}

/********************************************************** This func let the user to chosse the contact to edit **********************************************************  */

/**
 * @brief Låter användaren välja en kontakt att redigera.
 *
 * Denna funktion visar alla kontakter och låter användaren välja en kontakt att redigera.
 * När en kontakt har valts, anropar den `editSelectedContact` för att redigera kontaktens detaljer.
 *
 * @param window Referens till SFML-fönstret.
 * @param contacts Vektor av smarta pekare till kontaktobjekt.
 */
void editContact(sf::RenderWindow &window, std::vector<std::shared_ptr<contact>> &contacts)
{
    // Läs in kontakter från fil
    contacts.clear();
    readAllContacts(contacts);

    // Font- och textinställningar
    sf::Font font;
    if (!font.loadFromFile(DEFAULT_FONT))
    {
        std::cerr << "Kunde inte ladda fonten!" << std::endl;
        return;
    }

    float yOffset = 20.0f;
    std::vector<sf::Text> contactTexts;

    if (contacts.empty())
    {
        sf::Text noContactsText;
        noContactsText.setFont(font);
        noContactsText.setString("No contacts found in the file!");
        noContactsText.setCharacterSize(24);
        noContactsText.setFillColor(sf::Color::White);
        noContactsText.setPosition(500.0f, yOffset);

        contactTexts.push_back(noContactsText);
    }
    else
    {
        // Skapa textobjekt för varje kontakt
        for (size_t i = 0; i < contacts.size(); ++i)
        {
            sf::Text contactText;
            contactText.setFont(font);
            contactText.setString(contacts[i]->getfName() + " " + contacts[i]->getlName());
            contactText.setCharacterSize(20);
            contactText.setFillColor(sf::Color::White);
            contactText.setPosition(500.0f, yOffset);

            yOffset += 30.0f;

            contactTexts.push_back(contactText);
        }
    }

    // 'Edit'-knapp inställning
    sf::RectangleShape editButton(sf::Vector2f(1200, 50));
    editButton.setFillColor(sf::Color::Green);
    editButton.setPosition(50, window.getSize().y - 150);

    sf::Text editButtonText;
    editButtonText.setFont(font);
    editButtonText.setString("Edit");
    editButtonText.setCharacterSize(24);
    editButtonText.setFillColor(sf::Color::White);
    editButtonText.setPosition(editButton.getPosition().x + 550, editButton.getPosition().y + 10);

    // 'Back'-knapp inställning
    sf::RectangleShape backButton(sf::Vector2f(1200, 50));
    backButton.setFillColor(sf::Color::Blue);
    backButton.setPosition(50, window.getSize().y - 80);

    sf::Text backButtonText;
    backButtonText.setFont(font);
    backButtonText.setString("Back");
    backButtonText.setCharacterSize(24);
    backButtonText.setFillColor(sf::Color::White);
    backButtonText.setPosition(backButton.getPosition().x + 550, backButton.getPosition().y + 10);

    int selectedIndex = -1;

    // Huvudloop
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    sf::Vector2i mousePos = sf::Mouse::getPosition(window);

                    // Kontrollera om en kontakt klickades
                    for (size_t i = 0; i < contactTexts.size(); ++i)
                    {
                        if (contactTexts[i].getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos)))
                        {
                            selectedIndex = i;
                            for (auto &text : contactTexts)
                            {
                                text.setFillColor(sf::Color::White);
                            }
                            contactTexts[i].setFillColor(sf::Color::Red);
                            break;
                        }
                    }

                    // Kontrollera om 'Edit'-knappen klickades
                    if (editButton.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos)))
                    {
                        if (selectedIndex != -1)
                        {
                            editSelectedContact(window, contacts, selectedIndex);// visas fönstret med valda kontakt

                            // Uppdatera det visade kontaktens namn me hjälp av setString
                            contactTexts[selectedIndex].setString(contacts[selectedIndex]->getfName() + " " + contacts[selectedIndex]->getlName());
                            selectedIndex = -1;
                        }
                    }

                    // Kontrollera om 'Back'-knappen klickades
                    if (backButton.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos)))
                    {
                        return;
                    }
                }
            }
        }

        window.clear();
        for (const auto &text : contactTexts)
        {
            window.draw(text);
        }
        window.draw(editButton);
        window.draw(editButtonText);
        window.draw(backButton);
        window.draw(backButtonText);
        window.display();
    }
}
