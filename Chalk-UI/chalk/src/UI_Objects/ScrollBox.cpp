#include <chalk/lib/UI_Objects/ScrollBox.h>

namespace chk {
	sf::Vector2f scrollBox::getContentBoundsPixels() {
		sf::Vector2f r = getSizePixels();
		r.y = getScrollDepthPixels();
		r.x -= M_ContentPadding.left + M_ContentPadding.right;
		r.y -= M_ContentPadding.top + M_ContentPadding.bottom;
		return r;
	}

	void scrollBox::draw(sf::RenderTexture& Parent_RT, bool const& drawChdrn) {
		if (drawChdrn) {
			M_RT->clear(M_FillColor);
			drawChildren(*M_RT);
		}

		M_RT->setView(M_RT->getDefaultView());
		//M_RT.draw(M_ScrollBarBackground);
		M_RT->draw(M_ScrollBar);
		M_RT->display();
		M_rect.setTexture(&M_RT->getTexture());
		Parent_RT.draw(M_rect);
	}

	void scrollBox::updateTransform(bool callToParent) {
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

	void scrollBox::onMouseClick(const sf::Vector2i& mousePos, const sf::Vector2i& mDelta) {
		onLeftMouseClickedEvent.invoke(this);
		if (intersectsScrollbar(mousePos)) {
			M_scrollbarHeldDown = true;
		}
	}

	void scrollBox::onMouseHold(const sf::Vector2i& mousePos, const sf::Vector2i& mDelta) {
		onMouseHoldEvent.invoke(this);
		if (M_scrollbarHeldDown) {
			M_ScrollBarPercent += mDelta.y / M_ScrollBar.getSize().y;
			M_ScrollBarPercent = std::clamp(M_ScrollBarPercent, double(0), double(1));

			M_contentOffset.y = M_ScrollBarPercent * (getScrollDepthPixels());
			updateScrollBarTransform();
		}
	}

	void scrollBox::onMouseRelease(const sf::Vector2i& mousePos, const sf::Vector2i& mDelta) {
		onMouseReleaseEvent.invoke(this);
		M_scrollbarHeldDown = false;
	}

	void scrollBox::setScrollBarThickness(int thickness) {
		M_ScrollBarThickness = thickness;
		refresh();
	}

	int scrollBox::getScrollBarThickness() {
		return M_ScrollBarThickness;
	}

	void scrollBox::setScrollbarOutlineThickness(int thickness) {
		M_ScrollBar.setOutlineThickness(thickness);
		refresh();
	}

	int scrollBox::getScrollbarOutlineThickness() {
		return M_ScrollBar.getOutlineThickness();
	}

	void scrollBox::setScrollBarFillColor(sf::Color fillColor) {
		M_ScrollBar.setFillColor(fillColor);
		refresh();
	}

	sf::Color scrollBox::getScrollBarFillColor() {
		return M_ScrollBar.getFillColor();
	}

	void scrollBox::setScrollBarOutlineColor(sf::Color outlineColor) {
		M_ScrollBar.setOutlineColor(outlineColor);
		refresh();
	}

	sf::Color scrollBox::getScrollBarOutlineColor() {
		return M_ScrollBar.getOutlineColor();
	}

	void scrollBox::setScrollBarPercent(float percent) {
		M_ScrollBarPercent = percent;
		refresh();
	}
	float scrollBox::getScrollBarPercent() {
		return M_ScrollBarPercent;
	}

	void scrollBox::setScrollbarBackgroundColor(sf::Color color) {
		M_ScrollBarBackground.setFillColor(color);
		refresh();
	}
	sf::Color scrollBox::getScrollbarBackgroundColor() {
		return M_ScrollBarBackground.getFillColor();
	}

	void scrollBox::setScrollDepth(int pixels) {
		M_ScrollDepth = pixels;
		updateTransform();
		refresh();
	}

	int scrollBox::getScrollDepthPixels() {
		return M_ScrollDepth;
	}

	void scrollBox::updateScrollBarTransform() {
		sf::View view(sf::FloatRect(0.f, M_contentOffset.y, M_RT->getSize().x, M_RT->getSize().y + M_contentOffset.y));
		M_RT->setView(view);

		int height = getSizePixels().y / getScrollDepthPixels() * getSizePixels().y;
		int yOffset = (getSizePixels().y - M_ScrollBar.getSize().y) * M_ScrollBarPercent;
		M_ScrollBar.setSize(sf::Vector2f(M_ScrollBarThickness, height));
		if (M_Alignment == left) {
			M_ScrollBar.setPosition(sf::Vector2f(0, yOffset));
		}
		else if (M_Alignment == right) {
			M_ScrollBar.setPosition(sf::Vector2f(getSizePixels().x, yOffset) - sf::Vector2f(M_ScrollBarThickness, 0));
		}
	}

	bool scrollBox::intersectsScrollbar(const sf::Vector2i& mPos) {
		const int width = M_ScrollBar.getSize().x;
		const int height = M_ScrollBar.getSize().y;
		const sf::Vector2f offset = M_ScrollBar.getPosition();
		const sf::Vector2f topLeft = getAbsolutePositionPixels() + offset;
		if (mPos.x >= topLeft.x && mPos.y >= topLeft.y
			&& mPos.x <= topLeft.x + width && mPos.y <= topLeft.y + height) {
			return true;
		}
		return false;
	}
}