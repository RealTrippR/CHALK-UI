#include <chalk/lib/UI_Objects/UI_Object.h>

namespace chk {
	// SETTERS
	void UI_Object::setName(std::string name) {
		if (M_parent) {
			M_parent->handleChildNameUpdate(this, M_Name, name);
		}
		M_Name = name;
		refresh();

	}

	std::string UI_Object::getName() {
		return M_Name;
	}

	void UI_Object::setParent(objectContainer* parent) {

		if (M_parent != parent) {
			if (M_parent) {
				M_parent->removeChild(this);
			}
			M_parent = parent;
			if (M_parent) {
				M_parent->addChild(this);
			}
			updateTransform();
		}
		refresh();
	}

	objectContainer* UI_Object::getParent() {
		return M_parent;
	}

}