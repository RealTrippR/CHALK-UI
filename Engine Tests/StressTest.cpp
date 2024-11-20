#include <iostream>
#include <chalk/lib/UI.h>
#include <chalk/lib/Input.h>

#include <chrono>
#include <random>

int getTimeNano() {
	auto now = std::chrono::high_resolution_clock::now();
	int ns = now.time_since_epoch().count();

	return ns;
}

sf::Color createRandomColor() {
	static int i = 5;
	i++;
	sf::Color c;
	srand(getTimeNano() + i * 10);
	// 0-256
	int n = rand() % 257;
	c.r = n;
	srand(getTimeNano() + 150);
	// 0-256
	n = rand() % 257;
	c.g = n;
	srand(getTimeNano() + 500);
	// 0-256
	n = rand() % 257;
	c.b = n;
	return c;
}

void UI_Init() {
	using namespace chk;
	for (int i = 0; i < 50; ++i) {
		srand(getTimeNano() +2*i);

		// Generate a random number between 0 and 500
		int x = rand() % 501;
		srand(getTimeNano() +25*i);
		int y = rand() % 501;

		box& b = Instance.New<box>();
		b.setParent(&Workspace);
		b.setFillColor(createRandomColor());
		b.setOutlineThickness(2);
		b.setOutlineColor(createRandomColor());
		b.setPosition(UI_Vector2f(x, y));
		for (int j = 0; j < 10; ++j) {
			button& bu = Instance.New<button>();
			bu.setParent(&b);
			srand(getTimeNano() + 15);
			// Generate a random number between 0 and 100
			int x = rand() % 101;
			srand(getTimeNano() + 250);
			int y = rand() % 101;
			bu.setPosition(UI_Vector2f(x, y));
			bu.setFillColor(createRandomColor());
			bu.setFillColorOnClick(createRandomColor());
			bu.setFillColorOnHover(createRandomColor());
		}
	}
}

int main() {
	sf::RenderWindow window(sf::VideoMode(1000, 800), "SFML window", sf::Style::Default);
	chk::init(window);
	chk::setGlobalAntiAliasing(16);
	chk::config.setMaxCores(4);

	UI_Init();

	chk::text* t = &chk::Instance.New<chk::text>();
	t->setParent(&Workspace);
	t->setPosition(UI_Vector2f(650, 20));
	t->setCharacterSize(14);

	while (true) {
		chk::tick(window);
		chk::handleWindowEvents(*chk::windowPtr); // https://stackoverflow.com/questions/3922840/sfml-window-resizing-events-blocking-the-main-thread
		chk::render(window);

		t->setString("FPS:" + std::to_string(1000.f / chk::timeRecord::millisecondsLastTick));

		chk::dirty_render_flag = true; // constantly refresh
	}
}