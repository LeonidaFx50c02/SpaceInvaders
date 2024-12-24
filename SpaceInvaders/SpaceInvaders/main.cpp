#define IMM2D_WIDTH 640
#define IMM2D_HEIGHT 480
#define IMM2D_SCALE 1

#define IMM2D_IMPLEMENTATION
#include "immediate2d.h"
#include <string>
using namespace std;

void navicelleNemiche(int xR2, int  yR2, int wR2, int hR2);
void difese(int xR3, int  yR3, int wR3, int hR3);

void run() {
    int xR, yR, wR, hR;
    wR = 80;  // larghezza navicella
    hR = 40;  // altezza navicella
    xR = 60;  // posizione iniziale x
    yR = IMM2D_HEIGHT - hR - 10;  // posizione iniziale y (in basso)

    while (true) {
        Clear(Yellow); // Pulisce lo schermo ad ogni ciclo
        DrawRectangle(0, 60, 640, 300, Green, Transparent); // parte nemici
        DrawRectangle(0, 360, 640, 60, Blue, Transparent); // parte difesa
        DrawRectangle(0, 420, 640, 60, Red); // parte navicella

        // Disegna la navetta
        DrawRectangle(xR, yR, wR, hR, Black, Transparent);

        // Controllo del tasto premuto per il movimento della navetta
        char caratterePremuto = LastKey();

        if (caratterePremuto == Left) {
            xR -= 10;
            if (xR < 0) {
                xR = 0;  // Limite sinistro
            }
        }
        else if (caratterePremuto == Right) {
            xR += 10;
            if (xR + wR > 640) {
                xR = 640 - wR;  // Limite destro
            }
        }

        //MURA DI DIFESA
        int xR3, yR3, wR3, hR3;
        xR3 = 50;
        yR3 = 375;
        wR3 = 100;
        hR3 = 30;
        difese(xR3, yR3, wR3, hR3);

        //NAVICELLE NEMICHE
        int xR2, yR2, wR2, hR2;
        xR2 = 10;
        yR2 = 30;
        wR2 = 30;
        hR2 = 20;
        navicelleNemiche(xR2, yR2, wR2, hR2);

        // Aggiungi una pausa per evitare il sovraccarico della CPU (opzionale, dipende dalla libreria)
        Wait(10);  // Una pausa di 10 ms
    }
}

void navicelleNemiche(int xR2, int  yR2, int wR2, int hR2) {
    for (int i = 0; i < 4; i++) {
        xR2 = 10;
        yR2 += 30;
        for (int i = 0; i < 10; i++) {
            xR2 += 55;
            DrawRectangle(xR2, yR2, wR2, hR2, Red);
        }
    }
}

void difese(int xR3, int  yR3, int wR3, int hR3) {
    for (int i = 0; i < 4; i++) {
        DrawRectangle(xR3, yR3, wR3, hR3, Black);
        xR3 += 150;
    }
}
