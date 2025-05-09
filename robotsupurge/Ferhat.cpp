#include <iostream>
#include "Ferhat.h"

using namespace std;

vector<House> houses;

void chargeRobot(Robot &robot)
{
    cout << "Robot sarj ediliyor..." << endl;
    robot.charge = 100;
    cout << "Robotun sarj islemi tamamlandi. Sarj durumu: " << robot.charge << "%" << endl;
}

bool checkObstacleCollision(const House &house, double targetX, double targetY)
{
    for (const auto &obstacle : house.obstacles)
    {
        if (targetX >= obstacle.first && targetX <= obstacle.first &&
            targetY >= obstacle.second && targetY <= obstacle.second)
        {
            return true;
        }
    }
    return false;
}

void moveRobot(Robot &robot, double targetX, double targetY, int speedLevel, int mop)
{
    if (targetX < 0 || targetX > 100 || targetY < 0 || targetY > 100)
    {
        cout << "Hedef kordinatlar gecersiz. Koordinatlar 0 ile 100 arasinda olmalidir." << endl;
        return;
    }

    double initialX = robot.x;
    double initialY = robot.y;

    double deltaX = targetX - initialX;
    double deltaY = targetY - initialY;
    double distance = sqrt(deltaX * deltaX + deltaY * deltaY);

    double energyConsumptionRate;
    double stepDuration;

    if (speedLevel == 1)
    {
        energyConsumptionRate = mop ? 0.1 : 0.2;
        stepDuration = 2.0;
    }
    else if (speedLevel == 2)
    {
        energyConsumptionRate = mop ? 0.2 : 0.3;
        stepDuration = 1.0;
    }
    else
    {
        cout << "Gecersiz hiz seviyesi. Lutfen 1 veya 2 secin." << endl;
        return;
    }

    double energyConsumed = distance * energyConsumptionRate;

    if (energyConsumed <= robot.charge && !checkObstacleCollision(houses[0], targetX, targetY))
    {
        robot.x = targetX;
        robot.y = targetY;

        robot.charge -= static_cast<int>(energyConsumed);

        cout << "Robot, (" << initialX << ", " << initialY << ") konumundan (" << targetX << ", " << targetY << ") konumuna hareket etti." << endl;

        if (mop)
        {
            cout << "Silme islemi yapiliyor..." << endl;
            robot.charge -= static_cast<int>(distance * (speedLevel == 1 ? 0.2 : 0.3));
        }

        cout << "Pil durumu: " << robot.charge << "%" << endl;
        cout << "Adim suresi: " << stepDuration << " saniye" << endl;
    }
    else
    {
        cout << "Pil yetersiz veya engel var. Hedefe ulasilamadi." << endl;
    }
}

void cleanRoom(Robot &robot, int roomNumber, int speedLevel, vector<int> &cleanedRooms)
{
    if (roomNumber < 1 || roomNumber > houses.size())
    {
        cout << "Gecersiz oda numarasi. Lutfen 1 ile " << houses.size() << " arasinda bir sayi girin." << endl;
        return;
    }

    double roomCenterX = (houses[roomNumber - 1].x1 + houses[roomNumber - 1].x2) / 2.0;
    double roomCenterY = (houses[roomNumber - 1].y1 + houses[roomNumber - 1].y2) / 2.0;

    int mop;
    do
    {
        cout << "Silme islemi yapilsin mi? (1: Evet, 0: Hayir): ";
        cin >> mop;
        if (mop != 0 && mop != 1)
        {
            cout << "Lutfen 0 veya 1 secin." << endl;
        }
    } while (mop != 0 && mop != 1);

    moveRobot(robot, roomCenterX, roomCenterY, speedLevel, mop);
    cout << "Oda " << roomNumber << " temizleniyor..." << endl;

    cleanedRooms.push_back(roomNumber);

    if (robot.charge <= 10)
    {
        cout << "Robotun sarji cok dusuk. Sarj islemi baslatiliyor..." << endl;
        chargeRobot(robot);
    }
}

void cleanEntireHouse(Robot &robot, int speedLevel, vector<int> &cleanedRooms)
{
    int mop;
    do
    {
        cout << "Silme islemi yapilsin mi? (1: Evet, 0: Hayir): ";
        cin >> mop;
        if (mop != 0 && mop != 1)
        {
            cout << "Lutfen 0 veya 1 secin." << endl;
        }
    } while (mop != 0 && mop != 1);

    for (size_t i = 0; i < houses.size(); ++i)
    {
        double roomCenterX = (houses[i].x1 + houses[i].x2) / 2.0;
        double roomCenterY = (houses[i].y1 + houses[i].y2) / 2.0;

        moveRobot(robot, roomCenterX, roomCenterY, speedLevel, mop);
        cout << "Oda " << i + 1 << " temizleniyor..." << endl;

        cleanedRooms.push_back(i + 1);

        if (robot.charge <= 10)
        {
            cout << "Robotun sarji cok dusuk. Sarj islemi baslatiliyor..." << endl;
            chargeRobot(robot);
        }
    }

    cout << "Tum ev temizlendi." << endl;
}

void readHouseMap()
{
    ifstream file("harita.txt");

    if (!file)
    {
        cerr << "Harita dosyasi bulunamadi." << endl;
        return;
    }

    while (!file.eof())
    {
        House room;
        file >> room.x1 >> room.y1 >> room.x2 >> room.y2;

        double obstacleX, obstacleY;
        while (file >> obstacleX >> obstacleY)
        {
            room.obstacles.push_back({obstacleX, obstacleY});
        }

        houses.push_back(room);
    }

    file.close();
}

void writeRobotStatus(const Robot &robot, const vector<int> &cleanedRooms)
{
    ofstream file("temizlikRaporu.txt");

    if (!file)
    {
        cerr << "Robot durumu dosyasi olusturulamadi." << endl;
        return;
    }

    file << "Robot Koordinatlari: (" << robot.x << ", " << robot.y << ")" << endl;
    file << "Pil Durumu: " << robot.charge << "%" << endl;

    if (!cleanedRooms.empty())
    {
        file << "Temizlenen Odalar:\n";
        for (size_t i = 0; i < cleanedRooms.size(); ++i)
        {
            int roomNumber = cleanedRooms[i];
            file << "Oda " << roomNumber << ": (" << houses[roomNumber - 1].x1 << ", " << houses[roomNumber - 1].y1 << ") - ("
                 << houses[roomNumber - 1].x2 << ", " << houses[roomNumber - 1].y2 << ")\n";
        }
    }

    file.close();
}

void showHouseMap()
{
    cout << "Ev Haritasi:\n";
    for (size_t i = 0; i < houses.size(); ++i)
    {
        cout << "Oda " << i + 1 << ": (" << houses[i].x1 << ", " << houses[i].y1 << ") - (" << houses[i].x2 << ", " << houses[i].y2 << ")\n";
    }
}

void showRobotInfo(const Robot &robot)
{
    cout << "Robot Bilgileri:\n";
    cout << "Konum: (" << robot.x << ", " << robot.y << ")\n";
    cout << "Pil Durumu: " << robot.charge << "%\n";
}

void writeHouseMapToFile(const vector<House> &houses)
{
    ofstream file("harita.txt");

    if (!file)
    {
        cerr << "Harita dosyasi olusturulamadi." << endl;
        return;
    }

    for (size_t i = 0; i < houses.size(); ++i)
    {
        file << "Oda" << i + 1 << ": " << "(" << houses[i].x1 << "," << houses[i].y1 << ")" << "  " << "(" << houses[i].x2 << "," << houses[i].y2 << ")";
        
        for (const auto &obstacle : houses[i].obstacles)
        {
            file << "    " << "Engel" << i + 1 << ": " << "(" << obstacle.first << "," << obstacle.second << ")";
        }

        file << endl;
    }

    file.close();
}