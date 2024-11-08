#ifndef CHK_BUTTON_H
#define CHK_BUTTON_H

namespace chk {
	class button : public box {
		// I think that the contentBounds arg can be removed. maybe.
		inline void draw(sf::RenderTexture& Parent_RT) override {
			//FUNCTION INCOMPLETE!

			M_RT->clear(M_CurrentFillColor);
			drawChildren(*M_RT);
			M_RT->display();
			M_rect.setTexture(&M_RT->getTexture());
			Parent_RT.draw(M_rect);
		}
	public:
		void setFillColorOnHover(const sf::Color color) {
			M_FillColorOnHover = color;
			if (!M_Hovered) {
				M_FillColorOnHover = color;
			}
			refresh();
		}

		void setOutlineColorOnHover(const sf::Color color) {
			M_OutlineColorOnHover = color;
			if (!M_Hovered) {
				M_CurrentOutlineColor = color;
			}
			refresh();
		}

		void setFillColorOnClick(const sf::Color color) {
			M_FillColorOnClick = color;
			refresh();
		}

		void setOutlineColorOnClick(const sf::Color color) {
			M_OutlineColorOnClick = color;
			refresh();
		}

		void setFillColorAndOutlineColorOnHover(const sf::Color fillColor, const sf::Color outlineColor) {
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

		void setFillColorAndOutlineColorOnClick(const sf::Color fillColor, const sf::Color outlineColor) {
			M_FillColorOnClick = fillColor;
			M_OutlineColorOnClick = outlineColor;
			refresh();
		}

	public:

		inline void setFillColor(sf::Color fillColor) {
			M_FillColor = fillColor;
			if (!M_Hovered) {
				M_CurrentFillColor = fillColor;
			}
			refresh();
		}

		inline sf::Color getFillColor() {
			return M_FillColor;
		}

		inline void setOutlineColor(sf::Color outlineColor) override {
			M_OutlineColor = outlineColor;
			refresh();
		}

		inline sf::Color getOutlineColor() override {
			return M_OutlineColor;
		}
	public:
		const sf::Color getFillColorOnHover() {
			return M_FillColorOnHover;
		}
		const sf::Color getOutlineColorOnHover() {
			return M_OutlineColorOnHover;
		}
		const sf::Color getFillColorOnClick() {
			return M_FillColorOnClick;
		}
		const sf::Color getOutlineColorOnClick() {
			return M_OutlineColorOnClick;
		}
	public:
		button() : box() {
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