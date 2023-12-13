#include <GUI/Button.hpp>

Button::Button() {}

Button::Button(const sf::String& text, sf::Vector2f position, sf::Vector2f size,
                sf::Font& font, std::uint32_t charSize,
                sf::Color bgColor, sf::Color fgColor,
                sf::Color borderColor, float borderThickness) {
    
    m_ButtonText = text;
    m_ButtonFont = font;
    m_CharSize = charSize;
    m_FGColor = fgColor;
    m_BGColor = bgColor;

    m_ButtonShape.setPosition(position);
    m_ButtonShape.setSize(size);
    m_ButtonShape.setFillColor(bgColor);
    m_ButtonShape.setOutlineColor(borderColor);
    m_ButtonShape.setOutlineThickness(borderThickness);
}

Button::~Button() {}

void Button::draw(sf::RenderTarget& target, const sf::RenderStates& states) const {
    sf::Text buttonText(m_ButtonFont, m_ButtonText, m_CharSize);
    buttonText.setOrigin(buttonText.getGlobalBounds().getSize() / 2.f);
    float textX = (m_ButtonShape.getPosition().x + (m_ButtonShape.getGlobalBounds().width / 2.f));
    float textY = (m_ButtonShape.getPosition().y + (m_ButtonShape.getGlobalBounds().height / 2.f)) - (buttonText.getGlobalBounds().height / 2.f);
    buttonText.setPosition(sf::Vector2f(textX, textY));
    buttonText.setFillColor(m_FGColor);

    target.draw(m_ButtonShape);
    target.draw(buttonText);
}

void Button::triggerMouseEvent(WidgetMouseEvent_t event, sf::Vector2f mousePos, void* param) {
    if (!m_MouseCallback) return;

    switch (event) {
        case WidgetMouseEvent_t::MOUSE_MOVE: {
            if (getGlobalBounds().contains(mousePos)) m_MouseCallback(*this, WidgetMouseEvent_t::MOUSE_HOVER, mousePos, param);
            else m_MouseCallback(*this, WidgetMouseEvent_t::MOUSE_NOHOVER, mousePos, param);
            
            m_MouseCallback(*this, event, mousePos, param);
            break;
        }
        default:
            if (getGlobalBounds().contains(mousePos)) m_MouseCallback(*this, event, mousePos, param);
    }
}