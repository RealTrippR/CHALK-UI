#ifndef CHK_SLIDER_H
#define CHK_SLIDER_H

#include <chalk/lib/Universal_Includes.h>
#include <chalk/lib/DirtyRenderFlag.h>
#include <chalk/lib/Instance.h>
#include <chalk/lib/UI_Objects/UI_Drawable.h>

namespace chk {
	class slider : public UI_Drawable {
	public:
		void draw(sf::RenderTexture& Parent_RT) override;

		void onMouseHold(const sf::Vector2i& mPos, const sf::Vector2i& mDelta) override;

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
		inline float setSliderPercent(const float percent);

		inline void setSliderButtonTexture(std::string path);
		
		inline void setSliderButtonSize(UI_Vector2f size);

		inline void setSliderLineFillColor(sf::Color color);

		inline void setSliderLineOutlineColor(sf::Color color);

		inline void setSliderLineOutlineThickness(int thickness);

		void setSize(UI_Vector2f size);

		void setPosition(UI_Vector2f pos);

	// GETTERS:
		inline float getSliderPercent();

		inline sf::Texture* getSliderButtonTexture();

		inline sf::Color getSliderLineFillColor();

		inline sf::Color getSliderLineOutlineColor();

		inline int getSliderLineOutlineThickness();

	private:
		void updateSlider();

		void updatePercentFromMousePos(const sf::Vector2i& mPos);

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