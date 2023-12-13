#include <GUI/Slider.hpp>
#include <cmath>

Slider::Slider() {}
Slider::Slider(sf::Vector2f position, sf::Vector2f size,
                sf::Font& font, int minValue, int maxValue,
                sf::Color bgColor, sf::Color fgColor,
                sf::Color borderColor, float thickness) {
    
    m_SliderFont = font;
    m_FGColor = fgColor;
    m_BGColor = bgColor;
    m_Value = minValue;
    m_MinValue = minValue;
    m_MaxValue = maxValue;

    sf::Vector2f filledSize(0.f, thickness);
    sf::Vector2f clearSize(size.x - 35, thickness);
    m_FilledArea.setSize(filledSize);
    m_ClearArea.setSize(clearSize);

    m_SliderSize = size;

    m_FilledArea.setFillColor(borderColor);
    m_ClearArea.setFillColor(bgColor);

    m_FilledArea.setPosition(position);
    m_ClearArea.setPosition(position);

    m_SliderHandle.setRadius(6);
    m_SliderHandle.setOrigin(m_SliderHandle.getGlobalBounds().getSize() / 2.f);
    m_SliderHandle.setPosition(sf::Vector2f(m_ClearArea.getPosition().x, m_ClearArea.getPosition().y + m_ClearArea.getSize().y / 2.f));
    m_SliderHandle.setFillColor(borderColor);
}

Slider::~Slider() {}


void Slider::draw(sf::RenderTarget& target, const sf::RenderStates& states) const {
    sf::Text value(m_SliderFont, sf::String(std::to_string(m_Value)), 20);
    value.setOrigin(sf::Vector2f(value.getGlobalBounds().getPosition().x, value.getGlobalBounds().getSize().y / 2.f));
    float valSize = value.getGlobalBounds().width;
    value.setPosition(sf::Vector2f(m_ClearArea.getPosition().x + m_ClearArea.getSize().x + 10, m_ClearArea.getPosition().y - m_ClearArea.getSize().y / 2));
    value.setFillColor(m_FGColor);

    target.draw(m_ClearArea);
    target.draw(m_FilledArea);
    target.draw(m_SliderHandle);
    target.draw(value);
}

void Slider::handleDragEvent(sf::Vector2f mousePos) {
    float maxXPos = m_ClearArea.getPosition().x + m_ClearArea.getSize().x;
    float minXPos = 20;
    float handleXPos = __max(minXPos, __min(mousePos.x, maxXPos));

    m_SliderHandle.setPosition(sf::Vector2f(handleXPos, m_SliderHandle.getPosition().y));
    m_FilledArea.setSize(sf::Vector2f(handleXPos - m_FilledArea.getPosition().x, m_FilledArea.getSize().y));

    float percent = (handleXPos - minXPos) / (maxXPos - minXPos);
    m_Value = round((m_MaxValue - m_MinValue) * percent) + m_MinValue;
}

void Slider::triggerMouseEvent(WidgetMouseEvent_t event, sf::Vector2f mousePos, void* param) {
    switch (event) {
        case WidgetMouseEvent_t::MOUSE_MOVE: {
            if (m_Dragging) {
                handleDragEvent(mousePos);
            }

            if (m_MouseCallback) {
                if (m_FilledArea.getGlobalBounds().contains(mousePos) || m_SliderHandle.getGlobalBounds().contains(mousePos))
                    m_MouseCallback(*this, WidgetMouseEvent_t::MOUSE_HOVER, mousePos, param);
                else
                    m_MouseCallback(*this, WidgetMouseEvent_t::MOUSE_NOHOVER, mousePos, param);
                
                m_MouseCallback(*this, event, mousePos, param);
            }
            break;
        }

        case WidgetMouseEvent_t::MOUSE_PRESSED: {
            sf::Mouse::Button button = *(sf::Mouse::Button*)(param);
            if (m_SliderHandle.getGlobalBounds().contains(mousePos) && button == sf::Mouse::Button::Left) m_Dragging = true;
            break;
        }

        case WidgetMouseEvent_t::MOUSE_RELEASED: {
            m_Dragging = false;
        }

        default: 
            if (m_MouseCallback) m_MouseCallback(*this, event, mousePos, param);
    }
}