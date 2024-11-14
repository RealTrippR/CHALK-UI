#include <chalk/lib/UI_Objects/Box.h>


namespace chk {
	void box::drawChildren(sf::RenderTexture& RT) {
		for (auto& Z_Level : M_ZIndexDrawMap) {
			for (auto& obj : Z_Level.second) {
				if (obj->getVisibility()) {
					obj->draw(*M_RT);
				}
			}
		}
	}
	void box::draw(sf::RenderTexture& Parent_RT) {
		M_RT->clear(M_FillColor);
		drawChildren(*M_RT);
		M_RT->display();
		M_rect.setTexture(&M_RT->getTexture());
		Parent_RT.draw(M_rect);
	}

	void box::updateRenderTexture() {
		M_rect.setTextureRect(sf::IntRect(0, 0, getSizePixels().x, getSizePixels().y));

		sf::ContextSettings cset;
		cset.antialiasingLevel = M_antiAliasingLevel;
		M_RT->create(getSizePixels().x, getSizePixels().y, cset);
		sf::View v = sf::View(sf::FloatRect(0, 0, getSizePixels().x, getSizePixels().y));
		M_RT->setView(v);
	}

	void box::updateTransformBox() {
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
	}

	void box::updateTransform(bool callToParent) {
		updateTransformUI_Object(callToParent);
		updateTransformObjectContainer(callToParent);
		updateTransformBox();
	}

	sf::RenderTexture* box::getRenderTexture() {
		return M_RT;
	}

	void box::setFillColor(sf::Color fillColor) {
		// DO NNOOOTT SET THE FILL COLOR OF M_RECT!! e.g. M_rect.setFillColor(fillColor)
		M_FillColor = fillColor;
		refresh();
	}

	sf::Color box::getFillColor() {
		return M_FillColor;
	}

	void box::setOutlineColor(sf::Color outlineColor) {
		M_rect.setOutlineColor(outlineColor);
		refresh();
	}

	sf::Color box::getOutlineColor() {
		return M_rect.getOutlineColor();
	}

	void box::setOutlineThickness(int thickness) {
		M_rect.setOutlineThickness(thickness);
		refresh();
	}

	int box::getOutlineThickness() {
		return M_rect.getOutlineThickness();
	}

	void box::setCornerTaper(const unsigned int cornerTaper) {
		M_cornerTaper = cornerTaper;
		updateTransform(); // corner taper of rounded rect is set in this function
		refresh();
	}

	unsigned int box::getCornerTaper() {
		return M_cornerTaper;
	}
}