#include <SFML/Graphics.hpp>
#include <SFML/System/String.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <random>
#include <string>
#include <fstream>
#include <map>
#include "assets.h"
#include "hadafruit.h"
#include "skore.h"

const int WIDTH = 600;
const int HEIGHT = 600;
const int BLOCK_SIZE = 50;
//promenne
bool game_over = false;
bool main_menu = true;
bool skin_menu = false;
bool fruit_menu = false;
bool difficulty_menu = false;
bool game = false;
bool newPress = false;
int high_score = 0;
int score = 0;
sf::Color chosen_color = sf::Color (222, 69, 143);
std::string chosen_difficulty = "easy";

//barvy
sf::Color blue (45, 126, 136);
sf::Color green (45, 126, 34);
sf::Color pink (222,69,143);
sf::Color purple (126, 45, 136);
sf::Color red (255, 0, 0);
sf::Color yellow (255, 255, 0);

//textury

sf::Texture headTexture ;
sf::Texture hlava2Texture ;
sf::Texture hlava3Texture ;
sf::Texture hruskaTexture  ;
sf::Texture jablkoTexture ;
sf::Texture menuTexture  ;
sf::Texture ocasTexture  ;
sf::Texture ocasek2Texture ;
sf::Texture ocasek3Texture ;
sf::Texture svestkaTexture ;
sf::Texture chosen_head_texture = headTexture;
sf::Texture chosen_tail_texture = ocasTexture;
sf::Texture chosen_fruit_texture = jablkoTexture;
    
//skore
std::ifstream rfile;
std::ofstream wfile;

void drawText(sf::Font font,const std::string& text, int fontSize, const sf::Color& color, int x, int y, sf::RenderWindow& window) {
    sf::Text sfText;
    sfText.setFont(font);
    sfText.setString(text);
    sfText.setCharacterSize(fontSize);
    sfText.setFillColor(color);
    sfText.setPosition(x, y);

    window.draw(sfText);
}

//trida pro veskera tlacitka ve hre, vytvori se jedno a to vykreslim, kolikrat potrebuji
class Button {
private:
    sf::RectangleShape rect;
    sf::Color color;
    int width;
    int height;
    int x;
    int y;

public:
    Button(int x, int y) : x(x), y(y), width(160), height(40), color(sf::Color::White) {
        rect.setSize(sf::Vector2f(width, height));
        rect.setPosition(x, y);
        rect.setFillColor(color);
    }

    void draw(sf::RenderWindow& window) {
        window.draw(rect);
    }
};


int main()
{
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Hadik!");
    //obtiznost
    if (chosen_difficulty == "easy") {
    window.setFramerateLimit(10);
    }
    else if (chosen_difficulty == "medium") {
    window.setFramerateLimit(15);
    }
    else if (chosen_difficulty == "hard") {
    window.setFramerateLimit(20);
    }
 
    //skore
  //  rfile.open("High_score.txt");
 //   if (rfile.is_open())
 //   {
 //       std::string line;
  //      getline(rfile, line);
    //    high_score = stoi(line);
      //  rfile.close(); }
    high_score = zistiskore();
    Had had(chosen_color);
    Fruit fruit;
    Assets assets;
    sf::Clock clock;

    sf::Font font = assets.getFont();
    sf::Sprite goSprite= assets.getgosprite();
    sf::Sprite bgTexture = assets.getBgsprite();
    sf::Sprite menuSprite = assets.getmenusprite();

    headTexture = assets.getheadtexture();
    sf::Sprite headSprite(headTexture);
    hlava2Texture = assets.gethlava2texture();
    sf::Sprite hlava2Sprite(hlava2Texture);
    hlava3Texture = assets.gethlava3texture();
    sf::Sprite hlava3Sprite(hlava3Texture);
    hruskaTexture = assets.gethruskatexture();
    sf::Sprite hruskaSprite(hruskaTexture);
    jablkoTexture = assets.getjablkotexture();
    sf::Sprite jablkoSprite (jablkoTexture);
    svestkaTexture = assets.getsvestkatexture();
    sf::Sprite svestkaSprite(svestkaTexture);
    ocasTexture = assets.getocastexture();
    sf::Sprite ocasSprite(ocasTexture);
    ocasek2Texture = assets.getocasek2texture();
    sf::Sprite ocasek2Sprite(ocasek2Texture);
    ocasek3Texture = assets.getocasek3texture();
    sf::Sprite ocasek3Sprite(ocasek3Texture);
    chosen_head_texture = headTexture;
    chosen_tail_texture = ocasTexture;
    chosen_fruit_texture = jablkoTexture;
    


    while (window.isOpen())
    {
        sf::Event event;
        float currentTime = clock.restart().asSeconds();
        float fps = 1.f / currentTime;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        //menu, jeho tlacitka a jejich funkce pri stisku mysi
        if (main_menu==true)
        {
            window.draw(menuSprite);
            drawText(font,"Snake game!!", 50, sf::Color::Black, WIDTH / 2 - 150, HEIGHT - 500, window);
            Button start_button(WIDTH / 2 - 80, HEIGHT / 2 - 20);
            start_button.draw(window);
            drawText(font,"Start", 30, sf::Color::Black, WIDTH / 2 - 30, HEIGHT / 2 - 20, window);
            Button skin_button(WIDTH / 2 - 80, HEIGHT / 2 + 40);
            skin_button.draw(window);
            drawText(font,"Skin", 30, sf::Color::Black, WIDTH / 2 - 30, HEIGHT / 2 + 40, window);
            Button fruit_button(WIDTH / 2 - 80, HEIGHT / 2 + 100);
            fruit_button.draw(window);
            drawText(font,"Fruit", 30, sf::Color::Black, WIDTH / 2 - 30, HEIGHT / 2 + 100, window);
            Button difficulty_button(WIDTH / 2 - 80, HEIGHT / 2 + 160);
            difficulty_button.draw(window);
            drawText(font,"Difficulty", 30, sf::Color::Black, WIDTH / 2 - 55, HEIGHT / 2 + 160, window);

            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                if (!newPress) {
                newPress = true;
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                if (mousePos.x >= WIDTH / 2 - 80 && mousePos.x <= WIDTH / 2 + 80 && mousePos.y >= HEIGHT / 2 - 20 && mousePos.y <= HEIGHT / 2 + 20) {
                    main_menu = false;
                    game = true;
                    
                }
                else if (mousePos.x >= WIDTH / 2 - 80 && mousePos.x <= WIDTH / 2 + 80 && mousePos.y >= HEIGHT / 2 + 40 && mousePos.y <= HEIGHT / 2 + 80) {
                    main_menu = false;
                    skin_menu = true;
                }
                else if (mousePos.x >= WIDTH / 2 - 80 && mousePos.x <= WIDTH / 2 + 80 && mousePos.y >= HEIGHT / 2 + 100 && mousePos.y <= HEIGHT / 2 + 140) {
                    main_menu = false;
                    fruit_menu = true;
                }
                else if (mousePos.x >= WIDTH / 2 - 80 && mousePos.x <= WIDTH / 2 + 80 && mousePos.y >= HEIGHT / 2 + 160 && mousePos.y <= HEIGHT / 2 + 200) {
                    main_menu = false;
                    difficulty_menu = true;
                }
            }
            }
            else {
                newPress = false;
            }
        }

        else if (skin_menu==true)
        {
            window.draw(goSprite);
            drawText(font,"Choose a skin!!", 50, sf::Color::Black, WIDTH / 2 - 150, HEIGHT - 500, window);
            Button skin1_button(WIDTH / 2 - 80, HEIGHT / 2 - 20);
            skin1_button.draw(window);
            window.draw(headSprite);
            headSprite.setPosition(WIDTH / 2 - 20, HEIGHT / 2 - 17.5);
            headSprite.setScale(35/headSprite.getLocalBounds().width,35/headSprite.getLocalBounds().height);
            Button skin2_button(WIDTH / 2 - 80, HEIGHT / 2 + 40);
            skin2_button.draw(window);
            window.draw(hlava2Sprite);
            hlava2Sprite.setPosition(WIDTH / 2 - 20, HEIGHT / 2 + 42.5);
            hlava2Sprite.setScale(35/hlava2Sprite.getLocalBounds().width,35/hlava2Sprite.getLocalBounds().height);
            Button skin3_button(WIDTH / 2 - 80, HEIGHT / 2 + 100);
            skin3_button.draw(window);
            window.draw(hlava3Sprite);
            hlava3Sprite.setPosition(WIDTH / 2 - 20, HEIGHT / 2 + 102.5);
            hlava3Sprite.setScale(35/hlava3Sprite.getLocalBounds().width,35/hlava3Sprite.getLocalBounds().height);

            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                if (!newPress) {
                newPress = true;
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                if (mousePos.x >= WIDTH / 2 - 80 && mousePos.x <= WIDTH / 2 + 80 && mousePos.y >= HEIGHT / 2 - 20 && mousePos.y <= HEIGHT / 2 + 20) {
                    skin_menu = false;
                    main_menu = true;
                    chosen_color = pink;
                    chosen_head_texture = headTexture;
                    chosen_tail_texture = ocasTexture;
                }
                else if (mousePos.x >= WIDTH / 2 - 80 && mousePos.x <= WIDTH / 2 + 80 && mousePos.y >= HEIGHT / 2 + 40 && mousePos.y <= HEIGHT / 2 + 80) {
                    skin_menu = false;
                    main_menu = true;
                    chosen_color = green;
                    chosen_head_texture = hlava2Texture;
                    chosen_tail_texture = ocasek2Texture;
                }
                else if (mousePos.x >= WIDTH / 2 - 80 && mousePos.x <= WIDTH / 2 + 80 && mousePos.y >= HEIGHT / 2 + 100 && mousePos.y <= HEIGHT / 2 + 140) {
                    skin_menu = false;
                    main_menu = true;
                    chosen_color = blue;
                    chosen_head_texture = hlava3Texture;
                    chosen_tail_texture = ocasek3Texture;
                }
            }
            }
            else {
                newPress = false;
            }
        }

        else if (fruit_menu==true)
        {
            window.draw(goSprite);
            drawText(font,"Choose a fruit!!", 50, sf::Color::Black, WIDTH / 2 - 150, HEIGHT - 500, window);
            Button apple_button(WIDTH / 2 - 80, HEIGHT / 2 - 20);
            apple_button.draw(window);
            window.draw(jablkoSprite);
            jablkoSprite.setPosition(WIDTH / 2 - 20, HEIGHT / 2 - 20);
            jablkoSprite.setScale(35/jablkoSprite.getLocalBounds().width,35/jablkoSprite.getLocalBounds().height);
            Button pear_button(WIDTH / 2 - 80, HEIGHT / 2 + 40);
            pear_button.draw(window);
            window.draw(hruskaSprite);
            hruskaSprite.setPosition(WIDTH / 2 - 20, HEIGHT / 2 + 40);
            hruskaSprite.setScale(35/hruskaSprite.getLocalBounds().width,35/hruskaSprite.getLocalBounds().height);
            Button plum_button(WIDTH / 2 - 80, HEIGHT / 2 + 100);
            plum_button.draw(window);
            window.draw(svestkaSprite);
            svestkaSprite.setPosition(WIDTH / 2 - 20, HEIGHT / 2 + 100);
            svestkaSprite.setScale(35/svestkaSprite.getLocalBounds().width,35/svestkaSprite.getLocalBounds().height);

            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                if (!newPress) {
                newPress = true;
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                if (mousePos.x >= WIDTH / 2 - 80 && mousePos.x <= WIDTH / 2 + 80 && mousePos.y >= HEIGHT / 2 - 20 && mousePos.y <= HEIGHT / 2 + 20) {
                    fruit_menu = false;
                    main_menu = true;
                    chosen_fruit_texture = jablkoTexture;
                }
                else if (mousePos.x >= WIDTH / 2 - 80 && mousePos.x <= WIDTH / 2 + 80 && mousePos.y >= HEIGHT / 2 + 40 && mousePos.y <= HEIGHT / 2 + 80) {
                    fruit_menu = false;
                    main_menu = true;
                    chosen_fruit_texture = hruskaTexture;
                }
                else if (mousePos.x >= WIDTH / 2 - 80 && mousePos.x <= WIDTH / 2 + 80 && mousePos.y >= HEIGHT / 2 + 100 && mousePos.y <= HEIGHT / 2 + 140) {
                    fruit_menu = false;
                    main_menu = true;
                    chosen_fruit_texture = svestkaTexture;
                }
            }
            }
            else {
                newPress = false;
            }
        }

        else if (difficulty_menu==true)
        {
            window.draw(goSprite);
            drawText(font,"Choose a difficulty!!", 50, sf::Color::Black, WIDTH / 2 - 150, HEIGHT - 500, window);
            Button easy_button(WIDTH / 2 - 80, HEIGHT / 2 - 20);
            easy_button.draw(window);
            drawText(font,"Easy", 30, sf::Color::Black, WIDTH / 2 - 35, HEIGHT / 2 - 20, window);
            Button medium_button(WIDTH / 2 - 80, HEIGHT / 2 + 40);
            medium_button.draw(window);
            drawText(font,"Medium", 30, sf::Color::Black, WIDTH / 2 - 50, HEIGHT / 2 + 40, window);
            Button hard_button(WIDTH / 2 - 80, HEIGHT / 2 + 100);
            hard_button.draw(window);
            drawText(font,"Hard", 30, sf::Color::Black, WIDTH / 2 - 30, HEIGHT / 2 + 100, window);

            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                if (!newPress) {
                newPress = true;
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                if (mousePos.x >= WIDTH / 2 - 80 && mousePos.x <= WIDTH / 2 + 80 && mousePos.y >= HEIGHT / 2 - 20 && mousePos.y <= HEIGHT / 2 + 20) {
                    difficulty_menu = false;
                    main_menu = true;
                    chosen_difficulty = "easy";
                }
                else if (mousePos.x >= WIDTH / 2 - 80 && mousePos.x <= WIDTH / 2 + 80 && mousePos.y >= HEIGHT / 2 + 40 && mousePos.y <= HEIGHT / 2 + 80) {
                    difficulty_menu = false;
                    main_menu = true;
                    chosen_difficulty = "medium";
                }
                else if (mousePos.x >= WIDTH / 2 - 80 && mousePos.x <= WIDTH / 2 + 80 && mousePos.y >= HEIGHT / 2 + 100 && mousePos.y <= HEIGHT / 2 + 140) {
                    difficulty_menu = false;
                    main_menu = true;
                    chosen_difficulty = "hard";
                }
            }
            }
            else {
                newPress = false;
            }
        }
        //samotna hra
        else if (game==true)
        {
            window.draw(assets.getBgsprite());
            had.move();
            had.changeColor();
            
          fruit.changeFruit(chosen_fruit_texture);
            fruit.update(had.body);
            //kolize s ovocem, pripadne ho sebere, vygeneruje nove a zvysi skore o 1 nebo 2 podle toho, zda se ovoce pohybuje nebo ne
            if (had.body[0].getGlobalBounds().intersects(fruit.getBody().getGlobalBounds())) {
                had.grow();
                if (fruit.isMove()) {
                    score += 2;
                }
                else {
                    score+=1;
                }
                fruit.generate();
                assets.geteatsound().play();
            }

            //kolize s okrajem okna
            if (had.body[0].getPosition().x >= WIDTH || had.body[0].getPosition().x < 0 || had.body[0].getPosition().y >= HEIGHT || had.body[0].getPosition().y < 0) {
                assets.getgosound().play();
                game = false;
                game_over = true;
            }
            //for (const auto& block : had.body) {
            //    window.draw(block);
            //}
            window.draw(fruit.getBody());
            had.draw(window, chosen_head_texture, chosen_tail_texture);
        }

        //game over, vykresleni textu, tlacitek a jejich funkce pri stisku mysi
        else if (game_over==true)
        {
            window.draw(goSprite);
            drawText(font,"Game Over", 50, sf::Color::Black, WIDTH / 2 - 125, HEIGHT - 500, window);
            drawText(font,"Score: " + std::to_string(score), 30, sf::Color::Black, WIDTH / 2 - 50, HEIGHT - 400, window);
            drawText(font,"High Score: " + std::to_string(high_score), 30, sf::Color::Black, WIDTH / 2 - 100, HEIGHT - 350, window);
            if (score > high_score) {
                high_score = score;
                ulozskore(high_score);
              //  wfile.open("High_score.txt");
              //  wfile << high_score;
               // wfile.close();
            }
            Button playagain_button(WIDTH / 2 - 80, HEIGHT / 2 + 50);
            playagain_button.draw(window);
            drawText(font,"Play Again", 30, sf::Color::Black, WIDTH / 2 - 70, HEIGHT / 2 + 50, window);
            Button mainmenu_button(WIDTH / 2 - 80, HEIGHT / 2 + 130);
            mainmenu_button.draw(window);
            drawText(font,"Main Menu", 30, sf::Color::Black, WIDTH / 2 - 73.5, HEIGHT / 2 + 130, window);
            Button exit_button(WIDTH / 2 - 80, HEIGHT / 2 + 210);
            exit_button.draw(window);
            drawText(font,"Exit", 30, sf::Color::Black, WIDTH / 2 - 25, HEIGHT / 2 + 210, window);

            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                if (!newPress) {
                newPress = true;
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                if (mousePos.x >= WIDTH / 2 - 80 && mousePos.x <= WIDTH / 2 + 80 && mousePos.y >= HEIGHT / 2 + 50 && mousePos.y <= HEIGHT / 2 + 90) {
                    game_over = false;
                    game = true;
                    had.body.clear();
                    sf::RectangleShape head;
                    head.setSize(sf::Vector2f(BLOCK_SIZE, BLOCK_SIZE));
                    head.setFillColor(sf::Color::White);
                    head.setPosition(WIDTH / 2, HEIGHT / 2);
                    had.body.push_back(head);
                }
                else if (mousePos.x >= WIDTH / 2 - 80 && mousePos.x <= WIDTH / 2 + 80 && mousePos.y >= HEIGHT / 2 + 130 && mousePos.y <= HEIGHT / 2 + 170) {
                    game_over = false;
                    main_menu = true;
                }
                else if (mousePos.x >= WIDTH / 2 - 80 && mousePos.x <= WIDTH / 2 + 80 && mousePos.y >= HEIGHT / 2 + 210 && mousePos.y <= HEIGHT / 2 + 250) {
                    window.close();
                }
            }
            }
            else {
                newPress = false;
            }
        }
    window.display();
    window.clear();
    }
    return 0;
}