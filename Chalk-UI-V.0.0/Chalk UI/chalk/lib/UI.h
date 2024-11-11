#ifndef CHK_UI_HPP
#define CHK_UI_HPP


#define CHK_DEFAULT_ASSETS_DIR std::string("..\\Chalk UI\\default assets\\")
#define CHK_DEFAULT_OUTLINE_THICKNESS 2
#define CHK_WINDOW_BACKGROUND_COLOR sf::Color::Black


#include "Universal_Includes.h"
#include "DirtyRenderFlag.h"
#include "Instance.h"

bool chk::dirty_render_flag = true; // declared as an extern var in DirtyRenderFlag.h
chk::instance chk::Instance; //definition of extern var, declared in Instance.h

#include "Events/Event.h"

namespace chk {
	sf::Vector2i getMousePosition();
	Event<sf::Window> onWindowResize;
	Event<sf::Keyboard::Key> onKeyPress;
	Event<sf::Keyboard::Key> onKeyRelease;
	Event<void> onMouseClick;
	Event<void> onMouseRelease;
	Event<void> onMouseMoved;
	Event<float> onTick;
	Event<void> onQuit;
}

#include "FontManager.h"
#include "Config.h"
#include "Util.h"
#include "Events/KeybindBindingGroup.h"
#include "Events/Keybind.h"
#include "Events/KeybindManager.h"
#include "UI_Headers.h"
#include "Audio/AudioManager.h"
#include "Audio/Sound.h"
#include "Audio/InstancedSoundManager.h"

//#include "Audio/InstancedSound.h"

namespace chk {

#define Workspace (*chk::workspace)

	namespace timeRecord {
		typedef std::chrono::high_resolution_clock Clock;
		auto t1 = Clock::now(); // set every tick
		auto t2 = Clock::now(); // set at the end of every tick
		float millisecondsLastTick = 0;
	}

	box* workspace;
	sf::RenderWindow* windowPtr;
	sf::RenderTexture* window_RT;
	sf::Vector2i mPosOnBeginTick;
	sf::Vector2i mouseDelta;
	std::string windowName;
	sf::Vector2u desiredWindowSize;
	int windowStyle; // see sf::Style for the Enum.
	static sf::RectangleShape r;

	int globalAntiAliasing = 0;
	
	sf::Vector2i getMousePosition() {
		return sf::Mouse::getPosition(*windowPtr);
	}
	

	// updates the window Render Texture
	// the windowPtr must be loaded before this function is called.
	void refreshWindowRT() {
		sf::ContextSettings cset;
		cset.antialiasingLevel = globalAntiAliasing;
		window_RT->create(windowPtr->getSize().x, windowPtr->getSize().y,cset);
	}

	void recreateWindow() {
		sf::ContextSettings contextSettings = windowPtr->getSettings();
		windowPtr->create(sf::VideoMode(desiredWindowSize.x, desiredWindowSize.y), windowName, 7U, contextSettings);
	}

	void init(sf::RenderWindow &window) {


		workspace = new box;
		workspace->setName("Workspace");
		window_RT = new sf::RenderTexture;
		workspace->setSize(UI_Vector2f(window.getSize().x, window.getSize().y));
		desiredWindowSize = window.getSize();
		windowPtr = &window;

		window_RT->create(window.getSize().x, window.getSize().y);

		audioManager::init();

		r.setFillColor(sf::Color::White);
		r.setOutlineThickness(0);
		r.setPosition(0, 0);
		r.setSize(sf::Vector2f(window.getSize().x, window.getSize().y));
	}

	void cleanup() {
		audioManager::cleanup();
	}

	void render(sf::RenderWindow& window) {
		if (dirty_render_flag) {
			window.clear();
			window_RT->clear();
			workspace->setFillColor(CHK_WINDOW_BACKGROUND_COLOR);
			workspace->draw(*window_RT);
			window_RT->display();
			r.setTexture(&window_RT->getTexture(), true);
			window.draw(r);
			window.display();

			dirty_render_flag = false;
		}
	}

	inline void tick(sf::RenderWindow& window) {
		mouseDelta = sf::Mouse::getPosition(*windowPtr) - mPosOnBeginTick;
		timeRecord::t2 = timeRecord::Clock::now();
		const register auto t1t2 = timeRecord::t2 - timeRecord::t1;
		timeRecord::millisecondsLastTick = std::chrono::duration<float, std::milli>(t1t2).count();

		timeRecord::t1 = timeRecord::Clock::now();
		mPosOnBeginTick = sf::Mouse::getPosition(*windowPtr);
		onTick.invoke(&timeRecord::millisecondsLastTick);
	}



	// window control
	
	// anti ailising control
	void setGlobalAntiAliasing(const int level, objectContainer* par = &Workspace) {
		if (par == &Workspace) {
			recreateWindow();
			refreshWindowRT();
			workspace->setAntiAliasingLevel(level);
		}

		if (par->getChildren().size() == 0) {
			return;
		}
		for (UI_Object* obj : par->getChildren()) {
			objectContainer* con = dynamic_cast<objectContainer*>(obj);

			if (con != NULL) {
				con->setAntiAliasingLevel(5);
				setGlobalAntiAliasing(level, par);
			}
		}
		dirty_render_flag = true;
	}

	const int getGlobalAntiAliasing() {
		return globalAntiAliasing;
	}

	// window renaming, repositioning, resizing, and mode setting.

	void renameWindow(const std::string name) {
		windowName = name;
		windowPtr->setTitle(name);
		dirty_render_flag = true;
	}

	std::string getWindowName() {
		return windowName;
	}

	void setWindowPosition(const sf::Vector2i pos) {
		windowPtr->setPosition(pos);
		dirty_render_flag = true;
	}

	sf::Vector2i getWindowPosition() {
		return windowPtr->getPosition();
	}
	
	inline void setWindowSize(const sf::Vector2u size) {

		sf::RenderWindow &window=*windowPtr;
		sf::View view = window.getDefaultView();
		view.setSize(size.x, size.y);

		view.setCenter({
			static_cast<float>(size.x) / 2.f,
			static_cast<float>(size.y) / 2.f
		});

		Workspace.setSize(UI_Vector2f(size.x, size.y, absolute));

		window_RT->create(size.x, size.y);
		r.setSize(sf::Vector2f(window.getSize().x, window.getSize().y));

		window.setSize(sf::Vector2u(size.x, size.y));
		window.setView(view);

		onWindowResize.invoke(windowPtr);
	}

	sf::Vector2f getWindowSize() {
		return sf::Vector2f(windowPtr->getSize().x, windowPtr->getSize().y);
	}


}

#endif