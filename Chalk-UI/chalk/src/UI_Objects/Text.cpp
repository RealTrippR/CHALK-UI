#include <chalk/lib/UI_Objects/Text.h>

namespace chk {
	void text::draw(sf::RenderTexture& Parent_RT, const bool&b) {
		Parent_RT.draw(M_txt);
	}
	void text::updateTransform(bool callToParent) {
		updateTransformUI_Object();
		setSizeFromTextBounds();
	}
	void text::setPosition(UI_Vector2f pos) {
		M_Position = pos;
		updateTransform();
		refresh();
	}
	UI_Vector2f text::getPosition() {
		return M_Position;
	}

	// getters
	std::string text::getString() {
		return M_txt.getString();
	}

	sf::Font& text::getFontAsRef() {
		return *FontManager::getFontFromHandle(M_FontHandle);
	}

	sf::Color text::getFillColor() {
		return M_txt.getFillColor();
	}

	sf::Color text::getOutlineColor() {
		return M_txt.getOutlineColor();
	}

	int text::getOutlineThickness() {
		return M_txt.getOutlineThickness();
	}

	int text::getCharacterSize() {
		return M_txt.getCharacterSize();
	}

	int text::getLetterSpacing() {
		return M_txt.getLetterSpacing();
	}

	int text::getLineSpacing() {
		return M_txt.getLineSpacing();
	}

	bool text::getSizeToTextBounds() {
		return M_sizeToTextBounds;
	}

	// setters
	void text::setFont(const std::string& filename) {
		M_FontHandle = FontManager::loadFontFromDisk(filename);
		M_txt.setFont(*FontManager::getFontFromHandle(M_FontHandle));
		updateTransform();
		refresh();
	}

	void text::setFillColor(const sf::Color& color) {
		M_txt.setFillColor(color);
		updateTransform();
		refresh();

	}

	void text::setOutlineColor(const sf::Color& color) {
		M_txt.setOutlineColor(color);
		updateTransform();
		refresh();
	}

	void text::setOutlineThickness(const int& size) {
		M_txt.setOutlineThickness(size);
		updateTransform();
		refresh();
	}

	void text::setCharacterSize(const int& size) {
		M_txt.setCharacterSize(size);
		updateTransform();
		refresh();
	}

	void text::setLetterSpacing(const int& spacing) {
		M_txt.setLetterSpacing(spacing);
		updateTransform();
		refresh();
	}

	void text::setLineSpacing(const int& spacing) {
		M_txt.setLineSpacing(spacing);
		updateTransform();
		refresh();
	}

	void text::setString(const std::string& string) {
		M_txt.setString(string);
		updateTransform();
		refresh();
	}

	void text::setSizeToTextBounds(const bool& sizeToBounds) {
		M_sizeToTextBounds = sizeToBounds;
		updateTransform();
		refresh();
	}

	void text::setSizeFromTextBounds() {
		if (M_sizeToTextBounds) {
			sf::Text tmp = M_txt; // gets height of standard character, in this case 'A'
			tmp.setString("A");
			int yOffset = -tmp.getLocalBounds().top;
			//int charHeight = tmp.getLocalBounds().height;

			int height = M_txt.getGlobalBounds().height;
			M_Size = UI_Vector2f(M_txt.getGlobalBounds().width, height, absolute);
			std::cout << "H: " << height << "\n";

			M_pixelOffset.y = yOffset; // consider adding a M_privatePixelOffset for situations like these
			M_txt.setPosition(getPositionPixels());
			refresh();
		}
	}
}