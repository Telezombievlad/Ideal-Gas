#pragma once

//----------------------------------------------------------------------------
//{ Fun:
//----------------------------------------------------------------------------

	#define EVER (;,,;)

//}
//----------------------------------------------------------------------------


//----------------------------------------------------------------------------
//{ Console colors(TXLib only):
//----------------------------------------------------------------------------

	#ifdef __TXLIB_H_INCLUDED
		#define BLU txSetConsoleAttr(0xB);
		#define GRN txSetConsoleAttr(0xA);
		#define RED txSetConsoleAttr(0xC);
		#define YEL txSetConsoleAttr(0xE);
		#define WHT txSetConsoleAttr(0xF);
	#endif /*__TXLIB_H_INCLUDED*/

//}
//----------------------------------------------------------------------------


//----------------------------------------------------------------------------
//{ Different sleeps/waits:
//----------------------------------------------------------------------------

	#define WAIT waitUntilSpaceButtonIsPressed();
	#define DOTS waitUntilSpaceButtonIsPressedWhileMakingThreeDots();

//}
//----------------------------------------------------------------------------


//----------------------------------------------------------------------------
//{ Counter stuff:
//----------------------------------------------------------------------------

	#define COUNTER_STR(counter) ((counter) = GetTickCount());
	#define COUNTER_FIN(counter) ((counter) = (GetTickCount() - (counter)));

//}
//----------------------------------------------------------------------------


//----------------------------------------------------------------------------
//{ Making variable unused(recently absorbed info):
//----------------------------------------------------------------------------

	#define UNUSED_VARIABLE(variable) static_cast<void>(variable);

//}
//----------------------------------------------------------------------------


//----------------------------------------------------------------------------
//{ Additional function, used in those defines:
//----------------------------------------------------------------------------

	void waitUntilSpaceButtonIsPressed()
	{
		bool spaceButtonPressed = (GetAsyncKeyState(VK_SPACE)) ? true : false;
		bool ready = !spaceButtonPressed;

		while (true)
		{
			if (!GetAsyncKeyState(VK_SPACE) && spaceButtonPressed) ready = true;

			if (ready && GetAsyncKeyState(VK_SPACE)) break;
		}
	}

	void waitUntilSpaceButtonIsPressedWhileMakingThreeDots()
	{
		bool spaceButtonPressed = (GetAsyncKeyState(VK_SPACE)) ? true : false;
		bool ready = !spaceButtonPressed;

		txSleep(500);

		unsigned int currentDot = 0;
		for (; !(ready && GetAsyncKeyState(VK_SPACE)); currentDot++)
		{
			if (!GetAsyncKeyState(VK_SPACE) && spaceButtonPressed) ready = true;

			if (currentDot == 3)
			{
				printf("\b\b\b");
				printf("   ");
				printf("\b\b\b");

				currentDot = 0;
			}

			if (currentDot != 3) printf(".");

			txSleep(600);
		}

		for (; currentDot > 0; currentDot--) printf("\b");
	}

//}
//----------------------------------------------------------------------------
