#pragma once

#ifndef CHK_UI_OBJECT_H
#define CHK_UI_OBJECT_H


#include <chalk/lib/Universal_Includes.h>
#include <SFML/Graphics/Shader.hpp>
#include <chalk/lib/StandardEvents.h>
#include <chalk/lib/StandardFunctions.h>
#include <chalk/lib/UI_Objects/UI_Object.h>

namespace chk {
	class Instance; // forward declaration
	class objectContainer; // forward declaration

	class UI_Drawable : public UI_Object {
	public:
		inline virtual void draw(sf::RenderTexture& RT) {
			std::cout << "UI_DRAWABLE DRAW CALLED - THIS FUNCTION SHOULD NOT BE CALLED\n";
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
		Event<UI_Drawable> onMouseClickedEvent;
		Event<UI_Drawable> onLeftMouseClickedEvent;
		Event<UI_Drawable> onMiddleMouseClickedEvent;
		Event<UI_Drawable> onRightMouseClickedEvent;
		Event<UI_Drawable> onMouseReleaseEvent;
		Event<UI_Drawable> onMouseHoldEvent;
		Event<UI_Drawable> onMouseEnterEvent;
		Event<UI_Drawable> onMouseExitEvent;
		Event<UI_Drawable> onMouseHoveredEvent;
		
	public: // SETTERS

		void setPosition(UI_Vector2f pos);

		void setSize(UI_Vector2f size);

		void setOrigin(UI_Vector2f origin);

		void setMargin(UI_PaddingData margin);

		// sets rotation, in degrees
		void setRotation(float degrees);

		void setVisibility(bool visible);

		void setInputHandlingType(inputHandlingType type);

		void setPixelOffset(sf::Vector2i pixelOffset);

		void setZIndex(int index);

	public: // GETTERS
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

		bool getVisibility();

		inputHandlingType getInputHandlingType();
		
		sf::Vector2i getPixelOffset();

		short getZIndex();

	protected:
		friend Instance;
		friend objectContainer;

		sf::Vector2f M_AbsolutePositionPixels;
		
		sf::Vector2i M_pixelOffset;

		

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

#endif // !CHK_UI_OBJECT_H