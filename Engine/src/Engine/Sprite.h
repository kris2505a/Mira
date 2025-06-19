#pragma once
#include <SDL.h>
#include <string>
#include "Entity.h"
#include "Core.h"

class API Sprite : public Entity {
private:
    SDL_Texture* m_texture;
    SDL_Rect m_viewBox;
    SDL_Rect m_boundingBox;
    
    bool m_viewBoxEnabled;


public:
    virtual void render(SDL_Renderer* renderer) override;
    virtual void update(const float& deltaTime) override;

    Sprite(const std::string& path, SDL_Renderer* renderer);
    ~Sprite();
    void setView(const Vector2D<float>& size);
        
};