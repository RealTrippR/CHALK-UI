#ifndef CHK_BOX_HPP
#define CHK_BOX_HPP

#include <chalk/lib/Universal_Includes.h>
#include <chalk/lib/DirtyRenderFlag.h>
#include <chalk/lib/Instance.h>
#include <chalk/lib/UI_Objects/Object_Container.h>

namespace chk {
	class box : public objectContainer {
	protected:
		 void drawChildren(sf::RenderTexture& RT);
	public:
		 void draw(sf::RenderTexture& Parent_RT) override;

	protected:
		 void updateRenderTexture();

		 void updateTransform(bool callToParent = false);

		 void updateTransformBox();
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

		sf::RenderTexture* getRenderTexture();

	public:
		 void setFillColor(sf::Color fillColor);

		 sf::Color getFillColor();

		virtual  void setOutlineColor(sf::Color outlineColor);

		virtual  sf::Color getOutlineColor();

		 void setOutlineThickness(int thickness);

		 int getOutlineThickness();

		 void setCornerTaper(const unsigned int cornerTaper);

		 unsigned int getCornerTaper();
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