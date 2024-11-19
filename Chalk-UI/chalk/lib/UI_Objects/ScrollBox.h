#ifndef CHK_SCROLL_BOX_H*
#define CHK_SCROLL_BOX_H

#include <chalk/lib/UI_Objects/Box.h>

namespace chk {
	enum scrollbar_alignment {
		left,
		right
	};

	class scrollBox : public box {
	public:
		scrollBox(const scrollBox& other) : box(other) {
			M_ScrollBarBackground = other.M_ScrollBarBackground;
			M_ScrollBar = other.M_ScrollBar;
			M_ScrollBarLocked = other.M_ScrollBarLocked;
			M_scrollbarHeldDown = false;
			M_ScrollBarThickness = other.M_ScrollBarThickness;
			M_ScrollBarOutlineThickness = other.M_ScrollBarOutlineThickness;
			M_ScrollBarPercent = other.M_ScrollBarPercent;
			M_Alignment = other.M_Alignment;
			M_ScrollDepth = other.M_ScrollDepth;
		}

		scrollBox(const box& other) : box(other) {

		}

		scrollBox() = default;
	public:
		sf::Vector2f getContentBoundsPixels() override;

		void draw(sf::RenderTexture& Parent_RT, const bool& drawChdrn = true) override;

		void updateTransform(bool callToParent = false) override;

		void onMouseClick(const sf::Vector2i& mousePos, const sf::Vector2i& mDelta) override;

		void onMouseHold(const sf::Vector2i& mousePos, const sf::Vector2i& mDelta) override;

		void onMouseRelease(const sf::Vector2i& mousePos, const sf::Vector2i& mDelta) override;

	public:
		void setScrollBarThickness(int thickness);

		int getScrollBarThickness();

		void setScrollbarOutlineThickness(int thickness);

		int getScrollbarOutlineThickness();

		void setScrollBarFillColor(sf::Color fillColor);

		sf::Color getScrollBarFillColor();
		
		void setScrollBarOutlineColor(sf::Color outlineColor);

		sf::Color getScrollBarOutlineColor();

		void setScrollBarPercent(float percent);

		float getScrollBarPercent();

		void setScrollbarBackgroundColor(sf::Color color);

		sf::Color getScrollbarBackgroundColor();

		void setScrollDepth(int pixels);

		int getScrollDepthPixels();

	protected:
		void updateScrollBarTransform();

		bool intersectsScrollbar(const sf::Vector2i& mPos);

	protected:
		sf::RectangleShape M_ScrollBarBackground;
		sf::RectangleShape M_ScrollBar;
		bool M_ScrollBarLocked = false;
		bool M_scrollbarHeldDown = false;
		int M_ScrollBarThickness = 15;
		int M_ScrollBarOutlineThickness = 0;

		double M_ScrollBarPercent = 0;
		scrollbar_alignment M_Alignment = right;

		int M_ScrollDepth = 600;
	};
}


#endif // !CHK_SCROLL_BOX_H