#pragma once

#ifndef CHK_TEXT_H
#define CHK_TEXT_H

#include <chalk/lib/Universal_Includes.h>
#include <chalk/lib/DirtyRenderFlag.h>
#include <chalk/lib/Instance.h>
#include <chalk/lib/UI_Objects/UI_Drawable.h>
#include <chalk/lib/UI_Objects/Object_Container.h>
#include <chalk/lib/Text_Handling/FontManager.h>


namespace chk {
	class text : public UI_Drawable {
	public:
		void draw(sf::RenderTexture& Parent_RT,const bool& =false) override;
		void updateTransform(bool callToParent = false) override;

	public:
		void setPosition(UI_Vector2f pos);
		UI_Vector2f getPosition();

	public:
		// setters
		void setFont(const std::string& filename);

		void setFillColor(const sf::Color& color);

		void setOutlineColor(const sf::Color& color);

		void setOutlineThickness(const int& size);

		void setCharacterSize(const int& size);

		void setLetterSpacing(const int& spacing);

		void setLineSpacing(const int& spacing);

		void setString(const std::string& string);

		//void setTextAlignment(const float& alignment);

		void setSizeToTextBounds(const bool& sizeToBounds);

		//void setSizeToContent(bool sizeToContent);
	public:
		// getters
		std::string getString();

		sf::Font& getFontAsRef();

		sf::Color getFillColor();

		sf::Color getOutlineColor();

		int getOutlineThickness();

		int getCharacterSize();

		int getLetterSpacing();

		int getLineSpacing();

		bool getSizeToTextBounds();
		//bool getSizeToContent();

	public:
		text() {
			setFont("arial.ttf");
		}
	private:
		void setSizeFromTextBounds();

		FontHandle M_FontHandle;

		sf::Text M_txt;

		std::string M_String;

		float M_textAlignment = 0;

		bool M_sizeToTextBounds = true;
	};
}

#endif // !CHK_TEXTBOX_H