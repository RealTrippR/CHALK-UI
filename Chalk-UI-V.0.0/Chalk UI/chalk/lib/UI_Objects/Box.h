#ifndef CHK_BOX_HPP
#define CHK_BOX_HPP

namespace chk {
	class box : public objectContainer {
	protected:
		inline void drawChildren(sf::RenderTexture& RT) {
			for (auto& Z_Level : M_ZIndexDrawMap) {
				for (auto& obj : Z_Level.second) {
					if (obj->getVisibility()) {
						obj->draw(*M_RT);
					}
				}
			}
		}
	public:
		inline void draw(sf::RenderTexture& Parent_RT) override {
			M_RT->clear(M_FillColor);
			drawChildren(*M_RT);
			M_RT->display();
			M_rect.setTexture(&M_RT->getTexture());
			Parent_RT.draw(M_rect);
		}

	protected:
		inline void updateRenderTexture() {
			M_rect.setTextureRect(sf::IntRect(0,0, getSizePixels().x, getSizePixels().y));

			sf::ContextSettings cset;
			cset.antialiasingLevel = M_antiAliasingLevel;
			M_RT->create(getSizePixels().x, getSizePixels().y,cset);
			sf::View v = sf::View(sf::FloatRect(0, 0, getSizePixels().x, getSizePixels().y));
			M_RT->setView(v);
		}

		inline void updateTransformBox() {
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
		inline void updateTransform(bool callToParent = false) override {
			updateTransformUI_Object(callToParent);
			updateTransformObjectContainer(callToParent);
			updateTransformBox();
		}
	public:
		//void addChild(UI_Object obj) {
			//M_Children.push_back(std::make_shared<UI_Object>(obj));
		//}
		
		box() : objectContainer() {
			if (!M_RT) {
				M_RT = new sf::RenderTexture;
				updateRenderTexture();
			}

			// rectangle defaults
			//M_rect.setOutlineThickness(CHK_DEFAULT_OUTLINE_THICKNESS);
			//M_rect.setOutlineColor(sf::Color::Black);
			M_rect.setOutlineThickness(0);
			M_rect.setFillColor(sf::Color::White);
		}

		// deep copy
		box(const box& other) : objectContainer(other) {
			if (!M_RT) {
				M_RT = new sf::RenderTexture;
			}
			setFillColor(other.M_FillColor);
			setOutlineColor(other.M_rect.getOutlineColor());
			setOutlineThickness(other.M_rect.getOutlineThickness());
			setCornerTaper(other.M_cornerTaper);
			//const register sf::Vector2u tmp = other.M_RT->getSize();
			updateRenderTexture();
		}

		~box() {
			if (M_RT) {
				delete M_RT;
				M_RT = nullptr;
			}

			//for (auto& c : M_Children) {
				//c->parent = nullptr;
			//}
		}

		sf::RenderTexture* getRenderTexture() {
			return M_RT;
		}

	public:
		inline void setFillColor(sf::Color fillColor) {
			// DO NNOOOTT SET THE FILL COLOR OF M_RECT!! e.g. M_rect.setFillColor(fillColor)
			M_FillColor = fillColor;
			refresh();
		}

		inline sf::Color getFillColor() {
			return M_FillColor;
		}

		virtual inline void setOutlineColor(sf::Color outlineColor) {
			M_rect.setOutlineColor(outlineColor);
			refresh();
		}

		virtual inline sf::Color getOutlineColor() {
			return M_rect.getOutlineColor();
		}

		inline void setOutlineThickness(int thickness) {
			M_rect.setOutlineThickness(thickness);
			refresh();
		}

		inline int getOutlineThickness() {
			return M_rect.getOutlineThickness();
		}

		inline void setCornerTaper(const unsigned int cornerTaper) {
			M_cornerTaper = cornerTaper;
			updateTransform(); // corner taper of rounded rect is set in this function
			refresh();
		}

		inline unsigned int getCornerTaper() {
			return M_cornerTaper;
		}

	protected:

		unsigned int M_cornerTaper = 0;

		sf::RenderTexture* M_RT = nullptr;

		sf::RoundedRectangleShape M_rect;

		sf::Color M_FillColor = sf::Color::White;

		//box operator[](int index) {
		//return *M_Children.at(index);
		//}		
	};
}

#endif // !CHK_BOX_H