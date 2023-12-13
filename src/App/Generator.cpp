#include <App/Generator.hpp>
#include <vector>
#include <iostream>

Generator::Generator() {}

bool Generator::generate(unsigned int uiLength, unsigned int uiAdditional) {
    // In the worst possible scenario use the size of (uiLength + uiAdditional)^2
    m_iMapW = uiLength + uiAdditional;
    m_iMapH = uiLength + uiAdditional;

    // First we need to clear the array and initialize a new one that meets the size requirements
    m_arrMap.clear();
    m_arrMap = std::vector(m_iMapH, std::vector<int>(m_iMapW));

    // Initialize the random number generator
    srand(time(NULL));

    // Generate a random starting point.
    int currX = rand() % m_iMapW;
    int currY = rand() % m_iMapH;
    m_arrMap.at(currY).at(currX) = TileDesc_t::START;

    std::vector<sf::Vector2i> pathTiles;
    pathTiles.push_back(sf::Vector2i(currX, currY));

    // Generate the main path
    unsigned int pathLen = 1;
    unsigned int tryLimit = uiLength * uiLength + 1;
    while (pathLen < uiLength && tryLimit-- > 0) {
        int dir = rand() % (TileDirection_t::LEFT + 1);

        switch (dir) {
            case TileDirection_t::UP: {
                if (currY == 0) continue;
                if (m_arrMap.at(currY - 1).at(currX) != TileDesc_t::EMPTY) continue;

                // Update current tile
                m_arrMap.at(currY).at(currX) |= TileDesc_t::T_OPEN;
                // Update the next tile
                m_arrMap.at(--currY).at(currX) |= TileDesc_t::B_OPEN;
                break;
            }

            case TileDirection_t::RIGHT: {
                if (currX == m_iMapW - 1) continue;
                if (m_arrMap.at(currY).at(currX + 1) != TileDesc_t::EMPTY) continue;

                // Update current tile
                m_arrMap.at(currY).at(currX) |= TileDesc_t::R_OPEN;
                // Update the next tile
                m_arrMap.at(currY).at(++currX) |= TileDesc_t::L_OPEN;
                break;
            }

            case TileDirection_t::DOWN: {
                if (currY == m_iMapH - 1) continue;
                if (m_arrMap.at(currY + 1).at(currX) != TileDesc_t::EMPTY) continue;

                // Update current tile
                m_arrMap.at(currY).at(currX) |= TileDesc_t::B_OPEN;
                // Update the next tile
                m_arrMap.at(++currY).at(currX) |= TileDesc_t::T_OPEN;
                break;
            }

            case TileDirection_t::LEFT: {
                if (currX == 0) continue;
                if (m_arrMap.at(currY).at(currX - 1) != TileDesc_t::EMPTY) continue;

                // Update current tile
                m_arrMap.at(currY).at(currX) |= TileDesc_t::L_OPEN;
                // Update the next tile
                m_arrMap.at(currY).at(--currX) |= TileDesc_t::R_OPEN;
                break;
            }

            default: continue;
        }

        pathTiles.push_back(sf::Vector2i(currX, currY));

        pathLen++;
        if (pathLen == uiLength) {
            m_arrMap.at(currY).at(currX) |= TileDesc_t::END;
            break;
        }
    }

    if (tryLimit == 0 || pathLen < uiLength) return false;

    // Generate the other paths
    pathLen = 0;
    int startIndex = rand() % pathTiles.size();
    currX = pathTiles.at(startIndex).x;
    currY = pathTiles.at(startIndex).y;

    while (pathLen < uiAdditional) {
        bool increment = true;
        int dir = rand() % (TileDirection_t::LEFT + 1);

        switch (dir) {
            case TileDirection_t::UP: {
                if (currY == 0) continue;
                if (m_arrMap.at(currY - 1).at(currX) != TileDesc_t::EMPTY) increment = false;

                // Update current tile
                m_arrMap.at(currY).at(currX) |= TileDesc_t::T_OPEN;
                // Update the next tile
                m_arrMap.at(--currY).at(currX) |= TileDesc_t::B_OPEN;
                break;
            }

            case TileDirection_t::RIGHT: {
                if (currX == m_iMapW - 1) continue;
                if (m_arrMap.at(currY).at(currX + 1) != TileDesc_t::EMPTY) increment = false;

                // Update current tile
                m_arrMap.at(currY).at(currX) |= TileDesc_t::R_OPEN;
                // Update the next tile
                m_arrMap.at(currY).at(++currX) |= TileDesc_t::L_OPEN;
                break;
            }

            case TileDirection_t::DOWN: {
                if (currY == m_iMapH - 1) continue;
                if (m_arrMap.at(currY + 1).at(currX) != TileDesc_t::EMPTY) increment = false;

                // Update current tile
                m_arrMap.at(currY).at(currX) |= TileDesc_t::B_OPEN;
                // Update the next tile
                m_arrMap.at(++currY).at(currX) |= TileDesc_t::T_OPEN;
                break;
            }

            case TileDirection_t::LEFT: {
                if (currX == 0) continue;
                if (m_arrMap.at(currY).at(currX - 1) != TileDesc_t::EMPTY) increment = false;

                // Update current tile
                m_arrMap.at(currY).at(currX) |= TileDesc_t::L_OPEN;
                // Update the next tile
                m_arrMap.at(currY).at(--currX) |= TileDesc_t::R_OPEN;
                break;
            }

            default: continue;
        }

        //pathTiles.push_back(sf::Vector2i(currX, currY));
        if (increment)
            pathLen++;
    }

    return true;
}

Generator::~Generator() {}