#ifndef __SLIDER_HPP__
#define __SLIDER_HPP__

#include <SFML/Graphics.hpp>
#include <GUI/Widget.hpp>

class Slider : public Widget<Slider> {
    private:
        sf::RectangleShape m_FilledArea;
        sf::RectangleShape m_ClearArea;
        sf::CircleShape m_SliderHandle;

        sf::Vector2f m_SliderSize;

        sf::Font m_SliderFont;
        sf::Color m_FGColor = sf::Color::White;
        sf::Color m_BGColor = sf::Color::Black;
        
        int m_MinValue = 0;
        int m_MaxValue = 99;
        int m_Value = 0;

        bool m_Dragging = false;

    public:
        Slider();
        Slider(sf::Vector2f position, sf::Vector2f size,
                sf::Font& font, int minValue = 0, int maxValue = 99,
                sf::Color bgColor = sf::Color::Black, sf::Color fgColor = sf::Color::White,
                sf::Color borderColor = sf::Color{ 0x333333FF }, float thickness = 1);
        ~Slider();

        int &getValue() { return m_Value; }
        void triggerMouseEvent(WidgetMouseEvent_t event, sf::Vector2f mousePos, void* param) override;

    private:
        void handleDragEvent(sf::Vector2f mousePos);
        void draw(sf::RenderTarget& target, const sf::RenderStates& states) const override;
};

#endif