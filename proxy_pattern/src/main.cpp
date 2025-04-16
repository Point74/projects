#include "SFML/Graphics.hpp"
#include "Image.h"
#include "ProxyImage.h"
#include "MouseController.h"


using namespace std;


int main() {
    sf::RenderWindow window(sf::VideoMode(2000, 2000), "Image");

    window.setFramerateLimit(60);

    ProxyImage proxyImage(1000.0f, 1000.0f, "images/photo.png");
    MouseController mouseController(&proxyImage);

    while (window.isOpen()) {
        sf::Event event{};

        while (window.pollEvent(event)) {
            // если нажали крестик — закрыть окно
            if (event.type == sf::Event::Closed)
                window.close();

            mouseController.handleEvent(event, window);
        }

        window.clear(sf::Color::White);

        // рисуем рамку или изображение
        proxyImage.display(window);

        // отображаем всё, что нарисовали
        window.display();
    }

    return 0;
}