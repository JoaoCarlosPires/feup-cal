#include "Graph.h"
#include "helperfunctions.h"

using namespace std;

/*--------------------------------------------------------------------------------------------------------------------
                                                        NODE
----------------------------------------------------------------------------------------------------------------------*/

Node::Node() {
    this->rating = 0;
    this->visitTime = 0;
}

Node::Node(int id, double lat, double lon, double x, double y) {

    this->id = id;
    this->lat = lat;
    this->lon = lon;
    this->x = x;
    this->y = y;

    this->tags.estatua = 0;
    this->tags.museu = 0;
    this->tags.estadio = 0;
    this->tags.livraria = 0;
    this->tags.palacio = 0;
    this->tags.parque = 0;

    this->rating = 0;
    this->visitTime = 0;
}

void Node::setRating(int rating) {
    this->rating = rating;
}

int Node::getRating() {
    return this->rating;
}

void Node::setVisitTime(int time) {
    this->visitTime = time;
}

int Node::getVisitTime() {
    return this->visitTime;
}

int Node::getId() const {
    return this->id;
}

double Node::getLat() const {
    return this->lat;
}

double Node::getLon() const {
    return this->lon;
}

double Node::getX() const {
    return this->x;
}

double Node::getY() const {
    return this->y;
}

void Node::setId(int id) {
    this->id = id;
}

void Node::setCoords(double lan, double lon) {
    this->lat = lat;
    this->lon = lon;
}

void Node::setXY(double x, double y) {
    this->x = x;
    this->y = y;
}

void Node::printInfo() {
    cout << "Id[" << this->id << "] - (" << this->lat << "," << this->lon << ")" << endl;
}

void Node::addAdjEdge(Edge *edge) {
    this->adj.push_back(edge);
}

bool Node::operator== (Node other_node) {
    return this->id = other_node.id;
}


void Node::addTag(string type) {
    if (type == "Estatua") this->tags.estatua = 1;
    if (type == "Museu") this->tags.museu = 1;
    if (type == "Estadio") this->tags.estadio = 1;
    if (type == "Livraria") this->tags.livraria = 1;
    if (type == "Palacio") this->tags.palacio = 1;
    if (type == "Parque") this->tags.parque = 1;
}

struct Tourism Node::getNodeTags() const {
    return this->tags;
}

/**
 *  Calcula distancia linear um node e dadas coordenadas
 */
double Node::calcDist(double lat, double lon) {
    return sqrt(pow(this->lat-lat,2) + pow(this->lon-lon,2));
}

void Node::setVisited(bool visited) {
    this->visited = visited;
}

void Node::setDist(int dist) {
    this->dist = dist;
}

void Node::setPath(Node * path) {
    this->path = path;
}

vector<Edge *> Node::getAdjEdge() {
    return this->adj;
}

double Node::getPastWeight() const {
    return pastWeight;
}

void Node::setPastWeight(double pastWeight) {
    Node::pastWeight = pastWeight;
}

Node *Node::getPath() const {
    return path;
}

bool Node::isMostEfficient() const {
    return mostEfficient;
}

void Node::setMostEfficient(bool mostEfficient) {
    Node::mostEfficient = mostEfficient;
}

bool Node::isLastNode() const {
    return lastNode;
}

void Node::setLastNode(bool lastNode) {
    Node::lastNode = lastNode;
}

/*--------------------------------------------------------------------------------------------------------------------
                                                        EDGE
----------------------------------------------------------------------------------------------------------------------*/

Edge::Edge(Node* o, Node* d, double w, double f) {
    this->orig = o;
    this->dest = d;
    this->weight = w;
    this->flow = 0;
}

Node* Edge::getDest() const {
    return this->dest;
}
Node* Edge::getOrig() const {
    return this->orig;
}
double Edge::getFlow() const {
    return this->flow;
}
double Edge::getWeight() const {
    return this->weight;
}

void Edge::setWeight(double w) {
    this->weight = w;
}

/*--------------------------------------------------------------------------------------------------------------------
                                                        GRAPH
----------------------------------------------------------------------------------------------------------------------*/

Graph::Graph() {}

Node * Graph::findNode(double id) {
    vector<Node *>::iterator itr = this->nodes.begin();
    for (itr ; itr != this->nodes.end(); itr++)
        if ((*itr)->getId() == id) {
            return (*itr);
        }

    return NULL;
}

void Graph::addNode(int id, double lat, double lon, double x, double y) {
    Node *node = new Node(id, lat, lon, x, y);
    this->nodes.push_back(node);
}

void Graph::printNodeInfo() {
    for (Node* n : this->nodes) {
        n->printInfo();
    }
}

void Graph::addTag(int id, string type) {
    vector<Node *>::iterator itr = this->nodes.begin();
    for (itr ; itr != this->nodes.end(); itr++)
        if ((*itr)->getId() == id)  {
            (*itr)->addTag(type);
        }
}

vector<Node *> Graph::getNodes() {
    return nodes;
}


Edge Graph::findEdge(Node * orig, Node * dest) {
    for (Edge edge : this->edges) {
        if (edge.getDest() == dest && edge.getOrig() == dest) {
            return edge;
        }
    }
    return Edge();
}

Edge * Graph::addEdge(Node* orig, Node* dest) {
    Edge *edge = new Edge(orig, dest, 0, 0);
    this->edges.push_back(*edge);
    return edge;
}

void Graph::printEdgeInfo() {
    for (Edge edge : this->edges) {
        cout << "Origem: Id[" << edge.getOrig()->getId() << "] - (" << edge.getOrig()->getLat() << "," << edge.getOrig()->getLon() << ")" << endl;
        cout << "Destino: Id[" << edge.getDest()->getId() << "] - (" << edge.getDest()->getLat() << "," << edge.getDest()->getLon() << ")" << endl;
    }
}

vector<Edge> *Graph::getEdges() {
    return &edges;
}

Node Graph::getInitLoc(double lat, double lon) {

    Node* initNodeLoc = this->nodes[0];
    double dist = this->nodes[0]->calcDist(lat, lon);

    for (Node* n : this->nodes) {
        double n_dist = n->calcDist(lat, lon);
        if (n_dist < dist) {
            initNodeLoc = n;
            dist = n_dist;
        }
    }

    return *initNodeLoc;
}

/**
 * Algoritmo de Prim
 * Baseado no algoritmo dado nas aulas práticas mas adaptado ao noss programa
 * @param start Node inicial
 * @param timeAv tempo máximo
 * */
vector<Node* > Graph::calculatePrim(Node * start, int timeAv ) {

    double timeAvailable = timeAv * 60;

    if (nodes.size() == 0)
        return this->nodes;

    // Reset auxiliary info
    for (auto v : nodes) {
        v->setDist(INF);
        v->setPath(nullptr);
        v->setVisited(false); // known(v) in slides
        v->setMostEfficient(false);
        v->setLastNode(false);
    }

    // Start with start Node
    Node *s = start;
    s->setDist(0);
    s->setMostEfficient(true);

    // Initialize priority queue
    MutablePriorityQueue<Node> q;
    q.insert(s);

    // Process vertices in the priority queue
    while (!q.empty()) {
        auto v = q.extractMin();
        v->setVisited(true);
        for (auto e : v->getAdjEdge()) {
            Node* d = e->getDest();
            if (!(d->getVisited())) {
                double oldDist = d->getDist();
                d->setPastWeight(v->getPastWeight() +distanceBetweenNodes(v,d));
                if (v->getDist() >= d->getDist() && (d->getPastWeight() < timeAvailable)) {
                    d->setDist(v->getDist()+1);
                    v->setLastNode(false);
                    d->setLastNode(true);
                    d->setPath(v);
                    if (oldDist == INF)
                        q.insert(d);
                    else
                        q.decreaseKey(d);
                }
            }
        }
    }

    return this->nodes;
}

/**
 * Usado para duplicar nodes
 * @param dest Node de destino
 */
void Graph::addDuplicateEdges(Node * dest) {
    for (auto itr = edges.begin(); itr != edges.end(); itr++) {
        if ((*itr).getDest() == dest) {
            Edge *edge = new Edge((*itr).getOrig(), dest, (*itr).getWeight(), (*itr).getFlow());
            edges.push_back(*edge);
        }
    }
}

/**
 * Usado para duplicar nodes
 * @param dest Node de destino
 */
void Graph::addVisitedEdges(Node * dest) {
    for (auto itr = edges.begin(); itr != edges.end(); itr++) {
        if ((*itr).getDest() == dest) {
            (*itr).setWeight((*itr).getWeight()+dest->getVisitTime());
        }
    }
}

/**
 * Usado para duplicar nodes
 * @param anterior Node de Origem
 * @param dest Node de destino
 */
void Graph::addLeavingEdges(Node * anterior, Node * novo) {
    for (auto itr = edges.begin(); itr != edges.end(); itr++) {
        if ((*itr).getOrig() == anterior) {
            Edge *edge = new Edge(novo, (*itr).getDest(), (*itr).getWeight(), (*itr).getFlow());
            edges.push_back(*edge);
        }
    }
}

void Graph::setNodes(vector<Node *> newNodes) {
    this->nodes = newNodes;
}

/**
 * Adiciona peso aos nodes consoante as preferencias do utilizador
 * @param types Preferencias do utilizador
 */
void Graph::userPreferences(struct Tourism types) {
    bool estatua = types.estatua == 1;
    bool museu = types.museu == 1;
    bool estadio = types.estadio == 1;
    bool livraria = types.livraria == 1;
    bool palacio = types.palacio == 1;
    bool parque = types.parque == 1;

    bool duplicate;

    for (auto it = this->nodes.begin(); it != this->nodes.end(); it++) {
        duplicate = false;

        if ((*it)->getVisitTime() != 0) {
            if ((*it)->getNodeTags().estatua == 1) {
                if (!estatua) {
                    (*it)->setRating(0);
                    (*it)->setVisitTime(0);
                } else duplicate = true;

            }

            if ((*it)->getNodeTags().museu == 1) {
                if (!museu) {
                    (*it)->setRating(0);
                    (*it)->setVisitTime(0);
                } else duplicate = true;
            }

            if ((*it)->getNodeTags().estadio == 1) {
                if (!estadio) {
                    (*it)->setRating(0);
                    (*it)->setVisitTime(0);
                } else duplicate = true;
            }

            if ((*it)->getNodeTags().livraria == 1) {
                if (!livraria) {
                    (*it)->setRating(0);
                    (*it)->setVisitTime(0);
                } else duplicate = true;
            }

            if ((*it)->getNodeTags().palacio == 1) {
                if (!palacio) {
                    (*it)->setRating(0);
                    (*it)->setVisitTime(0);
                } else duplicate = true;
            }

            if ((*it)->getNodeTags().parque == 1) {
                if (!parque) {
                    (*it)->setRating(0);
                    (*it)->setVisitTime(0);
                } else duplicate = true;
            }
        }

        if (duplicate) {
            Node * aux = new Node((*it)->getId(), (*it)->getLat(), (*it)->getLon(), (*it)->getX(), (*it)->getY());
            addNode((*it)->getId(), (*it)->getLat(), (*it)->getLon(), (*it)->getX(), (*it)->getY());
            addDuplicateEdges(aux);
            addLeavingEdges(*it, aux);
            addVisitedEdges((*it));
        }
    }
}
