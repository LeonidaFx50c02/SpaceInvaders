//prova MIA
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

Image navicella = LoadImage("navicella.png");

//Image navicella(const char navicella);
void navicelleNemiche(int xR2, int  yR2, int wR2, int hR2, int nemici[4][10]);
void difese(int xR3, int  yR3, int wR3, int hR3, int difesa[]);
void menu();
void left();

void run() {
    menu();
    auto start = high_resolution_clock::now();

    bool limite = false;

    int xR, yR, wR, hR;
    wR = 80;  // larghezza navicella
    hR = 40;  // altezza navicella
    xR = 60;  // posizione iniziale x
    yR = IMM2D_HEIGHT - hR - 10;  // posizione iniziale y (in basso)


    //MOVIMENTO NEMICI (timer)
    auto lastMoveTime = high_resolution_clock::now();

    int xR3, yR3, wR3, hR3;

    //proiettile
    bool direzioneP = false;
    int Width = 10;
    int Height = 40;
    int xRp = xR;
    int yRp = IMM2D_HEIGHT - Height;
    bool sparato = false;

    //NEMICI

    int xR2 = 0, yR2 = 60, wR2 = 30, hR2 = 20;
    int nemicoDirezione = 4;
    //navicelle nemici
    int s = 55;
    int nemici[4][10] = {
        {xR2, xR2 + s * 1, xR2 + s * 2, xR2 + s * 3, xR2 + s * 4, xR2 + s * 5, xR2 + s * 6,xR2 + s * 7,xR2 + s * 8,xR2 + s * 9},
        {xR2, xR2 + s * 1, xR2 + s * 2, xR2 + s * 3, xR2 + s * 4, xR2 + s * 5, xR2 + s * 6,xR2 + s * 7,xR2 + s * 8,xR2 + s * 9},
        {xR2, xR2 + s * 1, xR2 + s * 2, xR2 + s * 3, xR2 + s * 4, xR2 + s * 5, xR2 + s * 6,xR2 + s * 7,xR2 + s * 8,xR2 + s * 9},
        {xR2, xR2 + s * 1, xR2 + s * 2, xR2 + s * 3, xR2 + s * 4, xR2 + s * 5, xR2 + s * 6,xR2 + s * 7,xR2 + s * 8,xR2 + s * 9},

    };
    //MURA DI DIFESE
    xR3 = 50;
    yR3 = 375;
    wR3 = 100;
    hR3 = 30;

    //difesa
    int d = 150;
    int difesa[4] = { xR3, xR3 + d * 1, xR3 + d * 2 , xR3 + d * 3 };


    while (true) {
        char key = LastBufferedKey();
        if (key == Esc) {
            left();
        }
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

        //mura di difesa
        difese(xR3, yR3, wR3, hR3, difesa);

        //NAVICELLE NEMICHE
        auto now = high_resolution_clock::now();
        auto elapsed = duration_cast<milliseconds>(now - lastMoveTime).count();

        if (elapsed > 500) {
            for (int i = 0; i < 4; i++) {
                for (int j = 0; j < 10; j++) {
                    if (nemici[i][j] != -1000) {
                        nemici[i][j] += nemicoDirezione;
                        if (nemici[0][10] + (9 * 55 + wR2) > IMM2D_WIDTH || nemici[i][j] < 0) {
                            nemicoDirezione *= -1; // Cambia direzione
                            yR2 += 30; // Scendi di una riga
                        }
                    }
                }
            }
            lastMoveTime = now;
        }



        //navicelle nemiche

        navicelleNemiche(xR2, yR2, wR2, hR2, nemici);

        //PROIETTILE

        if (key == 'c' && !sparato) {
            sparato = true;
            yRp = IMM2D_HEIGHT - Height;
            xRp = xR + (wR / 2);
        }

        if (sparato) {
            DrawRectangle(xRp, yRp, Width, Height, Black);
            yRp -= 2;

            if (yRp <= 0) {
                sparato = false;
            }

            //vedo se colpisce nemici
            for (int i = 0; i < 4; i++) {
                for (int j = 0; j < 10; j++) {
                    if (xRp >= nemici[i][j] && xRp <= nemici[i][j] + wR2 && yRp >= nemici[i][j] && yRp <= nemici[i][j] + hR2) {
                        sparato = false;
                        nemici[i][j] = -1000;  //tolgo nemico
                    }
                }
            }

            //vedo se colpisce difesa
            for (int i = 0; i < 4; i++) {
                if (xRp >= difesa[i] && xRp <= difesa[i] + wR3 && yRp <= yR3 + hR3) {
                    sparato = false;
                    difesa[i] = -10000;  //tolgo difesa
                }
            }
        }
        Wait(10);  // Una pausa di 10 ms
    }
}



void navicelleNemiche(int xR2, int yR2, int wR2, int hR2, int nemici[4][10]) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 10; j++) {
            // Se il nemico è attivo (non -1000)
            if (nemici[i][j] != -1000) {
                // Disegna il nemico in base alla posizione
                DrawRectangle(nemici[i][j], yR2, wR2, hR2, Red);
            }
        }
        // Sposta la yR2 di 30 per disegnare la riga successiva di nemici
        yR2 += 30;
    }


}

void difese(int xR3, int  yR3, int wR3, int hR3, int difesa[]) {
    for (int i = 0; i < 4; i++) {
        if (difesa[i] != -10000) {

            DrawRectangle(difesa[i], yR3, wR3, hR3, Black);
        }
    }
}

void menu() {
    Image Home = LoadImage("Assets/HomeSpace.png");
    DrawImage(IMM2D_WIDTH / 52, IMM2D_HEIGHT / 52, Home);
    while (true) {
        char key = LastKey();
        if (key == Enter) {
            break;
        }
    }

}

void left() {
    Image leftImg = LoadImage("Assets/left.png");
    DrawImage(IMM2D_WIDTH / 12, IMM2D_HEIGHT / 12, leftImg);
    while (true) {
        char key = LastKey();
        if (key == 'y') {
            CloseWindow();
        }
        else if (key == 'n') {
            break;
        }
    }
}