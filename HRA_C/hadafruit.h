#pragma once 
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/System/String.hpp>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <random>

class Had
{
    const int WIDTH = 600;
    const int HEIGHT = 600;
    const int BLOCK_SIZE = 50;
private:
    sf::Vector2f direction;
    char old_dir;
    sf::Color chosen_color;
   
    
public: 
    std::vector<sf::RectangleShape> body;
    Had(sf::Color chosen_colorx) {
        sf::RectangleShape head;
        chosen_color = chosen_colorx;
       
        head.setSize(sf::Vector2f(BLOCK_SIZE, BLOCK_SIZE));
        head.setFillColor(chosen_color);
        head.setPosition(WIDTH / 2, HEIGHT / 2);
        body.push_back(head);
       
    }

    void draw(sf::RenderWindow& window,sf::Texture& chosen_head_texturex, sf::Texture& chosen_tail_texturex) {
        //rotace hlavy
        sf::Sprite headSprite;
        sf::Texture chosen_head_texture = chosen_head_texturex;
        headSprite.setTexture(chosen_head_texture);
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
        sf::Texture chosen_tail_texture = chosen_tail_texture;
        tailSprite.setTexture(chosen_tail_texture);
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

    //ovladani hada a jeho smeru pohybu pomoci klavesnice
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

    //pridani bloku hada po sebrani ovoce
    void grow() {
        sf::RectangleShape newBlock;
        newBlock.setSize(sf::Vector2f(BLOCK_SIZE, BLOCK_SIZE));
        newBlock.setFillColor(chosen_color);
        newBlock.setPosition(body.back().getPosition());
        body.push_back(newBlock);
        //changeTail();
    }


    //funkce po zavolani meni barvu hada na vybranou
    void changeColor()
    {
        for (int i = 0; i < body.size(); i++)
        {
            body[i].setFillColor(chosen_color);
        }
    }

};


class Fruit
{
    const int WIDTH = 600;
    const int HEIGHT = 600;
    const int BLOCK_SIZE = 50;
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

    //funkce po zavolani meni ovoce na vybrane
    void changeFruit( sf::Texture& texture)
    {
     
        body.setTexture(&texture);
    }

    //funkce hlida, zda se ovoce nepohybuje mimo okno a zda se nepohybuje do tela hada a pripadne ho posune na jine misto a zmeni jeho smer
    void update(std::vector<sf::RectangleShape>& snakeBody) {
    //pohyb ovoce do jednoho ze 4 smeru, pohybuje se 25 snimku a pote zmeni smer
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
