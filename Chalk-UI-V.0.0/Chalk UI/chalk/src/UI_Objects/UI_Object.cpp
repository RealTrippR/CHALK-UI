
#include <chalk/lib/Universal_Includes.h>
#include <chalk/lib/DirtyRenderFlag.h>
#include <chalk/lib/Instance.h>
#include <chalk/lib/UI_Objects/UI_Object.h>
#include <chalk/lib/UI_Objects/Object_Container.h>

namespace chk {
    
    void UI_Object::updateTransformUI_Object(bool callToParent /*false by default*/) {
        /*if (M_parent && M_parent->getSizeToContent()) {
            M_parent->updateTransform(true);
        }*/
    }

    void UI_Object::refresh() {
        dirty_render_flag = true;
    }

    // SETTERS
    void UI_Object::setName(std::string name) {
        if (M_parent) {
            M_parent->handleChildNameUpdate(this, M_Name, name);
        }
        M_Name = name;
        refresh();
    }

    void UI_Object::setPosition(UI_Vector2f pos) {
        M_Position = pos;
        updateTransform();
        refresh();
    }

    void UI_Object::setSize(UI_Vector2f size) {
        M_Size = size;
        updateTransform();
        refresh();
    }

    void UI_Object::setMargin(UI_PaddingData margin) {
        M_Margin = margin;
        updateTransform();
        refresh();
    }

    void UI_Object::setRotation(float degrees) {
        M_Rotation = degrees;
        updateTransform();
        refresh();
    }
    
    void UI_Object::setZIndex(int index) {
        if (M_parent) {
            M_parent->HandleChildZIndexUpdated(this, M_ZIndex, index);
        }
        M_ZIndex = index;
        refresh();
    }

    // GETTERS
    std::string UI_Object::getName() {
        return M_Name;
    }

    UI_Vector2f UI_Object::getPosition() {
        return M_Position;
    }

    UI_Vector2f UI_Object::getSize() {
        return M_Size;
    }

    UI_PaddingData UI_Object::getMargin() {
        return M_Margin;
    }

    float UI_Object::getRotation() {
        return M_Rotation;
    }

    sf::Vector2f UI_Object::getPositionPixels(bool includeMargin) {
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

    sf::Vector2f UI_Object::getSizePixels(bool subtractMargin) {
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
    sf::FloatRect UI_Object::getBoundsPixels() {
        // Placeholder logic to calculate bounds, replace with actual logic
        return sf::FloatRect(getPositionPixels(), getSizePixels());
    }
    // note that this does not account for padding.
    sf::FloatRect UI_Object::getAbsoluteBoundsPixels() {
        return sf::FloatRect(getAbsolutePositionPixels(), getSizePixels());
    }

    sf::Vector2f UI_Object::getAbsolutePositionPixels() {
        if (M_parent != NULL) {
            return M_parent->getAbsolutePositionPixels() + getPositionPixels();
        } else {
            return sf::Vector2f(M_Position.x,M_Position.y);
        }
    }
    
    //template <typename T>
    //void UI_Object::addChild(T& object) {
    //}
    void UI_Object::setParent(objectContainer* parent) {

        if (M_parent != parent) {
            if (M_parent) {
                M_parent->removeChild(this);
            }
            M_parent = parent;
            if (M_parent) {
                M_parent->addChild(this);
            }
            updateTransform();
        }
        refresh();
    }

    objectContainer* UI_Object::getParent() {
        return M_parent;
    }
}

/*
void UI_Object::setParent(objectContainer* parent) {
    if (M_parent) {
        M_parent->removeChild(*this);
    }
    M_parent = parent;
    if (M_parent) {
        M_parent->addChild(*this);
    }
}
*/