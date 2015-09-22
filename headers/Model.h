#pragma once

//----------------------------------------------------------------------------
//{ Includes
//----------------------------------------------------------------------------

	#include <forward_list>

//}
//----------------------------------------------------------------------------


//----------------------------------------------------------------------------
//{ Model
//----------------------------------------------------------------------------

    class Model
    {
        public:

            // Constructor && destructor:

                Model(int x, int y, unsigned int width, unsigned int height, unsigned int startBallCount = 0);

                ~Model();

            // Getters:

                std::forward_list<Ball>* getBallArrayPointer();

            // Functions:

				// Adding and deleting balls:

				Model& add(const size_t additionalBalls = 1);

				Model& del(const size_t deletedBalls = 1);

				// Physics:
				Model& accelerate(Vector acceleration);
				Model& accelerateWall(Vector acceleration);
                Model& move();
				Model& slowdown(double slowness);

                Model& wallBounce();

                Model& ballBounce();

        private:

            int x_;
            int y_;

            unsigned int width_;
            unsigned int height_;

			std::forward_list<Ball> ballArray_;

			Box wall_;
	};

	//----------------------------------------------------------------------------
	//{ Constructor && destructor:
	//----------------------------------------------------------------------------

		Model::Model(int x, int y, unsigned int width, unsigned int height, unsigned int startBallCount /*= 0*/) :
			x_(x),
			y_(y),
			width_ (width),
			height_(height),
			ballArray_(std::forward_list<Ball>(startBallCount, Ball({0, 0}, {0, 0}, 0, TX_BLACK, 0))),
			wall_ (Box(Vector(x, y + height/2), Vector(0, 0), 500, TX_GREEN, width, 30))
		{
			for (std::forward_list<Ball>::iterator i = ballArray_.begin(); i != ballArray_.end(); i++)
			{
				*i = Ball(Vector(random(x, width), random(y, height)), Vector(random(-5, 5), random(-5, 5)), 10, TX_GREEN, 6);
			}
		}

		Model::~Model()
		{
			ballArray_.~forward_list();
		}

	//}
	//----------------------------------------------------------------------------


    //----------------------------------------------------------------------------
	//{ Getters:
	//----------------------------------------------------------------------------

        std::forward_list<Ball>* Model::getBallArrayPointer()
        {
            return &ballArray_;
        }

    //}
	//----------------------------------------------------------------------------


	//----------------------------------------------------------------------------
	//{ Functions:
	//----------------------------------------------------------------------------

		// Adding / deleting balls:
		
		Model& Model::add(const size_t additionalBalls /*= 1*/)
		{
			for (size_t i = 0; i < additionalBalls; i++)
			{
				assert(i < additionalBalls);

				ballArray_.push_front(Ball(Vector(random(x_, width_), random(y_, height_)), Vector(random(-5, 5), random(-5, 5)), 10, TX_GREEN, 6));
			}

			return *this;
		}
		
		Model& Model::del(const size_t deletedBalls /*= 1*/)
		{		
			for (size_t i = 0; i < deletedBalls; i++)
			{
				assert(i < deletedBalls);

				ballArray_.erase_after(ballArray_.begin());
			}

			return *this;
		}

		// Physics:

		Model& Model::accelerate(Vector acceleration)
		{
			for (std::forward_list<Ball>::iterator i = ballArray_.begin(); i != ballArray_.end(); i++)
			{
				i->accelerate(acceleration);
			}
		
			return *this;
		}

		Model& Model::accelerateWall(Vector acceleration)
		{
			wall_.speed() += acceleration;

			return *this;
		}

		Model& Model::move()
		{
			wall_.move();

			for (std::forward_list<Ball>::iterator i = ballArray_.begin(); i != ballArray_.end(); i++)
			{
				i->move();
			}

			return *this;
		}

		Model& Model::slowdown(double slowness)
		{
			assert(0 <= slowness && slowness <= 1);

			for (std::forward_list<Ball>::iterator i = ballArray_.begin(); i != ballArray_.end(); i++)
			{
				i->slowdown(slowness);
			}

			return *this;
		}

		Model& Model::wallBounce()
		{
			if (wall_.coords.x() - wall_.width < x_)
			{
				wall_.coords.x() = x_ + wall_.width;
				wall_.speed.x() *= -1;
			}

			if (wall_.coords.x() + wall_.width > x_ + width_)
			{
				wall_.coords.x() = x_ - wall_.width + width_;
				wall_.speed.x() *= -1;
			}

			if (wall_.coords.y() - wall_.height < y_)
			{
				wall_.coords.y() = y_ + wall_.height;
				wall_.speed.y() *= -1;
			}

			if (wall_.coords.y() + wall_.height > y_ + height_)
			{
				wall_.coords.y() = y_ - wall_.height + height_;
				wall_.speed.y() *= -1;
			}

			for (std::forward_list<Ball>::iterator i = ballArray_.begin(); i != ballArray_.end(); i++)
			{
				if (i->coords.x() - i->radius < x_)
				{
					i->coords.x() = x_ + i->radius;
					i->speed.x() *= -1;
				}

				if (i->coords.x() + i->radius > x_ + width_)
				{
					i->coords.x() = x_ - i->radius + width_;
					i->speed.x() *= -1;
				}

				if (i->coords.y() - i->radius < y_)
				{
					i->coords.y() = y_ + i->radius;
					i->speed.y() *= -1;
				}

				if (i->coords.y() + i->radius > y_ + height_)
				{
					i->coords.y() = y_ - i->radius + height_;
					i->speed.y() *= -1;
				}
			}

			return *this;
		}

		Model& Model::ballBounce()
		{
			for (std::forward_list<Ball>::iterator i = ballArray_.begin(); i != ballArray_.end(); i++)
			{
				for (std::forward_list<Ball>::iterator j = i; j != ballArray_.end(); j++)
				{
					if (j == i)
					{
						j++;
						if (j == ballArray_.end()) break;
					}

					j->interact(*i);
				}
			}

            return *this;
		}

	//}
	//----------------------------------------------------------------------------

//}
//----------------------------------------------------------------------------
