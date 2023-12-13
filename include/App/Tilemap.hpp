#ifndef __TILEMAP_HPP__
#define __TILEMAP_HPP__

#include <SFML/Graphics.hpp>
#include <vector>

class TileMap : public sf::Drawable, public sf::Transformable {
    private:
        sf::VertexArray m_vertices;
        sf::Texture m_tileset;
    
    public:
        bool load(const sf::String& tileset, sf::Vector2u tileSize, std::vector<std::vector<int>> &tiles, unsigned int width, unsigned int height);
    
    private:
        void draw(sf::RenderTarget& target, const sf::RenderStates& states) const override;
};

#endif