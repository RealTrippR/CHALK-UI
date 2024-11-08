#include "UI_Object.h"
#include "objectContainer.h"

namespace chk {

    void UI_Object::setPosition(UI_Vector2f pos) {
        M_Position = pos;
    }

    void UI_Object::setSize(UI_Vector2f size) {
        M_Size = size;
    }

    void UI_Object::setPadding(UI_FloatRect padding) {
        M_Padding = padding;
    }

    void UI_Object::setRotation(float degrees) {
        M_Rotation = degrees;
    }

    void UI_Object::setFillColor(sf::Color color) {
        M_FillColor = color;
    }

    void UI_Object::setOutlineThickness(int thickness) {
        M_OutlineThickness = thickness;
    }

    void UI_Object::setOutlineColor(sf::Color color) {
        M_OutlineColor = color;
    }

    UI_Vector2f UI_Object::getPosition() {
        return M_Position;
    }

    UI_Vector2f UI_Object::getSize() {
        return M_Size;
    }

    UI_FloatRect UI_Object::getPadding() {
        return M_Padding;
    }

    float UI_Object::getRotation() {
        return M_Rotation;
    }

    sf::Color UI_Object::getFillColor() {
        return M_FillColor;
    }

    sf::Color UI_Object::getOutlineColor() {
        return M_OutlineColor;
    }

    int UI_Object::getOutlineThickness() {
        return M_OutlineThickness;
    }

    sf::Vector2f UI_Object::getPositionPixels() {
        // Placeholder logic to convert position to pixels, replace with actual logic
        return sf::Vector2f(M_Position.x, M_Position.y);
    }

    sf::FloatRect UI_Object::getBoundsPixels() {
        // Placeholder logic to calculate bounds, replace with actual logic
        return sf::FloatRect(getPositionPixels(), getSizePixels());
    }

    void UI_Object::setParent(objectContainer* parent) {
        if (M_parent) {
            M_parent->removeChild(*this);
        }
        M_parent = parent;
        if (M_parent) {
            M_parent->addChild(*this);
        }
    }
}