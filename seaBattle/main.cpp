#include <iostream>
#include <vector>
#include <iomanip>


using namespace std;

const int SIZE = 10;

vector<vector<bool>> field_1(SIZE, vector<bool>(SIZE));
vector<vector<bool>> field_2(SIZE, vector<bool>(SIZE));

void seaBattle();
void printField1();
void printField2();
void navigate();
void enterCoordinatesInFirstField(char& x1, int& y1, char& x2, int& y2, int ship1, int ship2, int ship3, int ship4);
void rule();
//bool inputCheck();
bool checkValue(int x1, int y1, int x2, int y2);
void printShipFirstField(int x1, int y1, int x2, int y2);
void enterCoordinatesInSecondField(char& q1, int& w1, char& q2, int& w2, int& ship1, int& ship2, int& ship3, int& ship4);
void printShipSecondField(int q1, int w1, int q2, int w2);
bool freeFieldTest1(int x1, int y1, int x2, int y2);
bool freeFieldTest2(int x1, int y1, int x2, int y2);
void clearNumber();
void strike();
void hittingCheckField2(int x, int y);
void hittingCheckField1(int x, int y);



void rule() {
    cout << "\nRULES\nSpread out the ships.\n"
            "First enter the first coordinates, the first digit x, "
            "the second digit y, then the second coordinates again by x and y.\n"
            "Do not enter negative numbers.\nInput sequence: first letter then number\n";
}


void seaBattle() {
    /* 1 на 4 клетки
     * 2 на 3 клетки
     * 3 на 2 клетки
     * 4 на 1 клетку*/
    rule();
    printField1();
    printField2();
    navigate(); // расставить корабли
    strike();
}


void navigate() { // расставить корабли
    char x1, x2; //  координаты для первого поля
    int y1, y2;
    char q1, q2; // координаты для второго поля
    int w1, w2;
    int ship1 = 4;
    int ship2 = 3;
    int ship3 = 2;
    int ship4 = 1;

    enterCoordinatesInFirstField(x1, y1, x2, y2, ship1, ship2, ship3, ship4);
    enterCoordinatesInSecondField(q1, w1, q2, w2, ship1, ship2, ship3, ship4);
}


void strike() {
    bool flag1 = true;
    bool flag11 = false, flag22 = false;
    char x;
    int y, x11;

    while (flag1) {
        cout << "\n\nPlayer 1 enter the coordinates for the strike: "; cin >> x >> y;
        x11 = x - 'A';
        y = y - 1;
        if (x11 < 0 || x11 >= SIZE || y < 0 || y >= SIZE) {
            cout << "\nYou have entered the wrong coordinates,"
                    "the coordinates should be greater than 0 and less than 11. Try again.\n\n";
            continue;
        }

        hittingCheckField2(x11, y);
        printField2();
        clearNumber();

        // Проверка, остались ли корабли
        flag11 = false; flag22 = false;

        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                if (field_1[j][i])
                    flag11 = true;

                if (field_2[j][i])
                    flag22 = true;
            }
        }

        if (!flag22) {
            cout << "\nPlayer 1 wins!";
            break;
        }


        bool flag2 = true;
        while (flag2) {
            cout << "\n\nPlayer 2 enter the coordinates for the strike: "; cin >> x >> y;
            x11 = x - 'A';
            y = y - 1;
            if (x11 < 0 || x11 >= SIZE || y < 0 || y >= SIZE || isalpha(x11) || isdigit(y)) {
                cout << "\nYou have entered the wrong coordinates,"
                        "the coordinates should be greater than 0 and less than 11. Try again.\n\n";
                continue;
            }

            hittingCheckField1(x11, y);
            printField1();
            clearNumber();


            // Проверка, остались ли корабли
            flag11 = false;
            flag22 = false;

            for (int i = 0; i < SIZE; ++i) {
                for (int j = 0; j < SIZE; ++j) {
                    if (field_1[j][i])
                        flag11 = true;

                    if (field_2[j][i])
                        flag22 = true;
                }
            }

            if (!flag11) {
                cout << "\nPlayer 2 wins!";
                flag1 = false;
                break;
            }

            flag2 = false;  // Завершаем внутренний цикл

        }

    }

}


void hittingCheckField2(int x, int y) {
    if (field_2[y][x]) {
        cout << "You're hit!\n";
        field_2[y][x] = false;
    } else
        cout << "You missed!\n";
}


void hittingCheckField1(int x, int y) {
   if (field_1[y][x]) {
        cout << "You're hit!\n";
        field_1[y][x] = false;
    } else
        cout << "You missed!\n";
}


void clearNumber() {
    cin.clear();
    cin.ignore(1024, '\n');
}


void enterCoordinatesInFirstField(char& x1, int& y1, char& x2, int& y2, int ship1, int ship2, int ship3, int ship4) {
    bool flag = true;
    int x11, x22;

    while (flag) {
        cout << "\nleft: " << ship4 << " on 4 squares, " << ship3 << " on 3 squares, "
             << ship2 << " on 2 squares, " << ship1 << " on 1 squares.";

        if (ship4 == 0 && ship3 == 0 && ship2 == 0 && ship1 == 0) {
            flag = false;
            break;
        }

        cout << "\ncoordinates ships for first field\n";
        cout << "\nEnter first coordinates (x, y): "; cin >> x1 >> y1;
        cout << "Enter second coordinates (x, y): "; cin >> x2 >> y2;

        // преобразование координат
        x11 = x1 - 'A';
        x22 = x2 - 'A';
        y1 = y1 - 1;
        y2 = y2 - 1;

        if (x11 > x22) swap(x11, x22);
        if (y1 > y2) swap(y1, y2);

        if (!checkValue(x11, y1, x22, y2)) {
            clearNumber();
            continue;
        }

        if (!freeFieldTest1(x11, y1, x22, y2)) {
            cout << "\nThis field is occupied! Try entering different coordinates.\n";
            clearNumber();
            continue;
        }

        if (x22 - x11 + 1 > 4 || y2 - y1 + 1 > 4) {
            cout << "\nThe length of such a ship cannot be in the game! The length of the ship must not exceed 4 squares\n";
            clearNumber();
            continue;
        }

        if (x22 - x11 + 1 == 4 || y2 - y1 + 1 == 4) {
            if (ship4 == 0){
                cout << "\nThere are no ships of this format, try entering coordinates for other ships.\n";
                clearNumber();
                continue;
            }

            if (ship4 != 0)
                ship4--;
        }

        else if (x22 - x11 + 1 == 3 || y2 - y1 + 1 == 3) {
            if (ship3 == 0){
                cout << "\nThere are no ships of this format, try entering coordinates for other ships.\n";
                clearNumber();
                continue;
            }

            if (ship3 != 0)
                ship3--;

        }

        else if (x22 - x11 + 1 == 2 || y2 - y1 + 1 == 2) {
            if (ship2 == 0){
                cout << "\nThere are no ships of this format, try entering coordinates for other ships.\n";
                clearNumber();
                continue;
            }

            if (ship2 != 0)
                ship2--;

        }

        else if (x22 - x11 + 1 == 1 || y2 - y1 + 1 == 1) {
            if (ship1 == 0){
                cout << "\nThere are no ships of this format, try entering coordinates for other ships.\n";
                clearNumber();
                continue;
            }

            if (ship1 != 0)
                ship1--;

        }

        printShipFirstField(x11, y1, x22, y2);

        clearNumber();
    }
}


void enterCoordinatesInSecondField(char& q1, int& w1, char& q2, int& w2, int& ship1, int& ship2, int& ship3, int& ship4) {
    bool flag = true;
    int q11, q22;

    while (flag) {
        cout << "\nleft: " << ship4 << " on 4 squares, " << ship3 << " on 3 squares, "
             << ship2 << " on 2 squares, " << ship1 << " on 1 squares.\n";

        if (ship4 == 0 && ship3 == 0 && ship2 == 0 && ship1 == 0) {
            flag = false;
            break;
        }

        cout << "coordinates ships for second field\n";
        cout << "\nEnter first coordinates (x, y): "; cin >> q1 >> w1;
        cout << "Enter second coordinates (x, y): "; cin >> q2 >> w2;

        // преобразование координат
        q11 = q1 - 'A';
        q22 = q2 - 'A';
        w1 = w1 - 1;
        w2 = w2 - 1;

        if (q11 > q22) swap(q11, q22);
        if (w1 > w2) swap(w1, w2);

        if (!checkValue(q11, w1, q22, w2))
            continue;

        if (!freeFieldTest2(q11, w1, q22, w2)) {
            cout << "\nThis field is occupied! Try entering different coordinates.\n";
            clearNumber();
            continue;
        }

        if (q22 - q11 + 1 > 4 || w2 - w1 + 1 > 4) {
            cout << "\nThe length of such a ship cannot be in the game! The length of the ship must not exceed 4 squares\n";
            clearNumber();
            continue;
        }

        if (q22 - q11 + 1 == 4 || w2 - w1 + 1 == 4) {
            if (ship4 == 0){
                cout << "\nThere are no ships of this format, try entering coordinates for other ships.\n";
                clearNumber();
                continue;
            }

            if (ship4 != 0)
                ship4--;

        }

        else if (q22 - q11 + 1 == 3 || w2 - w1 + 1 == 3) {
            if (ship3 == 0){
                cout << "\nThere are no ships of this format, try entering coordinates for other ships.\n";
                clearNumber();
                continue;
            }

            if (ship3 != 0)
                ship3--;

        }

        else if (q22 - q11 + 1 == 2 || w2 - w1 + 1 == 2) {
            if (ship2 == 0){
                cout << "\nThere are no ships of this format, try entering coordinates for other ships.\n";
                clearNumber();
                continue;
            }

            if (ship2 != 0)
                ship2--;

        }

        else if (q22 - q11 + 1 == 1 || w2 - w1 + 1 == 1) {
            if (ship1 == 0){
                cout << "\nThere are no ships of this format, try entering coordinates for other ships.\n";
                clearNumber();
                continue;
            }

            if (ship1 != 0)
                ship1--;

        }

        printShipSecondField(q11, w1, q22, w2);

        clearNumber();
    }
}


bool freeFieldTest1(int x1, int y1, int x2, int y2) {
    for (int i = x1; i <= x2; ++i) {
        for (int j = y1; j <= y2; ++j) {
            if (field_1[j][i])
                return false;
        }
    }
    return true;
}


bool freeFieldTest2(int x1, int y1, int x2, int y2) {
    for (int i = x1; i <= x2; ++i) {
        for (int j = y1; j <= y2; ++j) {
            if (field_2[j][i])
                return false;
        }
    }
    return true;
}


//bool inputCheck() {
//    if (cin.fail()) {
//        cin.clear();
//        cin.ignore(1024, '\n');
//        cout << "\nIncorrect data entry! PLease enter positive integer values.\n";
//        return false;
//    }
//
//    return true;
//
//}


bool checkValue(int x1, int y1, int x2, int y2) {
    if (x1 < 0 || y1 < 0 || x2 < 0 || y2 < 0 || x1 >= SIZE || y1 >= SIZE || x2 >= SIZE || y2 >= SIZE || isalpha(x1) || isdigit(y1)) {
        cout << "\nIncorrect data entry! PLease enter positive integer values.\n";
        return false;
    }

    if (x1 != x2 && y1 != y2) {
        cout << "\nIncorrect data entry! Either x1 must not be equal to x2 and y1 must not be equal to y2 or\n"
                "x1 must not be equal to x2 and y1 must be equal to y2\n";
        return false;
    }

    return true;
}


void printShipFirstField(int x1, int y1, int x2, int y2) {
    for (int i = x1; i <= x2; ++i) {
        for (int j = y1; j <= y2; ++j)
            field_1[j][i] = true;
    }
    printField1();
}


void printField1() {
    cout << "\nfield 1: \n";
    char symbol = 65; // A
    cout << "  ";
    for (int i = 0; i < SIZE; ++i) {
        cout << setw(2) << symbol << ' ';
        symbol++;
    }
    cout << '\n';

    for (int i = 0; i < SIZE; ++i) {
        cout << setw(2) << i + 1;
        for (int j = 0; j < SIZE; ++j) {
            cout << setw(2) << (field_1[i][j] ? 1 : 0) << ' ';
        }
        cout << '\n';

    }
    cout << '\n';
}


void printShipSecondField(int q1, int w1, int q2, int w2) {
    for (int i = q1; i <= q2; ++i) {
        for (int j = w1; j <= w2; ++j)
            field_2[j][i] = true;
    }
    printField2();
}


void printField2() {
    cout << "field 2: \n";
    char symbol = 65; // A
    cout << "  ";
    for (int i = 0; i < SIZE; ++i) {
        cout << setw(2) << symbol << ' ';
        symbol++;
    }
    cout << '\n';

    for (int i = 0; i < SIZE; ++i) {
        cout << setw(2) << i + 1;
        for (int j = 0; j < SIZE; ++j) {
            cout << setw(2) << (field_2[i][j] ? 1 : 0) << ' ';
        }
        cout << '\n';
    }
}


int main() {
    seaBattle();
}