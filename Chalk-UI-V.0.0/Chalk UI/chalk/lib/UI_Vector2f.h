#pragma once

enum vectorType {
	absolute, // absolute value, in pixels
	percent // from 0.0 to 1.0
};

// a specialized 2d vector for UI_Objects
// x,y - the x and y coordinates of the vector
// type - tells the UI_Object how to process it
struct UI_Vector2f {
public:
	float x = 0,y = 0;
	vectorType typeX = absolute;
	vectorType typeY = absolute;

	UI_Vector2f() = default;
	UI_Vector2f(float x, float y) : x(x), y(y) {}
	UI_Vector2f(float x, float y, vectorType type) : x(x), y(y), typeX(type), typeY(type) {};
	UI_Vector2f(float x, float y, vectorType typeX, vectorType typeY) : x(x), y(y), typeX(typeX), typeY(typeY) {};
	//UI_Vector2f(float x, float y, vectorType type) : x(x), y(y), type(type) {}

	UI_Vector2f operator+(const UI_Vector2f& other) {
		return UI_Vector2f(x + other.x, y + other.y);
	}
	UI_Vector2f operator-(const UI_Vector2f& other) {
		return UI_Vector2f(x - other.x, y - other.y);
	}
	UI_Vector2f operator*(const UI_Vector2f& other) {
		return UI_Vector2f(x * other.x, y * other.y);
	}
	UI_Vector2f operator/(const UI_Vector2f& other) {
		return UI_Vector2f(x / other.x, y / other.y);
	}
	//UI_Vector2f(sf::Vector2f v, vectorType type) : x(v.x), y(v.y), type(type) {}
};