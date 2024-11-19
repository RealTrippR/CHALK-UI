#include <chalk/lib/UI_Objects/Image.h>

namespace chk {
	void image::draw(sf::RenderTexture& Parent_RT, const bool&b) {
		Parent_RT.draw(M_Rect);
	}

	inline void image::updateColorAndTexture() {
		M_Rect.setFillColor(M_FillColor);
		M_Rect.setTexture(&M_Texture, true);
	}

	void image::updateTransform(bool callToParent) {
		updateTransformUI_Object();
		M_Rect.setSize(getSizePixels());
		M_Rect.setPosition(getPositionPixels());
		updateColorAndTexture();
	}

	// GETTERS

	sf::Image image::getImage() {
		return M_Image;
	}

	sf::Image& image::getImageAsRef() {
		return M_Image;
	}

	sf::Color image::getPixel(int x, int y) {
		return M_Image.getPixel(x, y);
	}

	// returns the size of the image as it is in disk
	sf::Vector2u image::getImageSize() {
		return M_Image.getSize();
	}

	sf::Vector2f image::getPosition() {
		return M_Rect.getPosition();
	}

	void image::setPosition(UI_Vector2f position) {
		M_Position = position;
		updateTransform();
		refresh();
	}

	sf::Vector2f image::getSize() {
		return M_Rect.getSize();
	}

	void image::setSize(UI_Vector2f size) {
		M_Size = size;
		updateTransform();
		refresh();
	}

	void image::setFillColor(sf::Color fillColor) {
		M_FillColor = fillColor;
		updateTransform();
		refresh();
	}

	sf::Color image::getFillColor() {
		return M_FillColor;
	}

	void image::setOutlineColor(sf::Color outlineColor) {
		M_Rect.setOutlineColor(outlineColor);
		refresh();
	}

	sf::Color image::getOutlineColor() {
		return M_Rect.getOutlineColor();
	}

	void image::setOutlineThickness(int thickness) {
		M_Rect.setOutlineThickness(thickness);
		refresh();
	}

	int image::getOutlineThickness() {
		return M_Rect.getOutlineThickness();
	}

	// SETTERS
	void image::setImage(std::string path) {
		M_Image.loadFromFile(fs::absolute(path).string());
		M_Texture.loadFromImage(M_Image);
		updateTransform();
		refresh();
	}

	void image::setPixel(int x, int y, sf::Color color) {
		M_Image.setPixel(x, y, color);
		refresh();
	}
}