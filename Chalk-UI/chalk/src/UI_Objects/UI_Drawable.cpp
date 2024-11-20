
#include <chalk/lib/DirtyRenderFlag.h>
#include <chalk/lib/Instance.h>
#include <chalk/lib/UI_Objects/UI_Drawable.h>
#include <chalk/lib/UI_Objects/Object_Container.h>

namespace chk {
    
    void UI_Drawable::updateTransformUI_Object(bool callToParent /*false by default*/) {
        /*if (M_parent && M_parent->getSizeToContent()) {
            M_parent->updateTransform(true);
        }*/
    }

    


    void UI_Drawable::setPosition(UI_Vector2f pos) {
        M_Position = pos;
        updateTransform();
        refresh();
    }

    void UI_Drawable::setSize(UI_Vector2f size) {
        M_Size = size;
        updateTransform();
        refresh();
    }

    void UI_Drawable::setMargin(UI_PaddingData margin) {
        M_Margin = margin;
        updateTransform();
        refresh();
    }
    
    void UI_Drawable::setZIndex(int index) {
        if (M_parent) {
            M_parent->handleChildZIndexUpdated(this, M_ZIndex, index);
        }
        M_ZIndex = index;
        refresh();
    }

    // GETTERS

    UI_Vector2f UI_Drawable::getPosition() {
        return M_Position;
    }

    UI_Vector2f UI_Drawable::getSize() {
        return M_Size;
    }

    UI_PaddingData UI_Drawable::getMargin() {
        return M_Margin;
    }

    UI_PaddingData UI_Drawable::getInputBoundsExtension() {
        return M_InputBoundsExtension;
    }

    void UI_Drawable::setInputBoundsExtension(const UI_PaddingData boundsExtension) {
        M_InputBoundsExtension = boundsExtension;
    }

    short UI_Drawable::getZIndex() {
        return M_ZIndex;
    }

    sf::Vector2f UI_Drawable::getPositionPixels(bool includeMargin) {
        sf::Vector2f xy;
        if (M_Position.typeX == absolute) {
            xy.x = M_Position.x;
        }
        else {
            // the only object that shouldn't have a parent is the workspace
            if (M_parent) {
                xy.x = M_parent->getSizePixels().x * M_Position.x;
            }
        }
        if (M_Position.typeY == absolute) {
            xy.y = M_Position.y;
        }
        else {
            if (M_parent) {
                xy.y = M_parent->getSizePixels().y * M_Position.y;
            }
        }

        if (includeMargin) {
            xy.x += M_Margin.left;
            xy.y += M_Margin.top;
        }

        // handle origin
        if (M_Origin.typeX==absolute) {
            xy.x -= M_Origin.x;
        }
        else {
            xy.x -= M_Origin.x * getSizePixels().x;
        }

        if (M_Origin.typeY == absolute) {
            xy.y -= M_Origin.y;
        }
        else {
            xy.y -= M_Origin.y * getSizePixels().y;
        }

        // absolute pixel position offset
        xy.x += M_pixelOffset.x;
        xy.y += M_pixelOffset.y;
        return xy;
    }

    sf::Vector2f UI_Drawable::getSizePixels(bool subtractMargin) {
        sf::Vector2f xy;
        if (M_Size.typeX == absolute) {
            xy.x = M_Size.x;
        }
        else {
            // every object, save for the workspace, should have a parent
            if (M_parent) {
                xy.x = M_parent->getSizePixels().x * M_Size.x;
            }
        }
        if (M_Size.typeY == absolute) {
            xy.y = M_Size.y;
        }
        else {
            if (M_parent) {
                xy.y = M_parent->getSizePixels().y * M_Size.y;
            }
        }
        
        if (subtractMargin) {
            xy.x -= (M_Margin.left + M_Margin.right);
            xy.y -= (M_Margin.top + M_Margin.bottom);
        }

        return xy;
    }

    // note that this does not account for padding.
    sf::FloatRect UI_Drawable::getBoundsPixels() {
        // Placeholder logic to calculate bounds, replace with actual logic
        return sf::FloatRect(getPositionPixels(), getSizePixels());
    }
    // note that this does not account for padding.
    sf::FloatRect UI_Drawable::getAbsoluteBoundsPixels() {
        return sf::FloatRect(getAbsolutePositionPixels(), getSizePixels());
    }

    sf::Vector2f UI_Drawable::getAbsolutePositionPixels() {
        if (M_parent != NULL) {
            return M_parent->getAbsolutePositionPixels() + getPositionPixels();
        } else {
            return sf::Vector2f(M_Position.x,M_Position.y);
        }
    }

    bool UI_Drawable::getVisibility() {
        return M_visible;
    }

    inputHandlingType UI_Drawable::getInputHandlingType() {
        return M_InputHandlingType;
    }

    sf::Vector2i UI_Drawable::getPixelOffset() {
        return M_pixelOffset;
    }

    void UI_Drawable::setOrigin(UI_Vector2f origin) {
        M_Origin = origin;
        updateTransform();
        refresh();
    }

    void UI_Drawable::setVisibility(bool visible) {
        M_visible = visible;
        refresh();
    }

    void UI_Drawable::setInputHandlingType(inputHandlingType type) {
        M_InputHandlingType = type;
    }

    void UI_Drawable::setPixelOffset(sf::Vector2i pixelOffset) {
        M_pixelOffset = pixelOffset;
        updateTransform();
    }
}