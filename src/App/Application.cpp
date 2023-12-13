#include <App/Application.hpp>

Application::Application(const sf::String strTitle, unsigned int fW, unsigned int fH, unsigned int uiBPP) {
    m_VideoMode = sf::VideoMode(sf::Vector2u(fW, fH), uiBPP);
    m_Window.create(m_VideoMode, strTitle);
    m_Window.setMinimumSize(sf::Vector2u(768, 480));
    
    // Load and set the application icon
    if (m_WindowIcon.loadFromFile(std::filesystem::path(ICON_PATH)))
        m_Window.setIcon(m_WindowIcon);

    m_GuiView.reset(sf::FloatRect(sf::Vector2f(0, 0), sf::Vector2f(fW, fH)));
    m_GuiView.setCenter(sf::Vector2f(fW / 2, fH / 2));
    
    m_ViewportView.reset(sf::FloatRect(sf::Vector2f(0, 0), sf::Vector2f(fW, fH)));
    m_ViewportView.setCenter(sf::Vector2f(fW / 2, fH / 2));
    m_Window.setView(m_GuiView);

    m_ControlPanel = ControlPanel(*this);
}

// This function handles all the drawing
void Application::render() {
    // Clear the window
    m_Window.clear(sf::Color(22, 28, 34, 255));
    // Start rendering the entire viewport
    m_Window.setView(m_ViewportView);
    // m_Window.draw(m_TestPanel);
    m_Window.draw(m_Map);

    // Start GUI rendering on GUI view
    m_Window.setView(m_GuiView);
    // Draw the GUI elements
    m_Window.draw(m_ControlPanel);

    // Display the drawn elements
    m_Window.display();
}

bool Application::run() {
    while (m_Window.isOpen()) {
        sf::Event event;
        while (m_Window.pollEvent(event)) {
            m_ControlPanel.handleEvent(event);

            if (event.type == sf::Event::Closed) {
                m_Window.close();
                return true;
            }

            if (event.type == sf::Event::Resized) {
                m_GuiView.reset(sf::FloatRect(sf::Vector2f(0, 0), sf::Vector2f(event.size.width, event.size.height)));
                m_ControlPanel.setSize(sf::Vector2f(m_ControlPanel.getSize().x, event.size.height));

                sf::Vector2f viewportCenter = m_ViewportView.getCenter();
                m_ViewportView.reset(sf::FloatRect(sf::Vector2f(0, 0), sf::Vector2f(event.size.width, event.size.height)));
                m_ViewportView.setCenter(viewportCenter);
                m_ViewportView.zoom(m_ViewportZoom);
            }

            if (event.type == sf::Event::MouseWheelScrolled) {
                if (event.mouseWheelScroll.x > m_ControlPanel.getSize().x && event.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel) {
                    if (event.mouseWheelScroll.delta > 0 && m_ViewportZoom > 0.3f) {
                        m_ViewportZoom *= (1 - ZOOM_FACTOR) * (1 - ZOOM_FACTOR);
                        m_ViewportView.zoom((1 - ZOOM_FACTOR) * (1 - ZOOM_FACTOR));
                    }
                    if (event.mouseWheelScroll.delta < 0 && m_ViewportZoom < 3.0f) {
                        m_ViewportZoom *= (1 + ZOOM_FACTOR) * (1 + ZOOM_FACTOR);
                        m_ViewportView.zoom((1 + ZOOM_FACTOR) * (1 + ZOOM_FACTOR));
                    }
                }
            }

            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.x > m_ControlPanel.getSize().x && event.mouseButton.button == sf::Mouse::Left) {
                    m_ViewportMoving = true;
                    m_MouseStartPos = sf::Vector2(event.mouseButton.x, event.mouseButton.y);
                }
            }

            if (event.type == sf::Event::MouseMoved) {
                if (m_ViewportMoving) {
                    float xDiff = event.mouseMove.x - m_MouseStartPos.x;
                    float yDiff = event.mouseMove.y - m_MouseStartPos.y;

                    float centerX = m_ViewportView.getCenter().x - xDiff * m_ViewportZoom;
                    float centerY = m_ViewportView.getCenter().y - yDiff * m_ViewportZoom;

                    m_MouseStartPos.x += xDiff;
                    m_MouseStartPos.y += yDiff;

                    m_ViewportView.setCenter(sf::Vector2f(centerX, centerY));
                }
            }

            if (event.type == sf::Event::MouseButtonReleased) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    m_ViewportMoving = false;
                }
            }
        }

        // Render the window and all its elements
        this->render();
    }

    return true;
}

Application::~Application() {}