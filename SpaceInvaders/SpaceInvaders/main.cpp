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
    
    int xR2 = 0, yR2 = 30, wR2, hR2;

    int xR3, yR3, wR3, hR3;

    //proiettile
    bool direzioneP = false;
    int Width = 10;
    int Height = 40;
    int x = 320;
    int y = IMM2D_HEIGHT - Height;
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
        difese(xR3, yR3, wR3, hR3);

        //NAVICELLE NEMICHE
        wR2 = 30;
        hR2 = 20;
        auto now = high_resolution_clock::now();
        auto elapsed = duration_cast<seconds>(now - start).count();
        if (elapsed % 2 == 0) {
            for (int i = 0; i < 2; i++) {
                if (xR2 > 100) {
                    limite = true;
                }
                if (limite == true) {
                    xR2--;
                }
                if (xR2 < 0) {
                    limite = false;
                }
                if (limite == false) {
                    xR2++;
                }
            }
        }
        navicelleNemiche(xR2, yR2, wR2, hR2);

        //PROIETTILE
        char caratterePremuto2 = LastKey();
        if (caratterePremuto2=='c')
        {
            direzioneP = true;
            DrawRectangle(x, y, Width, Height, Black);
            if (direzioneP)
            {
                y--;
            }
            else if (y == 0) {
                direzioneP = false;
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