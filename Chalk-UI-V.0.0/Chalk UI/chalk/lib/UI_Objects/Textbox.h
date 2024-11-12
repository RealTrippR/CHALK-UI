#ifndef CHK_TEXTBOX_HPP
#define CHK_TEXTBOX_HPP

#include <chalk/lib/Universal_Includes.h>
#include <chalk/lib/DirtyRenderFlag.h>
#include <chalk/lib/Instance.h>
#include <chalk/lib/UI_Objects/UI_Drawable.h>
#include <chalk/lib/FontManager.h>

namespace chk {
	class textBox : public UI_Drawable {
	public:
		void draw(sf::RenderTexture& Parent_RT) override;
	public:
		Event<textBox> onStringUpdated;
		Event<textBox> onStringEntered;
		Event<textBox> onSelected;
		Event<textBox> onDeselected;
	public:
		void onMouseClick(const sf::Vector2i& mPos, const sf::Vector2i& mDelta) override;


		inline void updateInsertionBar();

		void updateTransform(bool callToParent = false) override;

	public:
		void select(bool overrideSelectedIndex = true);

		void deselect();

	public:
		// SETTERS
		void setEnabled(bool enabled);

		// loads the desired font from the font folder if the path is not absolute,
		// if it is absolute it is loaded from the absolute path.
		void setFont(const std::string& filePath);

		void setFillColor(const sf::Color& color);

		void setOutlineColor(const sf::Color& color);

		void setOutlineThickness(const int& size);

		void setCharacterSize(const int& size);

		void setLetterSpacing(const int& spacing);	

		void setLineSpacing(const int& spacing);

		void setString(const std::string& string);

		void setInsertionBarThickness(const int thicknessInPixels);

		void setCurrentSelectedIndex(const int index);

		void setInsertionBarColor(const sf::Color color);

	public:
		// GETTERS
		bool getEnabled();

		std::string getString();

		sf::Font& getFontAsRef();

		sf::Color getFillColor();

		sf::Color getOutlineColor();

		int getOutlineThickness();

		int getCharacterSize();

		int getLetterSpacing();

		int getLineSpacing();

		int getInsertionBarThickness();

		int getCurrentSelectedIndex();

		sf::Color getInsertionBarColor();

	public:
		// default Constructor
		textBox() : UI_Drawable() {
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
		void setBackgroundFillColor(const sf::Color color);

		sf::Color getBackgroundFillColor();

		void setBackgroundOutlineColor(const sf::Color outlineColor);

		sf::Color getBackgroundOutlineColor();

		void setBackgroundOutlineThickness(const int thickness);

		int getBackgroundOutlineThickness();

		void setBackgroundVisibility(const bool visible);

		bool getBackgroundVisibility();

	private:
		int getCharacterIndexAtMousePosition();

		int getCharacterWidthAtIndex(int i);

	private:

		void handleCharPress(char k);

		void handleKeyDelete();
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