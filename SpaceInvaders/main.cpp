#define IMM2D_WIDTH 640
#define IMM2D_HEIGHT 480
#define IMM2D_SCALE 1

#define IMM2D_IMPLEMENTATION
#include "immediate2d.h"
#include <string>
#include <chrono>
#include <thread>
#include <cstdlib>
#include <ctime> 

using namespace std;
using namespace std::chrono;

Image navicella = LoadImage("Assets/navicella.png");
using Image = int;
static constexpr const char NavicellaPng[] = "Assets/navicella.png";
static constexpr const char proiettileMioPng[] = "Assets/proiettileMio.png";
static constexpr const char proiettileNemicoPng[] = "Assets/proiettileNemico.png";
static constexpr const char NemicoPng[] = "Assets/Nemico.png";
static constexpr const char SfondoPng[] = "Assets/sfondo.png";
//Image navicella(const char navicella);
void navicelleNemiche(int xR2, int  yR2, int wR2, int hR2, int nemici[4][10], Image Nemico);
void difese(int xR3, int  yR3, int wR3, int hR3[], int difesa[]);
void menu();
void left();
bool replay();
void reset(bool colpo[], int& contaColpi, int& contatore, int contDifesa[], int& d, int& xR3, int& yR3, int& wR3, int hR3[], int difesa[], int& xR2, int& yR2, int& wR2, int& hR2, int nemici[4][10], Image Nemico, int& nemicoDirezione, int& s);
void run() {
    srand(time(NULL));
    menu();
    //sfondo
    const Image Sfondo = LoadImage(SfondoPng);
    //livelli
    int livello = 1;

    //contatore
    string contatoreStr = "";
    string frase = "PUNTEGGIO: ";
    int  contatore = 0;

    auto start = high_resolution_clock::now();
    //proiettili nemici
    auto start2 = high_resolution_clock::now();

    bool limite = false;
    //navicella
    int xR, yR, wR, hR;
    const Image navicella = LoadImage(NavicellaPng);
    wR = ImageWidth(navicella);  // larghezza navicella
    hR = ImageHeight(navicella);  // altezza navicella
    xR = 60;  // posizione iniziale x
    yR = IMM2D_HEIGHT - hR - 10;  // posizione iniziale y (in basso)

    //proiettili nemici
    bool direzionePN = false;
    int xRPN = 0;
    int yRPN = 200;
    bool sparatoN = false;
    auto lastMoveTime2 = high_resolution_clock::now();

    //MOVIMENTO NEMICI (timer)
    auto lastMoveTime = high_resolution_clock::now();

    int xR3, yR3, wR3;

    //proiettile
    bool direzioneP = false;
    const Image proiettileMio = LoadImage(proiettileMioPng);
    const Image proiettileNemico = LoadImage(proiettileNemicoPng);
    int Width = ImageWidth(proiettileMio);
    int Height = ImageHeight(proiettileMio);;
    int xRp = xR;
    int yRp = IMM2D_HEIGHT - Height;
    bool sparato = false;
    bool colpo[5];
    int colpoX[5];
    int colpoY[5];
    int contaColpi = 0;
    for (int i = 0; i < 5; i++)
    {
        colpo[i] = false;
        colpoX[i] = xRp;
        colpoY[i] = yRp;
    }



    //NEMICI
    int contElapsed = 500;
    const Image Nemico = LoadImage(NemicoPng);
    int xR2 = 0, yR2 = 60, wR2 = ImageWidth(Nemico), hR2 = ImageHeight(Nemico);
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
    yR3 = 365;
    wR3 = 100;
    int  hR3[4] = { 40, 40, 40, 40 };

    //difesa
    int d = 150;
    int difesa[4] = { xR3, xR3 + d * 1, xR3 + d * 2 , xR3 + d * 3 };
    int contDifesa[4] = { 4,4,4,4 };

    while (true) {
        //incremento livello
        if (contatore == 400)
        {
            reset(colpo, contaColpi, contatore, contDifesa, d, xR3, yR3, wR3, hR3, difesa, xR2, yR2, wR2, hR2, nemici, Nemico, nemicoDirezione, s);
            livello++;
            contElapsed--;
        }


        char key = LastBufferedKey();
        if (key == Esc) {
            left();
        }
        Clear(Black);// Pulisce lo schermo ad ogni ciclo
        //disegno sfondo
        DrawImage(0, 0, Sfondo);
        //DrawRectangle(0, 60, 640, 300, Green, Transparent); // parte nemici
        //DrawRectangle(0, 360, 640, 60, Blue, Transparent); // parte difesa
        //DrawRectangle(0, 420, 640, 60, Red); // parte navicella

        // Disegna la navetta
        /*DrawRectangle(xR, yR, wR, hR, Red, Transparent);*/
        DrawImage(xR, yR, navicella);

        // Controllo del tasto premuto per il movimento della navetta
        char caratterePremuto = LastKey();
        // contatore punteggio
        contatoreStr = frase + to_string(contatore);
        DrawString(110, 15, contatoreStr.c_str(), "Arial", 20, Red, true);


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


        //verifico il livello

        //spostamento nemici
        if (elapsed > contElapsed) {
            for (int i = 0; i < 4; i++) {
                for (int j = 0; j < 10; j++) {
                    if (nemici[i][j] != -1000) {
                        nemici[i][j] += nemicoDirezione;
                        if (nemici[i][j] + wR2 > IMM2D_WIDTH || nemici[i][j] < 0) {
                            nemicoDirezione *= -1; // Cambia direzione
                            yR2 += 30; // Scendi di una riga
                            if ((yR2 + ((20 * 4) + (30 * 3))) >= 360)
                            {
                                Clear(Black);
                                Image overImg = LoadImage("Assets/gameover.png");
                                DrawImage(IMM2D_WIDTH / 12, IMM2D_HEIGHT / 12, overImg);
                                Wait(5000);
                                Clear(Black);
                                bool v = replay();
                                if (v == true)
                                {
                                    reset(colpo, contaColpi, contatore, contDifesa, d, xR3, yR3, wR3, hR3, difesa, xR2, yR2, wR2, hR2, nemici, Nemico, nemicoDirezione, s);
                                    livello = 1;
                                    contElapsed = 500;
                                }

                            }
                        }
                    }
                }
            }
            lastMoveTime = now;
        }



        //navicelle nemiche

        navicelleNemiche(xR2, yR2, wR2, hR2, nemici, Nemico);

        //PROIETTILE

        //if (key == 32 && !sparato) {
        //    sparato = true;
        //    yRp = IMM2D_HEIGHT - Height-30;
        //    xRp = xR+10 /*+ (wR / 2)*/;
        //}
        bool verificoColpi = false;
        for (int i = 0; i < contaColpi; i++)
        {
            if (colpo[i])
            {
                verificoColpi = false;
                break;
            }
            else {
                verificoColpi = true;
            }
        }
        if (verificoColpi)
        {
            contaColpi = 0;
        }
        if (key == 32 && contaColpi < 5) {
            colpo[contaColpi] = true;
            colpoY[contaColpi] = IMM2D_HEIGHT - Height - 30;
            colpoX[contaColpi] = xR + 10;
            contaColpi++;
        }
        for (int i = 0; i < contaColpi; i++)
        {
            if (colpo[i]) {
                colpoY[i] -= 4;

                if (colpoY[i] <= 0) {
                    colpo[i] = false;
                }
                DrawImage(colpoX[i], colpoY[i], proiettileMio);
            }
        }
        for (int i = 0; i < contaColpi; i++)
        {
            if (colpo[i]) {

                for (int j = 0; j < 4; j++) {
                    for (int k = 0; k < 10; k++) {
                        if (nemici[j][k] != -1000) {
                            int parteX = nemici[j][k];
                            int parteY = yR2 + j * 50;
                            if (colpoX[i] >= parteX && colpoX[i] <= parteX + wR2 && colpoY[i] >= parteY && colpoY[i] <= parteY + hR2) {

                                nemici[j][k] = -1000;
                                colpo[i] = false;
                                contatore += 10;
                                break;
                            }
                        }
                    }
                }
            }
        }

        //if (sparato) {
        //    if (yRp <= 0) {
        //        sparato = false;
        //    }

        //    //vedo se colpisce nemici
        //    /*for (int i = 0; i < 4; i++) {
        //        for (int j = 0; j < 10; j++) {
        //            if (xRp >= nemici[i][j] && xRp <= nemici[i][j] + wR2 && yRp >= nemici[i][j] && yRp <= nemici[i][j] + hR2) {
        //                sparato = false;
        //                nemici[i][j] = -1000;  //tolgo nemico
        //            }
        //        }
        //    }*/
        //    for (int i = 0; i < 4; i++) {
        //        for (int j = 0; j < 10; j++) {
        //            if (nemici[i][j] != -1000) {
        //                int parteX = nemici[i][j];
        //                int parteY = yR2 + i * 50;
        //                if (xRp >= parteX && xRp <= parteX + wR2 && yRp >= parteY && yRp <= parteY + hR2) {
        //                    sparato = false;
        //                    nemici[i][j] = -1000;
        //                    contatore += 10;
        //                    break;
        //                }
        //            }
        //        }
        //    }
        //    DrawImage(xRp, yRp,proiettileMio);
        //    yRp -= 4;

        //    //vedo se colpisce difesa
        //    for (int i = 0; i < 4; i++) {
        //        if (xRp + Width > difesa[i] && xRp < difesa[i] + wR3 && yRp - Height > yR3 && yRp-Height < yR3 + hR3[i]) {
        //            sparato = false;
        //            contDifesa[i]--;
        //            hR3[i] -= 10;
        //            if (contDifesa[i] == 0) {
        //                difesa[i] = -10000;  //tolgo difesa;
        //            }
        //        }
        //    }
        //}

        for (int i = 0; i < 5; i++)
        {
            if (colpo[i]) {
                for (int j = 0; j < 4; j++)
                {
                    if (colpoX[i] + Width > difesa[j] && colpoX[i] < difesa[j] + wR3 && colpoY[i] - Height > yR3 && colpoY[i] - Height < yR3 + hR3[j]) {
                        colpo[i] = false;
                        contDifesa[j]--;
                        hR3[j] -= 10;
                        if (contDifesa[j] == 0) {
                            difesa[j] = -10000;  //tolgo difesa;
                        }
                    }
                }
            }
        }

        //proiettili nemici
        auto now2 = high_resolution_clock::now();
        auto elapsed2 = duration_cast<milliseconds>(now2 - lastMoveTime2).count();

        if (elapsed2 > 4500) {
            sparatoN = true;
            lastMoveTime2 = now;
            int riga = rand() % 4;
            int colonna = rand() % 10;
            bool isTrovato = false;
            if (nemici[riga][colonna] != -1000) {
                xRPN = nemici[riga][colonna] + (wR2 / 2);
                yRPN = yR2 + riga * 30 + hR2;
            }
        }
        if (sparatoN) {
            DrawImage(xRPN, yRPN, proiettileNemico);
            yRPN += 4;
            if (yRPN >= IMM2D_HEIGHT) {
                sparatoN = false;
            }

            //vedo se colpisce difesa
            for (int i = 0; i < 4; i++) {
                if (xRPN >= difesa[i] && xRPN <= difesa[i] + wR3 && yRPN + Height >= yR3 && yRPN + Height <= yR3 + hR3[i]) {
                    sparatoN = false;
                    contDifesa[i]--;
                    hR3[i] -= 10;
                    if (contDifesa[i] == 0) {
                        difesa[i] = -10000;  //tolgo difesa;
                    }
                }
            }

            //vedo se colpisce la mia navicella
            if (xRPN >= xR && xRPN <= xR + wR && yRPN + Height >= yR && yRPN + Height <= yR + hR) {
                sparatoN = false;
                Clear(Black);
                Image overImg = LoadImage("Assets/gameover.png");
                DrawImage(IMM2D_WIDTH / 12, IMM2D_HEIGHT / 12, overImg);
                Wait(5000);
                Clear(Black);
                bool v = replay();
                if (v == true)
                {
                    reset(colpo, contaColpi, contatore, contDifesa, d, xR3, yR3, wR3, hR3, difesa, xR2, yR2, wR2, hR2, nemici, Nemico, nemicoDirezione, s);
                    livello = 1;
                    contElapsed = 500;
                }
            }
        }
        Wait(32);  // Una pausa di 10 ms
    }
}



void navicelleNemiche(int xR2, int yR2, int wR2, int hR2, int nemici[4][10], Image Nemico) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 10; j++) {
            if (nemici[i][j] != -1000) {
                DrawImage(nemici[i][j], yR2, Nemico);
            }
        }
        yR2 += 50;
    }


}

void difese(int xR3, int  yR3, int wR3, int hR3[], int difesa[]) {
    for (int i = 0; i < 4; i++) {
        if (difesa[i] != -10000) {
            DrawRectangle(difesa[i], yR3, wR3, hR3[i], Green);
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

bool replay()
{
    bool y = false;
    Image replayImg = LoadImage("Assets/replay.png");
    DrawImage(IMM2D_WIDTH / 12, IMM2D_HEIGHT / 12, replayImg);
    while (true) {
        char key = LastKey();
        if (key == 'y') {
            y = true;
            break;

        }
        else if (key == 'n') {
            CloseWindow();
        }
    }
    return y;
}

void reset(bool colpo[], int& contaColpi, int& contatore, int contDifesa[], int& d, int& xR3, int& yR3, int& wR3, int hR3[], int difesa[], int& xR2, int& yR2, int& wR2, int& hR2, int nemici[4][10], Image Nemico, int& nemicoDirezione, int& s)
{
    //proiettili
    contaColpi = 0;
    for (int i = 0; i < 5; i++)
    {
        colpo[i] = false;
    }
    //punteggio
    contatore = 0;
    //NEMICI
    xR2 = 0, yR2 = 60, wR2 = ImageWidth(Nemico), hR2 = ImageHeight(Nemico);
    nemicoDirezione = 4;
    //navicelle nemici
    s = 55;
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            nemici[i][j] = xR2 + (55 * j);
        }
    }
    //MURA DI DIFESE
    xR3 = 50;
    yR3 = 365;
    wR3 = 100;
    for (int i = 0; i < 4; i++)
    {
        hR3[i] = 40;
    }

    //difesa
    d = 150;
    difesa[0] = xR3;
    difesa[1] = xR3 + d * 1;
    difesa[2] = xR3 + d * 2;
    difesa[3] = xR3 + d * 3;
    for (int i = 0; i < 4; i++)
    {
        contDifesa[i] = 40;
    }

}
