#include <iostream>
#include <string>
using namespace std;

enum class Route {
    ERR,
    LEWO_GORA,
    GORA,
    LEWO,
    PRAWO,
    DOL,
    PRAWO_DOL
};

struct Checkpoint {
    int x;
    int y;
    Route route;
    Checkpoint* next;

    Checkpoint(int x, int y, Route route) : x(x), y(y), route(route), next(nullptr) {}
};

class Stos {
private:
    Checkpoint* top;

public:
    Stos() : top(nullptr) {}

    ~Stos() {
        while (!isEmpty()) {
            pop();
        }
    }

    bool isEmpty() const {
        return top == nullptr;
    }

    void push(int x, int y, Route route = Route::ERR) {
        Checkpoint* newCheckpoint = new Checkpoint(x, y, route);
        newCheckpoint->next = top;
        top = newCheckpoint;
    }

    void pop() {
        if (isEmpty()) {
            cout << "Stos jest pusty!\n";
            return;
        }
        Checkpoint* temp = top;
        top = top->next;
        delete[] temp;
    }

    int getX() const {
        return top->x;
    }

    int getY() const {
        return top->y;
    }

    bool odwiedzone(int xInput, int yInput) const {
        Checkpoint* current = top;
        while (current != nullptr) {
            if (current->x == xInput && current->y == yInput) {
                return true;
            }
            current = current->next;
        }
        return false;
    }
};

int functionID(const string& input) {
    if (input == "BOARD_SIZE")
        return 1;
    else if (input == "PAWNS_NUMBER")
        return 2;
    else if (input == "IS_BOARD_CORRECT")
        return 3;
    else if (input == "IS_GAME_OVER")
        return 4;
    else if (input == "IS_BOARD_POSSIBLE")
        return 5;
    else
        return 0;
}

int boardSize(const string& plansza) {
    int licznik = 0;
    int size = plansza.size();
    for (int i = 0; i < size - 1; i++) {
        if (plansza[i] == '<')
            licznik++;
    }
    return sqrt(licznik);
}

int pawnsNumber(const string& plansza, char m) {
    int counter = 0;
    int size = plansza.size();
    for (int i = 0; i < size; i++) {
        if (m == 'a') {
            if (plansza[i] == 'r' || plansza[i] == 'b')
                counter++;
        }
        else if (plansza[i] == m)
            counter++;
    }
    return counter;
}

void copyArray(char**& tablica, char** tablicaStartowa, int size) {
    tablica = new char* [size];
    for (int i = 0; i < size; ++i) {
        tablica[i] = new char[size];
        for (int j = 0; j < size; ++j) {
            tablica[i][j] = tablicaStartowa[i][j];
        }
    }
}

bool isBoardCorrect(const string& plansza) {
    int r = pawnsNumber(plansza, 'r');
    int b = pawnsNumber(plansza, 'b');
    return (r == b + 1 || r == b);
}

void konwersjaNaTablice(string plansza, char**& tablica) {
    int size = boardSize(plansza);
    string temp = "";
    int tempSize = temp.size();
    while (tempSize != size * size) { // until there are as many elements as fields
        string wers = "";
        int planszaSize = plansza.size();
        int wersSize = wers.size();
        for (int i = 0; i < planszaSize && wersSize != size; i++) {
            if (plansza[i] == '<') {
                if (plansza[i + 2] == ' ')
                    wers += '#';
                else
                    wers += plansza[i + 2];
                plansza[i + 2] = '.';
                plansza[i] = '>';
                while (plansza[i] != '\n')
                    i++;
            }
            planszaSize = plansza.size();
            wersSize = wers.size();
        }
        temp += wers;
        tempSize = temp.size();
    }
    tablica = new char* [size];
    int k = 0;
    for (int i = 0; i < size; ++i) {
        tablica[i] = new char[size];
        for (int j = 0; j < size; ++j) {
            tablica[i][j] = temp[k++];
        }
    }
}

int pawnsNumber(char**& tablica, int size, char m) {
    int counter = 0;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (m == 'a') {
                if (tablica[i][j] == 'r' || tablica[i][j] == 'b')
                    counter++;
            }
            else if (tablica[i][j] == m)
                counter++;
        }
    }
    return counter;
}

bool isRedTouchingEnds(char**& tablica, int size) {
    int counter = 0;
    for (int i = 0; i < size; i++) { // checks if there is a red pawn at the top left edge
        if (tablica[0][i] == 'r')
            counter++;
    }
    for (int i = size - 1; i >= 0; i--) { // checks if there is a red pawn on the lower right edge
        if (tablica[size - 1][i] == 'r')
            counter++;
    }
    return counter;
}

bool isBlueTouchingEnds(char**& tablica, int size) {
    int counter = 0;
    for (int i = 0; i < size; i++) { // checks if there is a red pawn at the upper left edge
        if (tablica[i][0] == 'b')
            counter++;
    }
    for (int i = size - 1; i >= 0; i--) { // checks if there is a red pawn on the lower right edge
        if (tablica[i][size - 1] == 'b')
            counter++;
    }
    return counter;
}

bool isOnlyOnePath(char**& tablica, int size, int x, int y) {
    char p = tablica[y][x];
    int licznik = 0;
    if (y + 1 < size && tablica[y + 1][x] == p)
        licznik++;

    if (y + 1 < size && x + 1 < size && tablica[y + 1][x + 1] == p)
        licznik++;

    if (x - 1 >= 0 && tablica[y][x - 1] == p)
        licznik++;

    if (y - 1 >= 0 && x - 1 >= 0 && tablica[y - 1][x - 1] == p)
        licznik++;

    if (y - 1 >= 0 && tablica[y - 1][x] == p)
        licznik++;

    if (x + 1 < size && tablica[y][x + 1] == p) 
        licznik++;

    if (licznik <= 2)
        return true;
    else
        return false;
}

int playerWon(char**& tablica, const string& plansza, char p) {
    int size = boardSize(plansza);
    if (p == 'r' && !isRedTouchingEnds(tablica, size))
        return 0;
    if (p == 'b' && !isBlueTouchingEnds(tablica, size))
        return 0;

    int x = -1;
    int y = -1;
    for (int i = 0; i < size; i++) { // choosing a starting pawn
        if (p == 'r') {
            if (tablica[0][i] == 'r') {
                y = 0;
                x = i;
            }
            else continue;
        }
        else if (p == 'b') {
            if (tablica[i][0] == 'b') {
                x = 0;
                y = i;
            }
            else continue;
        }

        if (x == -1 || y == -1) { return 0; } // start not found
        Stos stos;
        stos.push(x, y);
        while (!stos.isEmpty()) {
            y = stos.getY();
            x = stos.getX();
            if ((p == 'r' && y == size - 1) || (p == 'b' && x == size - 1)) { // finish line was found
                int endX = x;
                int endY = y;
                if (pawnsNumber(tablica, size, 'T') > 0)
                    return 1;
                while (!stos.isEmpty()) {
                    x = stos.getX();
                    y = stos.getY();
                    if (isOnlyOnePath(tablica, size, x, y)) {
                        char** tablicaNew;
                        konwersjaNaTablice(plansza, tablicaNew);
                        tablicaNew[y][x] = 'T';
                        if (p == 'b' && !playerWon(tablicaNew, plansza, 'b')) { // if removing one pawn does not allow you to win, the board is correct
                            delete[] tablicaNew;
                            return 2;
                        }
                        if (p == 'r' && !playerWon(tablicaNew, plansza, 'r')) {
                            delete[] tablicaNew;
                            return 2;
                        }
                        delete[] tablicaNew;
                    }
                    stos.pop();
                }
                tablica[endY][endX] = 'X';
                stos.~Stos();
                return 1;
            }

            if (y + 1 < size && tablica[y + 1][x] == p && !stos.odwiedzone(x, y + 1))
                stos.push(x, y + 1, Route::DOL);

            else if (y + 1 < size && x + 1 < size && tablica[y + 1][x + 1] == p && !stos.odwiedzone(x + 1, y + 1))
                stos.push(x + 1, y + 1, Route::PRAWO_DOL);

            else if (x - 1 >= 0 && tablica[y][x - 1] == p && !stos.odwiedzone(x - 1, y))
                stos.push(x - 1, y, Route::LEWO);

            else if (y - 1 >= 0 && x - 1 >= 0 && tablica[y - 1][x - 1] == p && !stos.odwiedzone(x - 1, y - 1))
                stos.push(x - 1, y - 1, Route::LEWO_GORA);

            else if (y - 1 >= 0 && tablica[y - 1][x] == p && !stos.odwiedzone(x, y - 1))
                stos.push(x, y - 1, Route::GORA);

            else if (x + 1 < size && tablica[y][x + 1] == p && !stos.odwiedzone(x + 1, y))
                stos.push(x + 1, y, Route::PRAWO);

            else {
                tablica[y][x] = 'X';
                stos.pop();
            }
        }
        stos.~Stos();
    }
    return 0;
}

int isGameOver(const string& plansza) {
    char** tablica;
    konwersjaNaTablice(plansza, tablica);
    if (playerWon(tablica, plansza, 'r')) {
        return 1;
    }
    if (playerWon(tablica, plansza, 'b')) {
        return 2;
    }
    return 0;
}

bool isBoardPossible(const string& plansza) {
    if (!isBoardCorrect(plansza))
        return 0;
    int size = boardSize(plansza);
    char** tablicaStartowa;
    char** tablica;
    konwersjaNaTablice(plansza, tablicaStartowa);
    copyArray(tablica, tablicaStartowa, size);

    if (playerWon(tablica, plansza, 'r') && playerWon(tablica, plansza, 'b')) {
        delete[] tablica;
        delete[] tablicaStartowa;
        return 0;
    }

    copyArray(tablica, tablicaStartowa, size);
    if (playerWon(tablica, plansza, 'r') && playerWon(tablica, plansza, 'r')) {
        if (playerWon(tablica, plansza, 'r') != 2) {
            delete[] tablica;
            delete[] tablicaStartowa;
            return 0;
        }
    }

    copyArray(tablica, tablicaStartowa, size);
    if (playerWon(tablica, plansza, 'b') && playerWon(tablica, plansza, 'b')) {
        if (playerWon(tablica, plansza, 'b') != 2) {
            delete[] tablica;
            delete[] tablicaStartowa;
            return 0;
        }
    }

    copyArray(tablica, tablicaStartowa, size);
    if (playerWon(tablica, plansza, 'b') && pawnsNumber(plansza, 'r') > pawnsNumber(plansza, 'b')) {
        delete[] tablica;
        delete[] tablicaStartowa;
        return 0;
    }

    copyArray(tablica, tablicaStartowa, size);
    if (playerWon(tablica, plansza, 'r') && pawnsNumber(plansza, 'r') == pawnsNumber(plansza, 'b')) {
        delete[] tablica;
        delete[] tablicaStartowa;
        return 0;
    }

    delete[] tablica;
    delete[] tablicaStartowa;
    return 1;
}

int main() {
    string plansza;
    string line;
    int licznik = 1;
    while (getline(cin, line) && line != "end") {
        int operacja = functionID(line);
        int wynik;
        while (operacja) {
            switch (operacja) {
            case 1: // BOARD_SIZE
                cout << boardSize(plansza) << endl;
                break;
            case 2: // PAWNS_NUMBER
                cout << pawnsNumber(plansza, 'a') << endl;
                break;
            case 3: // IS_BOARD_CORRECT
                if (isBoardCorrect(plansza))
                    cout << "YES" << endl;
                else
                    cout << "NO" << endl;
                break;
            case 4: // IS_GAME_OVER
                wynik = isGameOver(plansza);
                if (!isBoardCorrect(plansza) || wynik == 0)
                    cout << "NO" << endl;
                else if (wynik == 1)
                    cout << "YES RED" << endl;
                else if (wynik == 2)
                    cout << "YES BLUE" << endl;
                break;
            case 5: // IS_BOARD_POSSIBLE
                if (isBoardPossible(plansza))
                    cout << "YES" << endl;
                else
                    cout << "NO" << endl;
            }
            getline(cin, line);
            operacja = functionID(line);
            if (!operacja) {
                plansza = "";
                licznik++;
            }
        }
        plansza += line + '\n';
    }
    return 0;
}