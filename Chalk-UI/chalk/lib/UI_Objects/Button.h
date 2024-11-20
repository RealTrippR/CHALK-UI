#ifndef CHK_BUTTON_H
#define CHK_BUTTON_H

#include <chalk/lib/Universal_Includes.h>
#include <chalk/lib/DirtyRenderFlag.h>
#include <chalk/lib/Instance.h>
#include <chalk/lib/UI_Objects/box.h>

namespace chk {
	class button : public box {
		void draw(sf::RenderTexture& Parent_RT, const bool& drawChdrn = true) override;
	public:
		void setFillColorOnHover(const sf::Color color);

		void setOutlineColorOnHover(const sf::Color color);

		void setFillColorOnClick(const sf::Color color);

		void setOutlineColorOnClick(const sf::Color color);

		void setFillColorAndOutlineColorOnHover(const sf::Color fillColor, const sf::Color outlineColor);

		void setFillColorAndOutlineColorOnClick(const sf::Color fillColor, const sf::Color outlineColor);

	public:

		void setFillColor(sf::Color fillColor);

		sf::Color getFillColor();

		void setOutlineColor(sf::Color outlineColor) override;

		sf::Color getOutlineColor() override;
	public:
		const sf::Color getFillColorOnHover();

		const sf::Color getOutlineColorOnHover();

		const sf::Color getFillColorOnClick();

		const sf::Color getOutlineColorOnClick();
	public:
		button() : box() {
			init();
		}

		// deep copy - needed to prevent the copying of events
		button(const button& other) : box(other) {
			init();
			M_OutlineColor = other.M_OutlineColor;
			M_CurrentFillColor = other.M_CurrentFillColor;

			M_CurrentOutlineColor = other.M_CurrentOutlineColor;
			M_FillColorOnHover = other.M_FillColorOnHover;
			M_OutlineColorOnHover = other.M_OutlineColorOnHover;
			M_FillColorOnClick = other.M_FillColorOnClick;
			M_OutlineColorOnClick = other.M_OutlineColorOnClick;
		}
	private:
		inline void init() {
			std::cout << "CONSTRUCTOR CALLED!\n" << this << "\n";
			this->onLeftMouseClickedEvent.bind([this]() {
				M_CurrentFillColor = M_FillColorOnClick;
				M_CurrentOutlineColor = M_OutlineColorOnClick;
				M_HeldDown = true;
				refresh();
				});
			this->onMouseHoveredEvent.bind([this]() {
				M_Hovered = true;
				M_CurrentFillColor = M_FillColorOnHover;
				M_CurrentOutlineColor = M_OutlineColorOnHover;
				refresh();
				});
			this->onMouseExitEvent.bind([this]() {
				if (!M_HeldDown) {
					M_CurrentFillColor = M_FillColor;
					M_CurrentOutlineColor = M_OutlineColor;
					refresh();
				}
				M_Hovered = false;
				});
			chk::onMouseRelease.bind([this]() {
				M_CurrentFillColor = M_FillColor;
				M_CurrentOutlineColor = M_OutlineColor;
				M_HeldDown = false;
				refresh();
				});
		}
	private:

		bool M_Hovered = false; // true if currently being hovered over
		bool M_HeldDown = false; // true if currently being held down

		sf::Color M_OutlineColor;
		sf::Color M_CurrentFillColor;

		sf::Color M_CurrentOutlineColor;
		sf::Color M_FillColorOnHover;
		sf::Color M_OutlineColorOnHover;
		sf::Color M_FillColorOnClick;
		sf::Color M_OutlineColorOnClick;
	};
}

#endif // !CHK_BUTTON_H