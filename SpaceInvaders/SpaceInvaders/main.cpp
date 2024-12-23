#define IMM2D_WIDTH 640
#define IMM2D_HEIGHT 480
#define IMM2D_SCALE 1

#define IMM2D_IMPLEMENTATION 
#include "immediate2d.h"
#include <string>
using namespace std;



void run() {

	int xR, yR, wR, hR;
	wR = 80;
	hR = 40;
	xR = 60;
	yR = IMM2D_HEIGHT - hR;
	Clear(Yellow);//parte navicella punti bonus
	DrawRectangle(0, 60, 640, 300, Green, Transparent);//parte nemici
	DrawRectangle(0, 360, 640, 60, Blue, Transparent);//parte difesa
	DrawRectangle(0, 420, 640, 60, Red);//parte mia navicella
	while (true) {
		DrawRectangle(xR, yR, wR, hR, Black, Transparent);//parte mia navicella
		char caratterePremuto = LastKey();
		if (caratterePremuto == Left)
		{
			xR -= 10;

		}
		else if (caratterePremuto == Right)
		{
			xR += 10;	
		}

	}
	Wait(2);
}


