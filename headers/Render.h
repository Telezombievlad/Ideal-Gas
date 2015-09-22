#pragma once

//----------------------------------------------------------------------------
//{ Additional functions
//----------------------------------------------------------------------------

    // LERPs

    inline double lerp(const double a, const double b, const double k)
    {
        assert(0 <= k && k <= 1.0);

        return a + k * (b - a);
    }

    inline COLORREF lerp(const COLORREF a, const COLORREF b, const double k)
    {
        //printf("%f\n", k);

        assert(0 <= k && k <= 1.0);

        return RGB(static_cast<char>(lerp(static_cast<double>(GetRValue(a)), static_cast<double>(GetRValue(b)), k)),
                   static_cast<char>(lerp(static_cast<double>(GetGValue(a)), static_cast<double>(GetGValue(b)), k)),
                   static_cast<char>(lerp(static_cast<double>(GetBValue(a)), static_cast<double>(GetBValue(b)), k)));
    }

    COLORREF multiColorLerp(const COLORREF* colorMap, size_t colorMapSize, const double lerpCoefficient)
    {
        assert(0 <= lerpCoefficient && lerpCoefficient <= 1);

        assert(2 <= colorMapSize);

        if (lerpCoefficient == 1.0) return colorMap[colorMapSize - 1];
        else
        {
            unsigned int colorAIndex = static_cast<unsigned int>(lerpCoefficient * (static_cast<double>(colorMapSize) - 1));

            assert(colorAIndex < colorMapSize - 1);

            return lerp(colorMap[colorAIndex], colorMap[colorAIndex + 1], lerpCoefficient * (colorMapSize - 1) - colorAIndex);
        }
    }

//}
//----------------------------------------------------------------------------


//----------------------------------------------------------------------------
//{ Renderer
//----------------------------------------------------------------------------

    class Renderer
    {
        public:

            // Constructor && destructor:

                Renderer(unsigned int windowWidth, unsigned int windowHeight, COLORREF backgroundColor);

            // Functions:

                // Debugging:

                    bool ok() const;

                // Rendering:

                     void  startRendering() const;
                     void finishRendering() const;

                    void clear() const;

                    void render(const Ball& ball,
                                const COLORREF* colorMap,
                                const size_t    colorMapSize,
                                double minSpeedModule,
                                double maxSpeedModule) const;

                    void render(const  Box&  box) const;

        private:

            unsigned int windowWidth_;
            unsigned int windowHeight_;

            COLORREF backgroundColor_;

    };


    //----------------------------------------------------------------------------
    //{ Constructor && destructor
    //----------------------------------------------------------------------------

        Renderer::Renderer(unsigned int windowWidth, unsigned int windowHeight, COLORREF backgroundColor) :
            windowWidth_     (windowWidth),
            windowHeight_    (windowHeight),
            backgroundColor_ (backgroundColor)
        {
            txCreateWindow(windowWidth, windowHeight);
            txTextCursor(false);

            assert(ok());
        }

    //}
    //----------------------------------------------------------------------------


    //----------------------------------------------------------------------------
    //{ Functions
    //----------------------------------------------------------------------------

        //----------------------------------------------------------------------------
        //{ Debugging
        //----------------------------------------------------------------------------

            bool Renderer::ok() const
            {
                return true;
            }

        //}
        //----------------------------------------------------------------------------


        //----------------------------------------------------------------------------
        //{ Rendering
        //----------------------------------------------------------------------------

            void Renderer::startRendering() const
            {
                txBegin();
            }

            void Renderer::finishRendering() const
            {
                txEnd();
            }

            void Renderer::clear() const
            {
                assert(ok());

                txSetFillColor(backgroundColor_);
                txClear();
            }

            void Renderer::render(const Ball& ball, const COLORREF* colorMap, const size_t colorMapSize, double minSpeedModule, double maxSpeedModule) const
            {
                assert(ok());

                double minSpeedModuleSquare = pow(minSpeedModule, 2);
                double maxSpeedModuleSquare = pow(maxSpeedModule, 2);

                double speedModuleSquare = pow(ball.speed.x(), 2) + pow(ball.speed.y(), 2);

                if (speedModuleSquare < minSpeedModuleSquare) speedModuleSquare = minSpeedModuleSquare;
                if (speedModuleSquare > maxSpeedModuleSquare) speedModuleSquare = maxSpeedModuleSquare;

                txSetFillColor(multiColorLerp(colorMap, colorMapSize, (speedModuleSquare - minSpeedModuleSquare) / (maxSpeedModuleSquare - minSpeedModuleSquare)));

                txSetColor(TX_BLACK);

                txCircle(ball.coords.x(), ball.coords.y(), ball.radius);
            }

            void Renderer::render(const Box& box) const
            {
                assert(ok());

                txSetColor(TX_BLACK);
                txSetFillColor(box.color);

                txRectangle(box.coords.x(),
                            box.coords.y(),
                            box.coords.x() + box.width,
                            box.coords.y() + box.height);

				txLine(box.coords.x(),
					   box.coords.y(),
					   box.coords.x() + box.width,
					   box.coords.y() + box.height);

				txLine(box.coords.x() + box.width,
					   box.coords.y(),
					   box.coords.x(),
					   box.coords.y() + box.height);
            }

        //}
        //----------------------------------------------------------------------------

    //}
    //----------------------------------------------------------------------------

//}
//----------------------------------------------------------------------------
