#include <iostream>
#include <chalk/lib/UI.h>
#include <chalk/lib/Input.h>
#include <chalk/lib/Audio.h>

void UI_Init() {
	using namespace chk;
	{
		button& b = Instance.New<button>();
		b.setParent(&Workspace); // both methods work
		b.setFillColor(sf::Color(255, 255, 255));
		b.setFillColorOnHover(sf::Color(75, 255, 75));
		b.setFillColorOnClick(sf::Color(255, 75, 75));

		b.setMargin({ 25,25,25,25 });
		b.setInputBoundsExtension({ 10, 10, 10, 10 });

		value<sf::CircleShape>* v = &Instance.New<value<sf::CircleShape>>("val");
		v->setParent(&b);
		b.onMouseClickedEvent.bind([v]() {
			std::cout << "Typename of v: " << v->getTypeName() << "\n";
		});
	}
	{
		button& b = Instance.New<button>("Button1");
		b.setParent(&Workspace);
		b.setZIndex(1);
		b.setInputHandlingType(consumeAndPassThrough);
		b.setPosition({ 250,50 });
		b.setFillColor(sf::Color(255, 20, 255));
		b.setFillColorOnHover(sf::Color(75, 255, 75));
		b.setFillColorOnClick(sf::Color(255, 75, 75));
	}
	{
		button& b = Instance.New<button>("Button2");
		b.setParent(&Workspace);
		b.setPosition({ 270,70 });
		b.setFillColor(sf::Color(10, 20, 255));
		b.setFillColorOnHover(sf::Color(100, 100, 100));
		b.setFillColorOnClick(sf::Color(50, 50, 50));
	}
	{
		image* img = &Instance.New<image>("Img1");
		img->setParent(&Workspace);
		img->setZIndex(1);
		img->setInputHandlingType(consume);
		img->setPosition({ 200,200 });
		img->onMouseEnterEvent.bind([img] {
			std::cout << img->getName() << "\n";
			img->setFillColor(sf::Color::Red);
		});
		img->onMouseExitEvent.bind([img]() {
			img->setFillColor(sf::Color::White);
		});
	}
	{
		image* img = &Instance.New<image>("Img2");
		img->setParent(&Workspace);
		img->setFillColor(sf::Color::Blue);
		img->setPosition({ 240,240 });
		img->onMouseEnterEvent.bind([img] {
			std::cout << img->getName() << "\n";
			img->setFillColor(sf::Color::Red);
		});
		img->onMouseExitEvent.bind([img]() {
			img->setFillColor(sf::Color::Blue);
		});
	}
	{
		textBox* t = &Instance.New<textBox>("TextBox");
		t->setParent(&Workspace);
		//t->setFont("C:\\Users\\user\\Documents\\Downloaded-Fonts\\RobotoRegular-3m4L.ttf");
		// or
		//t->setFont("arial.ttf"); (assuming that arial.tff is in the static\fonts folder)
		t->setPosition({ 50,350 });
		t->setSize({ 200,30 });
		t->setCharacterSize(25);
		t->setString("Enter Text!");
		t->setBackgroundOutlineThickness(2);
		t->setBackgroundOutlineColor(sf::Color::White);
		t->setBackgroundFillColor(sf::Color(20,20,20));
	}
	{
		/*
		slider* s = &Instance.New<slider>("slider");
		s->setParent(&Workspace);
		s->setPosition({400,400});
		*/
	}
}


int main() {
	using namespace chk;
	sf::RenderWindow window(sf::VideoMode(1000, 800), "SFML window", sf::Style::Default); // I should move this to init, bc there is no default function in SFML to retrieve the name of a window
	init(window);

	UI_Init();

	while (true) {
		chk::tick(window);
		chk::handleWindowEvents(*chk::windowPtr); // https://stackoverflow.com/questions/3922840/sfml-window-resizing-events-blocking-the-main-thread
		chk::render(window);
	}
}