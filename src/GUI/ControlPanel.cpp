#include <GUI/ControlPanel.hpp>
#include <App/Application.hpp>
#include <iostream>

void ControlPanel::generateBtnCallback(Button& sender, WidgetMouseEvent_t event, sf::Vector2f& mousePos, void* param) {
    switch (event) {
        case WidgetMouseEvent_t::MOUSE_HOVER: {
            sender.onMouseHover();
            break;
        }

        case WidgetMouseEvent_t::MOUSE_NOHOVER: {
            sender.onMouseLeave();
            break;
        }

        case WidgetMouseEvent_t::MOUSE_PRESSED: {
            sf::Mouse::Button button = *(sf::Mouse::Button*)(param);
            if (button != sf::Mouse::Button::Left) break;

            // Left button pressed
            float zoom = g_Application->getViewportZoom();
            while (!g_MapGen->generate(g_PathLen, g_AdditionalTilesCount));
            g_Map->load(TILESET_PATH, sf::Vector2u(SPRITE_WIDTH, SPRITE_HEIGHT), g_MapGen->getMap(), g_MapGen->getWidth(), g_MapGen->getHeight());
            g_ViewportView->setCenter(sf::Vector2f(g_MapGen->getWidth() * (SPRITE_WIDTH / 2) - getSize().x / 2 * zoom, g_MapGen->getHeight() * (SPRITE_HEIGHT / 2)));
            break;
        }
    }
}
void ControlPanel::exitBtnCallback(Button& sender, WidgetMouseEvent_t event, sf::Vector2f& mousePos, void* param) {
    switch (event) {
        case WidgetMouseEvent_t::MOUSE_HOVER: {
            sender.onMouseHover();
            break;
        }

        case WidgetMouseEvent_t::MOUSE_NOHOVER: {
            sender.onMouseLeave();
            break;
        }

        case WidgetMouseEvent_t::MOUSE_PRESSED: {
            sf::Mouse::Button button = *(sf::Mouse::Button*)(param);
            if (button != sf::Mouse::Button::Left) break;

            // Left button pressed
            g_Application->getWindow().close();
        }
    }
}

ControlPanel::ControlPanel() {}
ControlPanel::ControlPanel(Application &parent) { 
    g_Application = &parent;
    g_MapGen = &g_Application->getGenerator();
    g_Map = &g_Application->getTilemap();
    g_ViewportView = &g_Application->getViewportView();

    if (!m_HeaderBoldFont.loadFromFile(std::filesystem::path(ROBOTO_BLACK_PATH)));
    if (!m_HeaderRegularFont.loadFromFile(std::filesystem::path(ROBOTO_REGULAR_PATH)));
    if (!m_HeaderLightFont.loadFromFile(std::filesystem::path(ROBOTO_LIGHT_PATH)));

    m_PanelSize = sf::Vector2f(300.f, g_Application->getWindow().getSize().y);

    m_PanelBG.setPosition(sf::Vector2f(0.f, 0.f));
    m_PanelBG.setSize(m_PanelSize);
    m_PanelBG.setFillColor(sf::Color(17, 23, 29, 255));

    m_PanelBG.setOutlineThickness(1.4);
    m_PanelBG.setOutlineColor(sf::Color(182, 20, 59, 255));

    m_GenerateBtn = Button(L"Generate",
                            sf::Vector2f(20.f, 250.f), sf::Vector2f(260.f, 40.f),
                            m_HeaderLightFont, 22,
                            sf::Color(182, 20, 59, 70), sf::Color(182, 20, 59, 255),
                            sf::Color(182, 20, 59, 255), 1.f
                          );
    
    m_ExitBtn = Button(L"Exit",
                            sf::Vector2f(20.f, getSize().y - 60.f), sf::Vector2f(260.f, 40.f),
                            m_HeaderLightFont, 22,
                            sf::Color(182, 20, 59, 70), sf::Color(182, 20, 59, 255),
                            sf::Color(182, 20, 59, 255), 1.f
                          );

    m_PathLengthSlider = Slider(sf::Vector2f(20.f, 145.f), sf::Vector2f(260.f, 30.f), 
                                m_HeaderRegularFont, 5, 20,
                                sf::Color(182, 20, 59, 70), sf::Color(182, 20, 59, 255),
                                sf::Color(182, 20, 59, 255), 4.f
                               );
    
    m_AdditionalTileCountSlider = Slider(sf::Vector2f(20.f, 215.f), sf::Vector2f(260.f, 30.f), 
                                m_HeaderRegularFont, 5, 20,
                                sf::Color(182, 20, 59, 70), sf::Color(182, 20, 59, 255),
                                sf::Color(182, 20, 59, 255), 4.f
                               );

    auto generateCallback = std::bind(&generateBtnCallback, *this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4);
    auto exitCallback = std::bind(&exitBtnCallback, *this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4);
    m_GenerateBtn.setMouseCallback(generateCallback);
    m_ExitBtn.setMouseCallback(exitCallback);
}

void ControlPanel::setSize(sf::Vector2f size) {
    m_PanelSize = size;
    m_PanelBG.setSize(m_PanelSize);
}
void ControlPanel::setSize(sf::Vector2f &size) {
    m_PanelSize = size;
    m_PanelBG.setSize(m_PanelSize);
}

sf::Vector2f &ControlPanel::getSize() {
    return m_PanelSize;
}

void ControlPanel::draw(sf::RenderTarget& target, const sf::RenderStates& states) const {
    sf::Text headerText(m_HeaderBoldFont, L"DUNGEON GENERATOR", 24);
    headerText.setFillColor(sf::Color(140, 144, 154, 255));
    headerText.setPosition(sf::Vector2f(20.f, 20.f));

    sf::Text authorText(m_HeaderLightFont, L"by Michał Pazurek", 20);
    authorText.setFillColor(sf::Color(140, 144, 154, 255));
    authorText.setPosition(sf::Vector2f(20.f, 44.f));

    sf::Text pathLenSliderText(m_HeaderRegularFont, L"Main path length:", 20);
    pathLenSliderText.setFillColor(sf::Color(140, 144, 154, 255));
    pathLenSliderText.setPosition(sf::Vector2f(20.f, 105.f));

    sf::Text additionalTilesCountText(m_HeaderRegularFont, L"Additional tiles count:", 20);
    additionalTilesCountText.setFillColor(sf::Color(140, 144, 154, 255));
    additionalTilesCountText.setPosition(sf::Vector2f(20.f, 175.f));

    target.draw(m_PanelBG);
    target.draw(headerText);
    target.draw(authorText);

    target.draw(pathLenSliderText);
    target.draw(m_PathLengthSlider);
    target.draw(additionalTilesCountText);
    target.draw(m_AdditionalTileCountSlider);

    target.draw(m_GenerateBtn);
    target.draw(m_ExitBtn);
}

void ControlPanel::handleEvent(sf::Event& event) {
    g_PathLen = m_PathLengthSlider.getValue();
    g_AdditionalTilesCount = m_AdditionalTileCountSlider.getValue();
    if (event.type == sf::Event::MouseMoved) {
        m_GenerateBtn.triggerMouseEvent(WidgetMouseEvent_t::MOUSE_MOVE, sf::Vector2f(event.mouseMove.x, event.mouseMove.y), NULL);
        m_ExitBtn.triggerMouseEvent(WidgetMouseEvent_t::MOUSE_MOVE, sf::Vector2f(event.mouseMove.x, event.mouseMove.y), NULL);
        m_PathLengthSlider.triggerMouseEvent(WidgetMouseEvent_t::MOUSE_MOVE, sf::Vector2f(event.mouseMove.x, event.mouseMove.y), NULL);
        m_AdditionalTileCountSlider.triggerMouseEvent(WidgetMouseEvent_t::MOUSE_MOVE, sf::Vector2f(event.mouseMove.x, event.mouseMove.y), NULL);
    }
    if (event.type == sf::Event::MouseButtonPressed) {
        m_GenerateBtn.triggerMouseEvent(WidgetMouseEvent_t::MOUSE_PRESSED, sf::Vector2f(event.mouseButton.x, event.mouseButton.y), (void*)(&event.mouseButton.button));
        m_ExitBtn.triggerMouseEvent(WidgetMouseEvent_t::MOUSE_PRESSED, sf::Vector2f(event.mouseButton.x, event.mouseButton.y), (void*)(&event.mouseButton.button));
        m_PathLengthSlider.triggerMouseEvent(WidgetMouseEvent_t::MOUSE_PRESSED, sf::Vector2f(event.mouseButton.x, event.mouseButton.y), (void*)(&event.mouseButton.button));
        m_AdditionalTileCountSlider.triggerMouseEvent(WidgetMouseEvent_t::MOUSE_PRESSED, sf::Vector2f(event.mouseButton.x, event.mouseButton.y), (void*)(&event.mouseButton.button));
    }
    if (event.type == sf::Event::MouseButtonReleased) {
        m_GenerateBtn.triggerMouseEvent(WidgetMouseEvent_t::MOUSE_RELEASED, sf::Vector2f(event.mouseButton.x, event.mouseButton.y), (void*)(&event.mouseButton.button));
        m_ExitBtn.triggerMouseEvent(WidgetMouseEvent_t::MOUSE_RELEASED, sf::Vector2f(event.mouseButton.x, event.mouseButton.y), (void*)(&event.mouseButton.button));
        m_PathLengthSlider.triggerMouseEvent(WidgetMouseEvent_t::MOUSE_RELEASED, sf::Vector2f(event.mouseButton.x, event.mouseButton.y), (void*)(&event.mouseButton.button));
        m_AdditionalTileCountSlider.triggerMouseEvent(WidgetMouseEvent_t::MOUSE_RELEASED, sf::Vector2f(event.mouseButton.x, event.mouseButton.y), (void*)(&event.mouseButton.button));
    }

    if (event.type == sf::Event::Resized) {
        m_ExitBtn.setPosition(sf::Vector2f(m_ExitBtn.getPosition().x, event.size.height - 60.f));
    }
}

ControlPanel::~ControlPanel() {}