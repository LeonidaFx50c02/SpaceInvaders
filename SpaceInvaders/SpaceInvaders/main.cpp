#define IMM2D_WIDTH 640
#define IMM2D_HEIGHT 480
#define IMM2D_SCALE 1

#define IMM2D_IMPLEMENTATION
#include "immediate2d.h"
#include <string>
using namespace std;

void run() {
    int xR, yR, wR, hR;
    wR = 80;  // larghezza navicella
    hR = 40;  // altezza navicella
    xR = 60;  // posizione iniziale x
    yR = IMM2D_HEIGHT - hR;  // posizione iniziale y (in basso)

    // Disegno delle aree fisse (parte navicella, nemici, difesa)
    Clear(Yellow); // colore di sfondo
    DrawRectangle(0, 60, 640, 300, Green, Transparent); // parte nemici
    DrawRectangle(0, 360, 640, 60, Blue, Transparent); // parte difesa
    DrawRectangle(0, 420, 640, 60, Red); // parte navicella

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

        // Aggiungi una pausa per evitare il sovraccarico della CPU (opzionale, dipende dalla libreria)
        Wait(10);  // Una pausa di 10 ms
    }
}
