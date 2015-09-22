//----------------------------------------------------------------------------
//{ Includes
//----------------------------------------------------------------------------

	#include <vector>

    #include "headers\TXLib.h"

	#include "headers\DEFINES.h"
	
	#include "headers\Objects.h"
    #include "headers\Model.h"
    #include "headers\Render.h"
    #include "headers\Controller.h"

bool Matrix::check = true;
bool Vector::check = true;

//}
//----------------------------------------------------------------------------


//----------------------------------------------------------------------------
//{ Main
//----------------------------------------------------------------------------

    int main()
    {
        Renderer renderer = Renderer(1000, 800, TX_BLACK);

        Model model = Model(0, 0, 1000, 800, 10);

        controlEverything(&model, &renderer);

        return 0;
    }

//}
//----------------------------------------------------------------------------


