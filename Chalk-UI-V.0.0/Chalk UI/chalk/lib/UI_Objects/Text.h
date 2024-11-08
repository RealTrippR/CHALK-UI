#pragma once

#ifndef CHK_TEXT_H
#define CHK_TEXT_H

namespace chk {
	class text : public UI_Object {
	public:
		void draw(sf::RenderTexture& Parent_RT) override {
			Parent_RT.draw(M_txt);
		}
		void updateTransform(bool callToParent = false) override {
			updateTransformUI_Object();
			setSizeFromTextBounds();
		}
	public:
		void setPosition(UI_Vector2f pos) {
			M_Position = pos;
			updateTransform();
			refresh();
		}
		UI_Vector2f getPosition() {
			return M_Position;
		}
	public:
		// getters
		std::string getString() {
			return M_txt.getString();
		}

		sf::Font& getFontAsRef() {
			return *FontManager::getFontFromHandle(M_FontHandle);
		}

		sf::Color getFillColor() {
			return M_txt.getFillColor();
		}
		
		sf::Color getOutlineColor() {
			return M_txt.getOutlineColor();
		}

		int getOutlineThickness() {
			return M_txt.getOutlineThickness();
		}

		int getCharacterSize() {
			return M_txt.getCharacterSize();
		}

		int getLetterSpacing() {
			return M_txt.getLetterSpacing();
		}

		int getLineSpacing() {
			return M_txt.getLineSpacing();
		}

		bool getSizeToContent() {
			return M_SizeToContent;
		}

	public:
		// setters
		void setFont(const std::string& filename) {
			M_FontHandle = FontManager::loadFontFromDisk(filename);
			M_txt.setFont(*FontManager::getFontFromHandle(M_FontHandle));
			updateTransform();
			refresh();
		}

		void setFillColor(const sf::Color& color) {
			M_txt.setFillColor(color);
			updateTransform();
			refresh();

		}

		void setOutlineColor(const sf::Color& color) {
			M_txt.setOutlineColor(color);
			updateTransform();
			refresh();
		}

		void setOutlineThickness(const int& size) {
			M_txt.setOutlineThickness(size);
			updateTransform();
			refresh();
		}

		void setCharacterSize(const int& size) {
			M_txt.setCharacterSize(size);
			updateTransform();
			refresh();
		}

		void setLetterSpacing(const int& spacing) {
			M_txt.setLetterSpacing(spacing);
			updateTransform();
			refresh();
		}

		void setLineSpacing(const int& spacing) {
			M_txt.setLineSpacing(spacing);
			updateTransform();
			refresh();
		}

		void setString(const std::string& string) {
			M_txt.setString(string);
			updateTransform();
			refresh();
		}

		void setSizeToContent(bool sizeToContent) {
			M_SizeToContent = sizeToContent;
			updateTransform();
			refresh();
		}

		text() {
			setFont("arial.ttf");
		}
	private:
		void setSizeFromTextBounds() {

			sf::Text tmp = M_txt; // gets height of standard character, in this case 'A'
			tmp.setString("A");
			int yOffset = -tmp.getLocalBounds().top;
			int charHeight = tmp.getLocalBounds().height;

			M_Size = UI_Vector2f(M_txt.getGlobalBounds().width, charHeight, absolute);

			M_pixelOffset.y = yOffset; // consider adding a M_privatePixelOffset for situations like these
			M_txt.setPosition(getPositionPixels());
			refresh();
		}

		FontHandle M_FontHandle;

		sf::Text M_txt;

		std::string M_String;

		bool M_SizeToContent = true;
	};
}

#endif // !CHK_TEXTBOX_H
