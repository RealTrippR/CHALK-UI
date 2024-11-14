#include <chalk/lib/UI_Objects/Slider.h>

namespace chk {

	void slider::draw(sf::RenderTexture& Parent_RT) {
		Parent_RT.draw(M_sliderLine);
		Parent_RT.draw(M_sliderButton);
	}

	void slider::onMouseHold(const sf::Vector2i& mPos, const sf::Vector2i& mDelta) {
		onMouseHoldEvent.invoke(this);
		updatePercentFromMousePos(mPos);
		updateSlider();
	}
		
	// SETTERS:
		// sets the position in percent, ranging from 0-1;
	void slider::setSliderPercent(const float percent) {
		M_Percent = percent;
		updateSlider();
		refresh();
	}

	void slider::setSliderButtonTexture(std::string path) {
		path = util::getAbsoluteFilepath(path);
		M_sliderTexture = new sf::Texture;
		M_sliderTexture->create(M_sliderButtonSize.x, M_sliderButtonSize.y);
		M_sliderTexture->loadFromFile(path);
		M_sliderButton.setTexture(M_sliderTexture);
		refresh();
	}

	void slider::setSliderButtonSize(UI_Vector2f size) {
		M_sliderButtonSize = size;
		M_sliderButton.setSize(sf::Vector2f(M_sliderButtonSize.x, M_sliderButtonSize.y));
		refresh();
	}

	void slider::setSliderLineFillColor(sf::Color color) {
		M_sliderLine.setFillColor(color);
		refresh();
	}

	void slider::setSliderLineOutlineColor(sf::Color color) {
		M_sliderLine.setOutlineColor(color);
		refresh();
	}

	void slider::setSliderLineOutlineThickness(int thickness) {
		M_sliderLine.setOutlineThickness(thickness);
		refresh();
	}

	void slider::setSize(UI_Vector2f size) {
		M_Size = size;
		updateSlider();
		refresh();
	}

	void slider::setPosition(UI_Vector2f pos) {
		M_Position = pos;
		updateSlider();
		refresh();
	}

	// GETTERS:
	float slider::getSliderPercent() {
		return M_Percent;
	}

	sf::Texture* slider::getSliderButtonTexture() {
		return M_sliderTexture;
	}

	sf::Color slider::getSliderLineFillColor() {
		return M_sliderLine.getFillColor();
	}

	sf::Color slider::getSliderLineOutlineColor() {
		return M_sliderLine.getOutlineColor();
	}

	int slider::getSliderLineOutlineThickness() {
		return M_sliderLine.getOutlineThickness();
	}
	void slider::updateSlider() {
		M_sliderLine.setSize(sf::Vector2f(getSizePixels().x, M_sliderLineThickness));
		M_sliderLine.setOrigin(sf::Vector2f(0, M_sliderLine.getSize().y * .5));
		M_sliderLine.setPosition(getPositionPixels() + sf::Vector2f(0, getSizePixels().y * .5));
		M_sliderButton.setOrigin(sf::Vector2f(M_sliderButton.getSize().x * .5, M_sliderButton.getSize().y * .5));
		M_sliderButton.setPosition(getPositionPixels() + sf::Vector2f(getSizePixels().x * M_Percent, getSizePixels().y * .5));
	}

	void slider::updatePercentFromMousePos(const sf::Vector2i& mPos) {
		float offsetX = mPos.x - getAbsolutePositionPixels().x;
		M_Percent = offsetX / getAbsoluteBoundsPixels().width;
		M_Percent = std::clamp(M_Percent, 0.f, 1.f);
	}
}