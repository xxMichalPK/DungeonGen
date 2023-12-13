#ifndef __BUTTON_HPP__
#define __BUTTON_HPP__

#include <SFML/Graphics.hpp>
#include <GUI/Widget.hpp>

class Button : public Widget<Button> {
    private:
        sf::RectangleShape m_ButtonShape;

        std::uint32_t m_CharSize = 30;
        sf::Font m_ButtonFont;
        sf::Color m_FGColor = sf::Color::White;
        sf::Color m_BGColor = sf::Color::Black;
        sf::String m_ButtonText;

    public:
        Button();
        Button(const sf::String& text, sf::Vector2f position, sf::Vector2f size,
                sf::Font& font, std::uint32_t charSize = 30,
                sf::Color bgColor = sf::Color::Black, sf::Color fgColor = sf::Color::White,
                sf::Color borderColor = sf::Color{ 0x333333FF }, float borderThickness = 1);
        ~Button();

        sf::FloatRect getGlobalBounds() { return m_ButtonShape.getGlobalBounds(); }

        void triggerMouseEvent(WidgetMouseEvent_t event, sf::Vector2f mousePos, void* param) override;

        void onMouseHover() { this->m_ButtonShape.setFillColor( m_BGColor + sf::Color(0x1A1A1A00) ); };
        void onMouseLeave() { this->m_ButtonShape.setFillColor( m_BGColor ); };

        sf::Vector2f getPosition() { return m_ButtonShape.getPosition(); }
        void setPosition(sf::Vector2f position) { m_ButtonShape.setPosition(position); }

    private:
        void draw(sf::RenderTarget& target, const sf::RenderStates& states) const override;
};

#endif