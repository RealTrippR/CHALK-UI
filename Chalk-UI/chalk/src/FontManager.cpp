#include <chalk/lib/FontManager.h>

namespace chk {
	namespace FontManager {

		std::unordered_map<std::string, int> M_FontMap;
		std::vector<sf::Font*> M_Fonts;


		FontHandle loadFontFromDisk(const std::string& filePath) {
			auto it = M_FontMap.find(filePath);
			if (it == M_FontMap.end()) {
				sf::Font* font = new sf::Font;
				std::filesystem::path p = filePath;
				if (!p.is_absolute()) {
					p = CHK_DEFAULT_FONTS_FOLDER + filePath;
				}
				if (!font->loadFromFile(fs::absolute(p).string())) {
					delete font; // Clean up
					throw std::runtime_error("Failed to load font: " + filePath);
				}
				M_Fonts.push_back(font);
				M_FontMap[filePath] = M_Fonts.size() - 1;
				return FontHandle(M_Fonts.size() - 1);
			}
			return FontHandle(M_FontMap.find(filePath)->second);
		}

		sf::Font* getFontFromHandle(const FontHandle& hdl) {
			return M_Fonts[hdl.index];
		}
	}
}