#ifndef CHK_OBJECT_CONTAINER_HPP
#define CHK_OBJECT_CONTAINER_HPP


#include <chalk/lib/Universal_Includes.h>
#include <chalk/lib/DirtyRenderFlag.h>
#include <chalk/lib/Instance.h>
#include <chalk/lib/UI_Objects/UI_Drawable.h>
#include <chalk/lib/Config.h>

namespace chk {
	// keep this virtual - a compilation error will occur elsewise
	class objectContainer : public  UI_Drawable {
	public:
		void updateTransform(bool callToParent = false) override;
		void updateTransformObjectContainer(bool callToParent = false);
	protected:

		void drawChildren(sf::RenderTexture& RT);
	public:
		// when the object is destroyed, all of it's children will be deallocated
		~objectContainer() {
			clearAllChildren();
		}

		objectContainer() = default;

		// deep copy
		objectContainer(const objectContainer& other) : UI_Drawable(other) {
		}

	public:
		Event<UI_Drawable> onChildAddedEvent;
		Event<UI_Drawable> onChildRemovedEvent;
	
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
		virtual void onChildAdded(UI_Object* child);
		virtual void onChildRemoved(UI_Object* child);
	public:


		void addChild(UI_Object* obj);
		
		// This function removes the child from the parent, and by default this function deallocates it as well.
		void removeChild(UI_Object* obj, bool decallocate = true);

		// swaps the draw order of two children.
		// If both objects have a different Z index, then their Z indexes will be swapped.
		inline void swapChildren(UI_Drawable* obj1, UI_Drawable* obj2);

		// moves the child to a target index within it's Z index group.
		// everything to the right of the target index will be shifted over one to make room for the child.
		inline void intMoveChildToIndex(UI_Drawable* obj, const int index);

		// clears all children, and by default deallocates them as well.
		void clearAllChildren(bool deallocate = true);

		const std::vector<UI_Object*>& getChildren();

		std::map<int, std::vector<UI_Drawable*>>& getZIndexMap();
	public:

		inline const int getChildrenCount();


		inline void setContentOffset(sf::Vector2f offset);

		inline sf::Vector2f getContentOffset();

		inline void setContentPadding(UI_PaddingData contentPadding);

		inline UI_PaddingData getContentPadding();

		virtual sf::Vector2f getContentBoundsPixels();

		inline bool intersectsContentBounds(sf::Vector2i& mPos);

		void setAntiAliasingLevel(const int level);

		const int getAntiAliasingLevel();

	public:
		// operator overloads
		UI_Object* operator[](int index) {
			return M_Children[index];
		}

		std::vector<UI_Object*>& operator[](std::string name) {
			return M_NameMap[name];
		}


	protected:


		friend UI_Object;
		friend UI_Drawable;
		// moves the child into the correct Z Index group.
		void handleChildZIndexUpdated(UI_Drawable* obj, const int ZIndexFrom, const int ZIndexTo);

		void handleChildNameUpdate(UI_Object* obj, std::string& oldname, std::string& newname);

	protected:
		// key is the Z index, the vector is the objects assigned to that Z index.
		std::map<int, std::vector<UI_Drawable*>> M_ZIndexDrawMap;
		//std::map<int, std::vector<sf::RenderTexture>> M_ZIndexDrawMapOnlyObjectContainers;
		// key is the Z index, the vector of renderTextures is for multithreading
		//std::map<int, std::vector<sf::RenderTexture>> M_renderTexturesMultithreadMap;

		std::vector<UI_Object*> M_Children;

		std::unordered_map<std::string, std::vector<UI_Object*>> M_NameMap;

		UI_PaddingData M_ContentPadding;

		sf::Vector2f M_contentOffset = sf::Vector2f(0, 0);

		int M_antiAliasingLevel = 0;
		
		bool M_childrenDrawn = false;
		//bool M_SizeToContent = false;

		// for size to content //
		// short M_maxX; 
		// short M_maxY;
		/////////////////////////
	};
}


#endif // !CHK_OBJECT_CONTAINER_HPP