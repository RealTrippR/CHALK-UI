#ifndef FONT_MANAGER_H
#define FONT_MANAGER_H

#include "FontHandle.h";

namespace chk {
	namespace fs = std::filesystem;
	namespace FontManager {

		std::unordered_map<std::string, int> M_FontMap; // font map, first is filename, second is index
		std::vector<sf::Font*> M_Fonts;

		FontHandle loadFontFromDisk(const std::string& filename) {
			auto it = M_FontMap.find(filename);
			if (it == M_FontMap.end()) {
				sf::Font* font = new sf::Font;
				std::filesystem::path p = "..\\..\\chalk\\static\\Fonts\\" + filename;
				if (!font->loadFromFile(fs::absolute(p).string())) {
					delete font; // Clean up
					throw std::runtime_error("Failed to load font: " + filename);
				}
				M_Fonts.push_back(font);
				M_FontMap[filename] = M_Fonts.size() - 1;
				return FontHandle(M_Fonts.size() - 1);
			}
			return FontHandle(M_FontMap.find(filename)->second);
		}

		sf::Font* getFontFromHandle(const FontHandle& hdl) {
			return M_Fonts[hdl.index];
		}

	};
};
#endif // !FONT_MANAGER_H