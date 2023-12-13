#include <App/Application.hpp>

int main() {
    Application app("DungeonGen v0.0.1", 1280, 768);

    if (!app.run()) return 1;

    return 0;
}