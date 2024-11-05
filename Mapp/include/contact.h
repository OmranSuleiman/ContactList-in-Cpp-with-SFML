// contact.h

#ifndef CONTACT_H
#define CONTACT_H

#include <string>
#include <vector>
#include <memory> // För std::shared_ptr
#include <SFML/Graphics.hpp>

#define DEFAULT_FONT "c:\\windows\\fonts\\arial.ttf"
/**
 * @class contact
 * @brief Representerar en kontakt i adressboken.
 */
class contact
{
public:
    /**
     * @brief Standardkonstruktor.
     */
    contact();

    /**
     * @brief Konstruktor med parametrar.
     * @param fName Förnamn.
     * @param lName Efternamn.
     * @param phone Telefonnummer.
     * @param birthday Födelsedag i formatet ÅÅÅÅ-MM-DD.
     * @param address Adress.
     * @param zip Postnummer i formatet 123 45.
     * @param email E-postadress.
     */
    contact(std::string fName, std::string lName, std::string phone, std::string birthday,
            std::string address, std::string zip, std::string email);

    // Getter-metoder
    /**
     * @brief Hämtar förnamnet.
     * @return Förnamn.
     */
    std::string getfName() const;

    /**
     * @brief Hämtar efternamnet.
     * @return Efternamn.
     */
    std::string getlName() const;

    /**
     * @brief Hämtar telefonnumret.
     * @return Telefonnummer.
     */
    std::string getphoneNumber() const;

    /**
     * @brief Hämtar födelsedagen.
     * @return Födelsedag.
     */
    std::string getBirthday() const;

    /**
     * @brief Hämtar adressen.
     * @return Adress.
     */
    std::string getAddress() const;

    /**
     * @brief Hämtar postnumret.
     * @return Postnummer.
     */
    std::string getZipNumber() const;

    /**
     * @brief Hämtar e-postadressen.
     * @return E-postadress.
     */
    std::string getEmail() const;

    // Setter-metoder
    /**
     * @brief Sätter förnamnet.
     * @param fName Förnamn.
     */
    void setfName(const std::string &fName);

    /**
     * @brief Sätter efternamnet.
     * @param lName Efternamn.
     */
    void setlName(const std::string &lName);

    /**
     * @brief Sätter telefonnumret.
     * @param phone Telefonnummer.
     */
    void setPhoneNumber(const std::string &phone);

    /**
     * @brief Sätter födelsedagen.
     * @param birthday Födelsedag i formatet ÅÅÅÅ-MM-DD.
     */
    void setBirthday(const std::string &birthday);

    /**
     * @brief Sätter adressen.
     * @param address Adress.
     */
    void setAddress(const std::string &address);

    /**
     * @brief Sätter postnumret.
     * @param zip Postnummer i formatet 123 45.
     */
    void setZipNumber(const std::string &zip);

    /**
     * @brief Sätter e-postadressen.
     * @param email E-postadress.
     */
    void setEmail(const std::string &email);

private:
    std::string fName, lName, phone, birthday, address, zip, email;
};

/**
 * @class Button
 * @brief Representerar en GUI-knapp.
 */
class Button
{
public:
    /**
     * @brief Konstruktor för klassen Button.
     * @param text Texten som visas på knappen.
     * @param size Knappens storlek.
     * @param textSize Textens storlek.
     * @param bgColor Knappens bakgrundsfärg.
     * @param textColor Textens färg.
     */
    Button(std::string text, sf::Vector2f size, int textSize, sf::Color bgColor, sf::Color textColor);

    /**
     * @brief Sätter fonten för knappens text.
     * @param font Fonten som ska användas.
     */
    void setFont(sf::Font &font);

    /**
     * @brief Sätter positionen för knappen.
     * @param position Positionen som ska sättas.
     */
    void setPosition(sf::Vector2f position);

    /**
     * @brief Kontrollerar om musen är över knappen.
     * @param window SFML-fönstret.
     * @return True om musen är över knappen, annars false.
     */
    bool isMouseOver(sf::RenderWindow &window);

    sf::RectangleShape buttonShape; ///< Formen för knappen.
    sf::Text buttonText;            ///< Texten som visas på knappen.
};


// Funktionsdeklarationer

/**
 * @brief Läser in alla kontakter från filen.
 * @param contacts Vektor för att lagra kontakterna.
 */
void readAllContacts(std::vector<std::shared_ptr<contact>> &contacts);

/**
 * @brief Skriver alla kontakter till filen.
 * @param contacts Vektor av kontakter att skriva.
 */
void writeAllContacts(const std::vector<std::shared_ptr<contact>> &contacts);

/**
 * @brief Lägger till en ny kontakt.
 * @param window SFML-fönstret.
 * @param contacts Vektor av kontakter.
 */
void addContact(sf::RenderWindow &window, std::vector<std::shared_ptr<contact>> &contacts);

/**
 * @brief Visar alla kontakter.
 * @param window SFML-fönstret.
 * @param contacts Vektor av kontakter.
 */
void showAllContacts(sf::RenderWindow &window, std::vector<std::shared_ptr<contact>> &contacts);

/**
 * @brief Tar bort en kontakt.
 * @param window SFML-fönstret.
 * @param contacts Vektor av kontakter.
 */
void deleteContact(sf::RenderWindow &window, std::vector<std::shared_ptr<contact>> &contacts);

/**
 * @brief Redigerar en kontakt.
 * @param window SFML-fönstret.
 * @param contacts Vektor av kontakter.
 */
void editContact(sf::RenderWindow &window, std::vector<std::shared_ptr<contact>> &contacts);

#endif // CONTACT_H
