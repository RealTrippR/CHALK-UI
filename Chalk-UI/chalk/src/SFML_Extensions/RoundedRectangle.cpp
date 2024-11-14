#include "chalk/lib/SFML_Extensions/RoundedRectangle.h"

// Headers
////////////////////////////////////////////////////////////
#include <cmath>

namespace sf
{
    ////////////////////////////////////////////////////////////
    RoundedRectangleShape::RoundedRectangleShape(const Vector2f& size, float radius, unsigned int cornerPointCount)
    {
        mySize = size;
        myRadius = radius;
        myCornerPointCount = cornerPointCount;
        update();
    }

    ////////////////////////////////////////////////////////////
    void RoundedRectangleShape::setSize(const Vector2f& size)
    {
        mySize = size;
        update();
    }

    ////////////////////////////////////////////////////////////
    const Vector2f& RoundedRectangleShape::getSize() const
    {
        return mySize;
    }

    ////////////////////////////////////////////////////////////
    void RoundedRectangleShape::setCornersRadius(float radius)
    {
        myRadius = radius;
        updateCornered();
        update();
    }

    ////////////////////////////////////////////////////////////
    float RoundedRectangleShape::getCornersRadius() const
    {
        return myRadius;
    }

    ////////////////////////////////////////////////////////////
    void RoundedRectangleShape::setCornerPointCount(unsigned int count)
    {
        myCornerPointCount = count;
        updateCornered();
        update();
    }

    ////////////////////////////////////////////////////////////
    std::size_t RoundedRectangleShape::getPointCount() const
    {
        return myCornerPointCount * 4;
    }

    ////////////////////////////////////////////////////////////
    sf::Vector2f RoundedRectangleShape::getPoint(std::size_t index) const
    {
        if (myCornered) {
            if (index >= myCornerPointCount * 4)
                return sf::Vector2f(0, 0);

            float deltaAngle = 90.0f / (myCornerPointCount - 1);
            sf::Vector2f center;
            unsigned int centerIndex = index / myCornerPointCount;
            static const float pi = 3.141592654f;

            switch (centerIndex)
            {
            case 0: center.x = mySize.x - myRadius; center.y = myRadius; break;
            case 1: center.x = myRadius; center.y = myRadius; break;
            case 2: center.x = myRadius; center.y = mySize.y - myRadius; break;
            case 3: center.x = mySize.x - myRadius; center.y = mySize.y - myRadius; break;
            }

            return sf::Vector2f(myRadius * cos(deltaAngle * (index - centerIndex) * pi / 180) + center.x,
                -myRadius * sin(deltaAngle * (index - centerIndex) * pi / 180) + center.y);
        }
        else {
            switch (index)
            {
            case 0: return sf::Vector2f(0, 0);
            case 1: return sf::Vector2f(0, mySize.y);
            case 2: return mySize;
            case 3: return sf::Vector2f(mySize.x, 0);
            }
        }
    }
} // namespace sf

