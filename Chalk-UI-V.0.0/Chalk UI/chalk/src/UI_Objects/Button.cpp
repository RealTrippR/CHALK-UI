#include <chalk/lib/UI_Objects/Button.h>

namespace chk {
	void button::draw(sf::RenderTexture& Parent_RT) {

		M_RT->clear(M_CurrentFillColor);
		drawChildren(*M_RT);
		M_RT->display();
		M_rect.setTexture(&M_RT->getTexture());
		Parent_RT.draw(M_rect);
	}
	void button::setFillColorOnHover(const sf::Color color) {
		M_FillColorOnHover = color;
		if (!M_Hovered) {
			M_FillColorOnHover = color;
		}
		refresh();
	}

	void button::setOutlineColorOnHover(const sf::Color color) {
		M_OutlineColorOnHover = color;
		if (!M_Hovered) {
			M_CurrentOutlineColor = color;
		}
		refresh();
	}

	void button::setFillColorOnClick(const sf::Color color) {
		M_FillColorOnClick = color;
		refresh();
	}

	void button::setOutlineColorOnClick(const sf::Color color) {
		M_OutlineColorOnClick = color;
		refresh();
	}

	void button::setFillColorAndOutlineColorOnHover(const sf::Color fillColor, const sf::Color outlineColor) {
		M_FillColorOnHover = fillColor;
		if (!M_Hovered) {
			M_CurrentFillColor = fillColor;
		}
		M_OutlineColorOnHover = outlineColor;
		if (!M_Hovered) {
			M_CurrentOutlineColor = outlineColor;
		}
		refresh();
	}

	void button::setFillColorAndOutlineColorOnClick(const sf::Color fillColor, const sf::Color outlineColor) {
		M_FillColorOnClick = fillColor;
		M_OutlineColorOnClick = outlineColor;
		refresh();
	}
	void button::setFillColor(sf::Color fillColor) {
		M_FillColor = fillColor;
		if (!M_Hovered) {
			M_CurrentFillColor = fillColor;
		}
		refresh();
	}

	sf::Color button::getFillColor() {
		return M_FillColor;
	}

	void button::setOutlineColor(sf::Color outlineColor) {
		M_OutlineColor = outlineColor;
		refresh();
	}

	sf::Color button::getOutlineColor() {
		return M_OutlineColor;
	}

	const sf::Color button::getFillColorOnHover() {
		return M_FillColorOnHover;
	}
	const sf::Color button::getOutlineColorOnHover() {
		return M_OutlineColorOnHover;
	}
	const sf::Color button::getFillColorOnClick() {
		return M_FillColorOnClick;
	}
	const sf::Color button::getOutlineColorOnClick() {
		return M_OutlineColorOnClick;
	}
}