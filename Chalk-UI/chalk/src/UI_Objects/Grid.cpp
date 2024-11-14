#include <chalk/lib/UI_Objects/Grid.h>
namespace chk {
	void grid::draw(sf::RenderTexture& Parent_RT) {
		M_RT->clear(M_FillColor);
		for (auto& Z_Level : M_ZIndexDrawMap) {
			for (auto& obj : Z_Level.second) {
				if (obj->getVisibility()) {
					obj->draw(*M_RT);
				}
			}
		}
		M_RT->display();
		M_rect.setTexture(&M_RT->getTexture());
		Parent_RT.draw(M_rect);
	}

	inline void grid::updateTransformGrid() {
		unsigned int absoluteWidth = getSizePixels().x;
		unsigned int absoluteHeight = getSizePixels().y;
		unsigned int maxperpindicularLenSizeOfThisRowOrColumn = 0; // for the auto-wrap feature
		unsigned int perpindicularPixelOffset = 0; // the perpindicular offset is 90 degrees from the main child alignment (i.e. perpindicular to horizontal would be vertical)
		unsigned int xORyPixels = 0;
		for (auto& objRef : getChildren()) {
			UI_Drawable* obj = dynamic_cast<UI_Drawable*>(objRef);
			if (!obj) {
				return;
			}
			
			switch (M_ChildAlignment)
			{
			case horizontal:
				//obj->setPosition(UI_Vector2f(obj->getMargin().left + xORyPixels, obj->getPosition().y, absolute));
				obj->setPosition(UI_Vector2f(xORyPixels, obj->getPosition().y, absolute, obj->getPosition().typeY));

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
				obj->setPosition(UI_Vector2f(obj->getPosition().x, xORyPixels, obj->getPosition().typeX, absolute));
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
	void grid::onChildAdded(UI_Object* obj) {
		updateTransformGrid();
		onChildAddedEvent.invoke(this);
	}
	void grid::onChildRemoved(UI_Object* obj) {
		updateTransformGrid();
		onChildAddedEvent.invoke(this);
	}
	void grid::updateTransform(bool callToParent) {
		updateTransformUI_Object(callToParent);
		updateTransformObjectContainer(callToParent);
		updateTransformBox();
		updateTransformGrid();
	}
	void grid::setChildAlignment(grid_alignment childAlignment) {
		M_ChildAlignment = childAlignment;
		refresh();
	}

	grid_alignment grid::getChildAlignment() {
		return M_ChildAlignment;
	}
}