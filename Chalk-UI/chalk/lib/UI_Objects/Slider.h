#ifndef CHK_SLIDER_H
#define CHK_SLIDER_H

#include <chalk/lib/Universal_Includes.h>
#include <chalk/lib/DirtyRenderFlag.h>
#include <chalk/lib/Instance.h>
#include <chalk/lib/UI_Objects/UI_Drawable.h>

namespace chk {
	class slider : public UI_Drawable {
	public:
		void draw(sf::RenderTexture& Parent_RT, const bool& =false) override;

		void onMouseHold(const sf::Vector2i& mPos, const sf::Vector2i& mDelta) override;

		void updateTransform(bool callToParent = false) override;
	public:
		// constructor
		slider() {
			M_sliderTexture = new sf::RenderTexture();
			setSliderButtonSize({ 40, 40 });
			setSliderButtonTexture(CHK_DEFAULT_ASSETS_DIR + std::string("Images\\defaultSliderButton.png"));
			setSliderLineOutlineThickness(CHK_DEFAULT_OUTLINE_THICKNESS);
			setSliderLineOutlineColor(sf::Color::White);
			setSliderLineFillColor(sf::Color::White);
		}

		// destructor
		~slider() {
			if (M_sliderTexture) {
				delete M_sliderTexture;
			}
		}
	public:
		// invoked everytime the sliders percent is updated.
		Event<slider> onPercentUpdatedEvent;
	public:
		void refreshSliderButtonTexture();
	public:
	// SETTERS:
		// sets the position in percent, ranging from 0-1;
		void setSliderPercent(const float percent);

		void setSliderButtonTexture(std::string path);
		
		void setSliderButtonSize(sf::Vector2i size);

		void setSliderLineFillColor(sf::Color color);

		void setSliderLineOutlineColor(sf::Color color);

		void setSliderLineOutlineThickness(int thickness);

	// GETTERS:
		float getSliderPercent();

		const sf::Texture* getSliderButtonTexture();

		sf::Color getSliderLineFillColor();

		sf::Color getSliderLineOutlineColor();

		int getSliderLineOutlineThickness();

	private:
		void updatePercentFromMousePos(const sf::Vector2i& mPos);

	private:
		sf::RectangleShape M_sliderLine;
		sf::RectangleShape M_sliderButton;
		sf::Vector2i M_sliderButtonSize = { 40,40 };
		float M_Percent = 0; // 0 - 1
		int M_sliderLineThickness = 5;

		int M_sliderTextureAA = 0; // slider texture anti-aliasing
		// altough it would be simpler to just use a sf::Texture, a sf::RenderTexture is needed for Anti-Aliasing support
		sf::RenderTexture* M_sliderTexture = NULL;  // load a circle shape png from disk by default
		std::string M_sliderButtonTexturePath;
	};
}

#endif // !CHK_SLIDER_H