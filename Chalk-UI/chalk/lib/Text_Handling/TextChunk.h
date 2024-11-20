#ifndef CHK_TEXT_CHUNK_H
#define CHK_TEXT_CHUNK_H
#include <chalk/lib/Text_Handling/FontManager.h>

namespace chk {
	class textChunk {
		inline void setFont(const sf::Font& font) {
			M_Text.setFont(font);
		}

		inline const sf::Font* getFontAsRef() {
			return M_Text.getFont();
		}

		inline void setString(const std::string& str) {
			M_Text.setString(str);
		}

		inline const sf::String& getStringAsRef() {
			return M_Text.getString();
		}

		inline void setFillColor(const sf::Color& c) {
			M_Text.setFillColor(c);
		}

		inline const sf::Color getFillColor() {
			return M_Text.getFillColor();
		}

		inline void setOutlineColor(const sf::Color& c) {
			M_Text.setOutlineColor(c);
		}

		inline const sf::Color getOutlineColor() {
			return M_Text.getOutlineColor();
		}

		inline void setOutlineThickness(const int& thickness) {
			M_Text.setOutlineThickness(thickness);
		}

		inline const int getOutlineThickness() {
			return M_Text.getOutlineThickness();
		}

		inline void setCharacterSize(const unsigned int &size) {
			M_Text.setCharacterSize(size);
		}

		inline const unsigned int getCharacterSize() {
			return M_Text.getCharacterSize();
		}

		inline void setStyle(const sf::Uint32& style) {
			M_Text.setStyle(style);
		}

		inline const sf::Uint32 getStyle() {
			return M_Text.getStyle();
		}

	private:
		sf::Text M_Text;
		short length;
	};
}
#endif // !CHK_TEXT_CHUNK_H