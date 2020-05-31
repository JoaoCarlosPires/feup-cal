#ifndef TOURMATEAPP_GRAPH_H
#define TOURMATEAPP_GRAPH_H

#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <algorithm>
#include <unordered_set>
#include "MutablePriorityQueue.h"
#include <string>
#include <list>
#include "States.h"
#include <math.h>
#include "POITypes.h"

using namespace std;

#define INF -200000

class Node;
class Edge;
class Graph;


// Struct que representa todos os tipos de POI
struct Tourism {
    int estatua;
    int museu;
    int estadio;
    int livraria;
    int palacio;
    int parque;
};

class Node {

private:

    int id;                     // Node ID
    double lat, lon;            // Geographical Coordinates
    double x, y;                // XY Coordinates
    std::vector<Edge *> adj;    // Connected Edges
    struct Tourism tags;        // Enum for POI type
    bool visited;               // If can be visited or not
    bool mostEfficient = false; // If it's visited or not
    bool lastNode = false;      // End point of track
    double dist = 0;            // Distance to start node
    double pastWeight = 0;      //
    Node *path = nullptr;       // Next node of path
    int rating;             // Rating of POI (if applied)
    int visitTime;          // Visit Time of POI (if applied)
    int pastRating = 0;         //

public:

    int queueIndex = 0; 		// Required by MutablePriorityQueue

    Node();
    Node(int id, double lat, double lon, double x, double y);

    bool isLastNode() const;
    void setLastNode(bool lastNode);

    int getId() const ;
    double getLat() const ;
    double getLon() const ;
    double getX() const ;
    double getY() const ;

    double getPastWeight() const;
    void setPastWeight(double pastWeight);

    Node *getPath() const;
    void setPath(Node * path);

    bool isMostEfficient() const;
    void setMostEfficient(bool mostEfficient);

    void setId(int id);
    void setCoords(double lan, double lon);
    void setXY(double x, double y);

    void printInfo();

    void addAdjEdge(Edge * edge);
    vector<Edge *> getAdjEdge();

    bool operator== (Node other_node);

    void addTag(string type);
    struct Tourism getNodeTags() const;

    double calcDist(double lat, double lon);
    void setDist(int dist);
    double getDist() {return this->dist;}

    void setVisited(bool visited);
    bool getVisited() {return this->visited;}

    bool operator<(Node & node) const {return this->dist < node.getDist();} // // required by MutablePriorityQueue

    void setRating(int rating);
    int getRating();

    void setVisitTime(int time);
    int getVisitTime();

};

class Edge {

private:

    Node* orig;     // Origin Node of Edge
    Node* dest;     // Destination Node of Edge
    double weight;  // Weight of Edge
    double flow;    //
    Edge(Node* o, Node* d, double w, double f);
    Edge() {};

public:

    double getFlow() const;

    double getWeight() const;
    void setWeight(double weight);

    Node* getDest() const;

    Node* getOrig() const;

    friend class Graph;
    friend class Node;
};

class Graph {

private:

    std::vector<Node *> nodes;  // Nodes do Grafo
    std::vector<Edge> edges;    // Edges do Grafo

public:

    Graph();

    Node * findNode(double id);
    void printNodeInfo();
    void addNode(int id, double lat, double lon, double x, double y);
    vector<Node *> getNodes();

    Edge findEdge(Node* orig, Node* dest);
    void printEdgeInfo();
    Edge * addEdge(Node* orig, Node* dest);
    vector<Edge>* getEdges();

    void addTag(int id, string type);

    Node getInitLoc(double lat, double lon);

    vector<Node *> calculatePrim(Node* start, int timeAv);

    void setNodes(vector<Node *> newNodes);

    void addDuplicateEdges(Node * dest);

    void addVisitedEdges(Node * dest);

    void addLeavingEdges(Node * anterior, Node * novo);

    void userPreferences(struct Tourism userPref);
};

#endif //TOURMATEAPP_GRAPH_H