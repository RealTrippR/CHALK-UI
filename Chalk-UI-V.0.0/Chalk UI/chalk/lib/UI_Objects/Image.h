#ifndef CHK_IMAGE_HPP
#define CHK_IMAGE_HPP
#include <chalk/lib/Universal_Includes.h>
#include <chalk/lib/DirtyRenderFlag.h>
#include <chalk/lib/Instance.h>
#include <chalk/lib/UI_Objects/UI_Drawable>

namespace chk {
	class image : public UI_Drawable {
	public:
		void draw(sf::RenderTexture& Parent_RT) override;

	protected:
		inline void updateColorAndTexture();

		void updateTransform(bool callToParent = false);

	public:
		// GETTERS
		sf::Image getImage();

		sf::Image& getImageAsRef();

		sf::Color getPixel(int x, int y);

		// returns the size of the image as it is in disk
		sf::Vector2u getImageSize();

	public:

		sf::Vector2f getPosition();

		void setPosition(UI_Vector2f position);

		sf::Vector2f getSize();

		void setSize(UI_Vector2f size);

		void setFillColor(sf::Color fillColor);

		sf::Color getFillColor();

		void setOutlineColor(sf::Color outlineColor);

		sf::Color getOutlineColor();

		void setOutlineThickness(int thickness);

		int getOutlineThickness();

	public:
		// SETTERS
		void setImage(std::string path);

		void setPixel(int x, int y, sf::Color color);

		image() {
			setImage("..\\Chalk UI\\default assets\\Default_Image.png");
		}
	
	private:
		sf::Image M_Image;
		sf::Texture M_Texture;
		sf::RectangleShape M_Rect;

		sf::Color M_FillColor = sf::Color::White;
	};
}

#endif // !CHK_IMAGE_H