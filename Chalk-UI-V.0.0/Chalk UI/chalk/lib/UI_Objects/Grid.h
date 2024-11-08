#ifndef CHK_GRID_HPP
#define CHK_GRID_HPP

namespace chk {

	class grid : public box {
	public:
		void draw(sf::RenderTexture& Parent_RT) override {
			M_RT->clear(M_FillColor);
			for (auto& obj : getChildren()) {
				obj->draw(*M_RT);
			}
			M_RT->display();
			M_rect.setTexture(&M_RT->getTexture());
			Parent_RT.draw(M_rect);
		}

	public:
		inline void updateTransformGrid() {
			unsigned int absoluteWidth = getSizePixels().x;
			unsigned int absoluteHeight = getSizePixels().y;
			unsigned int maxperpindicularLenSizeOfThisRowOrColumn = 0; // for the auto-wrap feature
			unsigned int perpindicularPixelOffset = 0; // the perpindicular offset is 90 degrees from the main child alignment (i.e. perpindicular to horizontal would be vertical)
			unsigned int xORyPixels = 0;
			for (auto& obj : getChildren()) {
				switch (M_ChildAlignment)
				{
				case horizontal:
					//obj->setPosition(UI_Vector2f(obj->getMargin().left + xORyPixels, obj->getPosition().y, absolute));
					obj->setPosition(UI_Vector2f(xORyPixels, obj->getPosition().y, absolute,obj->getPosition().typeY));
					
					xORyPixels += obj->getAbsoluteBoundsPixels().width + obj->getMargin().left + obj->getMargin().right;

					/*if (M_AutoWrapAround) {
						maxperpindicularLenSizeOfThisRowOrColumn = std::max(int(maxperpindicularLenSizeOfThisRowOrColumn), int(obj->getSizePixels(false).y));
						if (xORyPixels > getContentBoundsPixels().x) {
							perpindicularPixelOffset += maxperpindicularLenSizeOfThisRowOrColumn;
						}
						obj->setPosition(UI_Vector2f(obj->getPosition().x, obj->getPosition().y));
					}*/

					break;
				case vertical:
					obj->setPosition(UI_Vector2f(obj->getPosition().x,xORyPixels, obj->getPosition().typeX,absolute));
					xORyPixels += obj->getAbsoluteBoundsPixels().height + obj->getMargin().top + obj->getMargin().bottom;
					/*if (M_AutoWrapAround) {
						maxperpindicularLenSizeOfThisRowOrColumn = std::max(int(maxperpindicularLenSizeOfThisRowOrColumn), int(obj->getSizePixels(false).x));
					}*/
					break;
				default:
					break;
				}
			}
		}
		inline void onChildAdded(UI_Object* obj) override {
			updateTransformGrid();
		}
		inline void onChildRemoved(UI_Object* obj) override {
			updateTransformGrid();
		}
		inline void updateTransform(bool callToParent = false) override {
			updateTransformUI_Object(callToParent);
			updateTransformObjectContainer(callToParent);
			updateTransformBox();
			updateTransformGrid();
		}
		void setChildAlignment(grid_alignment childAlignment) {
			M_ChildAlignment = childAlignment;
			refresh();
		}

		grid_alignment getChildAlignment() {
			return M_ChildAlignment;
		}

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