#include <iostream>
#include <chalk/lib/UI.h>
#include <chalk/lib/Input.h>

void UI_Init() {
	using namespace chk;

	box& b1 = Instance.New<box>("Box1");
	b1.setParent(&Workspace);
	b1.setFillColor(sf::Color::Blue);
	b1.setPosition({ 50,50 });

	box& b2 = Instance.New<box>(&b1,"Box2");
	b2.setParent(&Workspace);
	b2.setFillColor(sf::Color::Red);
	b2.setPosition({ 100,100 });

	box& c1 = Instance.New<box>("Circle");
	c1.setParent(&Workspace);
	c1.setPosition({ 500,50 });
	c1.setFillColor(sf::Color::White);
	c1.setCornerTaper(INT_MAX);
	c1.setSize({ 25,25 });
}

int main() {
	using namespace chk;
	sf::RenderWindow window(sf::VideoMode(1000, 800), "SFML window"); // I should move this to init, bc there is no default function in SFML to retrieve the name of a window
	init(window);
	setGlobalAntiAliasing(8);

	UI_Init(); // creates the UI Objects for this project

	onKeyPress.bind([](sf::Keyboard::Key* k) {
		box& b1 = *(box*)(Workspace[std::string("Box1")][0]);
		box& b2 = *(box*)(Workspace[std::string("Box2")][0]);

		if (b1.getZIndex() == 0) {
			b1.setZIndex(5);
			b2.setZIndex(0);
		}
		else {
			b1.setZIndex(0);
			b2.setZIndex(1);
		}

		// this works as well, but does not change the Z index of the Children.
		//Workspace.swapChildren(&b1, &b2);
	});

	while (true) {
		chk::tick(window);
		chk::handleWindowEvents(*chk::windowPtr);
		chk::render(window);
	}
}