#pragma once


#ifndef ROUNDEDRECTANGLESHAPE_HPP
#define ROUNDEDRECTANGLESHAPE_HPP

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <SFML/Graphics/Shape.hpp>

namespace sf
{
    ////////////////////////////////////////////////////////////
    /// \brief Specialized shape representing a rectangle
    /// with rounded corners
    ////////////////////////////////////////////////////////////
    class RoundedRectangleShape : public sf::Shape
    {
    public:
        ////////////////////////////////////////////////////////////
        /// \brief Default constructor
        ///
        /// \param size Size of the rectangle
        /// \param radius Radius for each rounded corner
        /// \param cornerPointCount Number of points of each corner
        ///
        ////////////////////////////////////////////////////////////
        explicit RoundedRectangleShape(const Vector2f& size = Vector2f(0, 0), float radius = 0, unsigned int cornerPointCount = 0);

        ////////////////////////////////////////////////////////////
        /// \brief Set the size of the rounded rectangle
        ///
        /// \param size New size of the rounded rectangle
        ///
        /// \see getSize
        ///
        ////////////////////////////////////////////////////////////
        void setSize(const Vector2f& size);

        ////////////////////////////////////////////////////////////
        /// \brief Get the size of the rounded rectangle
        ///
        /// \return Size of the rounded rectangle
        ///
        /// \see setSize
        ///
        ////////////////////////////////////////////////////////////
        const Vector2f& getSize() const;

        ////////////////////////////////////////////////////////////
        /// \brief Set the radius of the rounded corners
        ///
        /// \param radius Radius of the rounded corners
        ///
        /// \see getCornersRadius
        ///
        ////////////////////////////////////////////////////////////
        void setCornersRadius(float radius);

        ////////////////////////////////////////////////////////////
        /// \brief Get the radius of the rounded corners
        ///
        /// \return Radius of the rounded corners
        ///
        /// \see setCornersRadius
        ///
        ////////////////////////////////////////////////////////////
        float getCornersRadius() const;

        ////////////////////////////////////////////////////////////
        /// \brief Set the number of points of each corner
        ///
        /// \param count New number of points of the rounded rectangle
        ///
        /// \see getPointCount
        ///
        ////////////////////////////////////////////////////////////
        void setCornerPointCount(unsigned int count);

        ////////////////////////////////////////////////////////////
        /// \brief Get the number of points defining the rounded rectangle
        ///
        /// \return Number of points of the rounded rectangle
        ///
        ////////////////////////////////////////////////////////////
        virtual std::size_t getPointCount() const;

        ////////////////////////////////////////////////////////////
        /// \brief Get a point of the rounded rectangle
        ///
        /// The result is undefined if \a index is out of the valid range.
        ///
        /// \param index Index of the point to get, in range [0 .. GetPointCount() - 1]
        ///
        /// \return Index-th point of the shape
        ///
        ////////////////////////////////////////////////////////////
        virtual sf::Vector2f getPoint(std::size_t index) const;

    private:
        ////////////////////////////////////////////////////////////
       // Member data
       ////////////////////////////////////////////////////////////
        void updateCornered() {
            if (myRadius > 0 || myCornerPointCount > 1) {
                myCornered = true;
            }
            else {
                myCornered = false;
            }
        }
        Vector2f mySize;
        bool myCornered = false;
        float myRadius;
        unsigned int myCornerPointCount;
    };
}
#endif // ROUNDEDRECTANGLESHAPE_HPP

////////////////////////////////////////////////////////////
/// \class sf::RoundedRectangleShape
/// \ingroup graphics
///
/// This class inherits all the functions of sf::Transformable
/// (position, rotation, scale, bounds, ...) as well as the
/// functions of sf::Shape (outline, color, texture, ...).
///
/// Usage example:
/// \code
/// sf::RoundedRectangleShape roundedRectangle;
/// rectangle.setSize(sf::Vector2f(100, 50));
/// rectangle.setCornersRadius(5);
/// rectangle.setOutlineThickness(5);
/// rectangle.setPosition(10, 20);
/// ...
/// window.draw(rectangle);
/// \endcode
///
/// \see sf::Shape, sf::CircleShape, sf::ConvexShape
///
////////////////////////////////////////////////////////////



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
            case 0: return sf::Vector2f(0,0);
            case 1: return sf::Vector2f(0, mySize.y);
            case 2: return mySize;
            case 3: return sf::Vector2f(mySize.x, 0);
            }
        }
    }
} // namespace sf