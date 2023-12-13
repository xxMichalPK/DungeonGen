#ifndef __APPLICATION_HPP__
#define __APPLICATION_HPP__

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include <App/Tilemap.hpp>
#include <App/Generator.hpp>

#include <GUI/ControlPanel.hpp>

#define ZOOM_FACTOR 0.1f

#define SPRITE_WIDTH 32
#define SPRITE_HEIGHT 32

// The icon has to be png because SFML doesn't support ICO files?
#define ICON_PATH L"resources/icon.png"

#define TILESET_PATH L"resources/tileset.png"
#define ROBOTO_BLACK_PATH L"resources/fonts/Roboto-Black.ttf"
#define ROBOTO_REGULAR_PATH L"resources/fonts/Roboto-Regular.ttf"
#define ROBOTO_LIGHT_PATH L"resources/fonts/Roboto-Light.ttf"

class Application {
    private:
        // Window stuff
        sf::RenderWindow m_Window;
        sf::VideoMode m_VideoMode;
        sf::Image m_WindowIcon;

        // Viewports
        sf::View m_ViewportView;
        sf::View m_GuiView;

        // Mouse related variables for viewport movement
        bool m_ViewportMoving = false;
        float m_ViewportZoom = 1;
        sf::Vector2<int> m_MouseStartPos;

        // "GUI" elements
        ControlPanel m_ControlPanel;
        TileMap m_Map;

        // The map generator
        Generator m_MapGen;

        void render();

    public:
        // The default constructor
        Application(const sf::String strTitle, unsigned int fW, unsigned int fH, unsigned int uiBPP = 32U);
        ~Application();

        sf::RenderWindow& getWindow() { return m_Window; }
        Generator& getGenerator() { return m_MapGen; }
        TileMap& getTilemap() { return m_Map; }
        sf::View& getViewportView() { return m_ViewportView; }
        float& getViewportZoom() { return m_ViewportZoom; }

        // The main application procedure - "infinite" event loop
        bool run();
};

#endif