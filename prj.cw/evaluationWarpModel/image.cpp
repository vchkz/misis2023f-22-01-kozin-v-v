#include "image.h"
#include <nfd.h>
#include <opencv2/opencv.hpp>
#include <vector>
#include <ctime>

Image::Image() = default;

float Image::transparency = 0.5f;
float Image::pointRadius = 8.0f;

void Image::openImage() {
    nfdchar_t *outPath = nullptr;
    nfdresult_t result = NFD_OpenDialog(nullptr, nullptr, &outPath);
    if (result == NFD_OKAY) {
        if (!texture.loadFromFile(outPath)) {
            exit(EXIT_FAILURE);
        }
        is_opened = true;
        sprite.setTexture(texture);
        ast = Asterism(cv::Rect(0, 0, texture.getSize().x, texture.getSize().y));
        drawPicture();
    } else {
        std::cout << "nfd error" << std::endl;
    }
}



void Image::drawPicture() {
    internalTexture.clear();
    internalTexture.draw(sprite);
}

void Image::drawPicture(sf::Sprite overlaySprite) {
    drawPicture();
    overlaySprite.setColor(sf::Color(255, 255, 255, transparency * 255));
    internalTexture.draw(overlaySprite);
}

void Image::importPoints() {
    nfdchar_t *outPath = nullptr;
    nfdresult_t result = NFD_OpenDialog("txt", nullptr, &outPath);
    if (result == NFD_OKAY) {
        ast.loadPts(outPath);
    } else {
        std::cout << "nfd error" << std::endl;
    }
}



