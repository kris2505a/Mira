#include "Sprite.h"
#include "stb_image.h"
#include <iostream>

Sprite::Sprite(const std::string& path, SDL_Renderer* renderer) : m_texture(nullptr), m_viewBoxEnabled(false) {

    int width, height, channels;
    unsigned char* imageData = stbi_load(path.c_str(), &width, &height, &channels, 4);

    if (imageData == nullptr)
        std::cout << stbi_failure_reason() << std::endl;

    m_boundingBox.w = width / 2;
    m_boundingBox.h = height / 2;
    m_boundingBox.x = 0;
    m_boundingBox.y = 0;

    SDL_Surface* surface = SDL_CreateRGBSurfaceFrom(
        imageData, width, height, 32, width * 4, 0x000000FF, 0x0000FF00, 0x00FF0000, 0xFF000000
    );
    
    m_texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    stbi_image_free(imageData);
}

Sprite::~Sprite() {
    SDL_DestroyTexture(m_texture);
}

void Sprite::render(SDL_Renderer* renderer) {

    if (m_viewBoxEnabled)
        SDL_RenderCopy(renderer, m_texture, &m_viewBox, &m_boundingBox);
    else
        SDL_RenderCopy(renderer, m_texture, nullptr, &m_boundingBox);
}

void Sprite::update(const float& deltaTime) {

}

void Sprite::setView(const Vector2D<float>& size) {
    m_viewBoxEnabled = true;
    m_viewBox.x = 0;
    m_viewBox.y = 0;
    m_viewBox.w = size.x;
    m_viewBox.h = size.y;
}