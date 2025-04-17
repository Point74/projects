#include "SFML/Graphics.hpp"
#include "Image.h"
#include "ProxyImage.h"
#include "MouseController.h"


using namespace std;


int main() {
    sf::RenderWindow window(sf::VideoMode(800, 800), "Image");

    window.setFramerateLimit(60);

    sf::View view(sf::FloatRect(0, 0, 800, 800));
    window.setView(view);

    ProxyImage proxyImage(400.0f, 400.0f, "images/testImage.png");
    MouseController mouseController(&proxyImage);

    while (window.isOpen()) {
        sf::Event event{};

        while (window.pollEvent(event)) {
            // если нажали крестик — закрыть окно
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::Resized) {
                view.setSize(event.size.width, event.size.height);
                view.setCenter(event.size.width / 2, event.size.height / 2);

                window.setView(view);
            }

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