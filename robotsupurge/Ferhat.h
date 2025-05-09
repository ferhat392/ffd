#ifndef FERHAT_H_
#define FERHAT_H_

#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <ctime>

using namespace std;

struct Robot
{
    double x, y;
    int charge;
};

struct House
{
    double x1, y1, x2, y2;
    vector<pair<double, double>> obstacles;
};

extern vector<House> houses;

void chargeRobot(Robot &robot);
bool checkObstacleCollision(const House &house, double targetX, double targetY);
void moveRobot(Robot &robot, double targetX, double targetY, int speedLevel, int mop);
void cleanRoom(Robot &robot, int roomNumber, int speedLevel, vector<int> &cleanedRooms);
void cleanEntireHouse(Robot &robot, int speedLevel, vector<int> &cleanedRooms);
void readHouseMap();
void writeRobotStatus(const Robot &robot, const vector<int> &cleanedRooms);
void showHouseMap();
void showRobotInfo(const Robot &robot);
void writeHouseMapToFile(const vector<House> &houses);

#endif