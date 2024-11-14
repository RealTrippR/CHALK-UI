#ifndef CHK_CKEYBIND_MANAGER_H
#define CHK_CKEYBIND_MANAGER_H

namespace chk {
	namespace keybindManager {

		std::vector<keybind*> currentlyActiveKeybinds;

		//void addKeybind(keybind* kb) {
		//	//keybindList.push_back(kb);
		//}
		//void removeKeybind(keybind* kb) {
		//	for (keyMap)
		//	keybindList.erase(keybindList.begin() + (kb - keybindList[0]));
		//	
		//}

		inline void onKeybindRemoved(keybind *kb) {
			for (auto& key : kb->getKeyList()) {
				auto keybindvec = keyMap[key];
				keybindvec.erase(std::remove(keybindvec.begin(), keybindvec.end(), kb), keybindvec.end());
			}
		}

		void onKeybindCopied(keybind* kb) {
			for (auto& key : kb->getKeyList()) {
				keyMap[key].push_back(kb);
			}
		}

		std::vector<keybind*> getConflictingKeybinds(keybind *kb) {
			std::vector<keybind*> conflictingList;
			// iterates through the keys in the keybind
			for (sf::Keyboard::Key& k : kb->getKeyList()) {
				// iterates through the keymap with the keys of the keybind *kb
				std::vector<keybind*> kbvec = keyMap[k];
				for (keybind* kb2 : kbvec) {
					if (kb != kb2) {
						if (kb->getKeyList() == kb2->getKeyList()) {
							conflictingList.push_back(kb2);
						}
					}
				}
			}
			return conflictingList;
		}
		inline void onKeyAddedToKeybind(keybind* kb, const sf::Keyboard::Key k) {
			keyMap[k].push_back(kb);
		}
		inline void onKeyRemovedFromKeybind(keybind* kb, const sf::Keyboard::Key k) {
			auto& vec = keyMap[k]; // key vec
			vec.erase(std::remove(vec.begin(), vec.end(), kb), vec.end());
		}

		inline void handleKeyPress(sf::Keyboard::Key& keyPressed) {
			// gets the keybinds associated with a key and checks to see if their onbegin func groups should be invoked.
			const std::vector<keybind*>& bindList = keyMap[keyPressed];
			for (keybind* kb : bindList) {
				int pressedCount = 0;
				for (sf::Keyboard::Key k : kb->getKeyList()) {
					if (sf::Keyboard::isKeyPressed(k)) {
						pressedCount++;
					}
				}
				// all of the trigger keys are pressed, invoke the keybind!
				if (pressedCount == kb->getKeyList().size()) {
					kb->onBeginBindingGroup.invoke();
					currentlyActiveKeybinds.push_back(kb);
				}
			}
		}

		inline void onTick() {
			// call the while pressed func group for all the active keybinds
			for (keybind* kb : currentlyActiveKeybinds) {
				kb->whilePressedBindingGroup.invoke();
			}
		}

		inline void handleKeyRelease(sf::Keyboard::Key& keyReleased) {
			for (keybind* kb : currentlyActiveKeybinds) {
				int pressedCount = 0;
				for (auto& key : kb->getKeyList()) {
					if (sf::Keyboard::isKeyPressed(key)) {
						pressedCount++;
					}
				}
				if (pressedCount != kb->getKeyList().size()) {
					kb->onEndBindingGroup.invoke();
				}
			}
		}


		// first is a vector of keys, the second is the index of the keybind
		//std::unordered_map <std::vector<sf::Keyboard::Key>, int> KeyMap;
		//std::vector<keybind*> keybindList; // declaration is in keybind.h
	}
}

#endif // !CHK_CKEYBIND_MANAGER_H