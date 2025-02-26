#include <iostream>
#include <fstream>
#include <random>
#include <string>
#include <iomanip>
#include <algorithm>
#include <limits>
#include <set>
#include <utility>


using namespace std;


struct Position {
    int x;
    int y;
};


struct Character {
    string name;
    int health{};
    int armor{};
    int damage{};
    Position position{};
};


struct Enemy {
    int serialNumber{};
    int health{};
    int armor{};
    int damage{};

    Position position{};
};


struct Quantity {
    size_t quantityEnemy{};
    size_t quantityCharacter = 1;
};


const int SIZE = 20;
char FIELD[SIZE][SIZE];


void fillCharacter(Character& character);
void fillEnemies(vector<Enemy>& enemies);
void saveGame(Character& character, vector<Enemy>& enemies, Quantity& quantity);
void loadGame(Character& character, vector<Enemy>& enemies, set<pair<int, int>>& occupiedCells, pair<int, int>& newCell, Quantity& quantity);
int randomOut(int n, int m);
void printField();
string commandMove(string& command);
void physicGame(Character& character, vector<Enemy>& enemies, Quantity& quantity);
void moveEnemy(Character& character, vector<Enemy>& enemies, int& position, pair<int, int>& previousPosition);
void addPeopleOnField(Character& character, vector<Enemy>& enemies, set<pair<int, int>>& occupiedCells, pair<int, int>& newCell, Quantity& quantity);
void loadPeopleOnField(Character &character, vector<Enemy> &enemies, Quantity& quantity);
void damageCharacter(Character& character, vector<Enemy>& enemies, int& positionX, int& positionY); // урон по врагу
void damageEnemy(Character& character, vector<Enemy>& enemies, int& positionX, int& positionY); // урон по герою
void removeDeadEnemy(pair<int, int>& deleteCoordinate);
bool isCharacterLose(Character& character);
bool isOccupiedCells(set<pair<int, int>>& occupiedCells, pair<int, int>& newCells);
bool isOutside(int& position);
bool isAliveEnemy(vector<Enemy>& enemies);
void clearPosition(pair<int, int>& previousPosition);
void heroStatistics(Character& character, vector<Enemy>& enemies);



/*
 * в начале пользователю предлагают ввести команду, либо load, чтобы загрузить прогресс, если файл пустой, то начинаем игру с нуля
 * сделаем проверку, что файл пустой, если пустой, то создаём файл
 * если файл не пустой, то запускаем прогрес и продолжаем игру
 * если пользователь захочет ввести save вначале, то система выводит, вам пока нечего сохранять, потому что вы не начали/загрузили игру
*/



void roleGame(Character& character, vector<Enemy>& enemies) {
    string command;
    set<pair<int, int>> occupiedCells; // занятие позиции на карте
    pair<int, int> newCell;
    Quantity quantity;

    while (true) {
        cout << "Enter command for load game(load): ";
        getline(cin, command);

        if (command == "save") {
            cout << "You have nothing to save yet, because you haven't started/loaded the game yet!\n"
                    "If you want to exit from game enter 'exit'\nTry again!\n";

            continue;

        } else if (command == "load") {
            loadGame(character, enemies, occupiedCells, newCell, quantity);
            break;

        } else if (command == "exit") {
            cout << "Stop game....\n";
            return;

        } else {
            cout << "Invalid command!\nTry again!\n";
            continue;
        }
    }

    physicGame(character, enemies, quantity);
}


void physicGame(Character& character, vector<Enemy>& enemies, Quantity& quantity) {
    string command;
    int position;
    pair<int, int> previousPosition;

    while (character.health > 0 && isAliveEnemy(enemies)) {
        printField();
        heroStatistics(character, enemies);
        command = commandMove(command);
        previousPosition = {character.position.x, character.position.y};

        if (command == "save") {
            saveGame(character, enemies, quantity);
            return;

        } else if (command == "load") {
            cout << "You cannot load the game because you are already in the game!\n";

        } else if (command == "exit") {
            cout << "Stop game....\n";
            return;

        } else if (command == "L") { // лево
            position = character.position.y - 1;

            if (isOutside(position)) {
                moveEnemy(character, enemies, position, previousPosition);
                continue;
            }

            if (FIELD[character.position.x][position] == 'E') {
                damageCharacter(character, enemies, static_cast<int&>(character.position.x), position);
                continue;
            }

            clearPosition(previousPosition);

            character.position.y = position;
            FIELD[character.position.x][character.position.y] = 'P';

            moveEnemy(character, enemies, position, previousPosition);

        } else if (command == "R") { // право
            position = character.position.y + 1;

            if (isOutside(position)) {
                moveEnemy(character, enemies, position, previousPosition);
                continue;
            }

            if (FIELD[character.position.x][position] == 'E') {
                damageCharacter(character, enemies, static_cast<int&>(character.position.x), position);
                continue;
            }

            clearPosition(previousPosition);

            character.position.y = position;
            FIELD[character.position.x][character.position.y] = 'P';

            moveEnemy(character, enemies, position, previousPosition);

        } else if (command == "U") { // вверх
            position = character.position.x - 1;

            if (isOutside(position)) {
                continue;
            }

            if (FIELD[position][character.position.y] == 'E') {
                damageCharacter(character, enemies, position, static_cast<int&>(character.position.y));
                continue;
            }

            clearPosition(previousPosition);

            character.position.x = position;
            FIELD[character.position.x][character.position.y] = 'P';

            moveEnemy(character, enemies, position, previousPosition);

        } else if (command == "D") { // вниз
            position = character.position.x + 1;

            if (isOutside(position)) {
                moveEnemy(character, enemies, position, previousPosition);
                continue;
            }

            if (FIELD[position][character.position.y] == 'E') {
                damageCharacter(character, enemies, position, static_cast<int&>(character.position.y));
                continue;
            }

            clearPosition(previousPosition);

            character.position.x = position;
            FIELD[character.position.x][character.position.y] = 'P';

            moveEnemy(character, enemies, position, previousPosition);

        } else {
            moveEnemy(character, enemies, position, previousPosition);
            cout << "Invalid command! Try again!\n";
        }
    }

    if (isCharacterLose(character)) {
        cout << "\nEnemies is win!\nCharacter is lose!\n";

    } else {
        cout << "\nCharacter is win!\nEnemies is lose!\n";
    }

    printField();
    heroStatistics(character, enemies);
}


bool isAliveEnemy(vector<Enemy>& enemies) {
    size_t aliveEnemy = enemies.size();

    for (auto& enemy : enemies) {
        if (enemy.health == 0) {
            aliveEnemy--;
        }
    }

    if (aliveEnemy == 0) {
        return false;
    }

    return true;
}


void damageCharacter(Character& character, vector<Enemy>& enemies, int& positionX, int& positionY) {
    pair<int, int> deleteCoordinate;
    for (auto& enemy : enemies) {
        if (enemy.position.x == positionX && enemy.position.y == positionY) {
            if (enemy.armor > 0) {
                enemy.armor -= character.damage;

                if (enemy.armor < 0) {
                    enemy.health += enemy.armor;
                    enemy.armor = 0;

                    if (enemy.health <= 0) {
                        enemy.health = 0;

                        deleteCoordinate = {enemy.position.x, enemy.position.y};
                        removeDeadEnemy(deleteCoordinate);
                    }
                }

            } else {
                enemy.health -= character.damage;

                if (enemy.health <= 0) {
                    enemy.health = 0;
                    deleteCoordinate = {enemy.position.x, enemy.position.y};
                    removeDeadEnemy(deleteCoordinate);
                }
            }
        }
    }
}


void damageEnemy(Character& character, vector<Enemy>& enemies, int& positionX, int& positionY) {
    for (auto& enemy : enemies) {
        if (enemy.position.x == positionX && enemy.position.y == positionY) {
            character.armor -= enemy.damage;

            if (character.armor < 0) {
                character.health += character.armor;

                if (isCharacterLose(character)) {
                    return;
                }
            }
        }
    }
}


bool isCharacterLose(Character& character) {
    if (character.health <= 0) {
        character.health = 0;
        return true;
    }

    return false;
}


void clearPosition(pair<int, int>& previousPosition) {
    FIELD[previousPosition.first][previousPosition.second] = '.';
}


void printField() {
    char letter = 65; // A
    cout << "  ";
    // setw(2) = один пробел
    for (int i = 0; i < SIZE; ++i) {
        cout << letter << setw(2);
        letter++;
    }

    cout << '\n';

    for (int i = 0; i < SIZE; ++i) {
        cout << setw(2) << i + 1;
        for (int j = 0; j < SIZE; ++j) {
            cout << setw(2); // добавить логику для выявления героев, может сделать лямбда функцию, которая будет принимать героев
            if (FIELD[i][j] == 'P') {
                cout << 'P';

            } else if (FIELD[i][j] == 'E') {
                cout << 'E';

            } else {
                cout << '.';
            }
        }

        cout << "|\n";
    }

    cout << "   ";
    for (int k = 0; k < SIZE; ++k) {
        cout << "--";
    }
}


void heroStatistics(Character& character, vector<Enemy>& enemies) {
    cout << "\nCharacter:" <<
         "\nName: " << character.name <<
         "\nHealth: " << character.health <<
         "\nArmor: " << character.armor <<
         "\nDamage: " << character.damage << endl;

    for (auto& enemy : enemies) {
        if (enemy.health == 0) {
            cout << "Enemy #" << enemy.serialNumber << ": killed\n";
            continue;
        }

        cout << "Enemy #" << enemy.serialNumber <<
             "\nHealth: " << enemy.health <<
             "\nArmor: " << enemy.armor <<
             "\nDamage: " << enemy.damage << endl;
    }
}


void moveEnemy(Character& character, vector<Enemy>& enemies, int& position, pair<int, int>& previousPosition) {
    /* если выдаёт 0, то двигаемся влево
     * если выдаёт 1, то двигаемся право
     * если выдаёт 2, то двигаемся вверх
     * если выдаёт 3, то двигаемся вниз
     */

    for (auto& enemy : enemies) {
        if (enemy.health == 0) {
            continue;
        }

        previousPosition = {enemy.position.x, enemy.position.y};
        position = randomOut(0, 3);

        if (position == 0) {
            position = enemy.position.y - 1;

            if (isOutside(position)) {
                continue;
            }

            if (FIELD[enemy.position.x][position] == 'P') {
                damageEnemy(character, enemies, position, static_cast<int&>(enemy.position.y));

                if (isCharacterLose(character)) {
                    return;
                }

                continue;
            }

            if (FIELD[enemy.position.x][position] == 'E') {
                continue;
            }

            clearPosition(previousPosition);

            enemy.position.y = position;
            FIELD[enemy.position.x][enemy.position.y] = 'E';


        } else if (position == 1) {
            position = enemy.position.y + 1;

            if (isOutside(position)) {
                continue;
            }

            if (FIELD[enemy.position.x][position] == 'P') {
                damageEnemy(character, enemies, position, static_cast<int&>(enemy.position.y));

                if (isCharacterLose(character)) {
                    return;
                }

                continue;
            }

            if (FIELD[enemy.position.x][position] == 'E') {
                continue;
            }

            clearPosition(previousPosition);

            enemy.position.y = position;
            FIELD[enemy.position.x][enemy.position.y] = 'E';

        } else if (position == 2) {
            position = enemy.position.x - 1;

            if (isOutside(position)) {
                continue;
            }

            if (FIELD[position][enemy.position.y] == 'P') {
                damageEnemy(character, enemies, static_cast<int&>(enemy.position.x), position);

                if (isCharacterLose(character)) {
                    return;
                }

                continue;
            }

            if (FIELD[position][enemy.position.y] == 'E') {
                continue;
            }

            clearPosition(previousPosition);

            enemy.position.x = position;
            FIELD[enemy.position.x][enemy.position.y] = 'E';


        } else if (position == 3) {
            position = enemy.position.x + 1;

            if (isOutside(position)) {
                continue;
            }

            if (FIELD[position][enemy.position.y] == 'P') {
                damageEnemy(character, enemies, static_cast<int&>(enemy.position.x), position);

                if (isCharacterLose(character)) {
                    return;
                }

                continue;
            }

            if (FIELD[position][enemy.position.y] == 'E') {
                continue;
            }

            clearPosition(previousPosition);

            enemy.position.x = position;
            FIELD[enemy.position.x][enemy.position.y] = 'E';
        }
    }
}


void removeDeadEnemy(pair<int, int>& deleteCoordinate) {
    // если хотим удалить врага изи вектора, то тогда нужно передать вектор врагов (vector<Enemy>& enemies)
//    enemies.erase(remove_if(enemies.begin(), enemies.end(), [](const Enemy& enemy) {
//        return enemy.health <= 0;
//    }),enemies.end());
    FIELD[deleteCoordinate.first][deleteCoordinate.second] = '.';
}


bool isOutside(int& position) {
    if (position == -1 || position == SIZE) {
        return true;
    }

    return false;
}


string commandMove(string& command) {
    while (true) {
        cout << "\nEnter letter for move: ";
        cin >> command;
        if (command == "L" || command == "R" || command == "U" || command == "D" || command == "load" || command == "save")
            break;
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    return command;
}


void fillCharacter(Character& character) {
    cout << "\nEnter name of character: ";
    getline(cin, character.name);

    cout << "\nEnter number of health of the character: ";
    cin >> character.health;

    cout << "\nEnter number of armor of the character: ";
    cin >> character.armor;

    cout << "\nEnter number of damage of the character: ";
    cin >> character.damage;
}


void fillEnemies(vector<Enemy>& enemies) {
    for (int i = 0; i < enemies.size(); ++i) {
        enemies[i].serialNumber = i + 1;
        enemies[i].health = randomOut(50, 150);
        enemies[i].armor = randomOut(0, 50);
        enemies[i].damage = randomOut(15, 30);
    }
}


int randomOut(int n, int m) {
    random_device randomDevice;
    mt19937 rd(randomDevice());
    uniform_int_distribution<> intDistribution(n, m);

    int randomValue = intDistribution(rd);

    return randomValue;
}


void saveGame(Character& character, vector<Enemy>& enemies, Quantity& quantity) {
    fstream file("save.bin", ios::binary | ios::out | ios::trunc);

    if (!file.is_open()) {
        cerr << "\nFile don't open!\n";
        file.open("save.bin", ios::binary | ios::out | ios::trunc);

        if (!file.is_open()) {
            cout << "\nFile don't create!\n";
            return;
        }
    }

    // сохраняем героя
    size_t nameCharacter = character.name.length();
    file.write((char*)(&nameCharacter), sizeof(nameCharacter));
    file.write(character.name.c_str(), static_cast<streamsize>(character.name.size()));
    file.write((char*)(&character.health), static_cast<streamsize>(sizeof(character.health)));
    file.write((char*)(&character.armor), static_cast<streamsize>(sizeof(character.armor)));
    file.write((char*)(&character.damage), static_cast<streamsize>(sizeof(character.damage)));
    file.write((char*)(&character.position.x), static_cast<streamsize>(sizeof(character.position.x)));
    file.write((char*)(&character.position.y), static_cast<streamsize>(sizeof(character.position.y)));

    // сохраняем врагов
    quantity.quantityEnemy = enemies.size();
    file.write((char*)(&quantity.quantityEnemy), static_cast<streamsize>(sizeof(size_t)));
    for (auto & enemy : enemies) {
        file.write((char*)(&enemy.serialNumber), static_cast<streamsize>(sizeof(enemy.serialNumber)));
        file.write((char*)(&enemy.health), static_cast<streamsize>(sizeof(enemy.health)));
        file.write((char*)(&enemy.armor), static_cast<streamsize>(sizeof(enemy.armor)));
        file.write((char*)(&enemy.damage), static_cast<streamsize>(sizeof(enemy.damage)));
        file.write((char*)(&enemy.position.x), static_cast<streamsize>(sizeof(enemy.position.x)));
        file.write((char*)(&enemy.position.y), static_cast<streamsize>(sizeof(enemy.position.y)));
    }

    file.close();
}


void loadGame(Character& character, vector<Enemy>& enemies, set<pair<int, int>>& occupiedCells, pair<int, int>& newCell, Quantity& quantity) {
    fstream file("save.bin", ios::binary | ios::in);

    if (!file.is_open()) {
        file.open("save.bin", ios::binary | ios::out);

        if (!file.is_open()) {
            cout << "\nFile don't open!\n";
            return;
        }

        file.close();
        file.open("save.bin", ios::binary | ios::in);


        fillEnemies(enemies);
        fillCharacter(character);
        addPeopleOnField(character, enemies, occupiedCells, newCell, quantity); // первый вывод всех героев, для начала игры
        file.close();
        return;
    }

    // загружаем героя
    size_t nameCharacter;
    file.read((char*)(&nameCharacter), static_cast<streamsize>(sizeof(nameCharacter)));
    character.name.resize(nameCharacter);
    file.read(const_cast<char*>(character.name.data()), static_cast<streamsize>(nameCharacter));
    file.read((char*)(&character.health), static_cast<streamsize>(sizeof(character.health)));
    file.read((char*)(&character.armor), static_cast<streamsize>(sizeof(character.armor)));
    file.read((char*)(&character.damage), static_cast<streamsize>(sizeof(character.damage)));
    file.read((char*)(&character.position.x), static_cast<streamsize>(sizeof(character.position.x))); // координата по x, то есть по буквам
    file.read((char*)(&character.position.y), static_cast<streamsize>(sizeof(character.position.y))); // координата по y, то есть по цифрам

    //загружаем врагов
    file.read((char*)(&quantity.quantityEnemy), static_cast<streamsize>(sizeof(quantity.quantityEnemy)));
    for (size_t i = 0; i < quantity.quantityEnemy; ++i) {
        file.read((char*)(&enemies[i].serialNumber), static_cast<streamsize>(sizeof(enemies[i].serialNumber)));
        file.read((char*)(&enemies[i].health), static_cast<streamsize>(sizeof(enemies[i].health)));
        file.read((char*)(&enemies[i].armor), static_cast<streamsize>(sizeof(enemies[i].armor)));
        file.read((char*)(&enemies[i].damage), static_cast<streamsize>(sizeof(enemies[i].damage)));
        file.read((char*)(&enemies[i].position.x), static_cast<streamsize>(sizeof(enemies[i].position.x)));
        file.read((char*)(&enemies[i].position.y), static_cast<streamsize>(sizeof(enemies[i].position.y)));
    }

    file.close();

    loadPeopleOnField(character, enemies, quantity);
}


void loadPeopleOnField(Character& character, vector<Enemy>& enemies, Quantity& quantity) {
    quantity.quantityEnemy = enemies.size();

    while (quantity.quantityEnemy != 0 || quantity.quantityCharacter != 0) {
        int person = randomOut(0, 1);

        if (quantity.quantityCharacter == 0) {
            person = 0;
        }

        char gameHero;

        if (person == 1 && quantity.quantityCharacter >= 0) {
            gameHero = 'P';

            FIELD[character.position.x][character.position.y] = gameHero;
            quantity.quantityCharacter -= 1;

        } else if (person == 0 && quantity.quantityEnemy > 0) {
            gameHero = 'E';

            for (auto& enemy : enemies) {
                if (enemy.health == 0) {
                    quantity.quantityEnemy -= 1;
                    continue;
                }

                FIELD[enemy.position.x][enemy.position.y] = gameHero;
                quantity.quantityEnemy -= 1;
            }
        }
    }
}


bool isOccupiedCells(set<pair<int, int>>& occupiedCells, pair<int, int>& newCells) {
    if (occupiedCells.find(newCells) == occupiedCells.end()) {
        return false;
    }

    return true;
}


void addPeopleOnField(Character& character, vector<Enemy>& enemies, set<pair<int, int>>& occupiedCells, pair<int, int>& newCell, Quantity& quantity) {
    quantity.quantityEnemy = enemies.size();
    quantity.quantityCharacter = 1; // всего один герой по условию

    while (quantity.quantityEnemy != 0 || quantity.quantityCharacter != 0) {
        int person = randomOut(0, 1);

        if (quantity.quantityCharacter == 0) {
            person = 0;
        }

        char gameHero;

        if (person == 1 && quantity.quantityCharacter >= 0) {
            gameHero = 'P';

            while (true) {
                character.position.x = randomOut(0, 19);
                character.position.y = randomOut(0, 19);
                newCell = {character.position.x, character.position.y};


                if (isOccupiedCells(occupiedCells, newCell)) {
                    continue;
                }

                occupiedCells.insert(newCell);

                break;
            }

            FIELD[character.position.x][character.position.y] = gameHero;
            quantity.quantityCharacter -= 1;

        } else if (person == 0 && quantity.quantityEnemy > 0) {
            gameHero = 'E';

            for (auto& enemy : enemies) {
                while (true) {
                    enemy.position.x = randomOut(0, 19);
                    enemy.position.y = randomOut(0, 19);
                    newCell = {enemy.position.x, enemy.position.y};


                    if (isOccupiedCells(occupiedCells, newCell)) {
                        continue;
                    }

                    occupiedCells.insert(newCell);

                    break;
                }

                FIELD[enemy.position.x][enemy.position.y] = gameHero;
                quantity.quantityEnemy -= 1;
            }
        }
    }
}


int main() {
    Character character;
    int quantityEnemy = 5;
    vector<Enemy> enemies(quantityEnemy);

    roleGame(character, enemies);
}