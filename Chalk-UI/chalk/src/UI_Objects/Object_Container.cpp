#include <chalk/lib/UI_Objects/Object_Container.h>

using namespace chk;

void objectContainer::drawChildren(sf::RenderTexture& RT) {
	// single threaded rendering
	//if (config.getMaxCores() == unsigned short(1)) {
	for (auto& Z_Level : M_ZIndexDrawMap) {
		for (auto& obj : Z_Level.second) {
			if (obj->getVisibility()) {
				obj->draw(RT);
			}
		}
	}
	//}

	//// multi-threaded rendering
	//else {
	//	using std::thread;
	//	const unsigned short maxThreads = config.getMaxCores();

	//	for (auto& Z_Level : M_ZIndexDrawMapOnlyObjectContainers) {
	//		auto v = Z_Level.second;
	//		
	//		for (objectContainer* obj : Z_Level.second) {
	//			if (!obj->getVisibility()) {
	//				continue;
	//			}

	//			obj->clearRenderTexture();
	//			//// predraw children
	//			std::thread t1(&chk::objectContainer::drawChildren, this, std::ref(RT));
	//			t1.join();
	//		}
	//	}
	//	for (auto& Z_Level : M_ZIndexDrawMap) {
	//		for (auto& obj : Z_Level.second) {
	//			if (obj->getVisibility()) {
	//				obj->draw(RT);
	//			}
	//		}
	//	}
	//}
}

void objectContainer::updateTransform(bool callToParent) {
	updateTransformUI_Object();
	updateTransformObjectContainer(callToParent);
}

void objectContainer::updateTransformObjectContainer(bool callToParent) {

	if (callToParent) {
		return;
	}
	for (auto& obj : M_Children) {
		obj->updateTransform(true);
	}
}
	
void objectContainer::onChildAdded(UI_Object* child) {
	onChildAddedEvent.invoke(this);
	return;
}
void objectContainer::onChildRemoved(UI_Object* child) {
	onChildRemovedEvent.invoke(this);
	return;
}

void objectContainer::addChild(UI_Object* obj) {
	if (obj->M_parent != this) { // these 3 lines of code allow for addChild to be called from anywhere, not just the setParent function
		obj->setParent(this);
	}
	M_Children.push_back(obj);
	M_NameMap[obj->getName()].push_back(obj);
	UI_Drawable* asDrawable = dynamic_cast<UI_Drawable*>(obj);
	if (asDrawable) {
		M_ZIndexDrawMap[asDrawable->getZIndex()].push_back(asDrawable);
	}
	// erase from Z Index Map only objectContainers
	objectContainer* asContainer = dynamic_cast<objectContainer*>(obj);
	if (asContainer) {
		M_ZIndexDrawMapOnlyObjectContainers[asContainer->getZIndex()].push_back(asContainer);
	}

	onChildAdded(obj);
	refresh();
}

// This function removes the child from the parent, and by default this function deallocates it as well.
void objectContainer::removeChild(UI_Object* obj, bool decallocate) {
	auto& vec = M_NameMap[obj->getName()];
	vec.erase(std::remove(vec.begin(), vec.end(), obj), vec.end());

	M_Children.erase(std::remove(M_Children.begin(), M_Children.end(), obj), M_Children.end());
	
	// erase from Z Index Map
	UI_Drawable* asDrawable = dynamic_cast<UI_Drawable*>(obj);
	if (asDrawable) {
		std::vector<UI_Drawable*>& vec = M_ZIndexDrawMap[asDrawable->getZIndex()];
		vec.erase(std::remove(vec.begin(), vec.end(), asDrawable), vec.end());
	}

	// erase from Z Index Map only objectContainers
	objectContainer* asContainer = dynamic_cast<objectContainer*>(obj);
	if (asContainer) {
		std::vector<objectContainer*>& vec = M_ZIndexDrawMapOnlyObjectContainers[asContainer->getZIndex()];
		vec.erase(std::remove(vec.begin(), vec.end(), asContainer), vec.end());
	}
	
	onChildRemoved(obj);

	if (decallocate) {
		Instance.Remove(obj);
	}
	refresh();
}

// clears all children, and by default deallocates them as well.
void objectContainer::clearAllChildren(bool deallocate) {
	for (UI_Object* obj : M_Children) {
		Instance.Remove(obj);
	}

	M_Children.clear();
	M_NameMap.clear();
}

const std::vector<UI_Object*>& objectContainer::getChildren() {
	return M_Children;
}

std::map<int, std::vector<UI_Drawable*>>& objectContainer::getZIndexMap() {
	return M_ZIndexDrawMap;
}

inline const int objectContainer::getChildrenCount() {
	return M_Children.size();
}

		

		

void objectContainer::handleChildNameUpdate(UI_Object* obj, std::string& oldname, std::string& newname) {
	if (oldname != newname) {
		auto& vec = M_NameMap[obj->getName()];
		if (vec.size() == 1) {
			auto it = M_NameMap.find(obj->getName());
			M_NameMap.erase(it);
		}
		else {
			vec = M_NameMap[oldname];
			vec.erase(std::remove(vec.begin(), vec.end(), obj), vec.end());

			vec = M_NameMap[newname];
			vec.push_back(obj);
		}
	}
}


// sets the anti-aliasing level for the render texture.
void objectContainer::setAntiAliasingLevel(const int level) {
	M_antiAliasingLevel = level;
	updateTransform();
	refresh();
}

const int objectContainer::getAntiAliasingLevel() {
	return M_antiAliasingLevel;
}


inline void objectContainer::setContentOffset(sf::Vector2f offset) {
	M_contentOffset = offset;
}
inline sf::Vector2f objectContainer::getContentOffset() {
	return M_contentOffset;
}
inline void objectContainer::setContentPadding(UI_PaddingData contentPadding) {
	M_ContentPadding = contentPadding;
}
inline UI_PaddingData objectContainer::getContentPadding() {
	return M_ContentPadding;
}

sf::Vector2f objectContainer::getContentBoundsPixels() {
	sf::Vector2f r = getSizePixels();
	r.x -= M_ContentPadding.left + M_ContentPadding.right;
	r.y -= M_ContentPadding.top + M_ContentPadding.bottom;
	return r;
}

inline bool objectContainer::intersectsContentBounds(sf::Vector2i& mPos) {
	sf::Vector2f absPos = getAbsolutePositionPixels();
	sf::Vector2f absBounds = getContentBoundsPixels();
	if (mPos.x >= absPos.x && mPos.x <= absPos.x + absBounds.x
		&& mPos.y >= absPos.y && mPos.y <= absPos.y + absBounds.y) {
		return true;
	}
	return false;
}

// moves the child into the correct Z Index group.
void objectContainer::handleChildZIndexUpdated(UI_Drawable* obj, const int ZIndexFrom, const int ZIndexTo) {
	// remove the obj from ZIndexFrom
	std::vector<UI_Drawable*>& vec1 = M_ZIndexDrawMap[ZIndexFrom];
	vec1.erase(std::remove(vec1.begin(), vec1.end(), obj), vec1.end());

	/// add the object to it's new ZIndex
	std::vector<UI_Drawable*>& vec2 = M_ZIndexDrawMap[ZIndexTo];
	vec2.push_back(obj);
}


// swaps the draw order of two children.
		// If both objects have a different Z index, then their Z indexes will be swapped.
inline void objectContainer::swapChildren(UI_Drawable* obj1, UI_Drawable* obj2) {
	const short z1 = obj1->getZIndex();
	const short z2 = obj2->getZIndex();
	auto& v1 = M_ZIndexDrawMap[z1];
	auto i1 = std::find(v1.begin(), v1.end(), obj1);
	auto& v2 = M_ZIndexDrawMap[z2];
	auto i2 = std::find(v2.begin(), v2.end(), obj2);

	if (z1 == z2) {
		std::iter_swap(i1, i2);
	}
	else {
		// If objects have different Z-indices, move each to the other's vector
		v1.erase(i1);
		v2.erase(i2);
		v1.push_back(obj2);
		v2.push_back(obj1);

		obj1->setZIndex(z2);
		obj2->setZIndex(z1);
	}
	refresh();
}

// moves the child to a target index within it's Z index group.
// everything to the right of the target index will be shifted over one to make room for the child.
inline void objectContainer::intMoveChildToIndex(UI_Drawable* obj, const int index) {
	std::vector<UI_Drawable*>& v1 = M_ZIndexDrawMap[obj->getZIndex()];
	v1.erase(std::remove(v1.begin(), v1.end(), obj), v1.end());
	v1.resize(v1.size() + 1);
	for (int i = v1.size() - 2; i >= index; --i) {
		std::iter_swap(v1[i], v1[i + 1]);
	}
	v1[index] = obj;
	refresh();
}
