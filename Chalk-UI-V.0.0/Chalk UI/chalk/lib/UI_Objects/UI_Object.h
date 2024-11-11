#pragma once


#include <chalk/lib/Universal_Includes.h>
#include <SFML/Graphics/Shader.hpp>
#include <chalk/lib/standardEvents.h>


namespace chk {
	class Instance; // forward declaration
	class objectContainer; // forward declaration

	class UI_Object {
	public:
		inline virtual void draw(sf::RenderTexture& RT) {
			std::cout << "UIOBJECT DRAW CALLED - THIS FUNCTION SHOULD NOT BE CALLED\n";
		}

		/*inline void onTick(double& DT) {

		}*/

		void updateTransformUI_Object(bool callToParent = false);

		inline virtual void updateTransform(bool callToParent = false) {

		}
		
		inline void refresh();
	public:
		// returns true if it intersects the absolute bounds of this UI_Object, relevant to the left upper corner of the screen.
		bool intersectsAbsoluteBounds(sf::Vector2f absolutePos, bool returnFalseIfInvisible = true) {
			if (returnFalseIfInvisible && !M_visible) {
				return false;
			}
			sf::FloatRect bounds = getAbsoluteBoundsPixels();
			return
			(
					absolutePos.x >= bounds.left &&
					absolutePos.x <= bounds.left + bounds.width &&
					absolutePos.y >= bounds.top &&
					absolutePos.y <= bounds.top + bounds.height
			);
		}

		virtual void onMouseHover(const sf::Vector2i& mousePos, const sf::Vector2i& mDelta) {
			onMouseHoveredEvent.invoke(this);
		}

		virtual void onMouseClick(const sf::Vector2i &mousePos, const sf::Vector2i &mDelta) {
			//onLeftMouseClickedEvent.invoke(this); -> this function is called in input.h
			//std::cout << getName() << " has been clicked!\n";
		}

		virtual void onMouseRelease(const sf::Vector2i& mousePos, const sf::Vector2i &mDelta) {
			onMouseReleaseEvent.invoke(this);
			//std::cout << getName() << " has been released!\n";
		}
		virtual void onMouseEnter(const sf::Vector2i& mousePos, const sf::Vector2i &mDelta) {
			onMouseEnterEvent.invoke(this);
			//std::cout << "Mouse Enter - " << getName() << "\n";
		}
		virtual void onMouseExit(const sf::Vector2i& mousePos, const sf::Vector2i &mDelta) {
			onMouseExitEvent.invoke(this);
		}
		
		virtual void onMouseHold(const sf::Vector2i& mousePos, const sf::Vector2i &mDelta) {
			onMouseHoldEvent.invoke(this);
			//std::cout << "Mouse Hold - " << getName() << "\n";
		}

		//virtual void onMouseDrag() {

		//}

	public:
		Event<UI_Object> onMouseClickedEvent;
		Event<UI_Object> onLeftMouseClickedEvent;
		Event<UI_Object> onMiddleMouseClickedEvent;
		Event<UI_Object> onRightMouseClickedEvent;
		Event<UI_Object> onMouseReleaseEvent;
		Event<UI_Object> onMouseHoldEvent;
		Event<UI_Object> onMouseEnterEvent;
		Event<UI_Object> onMouseExitEvent;
		Event<UI_Object> onMouseHoveredEvent;
		
	public: // SETTERS
		void setName(std::string name);

		void setPosition(UI_Vector2f pos);
		void setSize(UI_Vector2f size);
		void setOrigin(UI_Vector2f origin) {
			M_Origin = origin;
			updateTransform();
			refresh();
		}
		void setMargin(UI_PaddingData margin);
		// sets rotation, in degrees
		void setRotation(float degrees);

		void setVisibility(bool visible) {
			M_visible = visible;
			refresh();
		}

		void setInputHandlingType(inputHandlingType type) {
			M_InputHandlingType = type;
		}

		void setPixelOffset(sf::Vector2i pixelOffset) {
			M_pixelOffset = pixelOffset;
			updateTransform();
		}

		void setZIndex(int index);

	public: // GETTERS
		std::string getName();

		UI_Vector2f getPosition();

		UI_Vector2f getSize();
		UI_PaddingData getMargin();
		// returns rotation, in degrees
		float getRotation();

		// returns the absolute size in pixels
		virtual sf::Vector2f getSizePixels(bool subtractMargin = true);

		// returns the absolute position in pixels, regardless of the object's set origin
		sf::Vector2f getPositionPixels(bool includeMargin = true);

		// returns the absolute position in pixels, meaning the position in pixels relative to the upper-left corner of the window
		sf::Vector2f getAbsolutePositionPixels();

		// returns the absolute bounds in pixels
		sf::FloatRect getBoundsPixels();
		
		sf::FloatRect getAbsoluteBoundsPixels();

		//template <typename T>
		//void addChild(T& object);
		void setParent(objectContainer* parent);

		objectContainer* getParent();

		inline bool getVisibility() {
			return M_visible;
		}

		inline inputHandlingType getInputHandlingType() {
			return M_InputHandlingType;
		}
		
		inline sf::Vector2i getPixelOffset() {
			return M_pixelOffset;
		}

		inline short getZIndex() {
			return M_ZIndex;
		}

	protected:
		friend instance;
		friend objectContainer;

		sf::Vector2f M_AbsolutePositionPixels;
		
		sf::Vector2i M_pixelOffset;

		objectContainer* M_parent = NULL;

		std::string M_Name;

		UI_Vector2f M_Size = UI_Vector2f(100,100);
		UI_Vector2f M_Position;
		UI_Vector2f M_Origin;
		//UI_PaddingData M_Padding;
		UI_PaddingData M_Margin;


		float M_Rotation = 0;

		short M_ZIndex = 0;

		bool M_visible = true;

		// 0: consumes
		// 1: passes through (no consume)
		// 2: consumeAndPassThrough
		inputHandlingType M_InputHandlingType = inputHandlingType::consume;
	};
}