#pragma once

#include "SFML/Graphics.hpp"
#include "Image.h"

#include <string>


using namespace std;


class ProxyImage {
    Image* realImage;
    sf::RectangleShape box;
    string fileName;
    bool isImageLoad;

public:
    ProxyImage(float width, float height, string file);

    ~ProxyImage();

    void display(sf::RenderWindow& window);

    void moveTo(float x, float y);

    void onRightDoubleClick();

    sf::Vector2f getPosition();
};