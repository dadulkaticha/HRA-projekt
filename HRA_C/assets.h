#pragma once 
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>


class Assets{
private:
 sf::Font font;
 sf::Music go_sound;
 sf::Music eat_sound;
 sf::Texture bgTexture;
 sf::Texture goTexture;
 sf::Texture headTexture;
 sf::Texture hlava2Texture;
 sf::Texture hlava3Texture;
 sf::Texture hruskaTexture;
 sf::Texture jablkoTexture;
 sf::Texture menuTexture;
 sf::Texture ocasTexture;
 sf::Texture ocasek2Texture;
 sf::Texture ocasek3Texture;
 sf::Texture svestkaTexture;
    
public:
Assets(){}

sf::Font& getFont()
{
    font.loadFromFile("C:\\Users\\dadul\\OneDrive\\Plocha\\PROGRAMOVANI\\programator kariera\\2\\HRA_C\\arial.ttf");//mam retardovany pocitac musi to byt takhle, jsem si vedoma ze to neni spravne, diky za pochopeni :-)
    return font;
}

sf::Music& getgosound()
{
  
    go_sound.openFromFile("C:\\Users\\dadul\\OneDrive\\Plocha\\PROGRAMOVANI\\programator kariera\\2\\HRA_C\\over.wav");
    return go_sound;
}

sf::Music& geteatsound()
{
   
     eat_sound.openFromFile("C:\\Users\\dadul\\OneDrive\\Plocha\\PROGRAMOVANI\\programator kariera\\2\\HRA_C\\eat.wav");
   
    return eat_sound;
}

sf::Sprite getBgsprite()
{
    bgTexture.loadFromFile("C:\\Users\\dadul\\OneDrive\\Plocha\\PROGRAMOVANI\\programator kariera\\2\\HRA_C\\obrazky\\bg.png");
    sf::Sprite bgsprite(bgTexture);
    return bgsprite;
}

sf::Sprite getgosprite()
{
    goTexture.loadFromFile("C:\\Users\\dadul\\OneDrive\\Plocha\\PROGRAMOVANI\\programator kariera\\2\\HRA_C\\obrazky\\go.png");
    sf::Sprite gosprite(goTexture);
    return gosprite;
}

sf::Texture getheadtexture()
{
    headTexture.loadFromFile("C:\\Users\\dadul\\OneDrive\\Plocha\\PROGRAMOVANI\\programator kariera\\2\\HRA_C\\obrazky\\head.png");

    return headTexture;
}

sf::Texture& gethlava2texture()
{
    hlava2Texture.loadFromFile("C:\\Users\\dadul\\OneDrive\\Plocha\\PROGRAMOVANI\\programator kariera\\2\\HRA_C\\obrazky\\hlava2.png");
    return hlava2Texture;

}

sf::Texture& gethlava3texture()
{
    hlava3Texture.loadFromFile("C:\\Users\\dadul\\OneDrive\\Plocha\\PROGRAMOVANI\\programator kariera\\2\\HRA_C\\obrazky\\hlava3.png");
    return hlava3Texture;
}

sf::Texture& gethruskatexture()
{
    hruskaTexture.loadFromFile("C:\\Users\\dadul\\OneDrive\\Plocha\\PROGRAMOVANI\\programator kariera\\2\\HRA_C\\obrazky\\hruska.png");
    return hruskaTexture;
}

sf::Texture& getjablkotexture()
{
    jablkoTexture.loadFromFile("C:\\Users\\dadul\\OneDrive\\Plocha\\PROGRAMOVANI\\programator kariera\\2\\HRA_C\\obrazky\\jablko.png");
    return jablkoTexture;
}

sf::Sprite getmenusprite()
{
    menuTexture.loadFromFile("C:\\Users\\dadul\\OneDrive\\Plocha\\PROGRAMOVANI\\programator kariera\\2\\HRA_C\\obrazky\\menu.png");
    sf::Sprite menuSprite (menuTexture);
    return menuSprite;
}

sf::Texture& getocastexture()
{
    ocasTexture.loadFromFile("C:\\Users\\dadul\\OneDrive\\Plocha\\PROGRAMOVANI\\programator kariera\\2\\HRA_C\\obrazky\\ocas.png");
    return ocasTexture;
}

sf::Texture& getocasek2texture()
{
    ocasek2Texture.loadFromFile("C:\\Users\\dadul\\OneDrive\\Plocha\\PROGRAMOVANI\\programator kariera\\2\\HRA_C\\obrazky\\ocasek2.png");
    return ocasek2Texture;
}

sf::Texture& getocasek3texture()
{
    ocasek3Texture.loadFromFile("C:\\Users\\dadul\\OneDrive\\Plocha\\PROGRAMOVANI\\programator kariera\\2\\HRA_C\\obrazky\\ocasek3.png");
    return ocasek3Texture;
}

sf::Texture& getsvestkatexture()
{
     svestkaTexture.loadFromFile("C:\\Users\\dadul\\OneDrive\\Plocha\\PROGRAMOVANI\\programator kariera\\2\\HRA_C\\obrazky\\svestka.png");
     return svestkaTexture;
}




};