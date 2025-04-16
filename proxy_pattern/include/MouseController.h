#pragma once

#include "SFML/Graphics.hpp"
#include "ProxyImage.h"

#include <string>

using namespace std;

class MouseController {
    ProxyImage* proxyImage;
    bool isDragging;
    sf::Vector2f offset;
    int clickCount;
    sf::Clock clickClock;

public:
    MouseController(ProxyImage* image);

    void handleEvent(sf::Event event, sf::RenderWindow& window);
};
