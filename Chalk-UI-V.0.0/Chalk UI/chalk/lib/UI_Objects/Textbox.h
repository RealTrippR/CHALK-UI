#ifndef CHK_TEXTBOX_HPP
#define CHK_TEXTBOX_HPP

namespace chk {
	class textBox : public UI_Object {
	public:
		inline void draw(sf::RenderTexture& Parent_RT) override {
			Parent_RT.draw(M_txt);
			if (!M_InsertionBarHidden) {
				Parent_RT.draw(M_insertionBar);
			}
		}
	public:
		Event<textBox> onStringUpdated;
		Event<textBox> onStringEntered;
		Event<textBox> onSelected;
		Event<textBox> onDeselected;
	public:
		void onMouseClick(const sf::Vector2i& mPos, const sf::Vector2i& mDelta) override {
			onLeftMouseClickedEvent.invoke(this);
			if (M_Enabled) {
				M_currentlySelectedIndex = getCharacterIndexAtMousePosition();

				select(false);
				updateTransform();
			}
		}


		inline void updateInsertionBar() {
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

		inline void updateTransform(bool callToParent = false) override {
			updateTransformUI_Object();

			sf::Text tmp = M_txt; // gets height of standard character, in this case 'A'
			tmp.setString("A");
			int yOffset = -tmp.getLocalBounds().top;
			int charHeight = tmp.getLocalBounds().height;

			M_Size = UI_Vector2f(M_txt.getGlobalBounds().width, charHeight, absolute);

			M_pixelOffset.y = yOffset; // consider adding a M_privatePixelOffset for situations like these
			M_txt.setPosition(getPositionPixels());
			updateInsertionBar();
			//M_txt.setPosition(sf::Vector2f(M_Position.x, M_Position.y - M_txt.getLocalBounds().top));
		}

	public:
		void select(bool overrideSelectedIndex = true) {
			M_currentTimerMilli = 0;
			if (overrideSelectedIndex) {
				M_currentlySelectedIndex = std::clamp(int(M_txt.getString().getSize()) - 1, 0, INT_MAX);
			}
			M_InsertionBarHidden = false;
			onSelected.invoke(this);

			updateTransform();
			refresh();
		}

		void deselect() {
			M_currentlySelectedIndex = -2;
			M_InsertionBarHidden = true;
			onDeselected.invoke(this);
			updateTransform();
			refresh();
		}

	public:
		// SETTERS
		void setEnabled(bool enabled) {
			M_Enabled = enabled;
			refresh();
		}

		// loads the desired font from the font folder if the path is not absolute,
		// if it is absolute it is loaded from the absolute path.
		void setFont(const std::string& filePath) {
			M_FontHandle = FontManager::loadFontFromDisk(filePath);
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
			onStringUpdated.invoke(this);
			refresh();
		}

		void setInsertionBarThickness(const int thicknessInPixels) {
			M_insertionBar.setSize(sf::Vector2f(thicknessInPixels, M_insertionBar.getSize().y));
			updateTransform();
			refresh();
		}

		void setCurrentSelectedIndex(const int index) {
			M_currentlySelectedIndex = index;
		}
		void setInsertionBarColor(const sf::Color color) {
			M_insertionBar.setFillColor(color);
		}

	public:
		// GETTERS
		bool getEnabled() {
			return M_Enabled;
		}

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

		int getInsertionBarThickness() {
			return M_insertionBar.getSize().x;
		}

		int getCurrentSelectedIndex() {
			return M_currentlySelectedIndex;
		}

		sf::Color getInsertionBarColor() {
			return M_insertionBar.getFillColor();
		}

	public:
		// default Constructor
		textBox() : UI_Object() {
			setFont("arial.ttf");
			//setCharacterSize(11);
			setLetterSpacing(2);
			setInsertionBarThickness(2);

			onTick.bind([this](float* DT) {

				if (M_currentlySelectedIndex != -2) {
					M_currentTimerMilli += *DT;
					if (M_InsertionBarHidden && M_currentTimerMilli > M_millisecondsInsertionBarHidden) {
						M_InsertionBarHidden = false;
						M_currentTimerMilli = 0;
						refresh();
					}
					if (!M_InsertionBarHidden && M_currentTimerMilli > M_millisecondsInsertionBarVisible) {
						M_InsertionBarHidden = true;
						M_currentTimerMilli = 0;
						refresh();
					}
				}
				});

			onKeyPress.bind([this](sf::Keyboard::Key *k, int &consumedIndex) {
				if (M_currentlySelectedIndex != -2) {

					if (*k == sf::Keyboard::Escape && consumedIndex < 1) {
						consumedIndex++;
						deselect();
						return;
					}

					if (*k == sf::Keyboard::Enter && consumedIndex < 1) {
						onStringEntered.invoke(this);
						consumedIndex++;
						deselect();
						return;
					}

					if (*k == sf::Keyboard::Left) {
						auto& i = M_currentlySelectedIndex;
						i = std::clamp(i - 1, -1, int(M_txt.getString().getSize() - 1));
					}
					if (*k == sf::Keyboard::Right) {
						auto& i = M_currentlySelectedIndex;
						i = std::clamp(i + 1, -1, int(M_txt.getString().getSize() - 1));
					}

					if (*k == sf::Keyboard::BackSpace) {
						handleKeyDelete();
					}
					else if (util::isValidKey(*k)) {
						handleCharPress(util::sfKeyToAscii(*k, util::isShiftPressed()));
						//updateTransform(); // do not call updateTranform outside this block, or it will cause the program to believe that the character at the current index is 0 pixels wide
					}
					updateTransform();
					refresh();
				}
			});

			/*chk::onMouseClick.bind([this]() {
			
				// this code is faulty because it will deselect the textbox even if a different textbox was clicked,
				// consider passing a vector of all clicked objects through the onMouseClick event, see if one of them was a textbox that's not this one.
				auto mPos = getMousePosition();
				if (!intersectsAbsoluteBounds(sf::Vector2f(mPos.x, mPos.y))) {
					deselect();
				}
			});*/
		}
		
		// copy constructor
		textBox(const textBox& other) : textBox() {
			M_Enabled = other.M_Enabled;

			M_InsertionBarHidden = true;

			M_FontHandle = other.M_FontHandle;

			M_txt = other.M_txt;

			M_insertionBar = other.M_insertionBar;

			M_millisecondsInsertionBarVisible = other.M_millisecondsInsertionBarVisible;
			M_millisecondsInsertionBarHidden = other.M_millisecondsInsertionBarHidden;

			updateTransform();
			refresh();
		}

	public:
		void setBackgroundFillColor(const sf::Color color) {
			M_Rect.setFillColor(color);
		}

		sf::Color getBackgroundFillColor() {
			return M_Rect.getFillColor();
		}

		void setBackgroundOutlineColor(const sf::Color outlineColor) {
			M_Rect.setOutlineColor(outlineColor);
		}

		sf::Color getBackgroundOutlineColor() {
			return M_Rect.getOutlineColor();
		}

		void setBackgroundOutlineThickness(const int thickness) {
			M_Rect.setOutlineThickness(thickness);
		}

		int getBackgroundOutlineThickness() {
			return M_Rect.getOutlineThickness();
		}

		void setBackgroundVisibility(const bool visible) {
			M_BackgroundRectVisible = visible;
		}

		bool getBackgroundVisibility() {
			return M_BackgroundRectVisible;
		}

	private:
		int getCharacterIndexAtMousePosition() {
			sf::Vector2i pos = getMousePosition();
			pos -= sf::Vector2i(getAbsolutePositionPixels().x,getAbsolutePositionPixels().y); // converts the mouse pos to local space.
			pos += sf::Vector2i(M_txt.getPosition());

			for (int i = 0; i < M_txt.getString().getSize(); ++i) {
				sf::Vector2f charPosition = M_txt.findCharacterPos(i);
				const sf::FloatRect textBounds = M_txt.getGlobalBounds();

				float characterWidth = M_txt.findCharacterPos(i + 1).x - charPosition.x;

				sf::FloatRect LocalCharBounds = sf::FloatRect(charPosition.x, charPosition.y, characterWidth, M_txt.getCharacterSize());

				if (LocalCharBounds.contains(sf::Vector2f(pos))) {
					return i;
				}
			}
			return (M_txt.getString().getSize()==0) ? 0 : M_txt.getString().getSize() - 1;
		}

		int getCharacterWidthAtIndex(int i) {
			const sf::FloatRect textBounds = M_txt.getGlobalBounds();
			sf::Vector2f charPosition = M_txt.findCharacterPos(i);
			// Handle the last character in the string

			//return (i==M_txt.getString().getSize()-1) ? textBounds.width - charPosition.x : M_txt.findCharacterPos(i+1).x - charPosition.x;
			return M_txt.findCharacterPos(i + 1).x - charPosition.x;
		}
	private:

		void handleCharPress(char k) {
			int& i = M_currentlySelectedIndex;
			std::string str = M_txt.getString().toAnsiString();
			if (i >= str.length()-1)
				str.push_back(k);
			else
				str.insert(str.begin() + i, k);
			M_txt.setString(str);
			(M_txt.getString().getSize() == 1) ? i = 0 : ++i;

			onStringUpdated.invoke(this);
		}
		void handleKeyDelete() {
			int& i = M_currentlySelectedIndex;

			// Ensure index is within bounds
			if (i < 0 || i >= M_txt.getString().getSize()) {
				return;
			}

			std::string str = M_txt.getString().toAnsiString();
			str.erase(str.begin() + i);
			M_txt.setString(str);

			if (i > 0) {
				--i;
			}
			onStringUpdated.invoke(this);
		}

	private:

		int M_currentlySelectedIndex = -2; // -2 represents unselected

		bool M_Enabled = true;
		
		bool M_InsertionBarHidden = true;

		FontHandle M_FontHandle;

		sf::Text M_txt;

		sf::RectangleShape M_insertionBar;

		unsigned int M_millisecondsInsertionBarVisible = 500;
		unsigned int M_millisecondsInsertionBarHidden = 800;

		float M_currentTimerMilli = 0;

		sf::RoundedRectangleShape M_Rect; // background rect
		bool M_BackgroundRectVisible = true;
	};
}

#endif // !CHK_TEXTBOX_H