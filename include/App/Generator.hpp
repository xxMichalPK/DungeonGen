#ifndef __GENERATOR_HPP__
#define __GENERATOR_HPP__

#include <vector>
#include <SFML/Graphics.hpp>

#define DEFAULT_MAP_WIDTH 10
#define DEFAULT_MAP_HEIGHT 10

typedef enum {
    EMPTY   = 0x00,
    START   = 0x01,
    END     = 0x02,
    R_OPEN  = 0x04,
    L_OPEN  = 0x08,
    T_OPEN  = 0x10,
    B_OPEN  = 0x20
} TileDesc_t;

typedef enum {
    UP = 0x00,
    RIGHT = 0x01,
    DOWN = 0x02,
    LEFT = 0x03
} TileDirection_t;

class Generator {
    private:
        int m_iMapW = DEFAULT_MAP_WIDTH;
        int m_iMapH = DEFAULT_MAP_HEIGHT;
        std::vector<std::vector<int>> m_arrMap;
    
    public:
        Generator();
        ~Generator();

        bool generate(unsigned int uiLength, unsigned int uiAdditional);

        std::vector<std::vector<int>> &getMap() { return m_arrMap; }
        int getHeight() { return m_iMapH; }
        int getWidth() { return m_iMapW; }
};

#endif