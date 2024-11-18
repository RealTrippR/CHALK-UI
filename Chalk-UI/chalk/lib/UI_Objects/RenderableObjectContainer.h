#ifndef CHK_RENDERABLE_OBJECT_CONTAINER_H
#define CHK_RENDERABLE_OBJECT_CONTAINER_H
#include <chalk/lib/Universal_Includes.h>
#include <chalk/lib/DirtyRenderFlag.h>
#include <chalk/lib/Instance.h>
#include <chalk/lib/UI_Objects/UI_Drawable.h>
#include <chalk/lib/UI_Objects/Object_Container.h>
#include <chalk/lib/Config.h>

namespace chk {
	class renderableObjectContainer : public objectContainer, public UI_Drawable {
	public:
		// to fix the diamond inheritence problem
		using UI_Drawable::refresh;
		using UI_Drawable::updateTransform;
	public:
		void updateTransform(bool callToParent = false) override;
		void updateTransformObjectContainer(bool callToParent = false);
	public:
		~renderableObjectContainer() {
			clearAllChildren();
		}
	public:
		// This function removes the child from the parent, and by default this function deallocates it as well.
		void removeChild(UI_Object* obj, bool decallocate = true);
	public:
		// sets the anti-aliasing level for the render texture.
		void setAntiAliasingLevel(const int level);

		const int getAntiAliasingLevel();

		std::map<int, std::vector<UI_Drawable*>>& getZIndexMap();


		// swaps the draw order of two children.
		// If both objects have a different Z index, then their Z indexes will be swapped.
		inline void swapChildren(UI_Drawable* obj1, UI_Drawable* obj2);

		// moves the child to a target index within it's Z index group.
		// everything to the right of the target index will be shifted over one to make room for the child.
		inline void intMoveChildToIndex(UI_Drawable* obj, const int index);

		// clears all children, and by default deallocates them as well.
		void clearAllChildren(bool deallocate = true) override;

	public:
		inline void setContentOffset(sf::Vector2f offset);

		inline sf::Vector2f getContentOffset();

		inline void setContentPadding(UI_PaddingData contentPadding);

		inline UI_PaddingData getContentPadding();

		virtual sf::Vector2f getContentBoundsPixels();

		inline bool intersectsContentBounds(sf::Vector2i& mPos);


	private:

		friend UI_Object;
		friend UI_Drawable;
		// moves the child into the correct Z Index group.
		void HandleChildZIndexUpdated(UI_Drawable* obj, const int ZIndexFrom, const int ZIndexTo);

	private:
		
		std::map<int, std::vector<UI_Drawable*>> M_ZIndexDrawMap;

		UI_PaddingData M_ContentPadding;

		sf::Vector2f M_contentOffset = sf::Vector2f(0, 0);

		int M_antiAliasingLevel = 0;
	};
}

#endif // !CHK_RENDERABLE_OBJECT_CONTAINER_H