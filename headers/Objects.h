#pragma once

//----------------------------------------------------------------------------
//{ Includes
//----------------------------------------------------------------------------

#include "Matrix.h"
#include "Vector.h" 

//}
//----------------------------------------------------------------------------


//----------------------------------------------------------------------------
//{ Object
//----------------------------------------------------------------------------

    struct Object
    {

        // Constructor && destructor:

            Object(Vector newCoords, Vector newSpeed, unsigned int mass, COLORREF newColor);

		// Functions:

			Object& accelerate(Vector acceleration);
			Object& move();

			Object& slowdown(double slowness);

        // Variables:

            Vector coords;
            Vector speed;

            unsigned int mass;

            COLORREF color;
    };


    //----------------------------------------------------------------------------
    //{ Constructor && destructor
    //----------------------------------------------------------------------------

        Object::Object(Vector newCoords, Vector newSpeed, unsigned int newMass, COLORREF newColor) :
            coords (newCoords),
            speed  (newSpeed),
            mass   (newMass),
            color  (newColor)
        {}

    //}
    //----------------------------------------------------------------------------


	//----------------------------------------------------------------------------
	//{ Functions
	//----------------------------------------------------------------------------

		Object& Object::accelerate(Vector acceleration)
		{
			speed += acceleration;

			return *this;
		}

		Object& Object::move()
		{
			coords += speed;

			return *this;
		}

		Object& Object::slowdown(double slowness)
		{
			assert(0 <= slowness && slowness <= 1);

			speed *= (1 - slowness);

			return *this;
		}

	//}
	//----------------------------------------------------------------------------

//}
//----------------------------------------------------------------------------


//----------------------------------------------------------------------------
//{ Ball
//----------------------------------------------------------------------------

    struct Ball : public Object
    {
		public:

            // Constructor:

                Ball(Vector newCoords, Vector newSpeed, unsigned int newMass, COLORREF newColor, unsigned int newRadius);

            // Functions:

                bool collision(const Ball& ball) const;

				Ball& interact(Ball& ball);

            // Variables:

                unsigned int radius;
    };


    //----------------------------------------------------------------------------
    //{ Constructor && destructor
    //----------------------------------------------------------------------------

        Ball::Ball(Vector newCoords, Vector newSpeed, unsigned int newMass, COLORREF newColor, unsigned int newRadius) :
            Object(newCoords, newSpeed, newMass, newColor),
            radius (newRadius)
        {}


    //}
    //----------------------------------------------------------------------------


    //----------------------------------------------------------------------------
    //{ Functions
    //----------------------------------------------------------------------------

        bool Ball::collision(const Ball& ball) const
        {
            return pow(coords.x() - ball.coords.x(), 2) + pow(coords.y() - ball.coords.y(), 2) < pow(radius + ball.radius, 2);
        }
		
		Ball& Ball::interact(Ball& ball)
		{
				if (!collision(ball)) return *this;

			// Shifting outside:

				Vector moveVector = coords - ball.coords;

				moveVector.normalize();
				moveVector *= (radius + ball.radius);

				coords = ball.coords + moveVector;

			// Creating new speed vectors:

				Vector thisNewSpeed = speed - ball.speed;
				Vector ballNewSpeed = Vector(0, 0);

			// Projecting on moveVector:

				Vector newOX = Vector(1, 0);

				moveVector.normalize();

				thisNewSpeed = Vector(moveVector * thisNewSpeed, Vector(-moveVector.y(), moveVector.x()) * thisNewSpeed);

				newOX = Vector(moveVector * newOX, Vector(-moveVector.y(), moveVector.x()) * newOX);
				Vector newOY = Vector(-newOX.y(), newOX.x());

			// Calculating:

				double thisNewSpeedX = thisNewSpeed.x();

				thisNewSpeed.x() = (mass - ball.mass) * thisNewSpeedX / (mass + ball.mass);
				ballNewSpeed.x() = 2 * mass * thisNewSpeedX / (mass + ball.mass);

			// Projecting back:

				thisNewSpeed = Vector(newOX * thisNewSpeed, newOY * thisNewSpeed);
				ballNewSpeed = Vector(newOX * ballNewSpeed, newOY * ballNewSpeed);

			// Adding lost speed:

				thisNewSpeed += ball.speed;
				ballNewSpeed += ball.speed;

				speed = thisNewSpeed;
				ball.speed = ballNewSpeed;

			// Return:

				return *this;
		}

    //}
    //----------------------------------------------------------------------------

//}
//----------------------------------------------------------------------------


//----------------------------------------------------------------------------
//{ Box
//----------------------------------------------------------------------------

    struct Box : public Object
    {
        Box(Vector newCoords, Vector newSpeed, unsigned int newMass, COLORREF newColor, unsigned int newWidth, unsigned int newHeight);

        unsigned int width;
        unsigned int height;
    };


    //----------------------------------------------------------------------------
    //{ Constructor && destructor
    //----------------------------------------------------------------------------

        Box::Box(Vector newCoords, Vector newSpeed, unsigned int newMass, COLORREF newColor, unsigned int newWidth, unsigned int newHeight) :
            Object(newCoords, newSpeed, newMass, newColor),
            width  (newWidth),
            height (newHeight)
        {}


    //}
    //----------------------------------------------------------------------------

//}
//----------------------------------------------------------------------------
