#include <iostream>
#include <chalk/lib/UI.h>
#include <chalk/lib/Input.h>

void UI_INIT() {
	using namespace chk;
	box& b = Instance.New<box>("TextHolder");
	b.setParent(&Workspace);
	b.setPosition({ 10,10 });
	b.setSize({250,200});
	b.setFillColor({ 30,30,30 });
	b.setOutlineColor(sf::Color::White);
	b.setOutlineThickness(2);

	text& t = Instance.New<text>("Text");
	t.setParent(&b);
	t.setCharacterSize(15);
	t.setPosition({ .5,.5,percent });
	t.setOrigin({ .5,.5,percent });
	t.setString("This is a text Object.\nIt supports multiple lines.\nBy default, it's size is\nset to the size of the Text");


	box& tbHolder = Instance.New<box>(&b, "textBoxHolder"); // notice the first argument in the Instance.New function - this means that tbHolder a copy of b
	tbHolder.setParent(&Workspace);
	tbHolder.setPosition({ 500,10 });
	tbHolder.setSize({200,100});
	tbHolder.setOutlineColor(sf::Color::Red);

	textBox& tb = Instance.New<textBox>();
	tb.setParent(&tbHolder);
	tb.setSize({ 1,1,percent });
	tb.setPosition({ 0,0 });
	tb.setCharacterSize(20);
	tb.setString({ "This is a textbox.\nThis is a textbox." });

	button& bu = Instance.New<button>("Button");
	bu.setParent(&Workspace);
	bu.setFillColor(sf::Color(40,40,40));
	bu.setFillColorOnHover(sf::Color(60, 60, 60));
	bu.setFillColorOnClick(sf::Color::Blue);
	bu.setPosition({ 10,250 });

	
	button& bu2 = Instance.New<button>(&bu, "Button2");
	bu2.setParent(&Workspace);
	bu2.setPosition({ 120,250 });
	bu2.onMouseEnterEvent.bind([]() {
		std::cout << "BU2 Enter\n";
	});
}

int main() {
	sf::RenderWindow window(sf::VideoMode(1000, 800), "SFML window", sf::Style::Default);
	chk::init(window);
	chk::setGlobalAntiAliasing(16);

	UI_INIT();

	while (true) {
		chk::tick(window);
		chk::handleWindowEvents(*chk::windowPtr); // https://stackoverflow.com/questions/3922840/sfml-window-resizing-events-blocking-the-main-thread
		chk::render(window);
	}
}