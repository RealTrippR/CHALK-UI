#ifndef CHK_OBJECT_CONTAINER_HPP
#define CHK_OBJECT_CONTAINER_HPP

namespace chk {
	// keep this virtual - a compilation error will occur elsewise
	class objectContainer : public  UI_Object {
	public:
		// when the object is destroyed, all of it's children will be deallocated
		~objectContainer() {
			clearAllChildren();
		}

		objectContainer() = default;

		// deep copy
		objectContainer(const objectContainer& other) : UI_Object(other) {
			M_ContentPadding = other.M_ContentPadding;
			M_contentOffset = other.M_contentOffset;
		}

	public:
		Event<UI_Object> onChildAddedEvent;
		Event<UI_Object> onChildRemovedEvent;
	public:
		void updateTransform(bool callToParent = false) override {
			updateTransformUI_Object();
			updateTransformObjectContainer(callToParent);
		}
		void updateTransformObjectContainer(bool callToParent = false) {
			/*M_maxX = 0;
			M_maxY = 0;
			if (M_SizeToContent) {
				for (auto& obj : M_Children) {
					const sf::Vector2f v = obj->getSizePixels();
					M_maxX = std::max(short(v.x), M_maxX);
					M_maxY = std::max(short(v.y), M_maxY);
				}
			}*/
			if (callToParent) {
				return;
			}
			for (auto& obj : M_Children) {
				obj->updateTransform(true);
			}
		}
	public:
		//inline sf::Vector2f getSizePixels(bool subtractMargin = true) override {
		//	sf::Vector2f xy;
		//	if (M_Size.typeX == absolute) {
		//		xy.x = M_Size.x;
		//	}
		//	else {
		//		// every object, save for the workspace, should have a parent
		//		if (M_parent) {
		//			xy.x = M_parent->getSizePixels().x * M_Size.x;
		//		}
		//	}
		//	if (M_Size.typeY == absolute) {
		//		xy.y = M_Size.y;
		//	}
		//	else {
		//		if (M_parent) {
		//			xy.y = M_parent->getSizePixels().y * M_Size.y;
		//		}
		//	}

		//	if (subtractMargin) {
		//		xy.x -= (M_Margin.left + M_Margin.right);
		//		xy.y -= (M_Margin.top + M_Margin.bottom);
		//	}

		//	/*if (M_SizeToContent) {
		//		xy.x = std::max(short(xy.x), M_maxX);
		//		xy.y = std::max(short(xy.y), M_maxY);
		//	}*/

		//	return xy;
		//}
	public:
		virtual void onChildAdded(UI_Object* child) {
			onChildAddedEvent.invoke(this);
			return;
		}
		virtual void onChildRemoved(UI_Object* child) {
			onChildRemovedEvent.invoke(this);
			return;
		}
	public:

		void handleChildNameUpdate(UI_Object *obj, std::string &oldname, std::string &newname) {
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

		void addChild(UI_Object* obj) {
			if (obj->M_parent != this) { // these 3 lines of code allow for addChild to be called from anywhere, not just the setParent function
				obj->setParent(this);
			}
			M_Children.push_back(obj);
			M_NameMap[obj->getName()].push_back(obj);
			M_ZIndexDrawMap[obj->getZIndex()].push_back(obj);
			onChildAdded(obj);
			refresh();
		}
		
		// This function removes the child from the parent, and by default this function deallocates it as well.

		// there might be a logic error within this function 
		void removeChild(UI_Object* obj, bool decallocate = true) {
			auto& vec = M_NameMap[obj->getName()];
			vec.erase(std::remove(vec.begin(), vec.end(), obj), vec.end());

			M_Children.erase(std::remove(M_Children.begin(), M_Children.end(), obj), M_Children.end());

			auto& vec2 = M_ZIndexDrawMap[obj->getZIndex()];
			vec2.erase(std::remove(vec2.begin(), vec2.end(), obj), vec2.end());

			onChildRemoved(obj);

			if (decallocate) {
				Instance.Remove(obj);
			}
			refresh();
		}

		// clears all children, and by default deallocates them as well.
		void clearAllChildren(bool deallocate = true) {
			for (UI_Object* obj : M_Children) {
				Instance.Remove(obj);
			}

			M_Children.clear();
			M_ZIndexDrawMap.clear();
			M_NameMap.clear();
		}

		const std::vector<UI_Object*>& getChildren() {
			return M_Children;
		}

		inline int getChildrenCount() {
			return M_Children.size();
		}
	
		// swaps the draw order of two children.
		// If both objects have a different Z index, then their Z index will be swapped.
		inline void swapChildren(UI_Object* obj1, UI_Object* obj2) {
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
		inline void intMoveChildToIndex(UI_Object* obj, const int index) {
			std::vector<UI_Object*>& v1 = M_ZIndexDrawMap[obj->getZIndex()];
			v1.erase(std::remove(v1.begin(), v1.end(), obj), v1.end());
			v1.resize(v1.size() + 1);
			for (int i = v1.size()-2; i >= index; --i) {
				std::iter_swap(v1[i], v1[i + 1]);
			}
			v1[index] = obj;
			refresh();
		}

	public:
		// operator overloads
		UI_Object* operator[](int index) {
			return M_Children[index];
		}

		std::vector<UI_Object*>& operator[](std::string name) {
			return M_NameMap[name];
		}

	public:
		inline void setContentOffset(sf::Vector2f offset) {
			M_contentOffset = offset;
		}
		inline sf::Vector2f getContentOffset() {
			return M_contentOffset;
		}
		inline void setContentPadding(UI_PaddingData contentPadding) {
			M_ContentPadding = contentPadding;
		}
		inline UI_PaddingData getContentPadding() {
			return M_ContentPadding;
		}
		inline virtual sf::Vector2f getContentBoundsPixels() {
			sf::Vector2f r = getSizePixels();
			r.x -= M_ContentPadding.left + M_ContentPadding.right;
			r.y -= M_ContentPadding.top + M_ContentPadding.bottom;
			return r;
		}

		inline bool intersectsContentBounds(sf::Vector2i &mPos) {
			sf::Vector2f absPos = getAbsolutePositionPixels();
			sf::Vector2f absBounds = getContentBoundsPixels();
			if (mPos.x >= absPos.x && mPos.x <= absPos.x + absBounds.x
				&& mPos.y >= absPos.y && mPos.y <= absPos.y + absBounds.y) {
				return true;
			}
			return false;
		}

		// sets the anti-aliasing level for the render texture.
		void setAntiAliasingLevel(const int level) {
			M_antiAliasingLevel = level;
			updateTransform();
			refresh();
		}

		const int getAntiAliasingLevel() {
			return M_antiAliasingLevel;
		}

	public:

		/*void setSizeToContent(const bool sizeToContent) {
			M_SizeToContent = sizeToContent;
			updateTransform();
			refresh();
		}

		const bool getSizeToContent() {
			return M_SizeToContent;
		}*/

	protected:

		friend UI_Object;
		// moves the child into the correct Z Index group.
		void HandleChildZIndexUpdated(UI_Object* obj, const int ZIndexFrom, const int ZIndexTo) {
			// remove the obj from ZIndexFrom
			std::vector<UI_Object*>& vec1 = M_ZIndexDrawMap[ZIndexFrom];
			vec1.erase(std::remove(vec1.begin(), vec1.end(), obj), vec1.end());

			/// add the object to it's new ZIndex
			std::vector<UI_Object*>& vec2 = M_ZIndexDrawMap[ZIndexTo];
			vec2.push_back(obj);
		}

	protected:
		// key is the Z index, the vector is the objects assigned to that Z index.

		std::map<int, std::vector<UI_Object*>> M_ZIndexDrawMap;

		std::vector<UI_Object*> M_Children;

		std::unordered_map<std::string, std::vector<UI_Object*>> M_NameMap;

		UI_PaddingData M_ContentPadding;

		sf::Vector2f M_contentOffset = sf::Vector2f(0, 0);

		int M_antiAliasingLevel = 0;

		//bool M_SizeToContent = false;

		// for size to content //
		// short M_maxX; 
		// short M_maxY;
		/////////////////////////
	};
}


#endif // !CHK_OBJECT_CONTAINER_HPP