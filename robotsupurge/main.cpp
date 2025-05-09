#include <iostream>
#include "Ferhat.h"

using namespace std;

int main()
{
    for (int i = 1; i <= 10; ++i)
    {
        House room;

        room.x1 = rand() % 100;
        room.y1 = rand() % 100;
        room.x2 = rand() % 100;
        room.y2 = rand() % 100;
        houses.push_back(room);
    }

    for (auto &house : houses)
    {
        house.obstacles.push_back({(house.x1 + house.x2) / 2.0, (house.y1 + house.y2) / 2.0});
    }

    Robot robot;
    robot.x = 0.0;
    robot.y = 0.0;
    robot.charge = 100;

    writeHouseMapToFile(houses);

    int choice;
    vector<int> cleanedRooms;

    do
    {
        cout << "\n***** MENU *****\n";
        cout << "1. Robotu Hareket Ettir\n";
        cout << "2. Belirli Bir Odayi Temizle\n";
        cout << "3. Tum Evi Temizle\n";
        cout << "4. Robotu Sarj Et\n";
        cout << "5. Ev Haritasini Goster\n";
        cout << "6. Robot Bilgilerini Goster\n";
        cout << "7. Cikis\n";
        cout << "Bir secenek girin: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
        {
            double targetX, targetY;
            int speedLevel;
            int mop;

            cout << "Hedef koordinatlari girin (X Y): ";
            cin >> targetX >> targetY;

            do
            {
                cout << "Hiz seviyesini secin (1 veya 2): ";
                cin >> speedLevel;
                if (speedLevel != 1 && speedLevel != 2)
                {
                    cout << "Gecersiz hiz seviyesi. Lutfen 1 veya 2 secin." << endl;
                }
            } while (speedLevel != 1 && speedLevel != 2);
            
            do
            {
                cout << "Silme islemi yapilsin mi? (1: Evet, 0: Hayir): ";
                cin >> mop;
                if (mop != 1 && mop != 0)
                {
                    cout << "Lutfen 1 veya 0 secin." << endl;
                }
            } while (mop != 1 && mop != 0);

            moveRobot(robot, targetX, targetY, speedLevel, mop);
        }
        break;
        case 2:
        {
            int roomNumber;
            int speedLevel;
            do
            {
                cout << "Temizlenecek oda numarasini girin: ";
                cin >> roomNumber;
                if (roomNumber < 1 || roomNumber > houses.size())
                {
                    cout << "Gecersiz oda numarasi. Lutfen 1 ile " << houses.size() << " arasinda bir sayi girin." << endl;
                }
            } while (roomNumber < 1 || roomNumber > houses.size());

            do
            {
                cout << "Hiz seviyesini secin (1 veya 2): ";
                cin >> speedLevel;
                if (speedLevel != 1 && speedLevel != 2)
                {
                    cout << "Gecersiz hiz seviyesi. Lutfen 1 veya 2 secin." << endl;
                }
            } while (speedLevel != 1 && speedLevel != 2);

            cleanRoom(robot, roomNumber, speedLevel, cleanedRooms);
        }
        break;
        case 3:
        {
            int speedLevel;
            do
            {
                cout << "Hiz seviyesini secin (1 veya 2): ";
                cin >> speedLevel;
                if (speedLevel != 1 && speedLevel != 2)
                {
                    cout << "Gecersiz hiz seviyesi. Lutfen 1 veya 2 secin." << endl;
                }
            } while (speedLevel != 1 && speedLevel != 2);

            cleanEntireHouse(robot, speedLevel, cleanedRooms);
        }
        break;
        case 4:
            chargeRobot(robot);
            break;
        case 5:
            showHouseMap();
            break;
        case 6:
            showRobotInfo(robot);
            break;
        case 7:
            cout << "Programdan cikiliyor...\n";
            break;
        default:
            cout << "Gecersiz secenek. Lutfen gecerli bir secenek girin.\n";
        }
    } while (choice != 7);

    writeRobotStatus(robot, cleanedRooms);

    return 0;
}