#include "../lib/UI.h";


namespace chk {
	box* workspace;

	void init() {
		workspace = new box;
	}

	void render(sf::RenderWindow& window) {
		for (std::shared_ptr<UI_Object> obj : workspace->getChildren()) {
			obj->draw(*workspace->getRenderTexture(), workspace->getSizePixels());
		}
		//for (auto &c : workspace.getChildren()) {
			//c.draw(workspace.RT);
		//}
	}

	void tick(sf::RenderWindow& window) {
		// check all the window's events that were triggered since the last iteration of the loop
		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			default:
				break;
			}
		}
	}
}