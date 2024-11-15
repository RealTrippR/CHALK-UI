#include <chalk/lib/UI_Objects/Textbox.h>

namespace chk {
	void textBox::draw(sf::RenderTexture& Parent_RT) {
		sf::RectangleShape s; // debug rect
		s.setFillColor(sf::Color::Green);
		s.setPosition(getPositionPixels());
		s.setSize(getSizePixels());
		Parent_RT.draw(s);

		Parent_RT.draw(M_txt);
		if (!M_InsertionBarHidden) {
			Parent_RT.draw(M_insertionBar);
		}
	}

	void textBox::onMouseClick(const sf::Vector2i& mPos, const sf::Vector2i& mDelta) {
		onMouseClickedEvent.invoke(this);

		if ( !sf::Mouse::isButtonPressed(sf::Mouse::Left) ) {
			return;
		}


		if (M_Enabled) {

			M_currentlySelectedIndex = getCharacterIndexAtMousePosition();
			select(false);
			updateTransform();

			// in V1.1 the ability to remove bindings will be added to events,
			// be sure to update this function once that's changed
			chk::onMouseClick.bind([this]() {
				sf::Vector2i mPos = chk::getMousePosition();
				if (!intersectsAbsoluteBounds(sf::Vector2f(mPos.x,mPos.y))) {
					deselect();
				}
			});
		}
	}

	void textBox::updateTransform(bool callToParent) {
		updateTransformUI_Object();

		sf::Text tmp = M_txt; // gets height of standard character, in this case 'A'
		tmp.setString("A");
		int yOffset = -tmp.getLocalBounds().top;
		int charHeight = tmp.getLocalBounds().height;

		//M_Size = UI_Vector2f(M_txt.getGlobalBounds().width, charHeight, absolute);

		M_pixelOffset.y = yOffset; // consider adding a M_privatePixelOffset for situations like these
		M_txt.setPosition(getPositionPixels()+sf::Vector2f(0,yOffset));
		updateInsertionBar();
	}

	inline void textBox::updateInsertionBar() {
		int& i = M_currentlySelectedIndex;
		if (M_txt.getString().getSize() > 0) {
			int charWidth = getCharacterWidthAtIndex(i);
			M_insertionBar.setPosition(M_txt.findCharacterPos(i).x + charWidth - M_txt.getLetterSpacing()
				, M_txt.getPosition().y - M_pixelOffset.y);
		}
		else {
			M_insertionBar.setPosition(M_txt.getPosition().x
				, M_txt.getPosition().y - M_pixelOffset.y);
		}
		M_insertionBar.setSize(sf::Vector2f(M_insertionBar.getSize().x, M_txt.getCharacterSize() + M_pixelOffset.y));
		M_insertionBar.setFillColor(sf::Color::White);
	}

	void textBox::select(bool overrideSelectedIndex) {
		M_currentTimerMilli = 0;
		if (overrideSelectedIndex) {
			M_currentlySelectedIndex = std::clamp(int(M_txt.getString().getSize()) - 1, 0, INT_MAX);
		}
		M_InsertionBarHidden = false;
		onSelected.invoke(this);

		updateTransform();
		refresh();
	}

	void textBox::deselect() {
		M_currentlySelectedIndex = -2;
		M_InsertionBarHidden = true;
		onDeselected.invoke(this);
		updateTransform();
		refresh();
	}

	void textBox::setEnabled(bool enabled) {
		M_Enabled = enabled;
		refresh();
	}

	// loads the desired font from the font folder if the path is not absolute,
	// if it is absolute it is loaded from the absolute path.
	void textBox::setFont(const std::string& filePath) {
		M_FontHandle = FontManager::loadFontFromDisk(filePath);
		M_txt.setFont(*FontManager::getFontFromHandle(M_FontHandle));
		updateTransform();
		refresh();
	}

	void textBox::setFillColor(const sf::Color& color) {
		M_txt.setFillColor(color);
		updateTransform();
		refresh();
	}

	void textBox::setOutlineColor(const sf::Color& color) {
		M_txt.setOutlineColor(color);
		updateTransform();
		refresh();
	}


	void textBox::setOutlineThickness(const int& size) {
		M_txt.setOutlineThickness(size);
		updateTransform();
		refresh();
	}

	void textBox::setCharacterSize(const int& size) {
		M_txt.setCharacterSize(size);
		updateTransform();
		refresh();
	}

	void textBox::setLetterSpacing(const int& spacing) {
		M_txt.setLetterSpacing(spacing);
		updateTransform();
		refresh();
	}

	void textBox::setLineSpacing(const int& spacing) {
		M_txt.setLineSpacing(spacing);
		updateTransform();
		refresh();
	}

	void textBox::setString(const std::string& string) {
		M_txt.setString(string);
		updateTransform();
		onStringUpdated.invoke(this);
		refresh();
	}

	void textBox::setInsertionBarThickness(const int thicknessInPixels) {
		M_insertionBar.setSize(sf::Vector2f(thicknessInPixels, M_insertionBar.getSize().y));
		updateTransform();
		refresh();
	}

	void textBox::setCurrentSelectedIndex(const int index) {
		M_currentlySelectedIndex = index;
		refresh();
	}
	void textBox::setInsertionBarColor(const sf::Color color) {
		M_insertionBar.setFillColor(color);
		refresh();
	}

	bool textBox::getEnabled() {
		return M_Enabled;
	}

	std::string textBox::getString() {
		return M_txt.getString();
	}

	sf::Font& textBox::getFontAsRef() {
		return *FontManager::getFontFromHandle(M_FontHandle);
	}

	sf::Color textBox::getFillColor() {
		return M_txt.getFillColor();
	}

	sf::Color textBox::getOutlineColor() {
		return M_txt.getOutlineColor();
	}

	int textBox::getOutlineThickness() {
		return M_txt.getOutlineThickness();
	}

	int textBox::getCharacterSize() {
		return M_txt.getCharacterSize();
	}

	int textBox::getLetterSpacing() {
		return M_txt.getLetterSpacing();
	}

	int textBox::getLineSpacing() {
		return M_txt.getLineSpacing();
	}

	int textBox::getInsertionBarThickness() {
		return M_insertionBar.getSize().x;
	}

	int textBox::getCurrentSelectedIndex() {
		return M_currentlySelectedIndex;
	}

	sf::Color textBox::getInsertionBarColor() {
		return M_insertionBar.getFillColor();
	}


	int textBox::getCharacterIndexAtMousePosition() {
		sf::Vector2i pos = getMousePosition();
		pos -= sf::Vector2i(getAbsolutePositionPixels().x, getAbsolutePositionPixels().y); // converts the mouse pos to local space.
		pos += sf::Vector2i(M_txt.getPosition());

		// edge case, handle selection in front of the first character
		M_txt.getCharacterSize();
		const sf::FloatRect textBounds = M_txt.getGlobalBounds();
		const float fac = 5 + (M_txt.getCharacterSize() * .05);
		const sf::FloatRect bounds = sf::FloatRect(textBounds.left - fac, textBounds.top, fac, M_txt.getCharacterSize());
		if (bounds.contains(sf::Vector2f(pos))) {
			return -1;
		}

		// cycle through the all the characters to test for intersection with mPos
		for (int i = 0; i < M_txt.getString().getSize(); ++i) {
			sf::Vector2f charPosition = M_txt.findCharacterPos(i);
			const sf::FloatRect textBounds = M_txt.getGlobalBounds();

			float characterWidth = M_txt.findCharacterPos(i + 1).x - charPosition.x;

			sf::FloatRect LocalCharBounds = sf::FloatRect(charPosition.x, charPosition.y, characterWidth, M_txt.getCharacterSize());

			if (LocalCharBounds.contains(sf::Vector2f(pos))) {
				return i;
			}
		}
		if (pos.x > M_txt.getPosition().x) {
			return M_txt.getString().getSize() - 1;
		}
		else {
			return -1;
		}
		return (M_txt.getString().getSize() == 0) ? 0 : -2;
	}

	int textBox::getCharacterWidthAtIndex(int i) {
		const sf::FloatRect textBounds = M_txt.getGlobalBounds();
		sf::Vector2f charPosition = M_txt.findCharacterPos(i);
		// Handle the last character in the string

		//return (i==M_txt.getString().getSize()-1) ? textBounds.width - charPosition.x : M_txt.findCharacterPos(i+1).x - charPosition.x;
		return M_txt.findCharacterPos(i + 1).x - charPosition.x;
	}

	void textBox::handleCharPress(char k) {
		int& i = M_currentlySelectedIndex;
		std::string str = M_txt.getString().toAnsiString();
		if (i >= str.length() - 1) {
			str.push_back(k);
		}
		else if (str.length() != 0)
		{
			str.insert(str.begin() + i + 1, k);
		}
		else {
			str = k;
		}
			
		M_txt.setString(str);
		(M_txt.getString().getSize() == 1) ? i = 0 : ++i;

		onStringUpdated.invoke(this);
	}

	void textBox::handleKeyDelete() {
		int& i = M_currentlySelectedIndex;

		// Ensure index is within bounds
		if (i < 0 || i >= M_txt.getString().getSize()) {
			return;
		}

		std::string str = M_txt.getString().toAnsiString();
		str.erase(str.begin() + i);
		M_txt.setString(str);

		if (i > -1) {
			--i;
		}

		onStringUpdated.invoke(this);
	}
}