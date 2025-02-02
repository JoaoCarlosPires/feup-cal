/*
 * Graph.h
 */
#ifndef GRAPH_H_
#define GRAPH_H_

#include <vector>
#include <queue>
#include <list>
#include <limits>
#include <cmath>
#include "MutablePriorityQueue.h"

using namespace std;

template <class T> class Edge;
template <class T> class Graph;
template <class T> class Vertex;

#define INF std::numeric_limits<double>::max()

/************************* Vertex  **************************/

template <class T>
class Vertex {
	T info;						// content of the vertex
	vector<Edge<T> > adj;		// outgoing edges
	
	double dist = 0;
	Vertex<T> *path = NULL;
	int queueIndex = 0; 		// required by MutablePriorityQueue

	bool visited = false;		// auxiliary field
	bool processing = false;	// auxiliary field

	void addEdge(Vertex<T> *dest, double w);

public:
	Vertex(T in);
	T getInfo() const;
	double getDist() const;
    void setDist(double d);
	Vertex *getPath() const;
    void setPath(Vertex<T>* t);

	bool operator<(Vertex<T> & vertex) const; // // required by MutablePriorityQueue
	friend class Graph<T>;
	friend class MutablePriorityQueue<Vertex<T>>;
};


template <class T>
Vertex<T>::Vertex(T in): info(in) {}

/*
 * Auxiliary function to add an outgoing edge to a vertex (this),
 * with a given destination vertex (d) and edge weight (w).
 */
template <class T>
void Vertex<T>::addEdge(Vertex<T> *d, double w) {
	adj.push_back(Edge<T>(d, w));
}

template <class T>
bool Vertex<T>::operator<(Vertex<T> & vertex) const {
	return this->dist < vertex.dist;
}

template <class T>
T Vertex<T>::getInfo() const {
	return this->info;
}

template <class T>
double Vertex<T>::getDist() const {
	return this->dist;
}

template <class T>
void Vertex<T>::setDist(double d) {
    this->dist = d;
}

template <class T>
Vertex<T> *Vertex<T>::getPath() const {
	return this->path;
}

template <class T>
void Vertex<T>::setPath(Vertex<T>* t) {
    if (t->getInfo() == 0) {
        this->path = NULL;
    } else
        this->path = t;
}

/********************** Edge  ****************************/

template <class T>
class Edge {
	Vertex<T> * dest;      // destination vertex
	double weight;         // edge weight
public:
	Edge(Vertex<T> *d, double w);
	friend class Graph<T>;
	friend class Vertex<T>;
};

template <class T>
Edge<T>::Edge(Vertex<T> *d, double w): dest(d), weight(w) {}


/*************************** Graph  **************************/

template <class T>
class Graph {
	vector<Vertex<T> *> vertexSet;    // vertex set

public:
	Vertex<T> *findVertex(const T &in) const;
	bool addVertex(const T &in);
	bool addEdge(const T &sourc, const T &dest, double w);
	int getNumVertex() const;
	vector<Vertex<T> *> getVertexSet() const;

	// Fp05 - single source
	void unweightedShortestPath(const T &s);    //TODO...
	void dijkstraShortestPath(const T &s);      //TODO...
	void bellmanFordShortestPath(const T &s);   //TODO...
	vector<T> getPathTo(const T &dest) const;   //TODO...

	// Fp05 - all pairs
	void floydWarshallShortestPath();   //TODO...
	vector<T> getfloydWarshallPath(const T &origin, const T &dest) const;   //TODO...

};

template <class T>
int Graph<T>::getNumVertex() const {
	return vertexSet.size();
}

template <class T>
vector<Vertex<T> *> Graph<T>::getVertexSet() const {
	return vertexSet;
}

/*
 * Auxiliary function to find a vertex with a given content.
 */
template <class T>
Vertex<T> * Graph<T>::findVertex(const T &in) const {
	for (auto v : vertexSet)
		if (v->info == in)
			return v;
	return NULL;
}

/*
 *  Adds a vertex with a given content or info (in) to a graph (this).
 *  Returns true if successful, and false if a vertex with that content already exists.
 */
template <class T>
bool Graph<T>::addVertex(const T &in) {
	if ( findVertex(in) != NULL)
		return false;
	vertexSet.push_back(new Vertex<T>(in));
	return true;
}

/*
 * Adds an edge to a graph (this), given the contents of the source and
 * destination vertices and the edge weight (w).
 * Returns true if successful, and false if the source or destination vertex does not exist.
 */
template <class T>
bool Graph<T>::addEdge(const T &sourc, const T &dest, double w) {
	auto v1 = findVertex(sourc);
	auto v2 = findVertex(dest);
	if (v1 == NULL || v2 == NULL)
		return false;
	v1->addEdge(v2,w);
	return true;
}


/**************** Single Source Shortest Path algorithms ************/

template<class T>
void Graph<T>::unweightedShortestPath(const T &orig) {
    /*
    *   Esta função implementa um algoritmo para encontrar os caminhos mais curtos a partir do elemento v do
    *   grafo (vértice cujo conteúdo é origin) a todos os outros vértices do grafo, ignorando os pesos das arestas.
	*/

    Vertex<T> *src = findVertex(orig);
    queue<Vertex<T>*> q;
    for(unsigned int i = 0; i < vertexSet.size(); i++) {
        vertexSet[i]->setPath(nullptr);
        vertexSet[i]->setDist(INF);
    }

    src->setDist(0);
    q.push(src);
    Vertex<T>* newV;

    while (!q.empty()) {
        newV = q.front();
        q.pop();
        for (Edge<T> w : newV->adj) {
            if (w.dest->getDist() == INF) {
                q.push(w.dest);
                w.dest->setDist(newV->getDist() + 1);
                w.dest->setPath(newV);
            }
        }
    }

    /*Vertex<T> *src = findVertex(orig), *v;

    for (auto ver : vertexSet) {
        ver->dist = INT64_MAX;
        ver->path = NULL;
    }

    src->dist = 0;
    queue<Vertex<T>*> Q;
    Q.push(src);

    while (!Q.empty()) {
        v = Q.front();
        Q.pop();
        typename vector<Edge<T>>::const_iterator it2 = v->adj.begin();
        while (it2 != v->adj.end()) {
            if ((*it2).dest->dist == INT64_MAX) {
                Q.push((*it2).dest);
                (*it2).dest->dist = v->dist + 1;
                (*it2).dest->path = v;
            }
            it2++;
        }
    }*/



}


template<class T>
void Graph<T>::dijkstraShortestPath(const T &origin) {
	// TODO
}


template<class T>
void Graph<T>::bellmanFordShortestPath(const T &orig) {
	// TODO
}


template<class T>
vector<T> Graph<T>::getPathTo(const T &dest) const{
	vector<T> res;
	double d = 1;
    for (unsigned int i = 0; i < vertexSet.size(); i++) {
        if (vertexSet[i]->getDist() == 0) {
            for (unsigned c = i; c < vertexSet.size(); c++) {
                if (d == vertexSet[c]->getDist()) {
                    res.push_back(vertexSet[c]->info);
                    d++;
                }
            }
            break;
        }
    }
	return res;

    /*vector<T> res;

    Vertex<T> *v = findVertex(dest);
    res.insert(res.begin(), v->info);

    while (v->path != NULL) {
        v = v->path;
        res.insert(res.begin(), v->info);
    }

    return res;*/
}



/**************** All Pairs Shortest Path  ***************/

template<class T>
void Graph<T>::floydWarshallShortestPath() {
	// TODO
}

template<class T>
vector<T> Graph<T>::getfloydWarshallPath(const T &orig, const T &dest) const{
	vector<T> res;
	// TODO
	return res;
}


#endif /* GRAPH_H_ */
