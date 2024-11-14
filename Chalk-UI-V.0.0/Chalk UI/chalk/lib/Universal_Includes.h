#ifndef CHK_UNIVERSAL_INCLUDES_H
#define CHK_UNIVERSAL_INCLUDES_H

#include <iostream>
#include <functional>
#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <vector>
#include <utility>
#include <functional>
#include <set>
#include <unordered_set>
#include <memory>
#include <filesystem>
#include <fstream>
#include <chrono>
#include <fstream>

#include "UI_Vector2f.h"
#include "UI_FloatRect.h"
#include "UI_PaddingData.h"
#include "Enums.h"
#include "Util.h"
#include "chalk/lib/SFML_Extensions/RoundedRectangle.h"

namespace chk {
	namespace fs = std::filesystem;
	#define CHK_DEFAULT_ASSETS_DIR std::string("..\\..\\chalk\\static\\DefaultAssets\\")
	#define CHK_DEFAULT_FONTS_FOLDER std::string("..\\..\\chalk\\static\\Fonts\\")
	#define CHK_DEFAULT_OUTLINE_THICKNESS 2
}

#endif // !CHK_UNIVERSAL_INCLUDES_H