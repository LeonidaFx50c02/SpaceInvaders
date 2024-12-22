#define IMM2D_WIDTH 640
#define IMM2D_HEIGHT 480
#define IMM2D_SCALE 1

#define IMM2D_IMPLEMENTATION 
#include "immediate2d.h"
#include <string>
using namespace std;



void run() {

	int x = 0;

	Clear(Yellow);//parte navicella punti bonus
	DrawRectangle(0, 60, 640, 300, Green, Transparent);//parte nemici
	DrawRectangle(0, 360, 640, 60, Blue, Transparent);//parte difesa
	DrawRectangle(0, 420, 640, 60, Red, Transparent);//parte mia navicella
	while (true) {
		DrawRectangle(x, 450, 50, 30, Black, Transparent);//parte mia navicella
		char caratterePremuto = LastKey();
		if (caratterePremuto == Left)
		{
			x -= 10;
		}
		else if (caratterePremuto == Right)
		{
			x += 10;
		}

	}

}


