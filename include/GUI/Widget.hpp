#ifndef __WIDGET_HPP__
#define __WIDGET_HPP__

#include <SFML/Graphics.hpp>

#include <functional>

typedef enum {
    MOUSE_MOVE,
    MOUSE_HOVER,
    MOUSE_NOHOVER,
    MOUSE_PRESSED,
    MOUSE_RELEASED
} WidgetMouseEvent_t;

typedef enum {
    KEY_PRESSED,
    KEY_RELEASED
} WidgetKeyboardEvent_t;

template <typename _Widget>
class Widget : public sf::Drawable {
    public:
        std::function<void(_Widget&, WidgetMouseEvent_t, sf::Vector2f&, void*)> m_MouseCallback;
        std::function<void(_Widget&, WidgetKeyboardEvent_t, void*)> m_KeyboardCallback;

    public:
        void setMouseCallback(std::function<void(_Widget&, WidgetMouseEvent_t, sf::Vector2f&, void*)> newCallback) { m_MouseCallback = newCallback; }

    protected:
        virtual void triggerMouseEvent(WidgetMouseEvent_t event, sf::Vector2f mousePos, void* param) = 0;
    
    private:
        void draw(sf::RenderTarget& target, const sf::RenderStates& states) const override = 0;
};

#endif