#ifndef CHK_GRID_HPP
#define CHK_GRID_HPP

#include <chalk/lib/Universal_Includes.h>
#include <chalk/lib/DirtyRenderFlag.h>
#include <chalk/lib/Instance.h>
#include <chalk/lib/UI_Objects/box.h>

namespace chk {

	class grid : public box {
	public:
		void draw(sf::RenderTexture& Parent_RT, const bool& drawChdrn = true) override;

	public:
		inline void updateTransformGrid();

		void onChildAdded(UI_Object* obj) override;

		void onChildRemoved(UI_Object* obj) override;

		void updateTransform(bool callToParent = false) override;

		void setChildAlignment(grid_alignment childAlignment);

		grid_alignment getChildAlignment();

		/*void setAutoWrapAround(bool autoWrapAround) {
			M_AutoWrapAround = autoWrapAround;
			updateTransform();
			refresh();
		}
		bool getAutoWrapAround() {
			return M_AutoWrapAround;
		}*/

		
	private:
		grid_alignment M_ChildAlignment = vertical;

		//bool M_AutoWrapAround = false;
	};
}
#endif // !CHK_GRID_HPP