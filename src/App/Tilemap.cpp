#include <App/Tilemap.hpp>

bool TileMap::load(const sf::String& tileset, sf::Vector2u tileSize, std::vector<std::vector<int>> &tiles, unsigned int width, unsigned int height) {
    // load the tileset texture
    if (!m_tileset.loadFromFile(std::filesystem::path(tileset)))
        return false;

    // resize the vertex array to fit the level size
    m_vertices.setPrimitiveType(sf::PrimitiveType::Triangles);
    m_vertices.resize(width * height * 6);

    // populate the vertex array, with two triangles per tile
    for (unsigned int i = 0; i < height; ++i) {
        for (unsigned int j = 0; j < width; ++j) {
            // get the current tile number
            int tileNumber = tiles.at(i).at(j);

            // find its position in the tileset texture
            int tu = tileNumber % (m_tileset.getSize().x / tileSize.x);
            int tv = tileNumber / (m_tileset.getSize().x / tileSize.x);

            // get a pointer to the triangles' vertices of the current tile
            sf::Vertex* triangles = &m_vertices[(j + i * width) * 6];

            // define the 6 corners of the two triangles
            triangles[0].position = sf::Vector2f(j * tileSize.x, i * tileSize.y);
            triangles[1].position = sf::Vector2f((j + 1) * tileSize.x, i * tileSize.y);
            triangles[2].position = sf::Vector2f(j * tileSize.x, (i + 1) * tileSize.y);
            triangles[3].position = sf::Vector2f(j * tileSize.x, (i + 1) * tileSize.y);
            triangles[4].position = sf::Vector2f((j + 1) * tileSize.x, i * tileSize.y);
            triangles[5].position = sf::Vector2f((j + 1) * tileSize.x, (i + 1) * tileSize.y);

            // define the 6 matching texture coordinates
            triangles[0].texCoords = sf::Vector2f(tu * tileSize.x, tv * tileSize.y);
            triangles[1].texCoords = sf::Vector2f((tu + 1) * tileSize.x, tv * tileSize.y);
            triangles[2].texCoords = sf::Vector2f(tu * tileSize.x, (tv + 1) * tileSize.y);
            triangles[3].texCoords = sf::Vector2f(tu * tileSize.x, (tv + 1) * tileSize.y);
            triangles[4].texCoords = sf::Vector2f((tu + 1) * tileSize.x, tv * tileSize.y);
            triangles[5].texCoords = sf::Vector2f((tu + 1) * tileSize.x, (tv + 1) * tileSize.y);
        }
    }
    
    return true;
}

void TileMap::draw(sf::RenderTarget& target, const sf::RenderStates& states) const {
    sf::RenderStates statesCopy(states);

    // apply the transform
    statesCopy.transform *= getTransform();

    // apply the tileset texture
    statesCopy.texture = &m_tileset;

    // draw the vertex array
    target.draw(m_vertices, statesCopy);
}