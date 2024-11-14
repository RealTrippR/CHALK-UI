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
		box* b = &Instance.New<box>("TextboxHolder");
		b->setParent(&Workspace);
		b->setFillColor(sf::Color::Transparent);
		b->setOutlineThickness(2);
		b->setPosition({ 50,350 });
		b->setSize({ 200,30 });

		textBox* t = &Instance.New<textBox>("TextBox");
		t->setParent(&Workspace);
		//t->setFont("C:\\Users\\user\\Documents\\Downloaded-Fonts\\RobotoRegular-3m4L.ttf");
		// or
		//t->setFont("arial.ttf"); (assuming that arial.tff is in the static\fonts folder)
		t->setSize({ 200,float(t->getCharacterSize()) });
		t->setCharacterSize(25);
		t->setString("Enter Text!");
		t->setPosition({ 5,.5,absolute,percent });
		t->setOrigin({ 0,2,absolute });

		button& test = Instance.New<button>("testButton");
		test.setParent(b);
		//test.setZIndex(0);
		test.setFillColor(sf::Color(255, 20, 255));
		test.setFillColorOnHover(sf::Color(75, 255, 75));
		test.setFillColorOnClick(sf::Color(255, 75, 75));

		test.onLeftMouseClickedEvent.bind([]() {
			std::cout << "CLICKED!";
		});
	}
	{
		slider* s = &Instance.New<slider>("slider");
		s->setParent(&Workspace);
		s->setPosition({400,400});
		s->setSize({ 300,50 });
	}
}


int main() {
	using namespace chk;
	sf::RenderWindow window(sf::VideoMode(1000, 800), "SFML window", sf::Style::Default); // I should move this to init, bc there is no default function in SFML to retrieve the name of a window
	init(window);
	chk::setGlobalAntiAliasing(16);


	UI_Init();

	while (true) {
		chk::tick(window);
		chk::handleWindowEvents(*chk::windowPtr); // https://stackoverflow.com/questions/3922840/sfml-window-resizing-events-blocking-the-main-thread
		chk::render(window);
	}
}