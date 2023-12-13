#ifndef __CONTROLPANEL_HPP__
#define __CONTROLPANEL_HPP__

#include <SFML/Graphics.hpp>

#include <GUI/Widget.hpp>
#include <GUI/Button.hpp>
#include <GUI/Slider.hpp>

#include <App/Generator.hpp>
#include <App/Tilemap.hpp>

class Application;

static sf::View* g_ViewportView = NULL;
static Generator* g_MapGen = NULL;
static TileMap* g_Map = NULL;
static Application* g_Application = NULL;

static int g_PathLen = 5;
static int g_AdditionalTilesCount = 5;

class ControlPanel : public sf::Drawable, public sf::Transformable {
    private:
        sf::RectangleShape m_PanelBG;
        sf::Font m_HeaderBoldFont;
        sf::Font m_HeaderRegularFont;
        sf::Font m_HeaderLightFont;
        Button m_GenerateBtn;
        Button m_ExitBtn;

        Slider m_PathLengthSlider;
        Slider m_AdditionalTileCountSlider;

        sf::Vector2f m_PanelSize;

    public:
        ControlPanel();
        ControlPanel(Application &parent);
        ~ControlPanel();

        void handleEvent(sf::Event& event);

        void setSize(sf::Vector2f size);
        void setSize(sf::Vector2f &size);
        sf::Vector2f &getSize();
    
    protected:
        void generateBtnCallback(Button& sender, WidgetMouseEvent_t event, sf::Vector2f& mousePos, void* param);
        void exitBtnCallback(Button& sender, WidgetMouseEvent_t event, sf::Vector2f& mousePos, void* param);
    
    private:
        void draw(sf::RenderTarget& target, const sf::RenderStates& states) const override;
};

#endif