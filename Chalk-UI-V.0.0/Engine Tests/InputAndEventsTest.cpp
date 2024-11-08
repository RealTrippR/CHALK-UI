#include <iostream>
#include <chalk/lib/UI.h>
#include <chalk/lib/Input.h>


void UI_Init() {
	using namespace chk;
	{
		button& b = Instance.New<button>();
		b.setParent(&Workspace); // both methods work
		b.setFillColor(sf::Color(255, 255, 255));
		b.setFillColorOnHover(sf::Color(75, 255, 75));
		b.setFillColorOnClick(sf::Color(255, 75, 75));
	}
	{
		button& b = Instance.New<button>();
		b.setParent(&Workspace);
		b.setInputHandlingType(passThrough);
		b.setPosition({ 250,50 });
		b.setFillColor(sf::Color(255, 255, 10));
		b.setFillColorOnHover(sf::Color(75, 255, 75));
		b.setFillColorOnClick(sf::Color(255, 75, 75));
	}
}


int main() {
	using namespace chk;
	sf::RenderWindow window(sf::VideoMode(1000, 800), "SFML window"); // I should move this to init, bc there is no default function in SFML to retrieve the name of a window
	init(window);

	UI_Init();

	while (true) {
		chk::tick(window);
		chk::handleWindowEvents(*chk::windowPtr); // https://stackoverflow.com/questions/3922840/sfml-window-resizing-events-blocking-the-main-thread
		chk::render(window);
	}
}