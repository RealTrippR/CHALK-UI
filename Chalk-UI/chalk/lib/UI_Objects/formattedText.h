#ifndef CHK_FORMATTED_TEXT_H
#define CHK_FORMATTED_TEXT_H

#include <chalk/lib/Universal_Includes.h>
#include <chalk/lib/DirtyRenderFlag.h>
#include <chalk/lib/Instance.h>
#include <chalk/lib/UI_Objects/UI_Drawable.h>
#include <chalk/lib/Text_Handling/FontManager.h>
#include <chalk/lib/Text_Handling/FormattedTextChunk.h>;

namespace chk {
	class formattedText : public UI_Drawable {
	public:
		void setFont(int startIndex, int endIndex);
		std::vector<sf::Font*>& getFont(int startIndex, int endIndex);
		
		void setCharacterSize();

	private:
		long long textLength;


	};
}

#endif // !CHK_FORMATTED_TEXT_H
