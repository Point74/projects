#include "Image.h"

#include <iostream>
#include <filesystem>


namespace fs = std::filesystem;


Image::Image(string file) : fileName(std::move(file)) {}

void Image::load() {
    string fullPath = getFullPathToFile(fileName);

    if (!texture.loadFromFile(fullPath))
        cerr << "Failed to load image: " << fullPath << endl;

    else sprite.setTexture(texture);
}

string Image::getFullPathToFile(const string& relativePath) {
    fs::path exePath = fs::current_path();
    fs::path fullPath = exePath / "../" / relativePath;

    return fullPath.lexically_normal().string();
}

void Image::display(sf::RenderWindow& window) {
    window.draw(sprite);
}

void Image::setPosition(float x, float y) {
    sprite.setPosition(x, y);
}

sf::Vector2f Image::getPosition() {
    return sprite.getPosition();
}