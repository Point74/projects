#include "MouseController.h"


MouseController::MouseController(ProxyImage* image) :
    proxyImage(image), isDragging(false), clickCount(0) {}

void MouseController::handleEvent(sf::Event event, sf::RenderWindow& window) {
    if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Left) {
            if (clickClock.getElapsedTime().asMilliseconds() < 300) {
                clickCount++;

            } else clickCount = 1;

            clickClock.restart();

            if (clickCount == 2) {
                proxyImage->onRightDoubleClick();
                clickCount = 0;

            } else if (clickCount == 1) {
                isDragging = true;
                sf::Vector2f mousePosition(event.mouseButton.x, event.mouseButton.y);
                offset = mousePosition - proxyImage->getPosition();
            }
        }
    }

    if (event.type == sf::Event::MouseButtonReleased) {
        if (event.mouseButton.button == sf::Mouse::Left) {
            isDragging = false;
        }
    }

    if (event.type == sf::Event::MouseMoved) {
        if (isDragging) {
            sf::Vector2f mousePosition(event.mouseMove.x, event.mouseMove.y);
            proxyImage->moveTo(mousePosition.x - offset.x, mousePosition.y - offset.y);
        }
    }
}