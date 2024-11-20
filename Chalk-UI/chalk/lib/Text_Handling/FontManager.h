#pragma once

#ifndef FONT_MANAGER_H
#define FONT_MANAGER_H

#include <chalk/lib/Universal_Includes.h>
#include "FontHandle.h";

namespace chk {
	namespace FontManager {

		// defined in FontManager.cpp
		extern std::unordered_map<std::string, int> M_FontMap; // font map, first is filename, second is index
		extern std::vector<sf::Font*> M_Fonts;

		FontHandle loadFontFromDisk(const std::string& filePath);

		sf::Font* getFontFromHandle(const FontHandle& hdl);
	};
};
#endif // !FONT_MANAGER_H