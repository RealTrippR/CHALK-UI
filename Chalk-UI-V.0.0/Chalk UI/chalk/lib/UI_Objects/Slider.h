#ifndef CHK_SLIDER_H
#define CHK_SLIDER_H

namespace chk {
	class slider : public UI_Object {
	public:
		void draw(sf::RenderTexture& Parent_RT) override {
			Parent_RT.draw(M_sliderLine);
			Parent_RT.draw(M_sliderButton);
		}

		void onMouseHold(const sf::Vector2i& mPos, const sf::Vector2i &mDelta) override {
			onMouseHoldEvent.invoke(this);
			updatePercentFromMousePos(mPos);
			updateSlider();
		}
	public:
		// constructor
		slider() {
			setSliderButtonSize(UI_Vector2f(40, 40));
			setSliderButtonTexture(CHK_DEFAULT_ASSETS_DIR+"defaultSliderButton.png");
			setSliderLineOutlineThickness(CHK_DEFAULT_OUTLINE_THICKNESS);
			setSliderLineOutlineColor(sf::Color::Black);
			setSliderLineFillColor(sf::Color::Black);
		}

		// destructor
		~slider() {
			if (M_sliderTexture) {
				delete M_sliderTexture;
			}
		}

	public:
	// SETTERS:
		// sets the position in percent, ranging from 0-1;
		inline float setSliderPercent(const float percent) {
			M_Percent = percent;
			updateSlider();
			refresh();
		}		

		/*
		void setSliderButtonTexture(sf::Texture& img) {
			M_sliderTexture = img;
			updateSlider();
		}
		*/

		inline void setSliderButtonTexture(std::string path) {
			path = util::getAbsoluteFilepath(path);
			M_sliderTexture = new sf::Texture;
			M_sliderTexture->create(M_sliderButtonSize.x,M_sliderButtonSize.y);
			M_sliderTexture->loadFromFile(path);
			M_sliderButton.setTexture(M_sliderTexture);
			refresh();
		}
		
		inline void setSliderButtonSize(UI_Vector2f size) {
			M_sliderButtonSize = size;
			M_sliderButton.setSize(sf::Vector2f(M_sliderButtonSize.x,M_sliderButtonSize.y));
			refresh();
		}

		inline void setSliderLineFillColor(sf::Color color) {
			M_sliderLine.setFillColor(color);
			refresh();
		}

		inline void setSliderLineOutlineColor(sf::Color color) {
			M_sliderLine.setOutlineColor(color);
			refresh();
		}

		inline void setSliderLineOutlineThickness(int thickness) {
			M_sliderLine.setOutlineThickness(thickness);
			refresh();
		}

		void setSize(UI_Vector2f size) {
			M_Size = size;
			updateSlider();
			refresh();
		}

		void setPosition(UI_Vector2f pos) {
			M_Position = pos;
			updateSlider();
			refresh();
		}

	// GETTERS:
		inline float getSliderPercent() {
			return M_Percent;
		}

		inline sf::Texture* getSliderButtonTexture() {
			return M_sliderTexture;
		}

		inline sf::Color getSliderLineFillColor() {
			return M_sliderLine.getFillColor();
		}

		inline sf::Color getSliderLineOutlineColor() {
			return M_sliderLine.getOutlineColor();
		}

		inline int getSliderLineOutlineThickness() {
			return M_sliderLine.getOutlineThickness();
		}

	private:
		void updateSlider() {
			M_sliderLine.setSize(sf::Vector2f(getSizePixels().x, M_sliderLineThickness));
			M_sliderLine.setOrigin(sf::Vector2f( 0,M_sliderLine.getSize().y * .5 ));
			M_sliderLine.setPosition(getPositionPixels()+sf::Vector2f(0,getSizePixels().y*.5));
			M_sliderButton.setOrigin(sf::Vector2f(M_sliderButton.getSize().x*.5, M_sliderButton.getSize().y*.5));
			M_sliderButton.setPosition(getPositionPixels() + sf::Vector2f(getSizePixels().x*M_Percent, getSizePixels().y * .5));
		}

		void updatePercentFromMousePos(const sf::Vector2i& mPos) {
			float offsetX = mPos.x - getAbsolutePositionPixels().x;
			M_Percent = offsetX / getAbsoluteBoundsPixels().width;
			M_Percent = std::clamp(M_Percent, 0.f, 1.f);
		}
	private:
		sf::RectangleShape M_sliderLine;
		sf::RectangleShape M_sliderButton;
		UI_Vector2f M_sliderButtonSize;
		float M_Percent = 0; // 0 - 1
		int M_sliderLineThickness = 5;
		sf::Texture* M_sliderTexture = NULL;  // load a circle shape png from disk by default
	};
}

#endif // !CHK_SLIDER_H