#include <SFML/Graphics.hpp>
#include <iostream>
#include <cctype>
#include <iomanip>
#include <sstream>
double calculate(std::string input)
{
    double num1;
    bool broke = false;
    for (int x = 0; x < input.length(); x++)
    {
        if (!std::isdigit(input[x]))
        {
            //cout << "input[x]: " << input[x] << endl;
            num1 = stod(input.substr(0, x));
           //cout << "num1: " << num1 << endl;
            input = input.substr(x, input.length() - x + 1);
            //cout << "input : " << input << endl << endl;
            broke = true;
            break;
        }

    }
    if (!broke)
    {
        return std::stod(input);
    }
    switch (input[0])
    {
    case '+':
        //cout << "triggered + " << endl;
        return num1 + calculate(input.substr(1, input.length() - 1));
        break;
    case '-':
        //cout << "triggered - " << endl;
        return num1 - calculate(input.substr(1, input.length() - 1));
        break;
    case '*':
        //cout << "triggered * " << endl;
        return num1 * calculate(input.substr(1, input.length() - 1));
        break;
    case '/':
        //cout << "triggered / " << endl;
        return num1 / calculate(input.substr(1, input.length() - 1));
        break;
    default:
        return 0;
    }
}

int main()
{
    std::ostringstream stream;

    
    // Create the SFML window
    sf::RenderWindow window(sf::VideoMode(220, 515), "SFML Text");
    int baseY = 20;

    // Create a font object and load a font file
    sf::Font font;
    if (!font.loadFromFile("asd.ttf"))
    {
        // If the font file cannot be loaded, exit the program with an error
        return EXIT_FAILURE;
    }
    int posX;
    int posY;
    sf::RectangleShape buttons[18];
    sf::Text buttonNum[18];
    for (int x = 0; x < 18; x++)
    {
        if (x < 9)
        {
            buttonNum[x].setString(std::to_string(x + 1));
        }
        else
        {
            switch (x)
            {
                case 9:
                    buttonNum[x].setString("0");
                    break;
                case 10:
                    buttonNum[x].setString("+");
                    break;
                case 11:
                    buttonNum[x].setString("-");
                    break;
                case 12:
                    buttonNum[x].setString("*");
                    break;
                case 13:
                    buttonNum[x].setString("/");
                    break;
                case 14:
                    buttonNum[x].setString("=");
                    break;
                case 15:
                    buttonNum[x].setString("C");
                    break;
            }
        }
        buttonNum[x].setFont(font);
        buttonNum[x].setCharacterSize(20);
        buttonNum[x].setFillColor(sf::Color::Black);

        buttons[x].setSize(sf::Vector2f(60, 60));
        buttons[x].setFillColor(sf::Color::White);
        
        posX = ((x % 3) * 70) + 10;
        posY = (((x / 3) + 1) * 70) + baseY;
        buttons[x].setPosition(posX, posY);
        buttonNum[x].setPosition(posX + 25, posY + 20);
        std::cout << "var x = " << x << " X = " << posX << " Y = " << posY << std::endl;
    }
    
    std::string inputText = "";
    

    // Create a text object
    sf::Text text(inputText, font, 18);

    // Set the position of the text
    text.setPosition(200, 30);
    int textX = 200;
    text.setFillColor(sf::Color::White);
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
                return 0;
            }
            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    for (int x = 0; x < 18; x++)
                    {
                        if (buttons[x].getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
                        {

                            if (x >= 9)
                            {
                                switch (x)
                                {
                                    case 9:
                                        inputText = inputText + "0";
                                        break;
                                    case 10:
                                        inputText = inputText + "+";
                                        break;
                                    case 11:
                                        inputText = inputText + "-";
                                        break;
                                    case 12:
                                        inputText = inputText + "*";
                                        break;
                                    case 13:
                                        inputText = inputText + "/";
                                        break;
                                    case 14:
                                        stream << std::fixed << std::setprecision(2) << calculate(inputText);
                                        inputText = stream.str();
                                        break;
                                    case 15:
                                        inputText = "";
                                        textX = 200;
                                        break;

                                }
                                //textX -= 11;
                            }
                            else 
                            {
                                inputText = inputText + std::to_string(x + 1);
                                //textX -= 10;
                                std::cout << x + 1 << std::endl;
                                
                            }
                            
                        }
                    }
                }
            }
        }


        window.clear(sf::Color::Black);
        text.setString(inputText);
        text.setPosition(210 - (inputText.length() * 10), 30);
            
        for (int x = 0; x < 18; x++)
        {
            window.draw(buttons[x]);
            window.draw(buttonNum[x]);
        }

        
        window.draw(text);
        window.display();
        


    }
    
}
