#ifndef UNTITLED_MENU_H
#define UNTITLED_MENU_H

#include "Graph.h"

using namespace std;

class Menu {

private:

    double carSpeedMultiplier = 6.0;
    double walkingSpeed = (5/3.6);

    Graph map = Graph();

    double latMin =  40000;
    double latMax = -40000;
    double lonMin =  40000;
    double lonMax = -40000;

    double xMin =  5000000000000000;
    double xMax = 0;
    double yMin =  5000000000000000;
    double yMax = 0;

    Node initNode;      // Start node of track
    double lastNodeId;  // Id of last node of track

    int currentState = START;
    int timeAvailable = 0;
    int initialLocationID = 0;
    int location = 0;

    bool poi = false;
    bool location_selected = false;
    bool picks[8] = {false};
    bool usingCar = false;

    string user = "";
    std::string userInput;
    struct Tourism types;

public:

    Menu();

    void run();

    void drawMainMenu();
    void drawTitle();

    void nameReceiver();

    double long getWalkingSpeed();

    void processInput();

    void parseNodeData(vector<string> data, int option);
    void retrieveFileData(string file_name_prefix, int option);
    void getMapInfo();

    void pickInitLocation();
    void pickTime();
    void pickTypesPOI();

    void calculate();

    void printGeoLimits();

    void mainMenuHandle();

    int calculateNodeWeight();

    void showGraph(vector<Node *> nodes, vector<Edge> * edges);

    double BFSFindBestPath(vector<Node *> vector, Node* start);

    void generateTag(Node * node);

    void toggleVehicle();

};

#endif //UNTITLED_MENU_H