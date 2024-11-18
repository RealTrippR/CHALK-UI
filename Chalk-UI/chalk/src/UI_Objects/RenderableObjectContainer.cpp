#include <chalk/lib/UI_Objects/RenderableObjectContainer.h>

using namespace chk;

// swaps the draw order of two children.
// If both objects have a different Z index, then their Z indexes will be swapped.
inline void renderableObjectContainer::swapChildren(UI_Drawable* obj1, UI_Drawable* obj2) {
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

std::map<int, std::vector<UI_Drawable*>>& renderableObjectContainer::getZIndexMap() {
	return M_ZIndexDrawMap;
}

// clears all children, and by default deallocates them as well.
void renderableObjectContainer::clearAllChildren(bool deallocate) {
	for (UI_Object* obj : M_Children) {
		Instance.Remove(obj);
	}

	M_Children.clear();
	M_ZIndexDrawMap.clear();
	M_NameMap.clear();
}


// moves the child to a target index within it's Z index group.
		// everything to the right of the target index will be shifted over one to make room for the child.
inline void renderableObjectContainer::intMoveChildToIndex(UI_Drawable* obj, const int index) {
	std::vector<UI_Drawable*>& v1 = M_ZIndexDrawMap[obj->getZIndex()];
	v1.erase(std::remove(v1.begin(), v1.end(), obj), v1.end());
	v1.resize(v1.size() + 1);
	for (int i = v1.size() - 2; i >= index; --i) {
		std::iter_swap(v1[i], v1[i + 1]);
	}
	v1[index] = obj;
	refresh();
}

inline void renderableObjectContainer::setContentOffset(sf::Vector2f offset) {
	M_contentOffset = offset;
}
inline sf::Vector2f renderableObjectContainer::getContentOffset() {
	return M_contentOffset;
}
inline void renderableObjectContainer::setContentPadding(UI_PaddingData contentPadding) {
	M_ContentPadding = contentPadding;
}
inline UI_PaddingData renderableObjectContainer::getContentPadding() {
	return M_ContentPadding;
}

sf::Vector2f renderableObjectContainer::getContentBoundsPixels() {
	sf::Vector2f r = getSizePixels();
	r.x -= M_ContentPadding.left + M_ContentPadding.right;
	r.y -= M_ContentPadding.top + M_ContentPadding.bottom;
	return r;
}

inline bool renderableObjectContainer::intersectsContentBounds(sf::Vector2i& mPos) {
	sf::Vector2f absPos = getAbsolutePositionPixels();
	sf::Vector2f absBounds = getContentBoundsPixels();
	if (mPos.x >= absPos.x && mPos.x <= absPos.x + absBounds.x
		&& mPos.y >= absPos.y && mPos.y <= absPos.y + absBounds.y) {
		return true;
	}
	return false;
}

// sets the anti-aliasing level for the render texture.
void renderableObjectContainer::setAntiAliasingLevel(const int level) {
	M_antiAliasingLevel = level;
	updateTransform();
	refresh();
}

const int renderableObjectContainer::getAntiAliasingLevel() {
	return M_antiAliasingLevel;
}

// This function removes the child from the parent, and by default this function deallocates it as well.
void renderableObjectContainer::removeChild(UI_Object* obj, bool decallocate) { 		// there might be a logic error within this function 
	auto& vec = M_NameMap[obj->getName()];
	vec.erase(std::remove(vec.begin(), vec.end(), obj), vec.end());

	M_Children.erase(std::remove(M_Children.begin(), M_Children.end(), obj), M_Children.end());

	UI_Drawable* asDrawable = dynamic_cast<UI_Drawable*>(obj);
	if (asDrawable) {
		auto& vec2 = M_ZIndexDrawMap[asDrawable->getZIndex()];
		vec2.erase(std::remove(vec2.begin(), vec2.end(), asDrawable), vec2.end());
	}

	onChildRemoved(obj);

	if (decallocate) {
		Instance.Remove(obj);
	}
	refresh();
}
// moves the child into the correct Z Index group.
void renderableObjectContainer::HandleChildZIndexUpdated(UI_Drawable* obj, const int ZIndexFrom, const int ZIndexTo) {
	// remove the obj from ZIndexFrom
	std::vector<UI_Drawable*>& vec1 = M_ZIndexDrawMap[ZIndexFrom];
	vec1.erase(std::remove(vec1.begin(), vec1.end(), obj), vec1.end());

	/// add the object to it's new ZIndex
	std::vector<UI_Drawable*>& vec2 = M_ZIndexDrawMap[ZIndexTo];
	vec2.push_back(obj);
}