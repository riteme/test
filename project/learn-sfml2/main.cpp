#include <iostream>

#include <SFML/Graphics.hpp>

using namespace std;

int main() {
    sf::RenderWindow wnd(sf::VideoMode(800, 600), "SFML Window", sf::Style::Titlebar | sf::Style::Close);
    sf::CircleShape circle(100.f);
    circle.setFillColor(sf::Color::Blue);

    sf::Event e;
    while (wnd.isOpen()) {
        while (wnd.pollEvent(e)) {
            switch (e.type) {
                case sf::Event::Closed: wnd.close(); break;
                case sf::Event::TextEntered:
                    if (e.text.unicode < 128) { cout << static_cast<char>(e.text.unicode) << endl; } else {
                        wcout << static_cast<wchar_t>(e.text.unicode) << endl;
                    }
                    break;
                default: break;
            }  // switch to e.type
        }

        wnd.clear();
        wnd.draw(circle);
        wnd.display();
    }

    return 0;
}
