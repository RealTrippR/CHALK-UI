#ifndef CHK_SCROLL_BOX_H*

#define CHK_SCROLL_BOX_H
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
		inline sf::Vector2f getContentBoundsPixels() override {
			sf::Vector2f r = getSizePixels();
			r.y = getScrollDepthPixels();
			r.x -= M_ContentPadding.left + M_ContentPadding.right;
			r.y -= M_ContentPadding.top + M_ContentPadding.bottom;
			return r;
		}
	protected:

	public:
		inline void draw(sf::RenderTexture& Parent_RT) override {
			M_RT->clear(M_FillColor);
			drawChildren(*M_RT);
			
			M_RT->setView(M_RT->getDefaultView());
			//M_RT.draw(M_ScrollBarBackground);
			M_RT->draw(M_ScrollBar);
			M_RT->display();
			M_rect.setTexture(&M_RT->getTexture());
			Parent_RT.draw(M_rect);
		}

		inline void updateTransform(bool callToParent = false) override {
			updateTransformUI_Object(callToParent);
			updateTransformObjectContainer(callToParent);

			M_rect.setPosition(getPositionPixels());
			M_rect.setSize(getSizePixels());
			updateRenderTexture();

			unsigned int smallestSidePixels = std::min(getSizePixels().x, getSizePixels().y);
			M_rect.setCornersRadius(std::clamp(M_cornerTaper, 0u, smallestSidePixels / 2u));
			switch (M_cornerTaper) {
			case 0:
				M_rect.setCornerPointCount(1);
				break;
			default:
				M_rect.setCornerPointCount(M_rect.getCornersRadius());
				break;
			}

			updateScrollBarTransform();
		}

		void onMouseClick(const sf::Vector2i& mousePos, const sf::Vector2i& mDelta) override {
			onLeftMouseClickedEvent.invoke(this);
			if (intersectsScrollbar(mousePos)) {
				M_scrollbarHeldDown = true;
			}
		}

		void onMouseHold(const sf::Vector2i& mousePos, const sf::Vector2i& mDelta) override {
			onMouseHoldEvent.invoke(this);
			if (M_scrollbarHeldDown) {
				M_ScrollBarPercent += mDelta.y / M_ScrollBar.getSize().y;
				M_ScrollBarPercent = std::clamp(M_ScrollBarPercent, double(0), double(1));

				M_contentOffset.y = M_ScrollBarPercent * (getScrollDepthPixels());
				updateScrollBarTransform();
			}
		}

		void onMouseRelease(const sf::Vector2i& mousePos, const sf::Vector2i& mDelta) override {
			onMouseReleaseEvent.invoke(this);
			M_scrollbarHeldDown = false;
		}

	public:
		inline void setScrollBarThickness(int thickness) {
			M_ScrollBarThickness = thickness;
			refresh();
		}

		inline int getScrollBarThickness() {
			return M_ScrollBarThickness;
		}

		inline void setScrollbarOutlineThickness(int thickness) {
			M_ScrollBar.setOutlineThickness(thickness);
			refresh();
		}

		inline int getScrollbarOutlineThickness() {
			M_ScrollBar.getOutlineThickness();
		}

		inline void setScrollBarFillColor(sf::Color fillColor) {
			M_ScrollBar.setFillColor(fillColor);
			refresh();
		}

		inline sf::Color getScrollBarFillColor() {
			return M_ScrollBar.getFillColor();
		}
		
		inline void setScrollBarOutlineColor(sf::Color outlineColor) {
			M_ScrollBar.setOutlineColor(outlineColor);
			refresh();
		}

		inline sf::Color getScrollBarOutlineColor() {
			return M_ScrollBar.getOutlineColor();
		}

		inline void setScrollBarPercent(float percent) {
			M_ScrollBarPercent = percent;
			refresh();
		}
		inline float getScrollBarPercent() {
			return M_ScrollBarPercent;
		}

		inline void setScrollbarBackgroundColor(sf::Color color) {
			M_ScrollBarBackground.setFillColor(color);
			refresh();
		}
		inline sf::Color getScrollbarBackgroundColor() {
			return M_ScrollBarBackground.getFillColor();
		}

		inline void setScrollDepth(int pixels) {
			M_ScrollDepth = pixels;
			updateTransform();
			refresh();
		}

		inline int getScrollDepthPixels() {
			return M_ScrollDepth;
		}
	protected:
		void updateScrollBarTransform() {
			sf::View view(sf::FloatRect(0.f, M_contentOffset.y, M_RT->getSize().x, M_RT->getSize().y + M_contentOffset.y));
			M_RT->setView(view);

			int height = getSizePixels().y / getScrollDepthPixels() * getSizePixels().y;
			int yOffset = (getSizePixels().y - M_ScrollBar.getSize().y) * M_ScrollBarPercent;
			M_ScrollBar.setSize(sf::Vector2f(M_ScrollBarThickness, height));
			if (M_Alignment == left) {
				M_ScrollBar.setPosition(sf::Vector2f(0, yOffset));
			}
			else if (M_Alignment == right) {
				M_ScrollBar.setPosition(sf::Vector2f(getSizePixels().x, yOffset)-sf::Vector2f(M_ScrollBarThickness,0));
			}
		}

		bool intersectsScrollbar(const sf::Vector2i &mPos) {
			const int width = M_ScrollBar.getSize().x;
			const int height = M_ScrollBar.getSize().y;
			const sf::Vector2f offset = M_ScrollBar.getPosition();
			const sf::Vector2f topLeft = getAbsolutePositionPixels() + offset;
			if (mPos.x >= topLeft.x && mPos.y >= topLeft.y
				&& mPos.x <= topLeft.x+width && mPos.y <= topLeft.y + height) {
				return true;
			}
			return false;
		}
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