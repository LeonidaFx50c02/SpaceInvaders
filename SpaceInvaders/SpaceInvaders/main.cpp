#define IMM2D_WIDTH 640
#define IMM2D_HEIGHT 480
#define IMM2D_SCALE 1

#define IMM2D_IMPLEMENTATION
#include "immediate2d.h"
#include <string>
#include <chrono>
#include <thread>

using namespace std;
using namespace std::chrono;

//Image navicella(const char navicella);
void navicelleNemiche(int xR2, int  yR2, int wR2, int hR2);
void difese(int xR3, int  yR3, int wR3, int hR3);

void run() {
    auto start = high_resolution_clock::now();

    bool limite = false;

    int xR, yR, wR, hR;
    wR = 80;  // larghezza navicella
    hR = 40;  // altezza navicella
    xR = 60;  // posizione iniziale x
    yR = IMM2D_HEIGHT - hR - 10;  // posizione iniziale y (in basso)

    //NEMICI
    int xR2 = 0, yR2 = 30, wR2 = 30, hR2 = 20;
    int nemicoDirezione = 4;

    //MOVIMENTO NEMICI (timer)
    auto lastMoveTime = high_resolution_clock::now();

    int xR3, yR3, wR3, hR3;

    //proiettile
    bool direzioneP = false;
    int Width = 10;
    int Height = 40;
    int x = 320;
    int y = IMM2D_HEIGHT - Height;
    bool sparato = false;
    while (true) {
        Clear(Yellow); // Pulisce lo schermo ad ogni ciclo
        DrawRectangle(0, 60, 640, 300, Green, Transparent); // parte nemici
        DrawRectangle(0, 360, 640, 60, Blue, Transparent); // parte difesa
        DrawRectangle(0, 420, 640, 60, Red); // parte navicella

        // Disegna la navetta
        DrawRectangle(xR, yR, wR, hR, Black, Transparent);
        //Image navicella(const char navicella);

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

        //MURA DI DIFESE
        xR3 = 50;
        yR3 = 375;
        wR3 = 100;
        hR3 = 30;
        /*difese(xR3, yR3, wR3, hR3);*/

        //NAVICELLE NEMICHE
        auto now = high_resolution_clock::now();
        auto elapsed = duration_cast<milliseconds>(now - lastMoveTime).count();

        //if (elapsed > 500) {
        //    xR2 += nemicoDirezione;
        //    if (xR2 + (9 * 55 + wR2) > IMM2D_WIDTH || xR2 < 0) {
        //        nemicoDirezione *= -1; // Cambia direzione
        //        yR2 += 30; // Scendi di una riga
        //    }
        //    lastMoveTime = now;
        //}

        navicelleNemiche(xR2, yR2, wR2, hR2);

        //PROIETTILE
        char caratterePremuto2 = LastBufferedKey();
        if (caratterePremuto2 == 'c' && !sparato) {
            sparato = true;
            y = IMM2D_HEIGHT - Height;
        }

        if (sparato) {
            x = xR + (wR / 2) - (Width / 2);
            DrawRectangle(x, y, Width, Height, Black);


            y -= 5;

            if (y <= 0) {
                sparato = false;
            }
            if (y == yR2 && x>= xR2 && x<= xR2+30) {
                sparato = false;
            }
        }
        Wait(10);  // Una pausa di 10 ms
    }
}

void navicelleNemiche(int xR2, int  yR2, int wR2, int hR2) {
    for (int i = 0; i < 4; i++) {
        yR2 += 30;
        for (int i = 0; i < 10; i++) {
            DrawRectangle(xR2, yR2, wR2, hR2, Red);
            xR2 += 55;
        }
        xR2 -= 550;
    }
}

void difese(int xR3, int  yR3, int wR3, int hR3) {
    for (int i = 0; i < 4; i++) {
        DrawRectangle(xR3, yR3, wR3, hR3, Black);
        xR3 += 150;
    }
}