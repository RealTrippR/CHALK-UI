#include <iostream>
#include <chalk/lib/UI.h>
#include <chalk/lib/Input.h>


void UI_Init() {
	using namespace chk;

	text& t = Instance.New<text>();
	t.setParent(&Workspace);
	t.setPosition({ 20,20 });
	t.setFillColor(sf::Color::White);
	t.setString("Press\nR to resize window\nM to change window style\nN to change the window name\nP to override the window's position");
}
int main() {
	using namespace chk;
	sf::RenderWindow window(sf::VideoMode(1000, 800), "SFML window"); // I should move this to init, bc there is no default function in SFML to retrieve the name of a window
	init(window);

	UI_Init();

	onKeyPress.bind([](sf::Keyboard::Key* k) {
		//std::cout << "K:" << *k << "\n";
		if (*k == sf::Keyboard::R) { // resize window
			std::cout << "Window resized.\n";
			int w = getWindowSize().x;
			if (1000==w) {
				setWindowSize({ 500,800 });
			}
			else {
				setWindowSize({ 1000,800 });
			}
		}
		if (*k == sf::Keyboard::M) { // cycle window style
			std::cout << "Window style changed.\n";
		}
		if (*k == sf::Keyboard::N) { // change window name
			std::cout << "Changed the window name.\n";
			if (getWindowName() == "WindowName") {
				renameWindow("OtherWindowName");
			}
			else {
				renameWindow("WindowName");
			}
		}
		if (*k == sf::Keyboard::P) {
			std::cout << "Overrode the position of the window to (50,100).\n";
			setWindowPosition({ 50,100 });
		}
	});


	while (true) {
		chk::tick(window);
		chk::handleWindowEvents(*chk::windowPtr); // https://stackoverflow.com/questions/3922840/sfml-window-resizing-events-blocking-the-main-thread
		chk::render(window);
	}
}