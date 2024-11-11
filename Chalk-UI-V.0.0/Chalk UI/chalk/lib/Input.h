#ifndef CHK_INPUT_HPP
#define CHK_INPUT_HPP

namespace chk {
	namespace input {
		//UI_Object* currentObj = NULL; // the current UI_Object that is being hovered over
		///UI_Object* clickedObj = NULL; // the object that is being held down
		std::vector<UI_Object*> currentObjects; // the UI objects that are currently being hovered over
		std::vector<UI_Object*> clickedObjects; // the UI objects that are being held down, but not always hovered over

		// returns as a reference
		sf::Vector2i& getMouseDeltaAsRef() {
			return mouseDelta;
		}

		
		// To fix this function, take into account Z-index

		std::vector<UI_Object*> getHoveredObjects(sf::Vector2i& mpos, objectContainer* parent) {
			std::vector<UI_Object*> returnList; // all hovered objects
			if (!parent->getVisibility()) {
				return {};
			}

			auto& zMap = parent->getZIndexMap();
			// Loops backwards through the Z-index map
			for (auto it = zMap.rbegin(); it != zMap.rend(); ++it) {
				auto v = it->second;
				for (int i = v.size() - 1; i >= 0; --i) {
					auto child = v[i];
					if (!child->getVisibility()) {
						continue;
					}

					objectContainer* childAsContainer = dynamic_cast<objectContainer*>(child);
					// the child is an objectContainer
					if (childAsContainer != NULL) {
						// the objects list is the all the hovered objects in the childcontainer
						std::vector<UI_Object*> objects = getHoveredObjects(mpos, childAsContainer);
						// if no children of the childcontainer are being hovered, than check the childContainer
						if (objects.empty()) {
							if (childAsContainer->getInputHandlingType() == consume
								&& childAsContainer->intersectsAbsoluteBounds(sf::Vector2f(mpos.x, mpos.y))) {
								returnList.push_back(childAsContainer);
								return returnList;
							}
							if (childAsContainer->getInputHandlingType() == consumeAndPassThrough
								&& childAsContainer->intersectsAbsoluteBounds(sf::Vector2f(mpos.x, mpos.y))) {
								returnList.push_back(childAsContainer);
							}
						}
						else {
							// iterates through childAsContainer's children that are being hovered over
							for (auto& obj : objects) {
								if ((obj->getInputHandlingType() == consume)
									&& obj->intersectsAbsoluteBounds(sf::Vector2f(mpos.x, mpos.y))) {
									returnList.push_back(childAsContainer);
									return returnList;
								}
								if ((obj->getInputHandlingType() == consumeAndPassThrough)
									&& obj->intersectsAbsoluteBounds(sf::Vector2f(mpos.x, mpos.y))) {
									returnList.push_back(childAsContainer);
								}
							}

							// adds the objects from the recursive calls to the return list
							returnList.insert(returnList.end(), objects.begin(), objects.end());
							return returnList;
						}
					}
					// the child is not an objectContainer
					else {
						if (child->intersectsAbsoluteBounds(sf::Vector2f(mpos.x, mpos.y)))
						{
							if (child->getInputHandlingType() == consume)
							{
								returnList.push_back(child);
								return returnList;
							}
							if (child->getInputHandlingType() == consumeAndPassThrough)
							{
								returnList.push_back(child);
							}
						}
					}
				}
			}
			return returnList;
		}

		void onMouseMoved(sf::Vector2i &mpos) {

			std::vector<UI_Object*> temp = getHoveredObjects(mpos, workspace);
			for (int i = 0; i < currentObjects.size(); ++i) {
				UI_Object* obj = currentObjects[i];
				if (find(temp.begin(), temp.end(), obj) == temp.end()) {
					obj->onMouseExit(mpos, mouseDelta);
					currentObjects.erase(currentObjects.begin() + i);
					--i;
				}
			}
			for (UI_Object* obj : temp) {
				// if obj from temp not found in current objects
				if (find(currentObjects.begin(), currentObjects.end(), obj) == currentObjects.end()) {
					obj->onMouseEnter(mpos, mouseDelta);
				}
			}
			currentObjects = temp;
		}

		void onMouseClick(sf::Vector2i &mpos) {
			//clickedObj = getHoveredObject(mpos, workspace);
			clickedObjects = getHoveredObjects(mpos, workspace);
			for (auto& clickedObj : clickedObjects) {
				clickedObj->onMouseClick(mpos, mouseDelta);
				clickedObj->onMouseClickedEvent.invoke(clickedObj);
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
					clickedObj->onLeftMouseClickedEvent.invoke(clickedObj);
				}
				if (sf::Mouse::isButtonPressed(sf::Mouse::Middle)) {
					clickedObj->onMiddleMouseClickedEvent.invoke(clickedObj);
				}
				if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
					clickedObj->onRightMouseClickedEvent.invoke(clickedObj);
				}
			}
		}

		void onMouseReleased(sf::Vector2i &mpos) {
			for (auto &obj : clickedObjects) {
				obj->onMouseRelease(mpos, mouseDelta);
			}
			clickedObjects.clear();
		}
	}

	// returns false if the user requested to close the window, returns true if otherwise.
	bool handleWindowEvents(sf::RenderWindow& window) {
		static sf::Vector2i lastMousePos;
		if (sf::Mouse::getPosition(*windowPtr) != lastMousePos) {
			lastMousePos = sf::Mouse::getPosition(*windowPtr);
			input::onMouseMoved(lastMousePos);
			onMouseMoved.invoke(NULL);
		}
		
		for (UI_Object* obj : input::clickedObjects) {
			obj->onMouseHold(lastMousePos, mouseDelta);
		}
		

		// on mouse hover functionality
		if (input::clickedObjects.size() == 0 /*will be true if the mouse is not being held down*/) {
			for (UI_Object* obj : input::currentObjects) {
				obj->onMouseHover(lastMousePos, mouseDelta);
			}
		}

		sf::Event event;
		sf::View view = window.getDefaultView();
		std::pair<sf::Keyboard::Key, int> tmp;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
				return false;
				break;
			case sf::Event::MouseButtonPressed:
				input::onMouseClick(lastMousePos);
				onMouseClick.invoke(NULL);
				break;
			case sf::Event::MouseButtonReleased:
				input::onMouseReleased(lastMousePos);
				onMouseRelease.invoke(NULL);
				break;
			case sf::Event::KeyPressed:
				keybindManager::handleKeyPress(event.key.code);
				onKeyPress.invoke(&event.key.code);
				break;
			case sf::Event::KeyReleased:
				keybindManager::handleKeyRelease(event.key.code);
				onKeyRelease.invoke(&event.key.code);
				break;
			case sf::Event::Resized:
				setWindowSize(sf::Vector2u(event.size.width,event.size.height));
				break;
			default:
				break;
			}

			dirty_render_flag = true; // refresh
		}
		return true;
	}
}

#endif