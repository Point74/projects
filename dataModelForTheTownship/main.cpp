#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <limits>
#include <optional>


using namespace std;


enum roomType{
    bedroom,
    kitchen,
    bathroom,
    children,
    living
};


struct Room {
    double areaRoom;
    roomType type;

    //Room(roomType _type, int area) : typeR(_type), areaRoom(area) {} // при вводе комнаты пользовать вводит тип комнаты и её прощадь
};


struct Floor {
    int numberFloor{};
    int heightFloor{};
    int quantityRooms{};
    vector<Room> room;
};


struct Fireplace { // относится только к бане и дому
    string location;
    double areaFireplace{};
};


struct House {
    double areaHouse{};
    optional<Fireplace> fireplace; // может быть, а может и не быть
    vector<Floor> floor;
};


enum buildingType {
    garage,
    shed,
    bathing,
    home
};


struct Building {
    double areaBuilding{};
    buildingType type{};
    optional<Fireplace> fireplace; // может быть, а может и не быть
    vector<House> house;
};


struct Site { // участок
    double areaSite{};
    int numberSite{};

    vector<Building> buildings;
};


struct Village { // посёлок
    int quantityVillage{};
    int quantitySite{};

    vector<Site> site;
};



void fillVillage(Village& village);
void fillSite(Village& village, Site& newSite); // добавляем сооружения и их площадь
void fillHouse(House& newHouse);
void printBuildingType();
void printRoomType(int& floor);
void printInfoVillage(const Village& village);
void printInfoSite(const Site& site);
void printInfoHouse(const House& house);
void printInfoRoom(const Room& room);
string getRoomType(roomType type);
string getBuildingType(buildingType type);
bool needFireplace();
Fireplace addFireplace(double & area);


/*
 * при добавлении комнаты вызывать булевую функцию, которая спрашивает у пользователя нужно ли добавить печь с трубой,
 * кроме ванной комнаты
 * если печь уже была добавлена, то больше не спрашиваем у пользователя про печь
 * если пользователь добавил на участок баню, то вызываем ту же функцию для уточнения печи
 *
 * если пользователь сказал, что ему нужна печь, то вызываем функцию для добавления печи с её площадью,
 * и площадь печи не должна быть больше или равна площади самой комнаты
*/


void fillVillage(Village& village) {
    cout << "Enter number of village: ";
    cin >> village.quantityVillage;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    int quantityVillage = village.quantityVillage;

    for (int i = 0; i < quantityVillage; ++i) {
        cout << "Enter number of sites in the village #" << i + 1 << ": ";
        cin >> village.quantitySite;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        int quantitySite = village.quantitySite;
        for (int j = 0; j < quantitySite; ++j) {
            Site newSite;
            newSite.numberSite = j + 1;
            cout << "Site #" << newSite.numberSite;
            fillSite(village, newSite);
        }
    }

    // вводим цифры, которые будут олицетворять здания и потом преобразуем в тип перечисления (enum) и
    // вызываем функцию чтобы добавить здания которые будут на участке

    // если пользователь добавил здание, то вызываем функцию, чтобы польщователь указал сколько в доме этажей

    // или может создавать вектор, который будет хранить какие сооружения есть
    printInfoVillage(village);
}


void fillSite(Village& village, Site& newSite)  {
    double sumAreaAllBuilding = 0;

    cout << "\nEnter area of site (M^2): ";
    cin >> newSite.areaSite;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    printBuildingType();
    string inputBuilding;

    getline(cin, inputBuilding);

    stringstream strBuildings(inputBuilding);
    int numberOfBuilding;

    while (strBuildings >> numberOfBuilding) {
        if (numberOfBuilding > 4 || numberOfBuilding < 1) {
            cout << "You choose a building that doesn't exist!\nTry enter again!\n";
            printBuildingType();
            getline(cin, inputBuilding);
            strBuildings.clear();
            strBuildings.str("");
            strBuildings.str(inputBuilding);

            continue;
        }

        bool flag = true;
        while (flag) {
            Building building;

            cout << "Enter the building area of the " << getBuildingType(static_cast<buildingType>(numberOfBuilding - 1)) << "(M^2)\n";
            cin >> building.areaBuilding;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            if (sumAreaAllBuilding + building.areaBuilding > newSite.areaSite) {
                cout << "The building should not exceed " << newSite.areaSite - sumAreaAllBuilding << "(M^2)\n";
                continue;
            }

            if (building.areaBuilding < 0) {
                cerr << "Building area can't be less 0!\n";
                continue;
            }

            sumAreaAllBuilding += building.areaBuilding;

            switch (static_cast<buildingType>(numberOfBuilding - 1)) {
                case garage:
                    building.type = garage;
                    newSite.buildings.push_back(building);
                    break;

                case shed:
                    building.type = shed;
                    newSite.buildings.push_back(building);
                    break;

                case bathing:
                    building.type = bathing;

                    if (needFireplace()) {
                        building.fireplace = addFireplace(building.areaBuilding);
                        building.fireplace->location = getBuildingType(static_cast<buildingType>(numberOfBuilding - 1));
                    }

                    newSite.buildings.push_back(building);
                    break;

                case home:
                    building.type = home;
                    House newHouse;
                    newHouse.areaHouse = building.areaBuilding;
                    fillHouse(newHouse);
                    building.house.push_back(newHouse);
                    newSite.buildings.push_back(building);
                    break;
            }

            flag = false;
        }
    }

    village.site.push_back(newSite);

}


void fillHouse(House& newHouse) {
    int totalFloors;

    bool flag = true;
    while(flag) {
        cout << "Enter how many floors there are in the house(1-3 floors): ";
        cin >> totalFloors;

        if (totalFloors < 1 || totalFloors > 3) {
            cout << "There can only be 1-3 floors in the house!";
            continue;
        }

        flag = false;
    }

    bool isFireplace = false;
    for (int i = 0; i < totalFloors; ++i) {
        double checkArea = 0;
        Floor newFloor;

        newFloor.numberFloor = i + 1;

        cout << "Enter the height of the " << newFloor.numberFloor << " floor: ";
        cin >> newFloor.heightFloor;

        bool flag1 = true;
        while(flag1) {
            cout << "Enter the number of rooms on the " << newFloor.numberFloor << " floor(2-4 rooms): ";
            cin >> newFloor.quantityRooms;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            if (newFloor.quantityRooms < 2 || newFloor.quantityRooms > 4) {
                cout << "There can only be 2-4 rooms on a floor!";
                continue;
            }

            flag1 = false;
        }

        int quantityRooms = newFloor.quantityRooms;

        cout << "First enter the room type, then the room size, then enter 'enter' and enter the room information again!";


        while (quantityRooms != 0) {
            Room newRoom{};
            bool correctTypeRoom = false;
            string roomAndArea;
            int roomTypeInput;

            while (!correctTypeRoom) {

                printRoomType(newFloor.numberFloor);
                getline(cin, roomAndArea);

                stringstream roomInfo(roomAndArea);
                roomInfo >> roomTypeInput >> newRoom.areaRoom;

                if (roomTypeInput > 5) { // спальня, кухня, ванная, детская, гостинная
                    cout << "You have entered a non-existent room! Enter again, but only the existing room shown on the screen!\n";
                    continue;
                }

                correctTypeRoom = true;
            }

            newRoom.type = static_cast<roomType>(roomTypeInput - 1);

            checkArea += newRoom.areaRoom;

            if (!isFireplace && (newRoom.type == living ||
                                 newRoom.type == kitchen ||
                                 newRoom.type == bedroom)) { // в детской и в ванной комнатах печь не предполагается

                if (needFireplace()) {
                    newHouse.fireplace = addFireplace(newRoom.areaRoom);
                    newHouse.fireplace->location = getRoomType(static_cast<roomType>(newRoom.type));
                    isFireplace = true;
                }
            }

            //Room newRoom(static_cast<enum roomType>(roomType - 1), roomArea);

            newFloor.room.push_back(newRoom);

            quantityRooms--;

            if (quantityRooms == 0 && checkArea != newHouse.areaHouse) {
                cout << "You have entered the areas of all rooms on the " << newFloor.numberFloor <<
                     " floor, but the sum of the areas of the rooms is not equal to the entire area of the house!\n"
                     "Enter the rooms and their areas again!";

                checkArea = 0;
                quantityRooms = newFloor.quantityRooms;
                newFloor.room.clear();

                if (isFireplace) {
                    isFireplace = false;
                    newHouse.fireplace->areaFireplace = 0;
                }
            }
        }

        newHouse.floor.push_back(newFloor);
    }
}


void printInfoVillage(const Village& village) {
    cout << "\n\nQuantity of village: " << village.quantityVillage << "\n";
    for (int i = 0; i < village.quantityVillage; ++i) {
        cout << "Village #" << i + 1 << '\n';
        cout << "Quantity of sites: " << village.site.size() << '\n';

        for (const auto & site : village.site) {
            //cout << "\nSite #" << j + 1 << '\n';
            printInfoSite(site);
        }
    }
}


void printInfoSite(const Site& site) {
    bool flag = false; // есть ли дом
    bool fire = true;

    cout << "\nSite #" << site.numberSite << '\n';
    cout << "Area: " << site.areaSite << '\n';

    for (auto build = site.buildings.begin(); build != site.buildings.end(); ++build) {
        cout << getBuildingType(static_cast<buildingType>(build->type)) << ": " << build->areaBuilding << "m^2\n";

        if (build->fireplace.has_value() && fire) {
            cout << "Area fireplace: " << build->fireplace->areaFireplace << " m^2\nLocation fireplace: " << build->fireplace->location << '\n';
            fire = false;
        }

        if (build->type == home) {
            flag = true;
        }

        if (next(build) == site.buildings.end() && flag) {
            printInfoHouse(build->house[0]);
        }
    }
}


void printInfoHouse(const House& house) {
    cout << "Quantity of floors in the house: " << house.floor.size() << '\n';
    bool flag = true;
    for (int i = 0; i < house.floor.size(); ++i) {
        cout << "Floor #" << i + 1 << '\n';
        cout << "Height floor: " << house.floor[i].heightFloor << '\n';
        cout << "Quantity of rooms: " << house.floor[i].quantityRooms << '\n';

        if (house.fireplace.has_value() && flag) {
            cout << "Area fireplace: " << house.fireplace->areaFireplace << " m^2\nLocation fireplace: " << house.fireplace->location << '\n';
            flag = false;
        }

        for (const auto& room : house.floor[i].room) {
            printInfoRoom(room);
        }
    }
}


void printInfoRoom(const Room& room) {
    cout << "Room type: " << getRoomType(room.type) << " " << room.areaRoom << "m^2\n";
}


string getRoomType(roomType type) {
    switch (type) {
        case bedroom:
            return "Bedroom";

        case kitchen:
            return "Kitchen";

        case bathroom:
            return "Bathroom";

        case children:
            return "Children";

        case living:
            return "Living";

        default:
            return "Unknown building!\n";
    }
}


string getBuildingType(buildingType type) {
    switch (type) {
        case garage:
            return "Garage";

        case shed:
            return "Shed";

        case bathing:
            return "Bathing";

        case home:
            return "House";

        default:
            return "Error!\n";
    }
}


void printRoomType(int& floor) {
    cout << "\n1. Bedroom\n2. Kitchen\n3. Bathroom\n4. Children\n5. Living\n" << "Select which rooms on the " << floor << " floor: ";
}


void printBuildingType() {
    cout << "\n1. Garage\n2. Shed\n3. Bathing\n4. House\nSelect which buildings on the site: ";
}


Fireplace addFireplace(double& area) {
    Fireplace fireplace{};

    bool flag = true;
    while (flag) {
        cout << "Enter area of the fireplace: ";
        cin >> fireplace.areaFireplace;

        if (fireplace.areaFireplace >= area) {
            cout << "The area of the fireplace must not exceed the area of the room! Try enter area again!\n"; // баня будет считаться как помещение
            continue;
        }

        flag = false;
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    return fireplace;
}


bool needFireplace() {
    string answer;

    while (true) {
        cout << "Do you need a fireplace? Choose y(Yes) or n(No)";
        getline(cin, answer);

        if (answer == "y") {
            return true;

        } else if (answer == "n"){
            return false;

        } else {
            cout << "Incorrect answers entry! Try again!\n";
            continue;
        }
    }
}


int main() {
    Village village{};

    fillVillage(village);
}