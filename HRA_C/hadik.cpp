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
//sf::Color chosen_fruit = sf::Color::Red;
//std::string chosen_head;
//std::string chosen_tail;
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
sf::Texture* bgTexture = new sf::Texture();
sf::Texture* goTexture = new sf::Texture();
sf::Texture* headTexture = new sf::Texture();
sf::Texture* hlava2Texture = new sf::Texture();
sf::Texture* hlava3Texture = new sf::Texture();
sf::Texture* hruskaTexture = new sf::Texture();
sf::Texture* jablkoTexture = new sf::Texture();
sf::Texture* menuTexture = new sf::Texture();
sf::Texture* ocasTexture = new sf::Texture();
sf::Texture* ocasek2Texture = new sf::Texture();
sf::Texture* ocasek3Texture = new sf::Texture();
sf::Texture* svestkaTexture = new sf::Texture();
sf::Texture* chosen_head_texture = headTexture;
sf::Texture* chosen_tail_texture = ocasTexture;
sf::Texture* chosen_fruit_texture = jablkoTexture;
    
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

class Had
{
private:
    sf::Vector2f direction;
    char old_dir;

public:
    std::vector<sf::RectangleShape> body;

    Had() {
        sf::RectangleShape head;
        head.setSize(sf::Vector2f(BLOCK_SIZE, BLOCK_SIZE));
        head.setFillColor(chosen_color);
        head.setPosition(WIDTH / 2, HEIGHT / 2);
        body.push_back(head);
    }

    void draw(sf::RenderWindow& window) {
        //rotace hlavy
        sf::Sprite headSprite;
        headSprite.setTexture(*chosen_head_texture);
        headSprite.setOrigin(headSprite.getLocalBounds().width / 2, headSprite.getLocalBounds().height / 2);
        //headSprite.setPosition(body[0].getPosition());
        headSprite.setPosition(body[0].getPosition() + sf::Vector2f(BLOCK_SIZE / 2, BLOCK_SIZE / 2));
        //doprava
        if (direction == sf::Vector2f(1, 0)) {
            headSprite.setRotation(0);
        }
        //dolu
        else if (direction == sf::Vector2f(0, 1)) {
            headSprite.setRotation(90);
        }
        //doleva
        else if (direction == sf::Vector2f(-1, 0)) {
            headSprite.setRotation(180);
        }
        //nahoru
        else if (direction == sf::Vector2f(0, -1)) {
            headSprite.setRotation(270);
        }
        window.draw(headSprite);

        //vykresleni tela
        for (int i = 1; i < body.size() - 1; ++i) {
            window.draw(body[i]);
        }

        //rotace ocasu
        sf::Sprite tailSprite;
        tailSprite.setTexture(*chosen_tail_texture);
        tailSprite.setOrigin(tailSprite.getLocalBounds().width / 2, tailSprite.getLocalBounds().height / 2);
        tailSprite.setPosition(body.back().getPosition() + sf::Vector2f(BLOCK_SIZE / 2, BLOCK_SIZE / 2));

        sf::Vector2f tailDirection = body[body.size() - 1].getPosition() - body[body.size() - 2].getPosition();
        //doprava
        if (tailDirection == sf::Vector2f(BLOCK_SIZE, 0)) {
            tailSprite.setRotation(180);
        }
        //dolu
        else if (tailDirection == sf::Vector2f(0, BLOCK_SIZE)) {
            tailSprite.setRotation(270);
        }
        //doleva
        else if (tailDirection == sf::Vector2f(-BLOCK_SIZE, 0)) {
            tailSprite.setRotation(0);
        }
        //nahoru
        else if (tailDirection == sf::Vector2f(0, -BLOCK_SIZE)) {
            tailSprite.setRotation(90);
        }
        if (body.size() > 1) {
            window.draw(tailSprite);
        }
        
    }

    void move() {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && old_dir != 's') {
            direction = sf::Vector2f(0, -1);
            old_dir = 'w';
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && old_dir != 'd') {
            direction = sf::Vector2f(-1, 0);
            old_dir = 'a';
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && old_dir != 'a') {
            direction = sf::Vector2f(1, 0);
            old_dir = 'd';
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && old_dir != 'w') {
            direction = sf::Vector2f(0, 1);
            old_dir = 's';
        }

        for (int i = body.size() - 1; i > 0; --i) {
            body[i].setPosition(body[i - 1].getPosition());
        }

        body[0].move(direction.x * BLOCK_SIZE, direction.y * BLOCK_SIZE);
        //changeHead();
    }

    void grow() {
        sf::RectangleShape newBlock;
        newBlock.setSize(sf::Vector2f(BLOCK_SIZE, BLOCK_SIZE));
        newBlock.setFillColor(chosen_color);
        newBlock.setPosition(body.back().getPosition());
        body.push_back(newBlock);
        //changeTail();
    }

    void changeColor()
    {
        for (int i = 0; i < body.size(); i++)
        {
            body[i].setFillColor(chosen_color);
        }
    }

    void changeHead()
    {
        if (!body.empty()) {
            body[0].setTexture(chosen_head_texture);
        }
    }

    void changeTail()
    {
        if (!body.empty()) {
            if (body.size() > 1) {
                body[body.size() - 2].setTexture(nullptr);
            }

        
            body[body.size() - 1].setTexture(chosen_tail_texture);
        }
    }
};

class Fruit
{
private:
    sf::RectangleShape body;
    int counter = 0;
    int rand = std::rand() % 4 + 1; //vybere jednu ze 4 moznosti
    bool move = std::rand() % 2; //generuje jestli se bude hýbat nebo ne

public:
    Fruit() {
        body.setSize(sf::Vector2f(BLOCK_SIZE, BLOCK_SIZE));
        generate();
    }

    bool isMove() const {
        return move;
    }

    void generate() {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(0, WIDTH / BLOCK_SIZE - 1);

        int x = dis(gen) * BLOCK_SIZE;
        int y = dis(gen) * BLOCK_SIZE;

        body.setPosition(x, y);
    }

    void changeFruit()
    {
        body.setTexture(chosen_fruit_texture);
    }

    void update(std::vector<sf::RectangleShape>& snakeBody) {
    if (move) {
        if (counter <= 25) {
            if (rand == 1 && body.getPosition().x < WIDTH - BLOCK_SIZE) {
                body.move(10, 0);
            }
            else if (rand == 2 && body.getPosition().x > 0) {
                body.move(-10, 0);
            }
            else if (rand == 3 && body.getPosition().y > 0) {
                body.move(0, -10);
            }
            else if (rand == 4 && body.getPosition().y < HEIGHT - BLOCK_SIZE) {
                body.move(0, 10);
            }

            counter++;

            if (counter == 25 || body.getPosition().x >= WIDTH - BLOCK_SIZE || body.getPosition().x <= 0 || body.getPosition().y >= HEIGHT - BLOCK_SIZE || body.getPosition().y <= 0) {
                counter = 0;
                rand = std::rand() % 4 + 1;
            }

            for (auto& rect : snakeBody) {
                if (body.getGlobalBounds().intersects(rect.getGlobalBounds())) {
                    counter = 0;
                    rand = std::rand() % 4 + 1;
                }
            }
        }
    }
}

    sf::RectangleShape getBody() const { return body; }
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
    

    //načtení fontu
    sf::Font font;
    font.loadFromFile("C:\\Users\\dadul\\OneDrive\\Plocha\\PROGRAMOVANI\\programator kariera\\2\\HRA_C\\arial.ttf");//Mám retardovaný pocitac musi to byt takhle, jsem si vedoma ze to neni spravne, diky za pochopeni. :-)

    //načtení zvuků
    sf::SoundBuffer goBuffer;
    goBuffer.loadFromFile("C:\\Users\\dadul\\OneDrive\\Plocha\\PROGRAMOVANI\\programator kariera\\2\\HRA_C\\over.wav");
    sf::Sound go_sound;
    go_sound.setBuffer(goBuffer);
    sf::SoundBuffer eatBuffer;
    eatBuffer.loadFromFile("C:\\Users\\dadul\\OneDrive\\Plocha\\PROGRAMOVANI\\programator kariera\\2\\HRA_C\\eat.wav");
    sf::Sound eat_sound;
    eat_sound.setBuffer(eatBuffer);

    //načtení obrázků 
    bgTexture->loadFromFile("C:\\Users\\dadul\\OneDrive\\Plocha\\PROGRAMOVANI\\programator kariera\\2\\HRA_C\\obrazky\\bg.png");
    sf::Sprite bgSprite(*bgTexture);
    bgSprite.setTexture(*bgTexture);
    goTexture->loadFromFile("C:\\Users\\dadul\\OneDrive\\Plocha\\PROGRAMOVANI\\programator kariera\\2\\HRA_C\\obrazky\\go.png");
    sf::Sprite goSprite(*goTexture);
    goSprite.setTexture(*goTexture);
    headTexture->loadFromFile("C:\\Users\\dadul\\OneDrive\\Plocha\\PROGRAMOVANI\\programator kariera\\2\\HRA_C\\obrazky\\head.png");
    sf::Sprite headSprite(*headTexture);
    headSprite.setTexture(*headTexture);
    hlava2Texture->loadFromFile("C:\\Users\\dadul\\OneDrive\\Plocha\\PROGRAMOVANI\\programator kariera\\2\\HRA_C\\obrazky\\hlava2.png");
    sf::Sprite hlava2Sprite(*hlava2Texture);
    hlava2Sprite.setTexture(*hlava2Texture);
    hlava3Texture->loadFromFile("C:\\Users\\dadul\\OneDrive\\Plocha\\PROGRAMOVANI\\programator kariera\\2\\HRA_C\\obrazky\\hlava3.png");
    sf::Sprite hlava3Sprite(*hlava3Texture);
    hlava3Sprite.setTexture(*hlava3Texture);
    hruskaTexture->loadFromFile("C:\\Users\\dadul\\OneDrive\\Plocha\\PROGRAMOVANI\\programator kariera\\2\\HRA_C\\obrazky\\hruska.png");
    sf::Sprite hruskaSprite(*hruskaTexture);
    hruskaSprite.setTexture(*hruskaTexture);
    jablkoTexture->loadFromFile("C:\\Users\\dadul\\OneDrive\\Plocha\\PROGRAMOVANI\\programator kariera\\2\\HRA_C\\obrazky\\jablko.png");
    sf::Sprite jablkoSprite(*jablkoTexture);
    jablkoSprite.setTexture(*jablkoTexture);
    menuTexture->loadFromFile("C:\\Users\\dadul\\OneDrive\\Plocha\\PROGRAMOVANI\\programator kariera\\2\\HRA_C\\obrazky\\menu.png");
    sf::Sprite menuSprite(*menuTexture);
    menuSprite.setTexture(*menuTexture);
    ocasTexture->loadFromFile("C:\\Users\\dadul\\OneDrive\\Plocha\\PROGRAMOVANI\\programator kariera\\2\\HRA_C\\obrazky\\ocas.png");
    sf::Sprite ocasSprite(*ocasTexture);
    ocasSprite.setTexture(*ocasTexture);
    ocasek2Texture->loadFromFile("C:\\Users\\dadul\\OneDrive\\Plocha\\PROGRAMOVANI\\programator kariera\\2\\HRA_C\\obrazky\\ocasek2.png");
    sf::Sprite ocasek2Sprite(*ocasek2Texture);
    ocasek2Sprite.setTexture(*ocasek2Texture);
    ocasek3Texture->loadFromFile("C:\\Users\\dadul\\OneDrive\\Plocha\\PROGRAMOVANI\\programator kariera\\2\\HRA_C\\obrazky\\ocasek3.png");
    sf::Sprite ocasek3Sprite(*ocasek3Texture);
    ocasek3Sprite.setTexture(*ocasek3Texture);
    svestkaTexture->loadFromFile("C:\\Users\\dadul\\OneDrive\\Plocha\\PROGRAMOVANI\\programator kariera\\2\\HRA_C\\obrazky\\svestka.png");
    sf::Sprite svestkaSprite(*svestkaTexture);
    svestkaSprite.setTexture(*svestkaTexture);

    //skore
    rfile.open("High_score.txt");
    if (rfile.is_open())
    {
        std::string line;
        getline(rfile, line);
        high_score = stoi(line);
        rfile.close();
    }

    Had had;
    Fruit fruit;

    sf::Clock clock;

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
                    //chosen_head = "head";
                    //chosen_tail = "tail";
                    chosen_color = pink;
                    chosen_head_texture = headTexture;
                    chosen_tail_texture = ocasTexture;
                }
                else if (mousePos.x >= WIDTH / 2 - 80 && mousePos.x <= WIDTH / 2 + 80 && mousePos.y >= HEIGHT / 2 + 40 && mousePos.y <= HEIGHT / 2 + 80) {
                    skin_menu = false;
                    main_menu = true;
                    //chosen_head = "hlava2";
                    //chosen_tail = "ocasek2";
                    chosen_color = green;
                    chosen_head_texture = hlava2Texture;
                    chosen_tail_texture = ocasek2Texture;
                }
                else if (mousePos.x >= WIDTH / 2 - 80 && mousePos.x <= WIDTH / 2 + 80 && mousePos.y >= HEIGHT / 2 + 100 && mousePos.y <= HEIGHT / 2 + 140) {
                    skin_menu = false;
                    main_menu = true;
                    //chosen_head = "hlava3";
                    //chosen_tail = "ocasek3";
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

        else if (game==true)
        {
            window.draw(bgSprite);
            had.move();
            had.changeColor();
            //had.changeHead();
            //had.changeTail();
            
            fruit.changeFruit();
            fruit.update(had.body);

            if (had.body[0].getGlobalBounds().intersects(fruit.getBody().getGlobalBounds())) {
                had.grow();
                if (fruit.isMove()) {
                    score += 2;
                }
                else {
                    score+=1;
                }
                fruit.generate();
                eat_sound.play();
            }

            if (had.body[0].getPosition().x >= WIDTH || had.body[0].getPosition().x < 0 || had.body[0].getPosition().y >= HEIGHT || had.body[0].getPosition().y < 0) {
                go_sound.play();
                game = false;
                game_over = true;
            }
            //for (const auto& block : had.body) {
            //    window.draw(block);
            //}
           
            window.draw(fruit.getBody());
            had.draw(window);
        }

        else if (game_over==true)
        {
            window.draw(goSprite);
            drawText(font,"Game Over", 50, sf::Color::Black, WIDTH / 2 - 125, HEIGHT - 500, window);
            drawText(font,"Score: " + std::to_string(score), 30, sf::Color::Black, WIDTH / 2 - 50, HEIGHT - 400, window);
            drawText(font,"High Score: " + std::to_string(high_score), 30, sf::Color::Black, WIDTH / 2 - 100, HEIGHT - 350, window);
            if (score > high_score) {
                high_score = score;
                wfile.open("High_score.txt");
                wfile << high_score;
                wfile.close();
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