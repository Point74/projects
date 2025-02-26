#include <iostream>
#include <fstream>

#include "cpu.cpp"
#include "disk.cpp"
#include "gpu.cpp"
#include "kbd.cpp"
#include "ram.cpp"
#include "utils.cpp"

using namespace std;

int main() {
    fstream file("data.txt");
    if(!isOpenFile(file, "data.txt")) {
        cout << "File don't open!\n";
        return 1;
    }

    const int sizeBuffer = 8;
    int buffer[sizeBuffer] = {};
    string answer;

    while (true) {
        file.clear();
        file.seekg(0, ios::beg);
        file.seekp(0, ios::beg);

        commandsProgram();
        int command;
        cout << "Enter command for action(number): ";
        cin >> command;

        if (command == 1) { // суммирование чисел
            if (isEmptyStorage(buffer, sizeBuffer)) {
                cout << "Buffer is empty! You should fill the buffer!\n";
                continue;
            }

            compute(buffer, sizeBuffer);

        } else if (command == 2) { // сохранение данных в файл
            if (isEmptyStorage(buffer, sizeBuffer)) {
                cout << "Buffer is empty! You should fill the buffer!\n";
                continue;
            }

            save(file, buffer, sizeBuffer);

        } else if (command == 3) { // загрузка данных из файла
            if (isEmptyFile(file, "data.txt")) {
                cout << "File is empty! Enter other command!\n";
                continue;
            }

            file.seekg(0, ios::beg);
            file.close();
            file.open("data.txt", ios::in);
            load(file, buffer, sizeBuffer);

        } else if (command == 4) { // ввод данных с клавиатуры
            if (!isEmptyStorage(buffer, sizeBuffer)) {
                cout << "You have data in the buffer. If you want to enter new data, enter 'y',"
                        "\nif you want to work with old data enter 'n', and than enter other command.\n"
                        "Command: ";

                cin >> answer;
                if (answer == "n") {
                    continue;

                } else if (answer == "y") {
                    input(buffer, sizeBuffer);
                    continue;

                } else {
                    cout << "Invalid command!\n";
                    continue;
                }
            }

            else {
                file.seekg(0, ios::end);
                if (file.tellg() == 0) {
                    input(buffer, sizeBuffer);

                } else {
                    cout << "You have data in the file. If you want to enter new data, enter 'y',"
                            "\nif you want to work with old data enter 'n', and than enter other command.\n"
                            "Command: ";

                    cin >> answer;
                    if (answer == "n") {
                        continue;

                    } else if (answer == "y") {
                        file.seekp(0, ios::beg);
                        file << ""; // очищаем файл
                        file.flush();
                        input(buffer, sizeBuffer);
                        continue;

                    } else {
                        cout << "Invalid command!\n";
                        continue;
                    }
                }
            }

        } else if (command == 5) { // вывод результата
            display(buffer, sizeBuffer);

        } else if (command == 6) { // выход из программы
            exit();
            break;

        } else {
            cout << "Invalid command! Try enter command again!\n";
            continue;
        }
    }
}