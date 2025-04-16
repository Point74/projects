#pragma once

#include "SFML/Graphics.hpp"

#include <string>


using namespace std;


class Image {
    sf::Texture texture; // загрузить картинку
    sf::Sprite sprite; // отобразить картинку
    string fileName;

    string getFullPathToFile(const string& relativePath);

public:
    Image(string file);

    void load();

    void display(sf::RenderWindow& window);

    void setPosition(float x, float y);

    sf::Vector2f getPosition();
};