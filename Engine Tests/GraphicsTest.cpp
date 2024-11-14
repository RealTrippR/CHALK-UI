#include <iostream>
#include <chalk/lib/UI.h>
#include <chalk/lib/Input.h>

void UI_Init() {
	using namespace chk;
	box& holder = Instance.New<box>("holder");
	holder.setParent(&Workspace);

	holder.setFillColor(sf::Color::Blue);
	holder.setPosition({50,50});
	holder.setSize({ 200,200 });

	box& child = Instance.New<box>("box1");
	child.setParent(&holder);
	child.setFillColor(sf::Color::Red);
	child.setSize({ 50,50 });
}

int main() {
	using namespace chk;
	sf::RenderWindow window(sf::VideoMode(1000, 800), "SFML window"); // I should move this to init, bc there is no default function in SFML to retrieve the name of a window
	init(window);
	setGlobalAntiAliasing(8);

	UI_Init(); // creates the UI Objects for this project

	onKeyPress.bind([] {
		// moves the box left or right when the respective arrow key is pressed.
		box* b1 = (box*)(*(box*)(Workspace["holder"][0]))["box1"][0];
		//box* b1 = (box*)(Workspace["holder"][0]);

		if (b1->getSizePixels().x > 300) {
			b1->setSize({ 50,50 });
			b1->setFillColor(sf::Color::Red);
		}
		else {
			b1->setSize({ 500,50 });
			b1->setFillColor(sf::Color::Green);
		}

		

		std::cout << (*(box*)(Workspace["holder"][0])).getSizePixels().x << "X \n";
		//Workspace.setPosition({0,0});
	});
	

	while (true) {
		chk::tick(window);
		chk::handleWindowEvents(*chk::windowPtr);
		chk::render(window);
	}
}