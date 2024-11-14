#ifndef CHK_STANDARD_EVENTS_H
#define CHK_STANDARD_EVENTS_H

#include <chalk/lib/Events/Event.h>;

namespace chk {
	extern Event<sf::Window> onWindowResize;
	extern Event<sf::Keyboard::Key> onKeyPress;
	extern Event<sf::Keyboard::Key> onKeyRelease;
	extern Event<void> onMouseClick;
	extern Event<void> onMouseRelease;
	extern Event<void> onMouseMoved;
	extern Event<float> onTick;
	extern Event<void> onQuit;
}

#endif //!CHK_STANDARD_EVENTS_H