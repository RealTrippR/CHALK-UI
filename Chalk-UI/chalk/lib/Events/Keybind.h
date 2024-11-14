#ifndef CHK_KEYBIND_HPP
#define CHK_KEYBIND_HPP

namespace chk {
	class keybind; // FORWARD DECLARATION
	namespace keybindManager {
		/*void addKeybind(keybind* kb);
		void removeKeybind(keybind* kb);*/
		void onKeyAddedToKeybind(keybind* kb, const sf::Keyboard::Key k);
		void onKeyRemovedFromKeybind(keybind* kb, const sf::Keyboard::Key k);
		void onKeybindRemoved(keybind* kb);
		void onKeybindCopied(keybind* kb);
		// the keyMap links the keys to their keybinds
		std::unordered_map<sf::Keyboard::Key, std::vector<keybind*>> keyMap; // the first index is the key - the second is the list keybinds that have this key in them
	}

	// the keybind class allows for the calling of events upon being invoked. It's invokation is handled by the namespace keybindManager.
	// keep in mind that keybinds should not go out of scope, and their memory address should not change.
	// If you want keybinds to last the runtime of your program, declare them in a header file.
	class keybind {
	public:
		keybind() {
			onBeginBindingGroup.M_ParentRef = this;
			onEndBindingGroup.M_ParentRef = this;
			whilePressedBindingGroup.M_ParentRef = this;
		}
		// constructor, keylist as args
		keybind(std::vector<sf::Keyboard::Key> keyList) {
			onBeginBindingGroup.M_ParentRef = this;
			onEndBindingGroup.M_ParentRef = this;
			whilePressedBindingGroup.M_ParentRef = this;
			for (sf::Keyboard::Key &k : keyList) {
				addKey(k);
			}
		}

		keybind(keybind &other) {
			keybindManager::onKeybindRemoved(this);
			M_KeyList = other.M_KeyList;
			M_KeyExistenceMap = other.M_KeyExistenceMap;
			M_BindedFunctionsNoArgs = other.M_BindedFunctionsNoArgs;
			M_BindedFunctionsNoArgs_ExistenceRecord = other.M_BindedFunctionsNoArgs_ExistenceRecord;
			M_BindedFunctionsWithArgs = other.M_BindedFunctionsWithArgs;
			M_BindedFunctionsWithArgs_ExistenceRecord = other.M_BindedFunctionsWithArgs_ExistenceRecord;

			keybindManager::onKeybindCopied(this);

			onBeginBindingGroup.M_ParentRef = this;
			onEndBindingGroup.M_ParentRef = this;
			whilePressedBindingGroup.M_ParentRef = this;
		}
		// destructor
		~keybind() {
			using namespace keybindManager;
			onKeybindRemoved(this);
		}

	public: // trigger key management:

	// add a trigger key
	void addKey(sf::Keyboard::Key k) {
		keybindManager::onKeyAddedToKeybind(this, k);
		if (M_KeyExistenceMap.find(k) == M_KeyExistenceMap.end()) {
			M_KeyList.push_back(k);
		}
	}
	// remove a trigger key
	void removeKey(sf::Keyboard::Key k) {
		keybindManager::onKeyRemovedFromKeybind(this, k);
		if (M_KeyExistenceMap.find(k) != M_KeyExistenceMap.end()) {
			M_KeyList.erase(
				std::remove(M_KeyList.begin(), M_KeyList.end(), k),
				M_KeyList.end()
			);

		}
	}

	// returns a reference to the keylist. Do not directly modify this list under any circumstances.
	std::vector<sf::Keyboard::Key>& getKeyList() {
		return M_KeyList;
	}

	// completely empties the keylist
	void clearKeyList() {
		M_KeyList.clear();
		M_KeyExistenceMap.clear();
		keybindManager::onKeybindRemoved(this);
	}
	public:
		int getTicksActive() {
			return M_ticksActive;
		}

		void incrementTicksActive() {
			++M_ticksActive;
		}

		void setTicksActive(const int ticksActive) {
			M_ticksActive = ticksActive;
		}

		
		int getMillisecondsActive() {
			return M_millisecondsActive;
		}
		
		void addToMillisecondsActive(int milliseconds) {
			M_millisecondsActive += milliseconds;
		}
		void setMillisecondsActive(unsigned int milliseconds) {
			M_millisecondsActive = milliseconds;
		}

	public: // binding groups
		// the functions binded to this group will be called when the keys of the keybind are first held down.
		keybindBindingGroup onBeginBindingGroup;
		// the functions binded to this group will be called when the keys of the keybind are released.
		keybindBindingGroup onEndBindingGroup;
		// the functions binded to this group will be called every tick that the keys of the keybind are held down.
		keybindBindingGroup whilePressedBindingGroup;
	private:
		std::vector<sf::Keyboard::Key> M_KeyList;
		std::set<sf::Keyboard::Key> M_KeyExistenceMap;
	private:
		std::vector<void(*)()> M_BindedFunctionsNoArgs;
		std::set<void(*)()> M_BindedFunctionsNoArgs_ExistenceRecord;
		std::set<void(*)(keybind*)> M_BindedFunctionsWithArgs_ExistenceRecord;
		std::vector<void(*)(keybind*)> M_BindedFunctionsWithArgs;

	private:
		unsigned int M_ticksActive = 0;
		unsigned int M_millisecondsActive = 0;
	};
	
}

#endif // !CHK_KEYBIND