#include <cstdio>
#include "graphviewer.h"
#include <fstream>
#include <iostream>
#include <sstream>

void exercicio1();
void exercicio2();
void exercicio3();


void exercicio1()
{
    GraphViewer *gv = new GraphViewer(600, 600, true);

    gv->setBackground("background.jpg");

    gv->createWindow(600, 600);

    gv->defineVertexColor("blue");

    gv->defineEdgeColor("black");

    int idNo = 0;
    gv->addNode(idNo);
    gv->rearrange();

    idNo = 1;
    gv->addNode(idNo);
    gv->rearrange();

    // para arestas bidireccionais
    gv->addEdge(0,0,1,EdgeType::UNDIRECTED);
    // para arestas direccionais
    //gv->addEdge(idAresta,idNoOrigem,idNoDestino, EdgeType::DIRECTED);

    gv->removeNode(1);

    idNo = 2;
    gv->addNode(idNo);
    gv->rearrange();

    gv->addEdge(1,0,2,EdgeType::UNDIRECTED);

    gv->setVertexLabel(2, "Isto e um no");

    gv->setEdgeLabel(1, "Isto e uma aresta");

    gv->setVertexColor(2, "green");

    gv->setEdgeColor(1, "yellow");




}

void exercicio2()
{
    GraphViewer *gv = new GraphViewer(600, 600, false);

    gv->createWindow(600, 600);

    int idNo = 0;
    gv->addNode(0, 300, 50);
    gv->rearrange();

    gv->addNode(1, 318, 58);
    gv->rearrange();

    gv->addNode(2, 325, 75);
    gv->rearrange();

    gv->addNode(3, 318, 93);
    gv->rearrange();

    gv->addNode(4, 282, 93);
    gv->rearrange();

    gv->addNode(5, 300, 50);
    gv->rearrange();

    gv->addNode(6, 275, 75);
    gv->rearrange();

    gv->addNode(7, 282, 58);
    gv->rearrange();

    gv->addNode(8, 150, 200);
    gv->rearrange();

    gv->addNode(9, 300, 200);
    gv->rearrange();

    gv->addNode(10, 450, 200);
    gv->rearrange();

    gv->addNode(11, 300, 400);
    gv->rearrange();

    gv->addNode(12, 200, 550);
    gv->rearrange();

    gv->addNode(13, 400, 550);
    gv->rearrange();

    gv->addEdge(0,0,1,EdgeType::UNDIRECTED);
    gv->addEdge(1,1,2,EdgeType::UNDIRECTED);
    gv->addEdge(2,2,3,EdgeType::UNDIRECTED);
    gv->addEdge(3,3,4,EdgeType::UNDIRECTED);
    gv->addEdge(4,4,5,EdgeType::UNDIRECTED);
    gv->addEdge(5,5,6,EdgeType::UNDIRECTED);
    gv->addEdge(6,6,7,EdgeType::UNDIRECTED);
    gv->addEdge(7,7,0,EdgeType::UNDIRECTED);
    gv->addEdge(8,4,9,EdgeType::UNDIRECTED);
    gv->addEdge(9,9,8,EdgeType::UNDIRECTED);
    gv->addEdge(10,9,10,EdgeType::UNDIRECTED);
    gv->addEdge(11,9,11,EdgeType::UNDIRECTED);
    gv->addEdge(12,11,12,EdgeType::UNDIRECTED);
    gv->addEdge(13,11,13,EdgeType::UNDIRECTED);

    sleep(2);

    gv->removeNode(12);
    gv->removeNode(13);

    sleep(2);

    gv->addNode(14, 250, 550);
    gv->rearrange();

    gv->addNode(15, 350, 550);
    gv->rearrange();

    gv->addEdge(14,11,14,EdgeType::UNDIRECTED);
    gv->addEdge(15,11,15,EdgeType::UNDIRECTED);

}

void exercicio3()
{
// TODO: Implement here exercise 3!
// To read map files, use relative paths:
// Vertices data: "../resources/mapa1/nos.txt"
// Edges data: "../resources/mapa1/arestas.txt"
// ...
}

int main() {
    /*
     * Uncomment the line below to run Exercise 1
     */
    //exercicio1();

    /*
      * Uncomment the line below to run Exercise 2
      */
    exercicio2();

    /*
      * Uncomment the line below to run Exercise 3
      */
	//
	//exercicio3();

	getchar();
	return 0;
}
