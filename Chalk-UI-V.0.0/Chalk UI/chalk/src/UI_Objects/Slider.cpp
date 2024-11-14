#include <chalk/lib/UI_Objects/Slider.h>

namespace chk {

	void slider::draw(sf::RenderTexture& Parent_RT) {
		Parent_RT.draw(M_sliderLine);
		Parent_RT.draw(M_sliderButton);
	}

	void slider::onMouseHold(const sf::Vector2i& mPos, const sf::Vector2i& mDelta) {
		onMouseHoldEvent.invoke(this);
		updatePercentFromMousePos(mPos);
		refresh();
	}

	void slider::updateTransform(bool callToParent) {
		updateTransformUI_Object(callToParent);

		M_sliderLine.setSize(sf::Vector2f(getSizePixels().x, M_sliderLineThickness));
		M_sliderLine.setOrigin(sf::Vector2f(0, M_sliderLine.getSize().y * .5));
		M_sliderLine.setPosition(getPositionPixels() + sf::Vector2f(0, getSizePixels().y * .5));

		M_sliderButton.setOrigin(sf::Vector2f(M_sliderButton.getSize().x * .5, M_sliderButton.getSize().y * .5));
		M_sliderButton.setPosition(getPositionPixels() + sf::Vector2f(getSizePixels().x * M_Percent, getSizePixels().y * .5));

		M_InputBoundsExtension.left = std::clamp(M_InputBoundsExtension.left, M_sliderButtonSize.x / 2, INT_MAX);
		M_InputBoundsExtension.right = std::clamp(M_InputBoundsExtension.right, M_sliderButtonSize.x / 2, INT_MAX);
	}
		
	// SETTERS:
		// sets the position in percent, ranging from 0-1;
	void slider::setSliderPercent(const float percent) {
		M_Percent = percent;
		M_sliderButton.setOrigin(sf::Vector2f(M_sliderButton.getSize().x * .5, M_sliderButton.getSize().y * .5));
		M_sliderButton.setPosition(getPositionPixels() + sf::Vector2f(getSizePixels().x * M_Percent, getSizePixels().y * .5));

		onPercentUpdatedEvent.invoke(this);
		refresh();
	}

	void slider::refreshSliderButtonTexture() {

		static sf::ContextSettings cset;
		cset.antialiasingLevel = getGlobalAntiAliasing();
		M_sliderTexture->create(M_sliderButtonSize.x, M_sliderButtonSize.y, cset);

		static sf::RectangleShape r;
		r.setSize(sf::Vector2f(M_sliderButtonSize.x, M_sliderButtonSize.y));

		sf::Texture t;
		if (!t.loadFromFile(M_sliderButtonTexturePath)) {
			std::cout << "CHK::SLIDER - FAILED TO LOAD TEXTURE: " << M_sliderButtonTexturePath << "\n";
		}
		else {
			std::cout << "SLIDER: " << M_sliderButtonTexturePath << "\n";
			r.setTexture(&t);

			M_sliderTexture->clear(sf::Color::Transparent);
			M_sliderTexture->draw(r);
			M_sliderTexture->display();

			M_sliderButton.setTexture(&M_sliderTexture->getTexture());
		}
	}

	void slider::setSliderButtonTexture(std::string path) {
		M_sliderButtonTexturePath = util::getAbsoluteFilepath(path);
		refreshSliderButtonTexture();
		refresh();
	}

	void slider::setSliderButtonSize(sf::Vector2i size) {
		M_sliderButtonSize = size;
		M_sliderButton.setSize(sf::Vector2f(M_sliderButtonSize.x, M_sliderButtonSize.y));
		if (!M_sliderButtonTexturePath.empty()) {
			refreshSliderButtonTexture();
		}
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

	// GETTERS:
	float slider::getSliderPercent() {
		return M_Percent;
	}

	const sf::Texture* slider::getSliderButtonTexture() {
		return &(M_sliderTexture->getTexture());
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

	void slider::updatePercentFromMousePos(const sf::Vector2i& mPos) {
		float offsetX = mPos.x - getAbsolutePositionPixels().x;
		M_Percent = offsetX / getAbsoluteBoundsPixels().width;
		setSliderPercent(std::clamp(M_Percent, 0.f, 1.f));
	}
}